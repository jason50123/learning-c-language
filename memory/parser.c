#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <scsi/scsi.h>
#include <scsi/sg.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>


#define NAME_COUNT 25

void FillRead16Command(struct sg_io_hdr *io_hdr, unsigned int lba, unsigned short sectorCount) {
    u_int8_t sense_buffer[32];

    memset(io_hdr, 0, sizeof(struct sg_io_hdr));

    io_hdr->interface_id = 'S';
    io_hdr->dxfer_direction = SG_DXFER_FROM_DEV;
    io_hdr->cmd_len = 16;
    io_hdr->mx_sb_len = 32;
    io_hdr->iovec_count = 0;
    io_hdr->dxfer_len = sectorCount * 512;
    io_hdr->dxferp = malloc(io_hdr->dxfer_len);
    io_hdr->cmdp = malloc(io_hdr->cmd_len);
    io_hdr->sbp = sense_buffer;


    io_hdr->cmdp[0] = 0x88; 
    io_hdr->cmdp[1] = 0x00;
    io_hdr->cmdp[2] = 0x00;
    io_hdr->cmdp[3] = 0x00;
    io_hdr->cmdp[4] = 0x00;
    io_hdr->cmdp[5] = 0x00;
    io_hdr->cmdp[6] = 0x00;
    io_hdr->cmdp[7] = 0x00;
    io_hdr->cmdp[8] = 0x00;
    io_hdr->cmdp[9] = lba;
    io_hdr->cmdp[10] = 0x00;
    io_hdr->cmdp[11] = 0x00;
    io_hdr->cmdp[12] = 0x00;
    io_hdr->cmdp[13] = sectorCount;
    io_hdr->cmdp[14] = 0x00;
    io_hdr->cmdp[15] = 0x00;

    // Set transfer length

}

void FillWrite16Command(struct sg_io_hdr *io_hdr, unsigned int lba, unsigned short sectorCount, const char *userInput) {

    memset(io_hdr, 0, sizeof(struct sg_io_hdr));

    io_hdr->interface_id = 'S';
    io_hdr->dxfer_direction = SG_DXFER_TO_DEV;
    io_hdr->cmd_len = 16;
    io_hdr->mx_sb_len = 32;
    io_hdr->iovec_count = 0;
    io_hdr->dxfer_len = sectorCount * 512;
    io_hdr->dxferp = malloc(io_hdr->dxfer_len);
    io_hdr->cmdp = malloc(io_hdr->cmd_len);


    io_hdr->cmdp[0] = 0x8A; 
    io_hdr->cmdp[1] = 0x00;
    io_hdr->cmdp[2] = 0x00;
    io_hdr->cmdp[3] = 0x00;
    io_hdr->cmdp[4] = 0x00;
    io_hdr->cmdp[5] = 0x00;
    io_hdr->cmdp[6] = 0x00;
    io_hdr->cmdp[7] = 0x00;
    io_hdr->cmdp[8] = 0x00;
    io_hdr->cmdp[9] = lba;
    io_hdr->cmdp[10] = 0x00;
    io_hdr->cmdp[11] = 0x00;
    io_hdr->cmdp[12] = 0x00;
    io_hdr->cmdp[13] = sectorCount;
    io_hdr->cmdp[14] = 0x00;
    io_hdr->cmdp[15] = 0x00;
    printf("%d\n", userInput[1]);
    memcpy(io_hdr->dxferp, userInput, io_hdr->dxfer_len);
    //printf("\n this is userinput： %s\n",userInput);
}


int hexCharToInt(char c) {
    if (c >= '0' && c <= '9') {
        return c - '0';
    } else if (c >= 'a' && c <= 'f') {
        return 10 + c - 'a';
    } else if (c >= 'A' && c <= 'F') {
        return 10 + c - 'A';
    } else {
        return -1; // 非法字符
    }
}


void hexStringToBinary(const char *hexString, unsigned char *binaryData) {
    size_t len = strlen(hexString);
    for (size_t i = 0; i < len; i += 2) {
        int high = hexCharToInt(hexString[i]);
        int low = hexCharToInt(hexString[i + 1]);

        if (high == -1 || low == -1) {
            fprintf(stderr, "Error: Invalid hex character in input at position %zu: '%c%c'\n", i, hexString[i], hexString[i + 1]);
            exit(EXIT_FAILURE);
        }

        binaryData[i / 2] = (high << 4) | low;
    }
}


int main(int argc, char *argv[]) {
    struct sg_io_hdr io_hdr;
    char *operation;
    unsigned int lba, sector;
    //const char *userInput;

    const char *hex_data_to_write = argv[8];

    // if (argc != 9) {
    //     printf("Usage: %s <path> <read/write> --lba <lba> --sector_cnt <sectorCnt> --data <data>\n", argv[0]);
    //     return 1;
    // }

    operation = argv[2];
    //userInput = argv[8];




    // printf("%s \n",operation);
    // printf("%s \n",argv[1]);
    // printf("%s \n",argv[3]);
    // printf("%s \n",argv[4]);
    // printf("%s \n",argv[5]);
    // printf("%s \n",argv[6]);

    // if (userInput == NULL) {
    //     printf("Error: Missing data parameter.\n");
    //     return 1;
    // }

    if (strcmp(operation, "read") != 0 && strcmp(operation, "write") != 0) {
        printf("Invalid operation. Use 'read' or 'write'\n");
        return 1;
    }
    
    if (sscanf(argv[4], "%u", &lba) != 1) {
        printf("%s",argv[4]);
        printf("Error parsing lba parameter.\n");
        return 1;
    }

    if (sscanf(argv[6], "%u", &sector) != 1) {
        printf("Error parsing sector parameter.\n");
        return 1;
    }
    
    int fileDescriptor = open(argv[1], O_RDWR);
    if (fileDescriptor < 0) {
        perror("Error opening file");
        return 1;
    }
    
    if (strcmp(operation, "read") == 0) {
        printf("read operating start\n");
        printf("read parameter lba: %d\n",lba);
        printf("read parameter sector: %d\n",sector);
        FillRead16Command(&io_hdr, lba, sector);
        io_hdr.timeout = 10000; 

        if (ioctl(fileDescriptor, SG_IO, &io_hdr) < 0) {
            perror("Error sending SCSI command");
            close(fileDescriptor);
        return 1;
        }

        if ((io_hdr.info & SG_INFO_OK_MASK) != SG_INFO_OK) {
            fprintf(stderr, "SCSI command failed\n");

        // Print sense buffer information (if available)
        if (io_hdr.sb_len_wr > 0) {
            fprintf(stderr, "Sense buffer: ");
            for (unsigned int i = 0; i < io_hdr.sb_len_wr; i++) {
                fprintf(stderr, "%02X ", ((unsigned char *)io_hdr.sbp)[i]);
            }
            fprintf(stderr, "\n");
        }

        close(fileDescriptor);
        return 1;
        }

    //char *readData = (char *)io_hdr.dxferp;

    unsigned char *readData = (unsigned char *)io_hdr.dxferp;

    // Print the read data
    printf("Read Data:\n");
    for (int i = 0; i < io_hdr.dxfer_len; i++) {
        printf("%02X ", readData[i]);
        if ((i + 1) % 16 == 0) {
            printf("\n");
        }
    }

        goto end;

    } else if (strcmp(operation, "write") == 0) {

    size_t binary_data_size = strlen(hex_data_to_write) / 2;
    unsigned char *binary_data = malloc(binary_data_size);

    hexStringToBinary(hex_data_to_write, binary_data);
        FillWrite16Command(&io_hdr, lba, sector, binary_data);
        // Implement logic to send the SCSI write command and handle the result
        io_hdr.timeout = 10000;
        printf("user input %s\n", binary_data);

        if (ioctl(fileDescriptor, SG_IO, &io_hdr) < 0) {
            perror("Error sending SCSI command");
            close(fileDescriptor);
            return 1;
        }
        
        if ((io_hdr.info & SG_INFO_OK_MASK) != SG_INFO_OK) {
            fprintf(stderr, "SCSI command failed\n");

            // Print sense buffer information (if available)
            if (io_hdr.sb_len_wr > 0) {
                fprintf(stderr, "Sense buffer: ");
                for (unsigned int i = 0; i < io_hdr.sb_len_wr; i++) {
                    fprintf(stderr, "%02X ", ((unsigned char *)io_hdr.sbp)[i]);
                }
                fprintf(stderr, "\n");
            }
                    
            close(fileDescriptor);
            return 1;
            
        }
        if (io_hdr.status) {
            fprintf(stderr, "SCSI command failed with status 0x%x\n", io_hdr.status);
        }else {
        printf("SCSI WRITE(16) command sent successfully\n");
    }

    
    }
    end:
    free(io_hdr.dxferp);
    free(io_hdr.cmdp);
    close(fileDescriptor);

    return 0;
}
