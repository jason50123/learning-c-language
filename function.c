int __ref reclaim_mram_pages(unsigned long start_pfn, unsigned long nr_pages,
                             struct memory_group *group, struct dev_pagemap *pgmap)
{
    const unsigned long end_pfn = start_pfn + nr_pages;
    unsigned long pfn, pfn_it, system_ram_pages = 0;
    unsigned long flags;
    struct zone *zone;
    struct memory_notify arg;
    int ret, node, i;
    char *reason;
    struct mhp_params params = {
        .altmap = pgmap_altmap(pgmap),
        .pgprot = PAGE_KERNEL,
    };
    struct range *range;

    if (WARN_ON_ONCE(!nr_pages ||
                     !IS_ALIGNED(start_pfn, pageblock_nr_pages) ||
                     !IS_ALIGNED(start_pfn + nr_pages, PAGES_PER_SECTION)))
        return -EINVAL;

    mem_hotplug_begin();

    zone = test_pages_in_a_zone(start_pfn, end_pfn);
    if (!zone)
    {
        ret = -EINVAL;
        reason = "multizone range";
        goto failed_removal;
    }
    node = zone_to_nid(zone);

    zone_pcp_disable(zone);
    lru_cache_disable();

    ret = start_isolate_page_range(start_pfn, end_pfn,
                                   MIGRATE_MOVABLE,
                                   MEMORY_OFFLINE | REPORT_FAILURE);
    if (ret)
    {
        reason = "failure to isolate range";
        goto failed_removal_pcplists_disabled;
    }

    arg.start_pfn = start_pfn;
    arg.nr_pages = nr_pages;
    node_states_check_changes_offline(nr_pages, zone, &arg);

    ret = memory_notify(MEM_GOING_OFFLINE, &arg);
    ret = notifier_to_errno(ret);
    if (ret)
    {
        reason = "notifier failure";
        goto failed_removal_isolated;
    }
    for (pfn_it = start_pfn; pfn_it < end_pfn; pfn_it += 64)
    {
        do
        {
            /* We scan and perform migrations only for MRAM pages */
            pfn = pfn_it;
            do
            {
                if (signal_pending(current))
                {
                    ret = -EINTR;
                    reason = "signal backoff";
                    goto failed_removal_isolated;
                }

                cond_resched();

                ret = scan_movable_pages(pfn, pfn_it + 32, &pfn);
                if (!ret)
                {
                    /*
                     * TODO: fatal migration failures should bail
                     * out
                     */
                    do_migrate_range(pfn, pfn_it + 32);
                }
            } while (!ret);

            if (ret != -ENOENT)
            {
                reason = "unmovable page";
                goto failed_removal_isolated;
            }
            /*
             * Dissolve free hugepages in the memory block before doing
             * offlining actually in order to make hugetlbfs's object
             * counting consistent.
             */
            ret = dissolve_free_huge_pages(pfn_it, pfn_it + 32);
            if (ret)
            {
                reason = "failure to dissolve huge pages";
                goto failed_removal_isolated;
            }

            ret = test_pages_isolated(pfn_it, pfn_it + 32, MEMORY_OFFLINE);
        } while (ret);
    }

    /* Mark all sections offline and remove free pages from the buddy. */
    for (pfn_it = start_pfn; pfn_it < end_pfn; pfn_it += 64)
        __offline_isolated_pages(pfn_it, pfn_it + 32);
    pr_debug("Offlined Pages %ld\n", nr_pages);

    /*
     * The memory sections are marked offline, and the pageblock flags
     * effectively stale; nobody should be touching them. Fixup the number
     * of isolated pageblocks, memory onlining will properly revert this.
     */
    spin_lock_irqsave(&zone->lock, flags);
    zone->nr_isolate_pageblock -= nr_pages / pageblock_nr_pages;
    spin_unlock_irqrestore(&zone->lock, flags);

    lru_cache_enable();
    zone_pcp_enable(zone);

    /* removal success */
    /* Only half of the pages in the range is managed by the buddy */
    adjust_managed_page_count(pfn_to_page(start_pfn), -(nr_pages >> 1));
    adjust_present_page_count(pfn_to_page(start_pfn), group, -nr_pages);

    /* reinitialise watermarks and update pcp limits */
    init_per_zone_wmark_min();

    if (!populated_zone(zone))
    {
        zone_pcp_reset(zone);
        build_all_zonelists(NULL);
    }

    node_states_clear_node(node, &arg);
    if (arg.status_change_nid >= 0)
    {
        kswapd_stop(node);
        kcompactd_stop(node);
    }

    writeback_set_ratelimit();

    memory_notify(MEM_OFFLINE, &arg);
    remove_pfn_range_from_zone(zone, start_pfn, nr_pages);

    for (i = 0; i < pgmap->nr_range; i++)
    {
        range = &pgmap->ranges[i];
        move_pfn_range_to_zone(zone, start_pfn,
                               nr_pages, params.altmap,
                               MIGRATE_MOVABLE);
    }

    mem_hotplug_done();

    for (i = 0; i < pgmap->nr_range; i++)
    {
        range = &pgmap->ranges[i];
        memmap_init_zone_device(&NODE_DATA(node)->node_zones[ZONE_DEVICE],
                                start_pfn,
                                nr_pages, pgmap);
    }
    return 0;

failed_removal_isolated:
    undo_isolate_page_range(start_pfn, end_pfn, MIGRATE_MOVABLE);
    memory_notify(MEM_CANCEL_OFFLINE, &arg);
failed_removal_pcplists_disabled:
    lru_cache_enable();
    zone_pcp_enable(zone);
failed_removal:
    pr_info("MRAM offlining [mem %#010llx-%#010llx] failed due to %s\n",
            (unsigned long long)start_pfn << PAGE_SHIFT,
            ((unsigned long long)end_pfn << PAGE_SHIFT) - 1,
            reason);
    /* pushback to free area */
    mem_hotplug_done();
    return ret;
}
EXPORT_SYMBOL(reclaim_mram_pages);