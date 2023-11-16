#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <tchar.h>
#include <scsi.h>

#define NAME_COUNT 25



void FillRead16Command(SCSI_PASS_THROUGH_WITH_BUFFERS* sptwb, DWORD sectorNumber, WORD sectorCount) {
    // 清零整??构
    ZeroMemory(sptwb, sizeof(SCSI_PASS_THROUGH_WITH_BUFFERS));

    // ?置 SCSI_PASS_THROUGH_DIRECT ?构的字段
    sptwb->spt.Length = sizeof(SCSI_PASS_THROUGH_DIRECT);
    sptwb->spt.PathId = 0;
    sptwb->spt.TargetId = 1; // 适配器目?ID
    sptwb->spt.Lun = 0;
    sptwb->spt.CdbLength = CDB10GENERIC_LENGTH; // 使用 10 字?的 CDB
    sptwb->spt.SenseInfoLength = 24; // ?留足?大的空?以容? SenseInfo
    sptwb->spt.DataIn = SCSI_IOCTL_DATA_IN;
    sptwb->spt.DataTransferLength = sectorCount * 512; // ?据???度，以字???位
    sptwb->spt.TimeOutValue = 2; // 超?值（以秒??位）

    // ?置 CDB（Command Descriptor Block）
    sptwb->spt.Cdb[0] = 0x88; // Read(16) 命令?
    sptwb->spt.Cdb[1] = 0x10; // 控制字?，例如 FUA（?制更新）
    
    // ?置 LBA（???地址）
    sptwb->spt.Cdb[2] = (BYTE)((sectorNumber >> 24) & 0xFF);
    sptwb->spt.Cdb[3] = (BYTE)((sectorNumber >> 16) & 0xFF);
    sptwb->spt.Cdb[4] = (BYTE)((sectorNumber >> 8) & 0xFF);
    sptwb->spt.Cdb[5] = (BYTE)(sectorNumber & 0xFF);

    // ?置???度
    sptwb->spt.Cdb[7] = (BYTE)((sectorCount >> 8) & 0xFF);
    sptwb->spt.Cdb[8] = (BYTE)(sectorCount & 0xFF);
}



void FillWrite16Command(SCSI_PASS_THROUGH_WITH_BUFFERS* sptwb, DWORD sectorNumber, WORD sectorCount) {
    // 清零整??构
    ZeroMemory(sptwb, sizeof(SCSI_PASS_THROUGH_WITH_BUFFERS));

    // ?置 SCSI_PASS_THROUGH_DIRECT ?构的字段
    sptwb->spt.Length = sizeof(SCSI_PASS_THROUGH_DIRECT);
    sptwb->spt.PathId = 0;
    sptwb->spt.TargetId = 1; // 适配器目?ID
    sptwb->spt.Lun = 0;
    sptwb->spt.CdbLength = CDB10GENERIC_LENGTH; // 使用 10 字?的 CDB
    sptwb->spt.SenseInfoLength = 24; // ?留足?大的空?以容? SenseInfo
    sptwb->spt.DataIn = SCSI_IOCTL_DATA_OUT; // ? DataIn 改? DataOut 表示?操作
    sptwb->spt.DataTransferLength = sectorCount * 512; // ?据???度，以字???位
    sptwb->spt.TimeOutValue = 2; // 超?值（以秒??位）

    // ?置 CDB（Command Descriptor Block）
    sptwb->spt.Cdb[0] = 0x8A; // Write(16) 命令?
    sptwb->spt.Cdb[1] = 0x10; // 控制字?，例如 FUA（?制更新）

    // ?置 LBA（???地址）
    sptwb->spt.Cdb[2] = (BYTE)((sectorNumber >> 24) & 0xFF);
    sptwb->spt.Cdb[3] = (BYTE)((sectorNumber >> 16) & 0xFF);
    sptwb->spt.Cdb[4] = (BYTE)((sectorNumber >> 8) & 0xFF);
    sptwb->spt.Cdb[5] = (BYTE)(sectorNumber & 0xFF);

    // ?置???度
    sptwb->spt.Cdb[7] = (BYTE)((sectorCount >> 8) & 0xFF);
    sptwb->spt.Cdb[8] = (BYTE)(sectorCount & 0xFF);
}



// Function to handle write operation
void writeOperation(int lba, int sectorCnt, int data)
{
    // Implement your logic for write operation here
    printf("Performing write operation\n");
    printf("Starting Logical Block Address: %d\n", lba);
    printf("Sector Count: %d\n", sectorCnt);
    printf("Data: %x\n", data);
}

int main(int argc, char *argv[])
{
    HANDLE fileHandle = NULL;
    DWORD accessMode = 0, shareMode = 0, lba = 0;
    WORD sector = 0; 
    CHAR string[NAME_COUNT];
    ULONG errorCode = 0;

    


    if ((argc < 5) || (argc > 6))
    {
        printf("Usage: %s <path> <read/write> --lba <lba> --sector_cnt <sectorCnt> --data <data>\n", argv[0]);
        return 1;
    }

    shareMode = FILE_SHARE_READ | FILE_SHARE_WRITE; // default
    accessMode = GENERIC_WRITE | GENERIC_READ;      // default

    StringCbPrintf(string, sizeof(string), "\\\\.\\%s", argv[1]);
    char *operation = argv[2];


    if (argc == 7)
    {
        if (strcmp(operation, "read") == 0)
        {
            shareMode = FILE_SHARE_READ;
        }
        else if (strcmp(operation, "write"))
        {
            shareMode = FILE_SHARE_WRITE;
        }
        else
        {
            printf("please try it again");
        }
    }
    if (_stscanf_s(argv[3], _T("%u"), &lba) != 1) {
        _tprintf(_T("Error parsing lba parameter.\n"));
        return 1;
    }
    
    if (_stscanf_s(argv[4], _T("%hu"), &sector) != 1) {
        _tprintf(_T("Error parsing sector parameter.\n"));
        return 1;
    }

    /*
    //設定file handle
    fileHandle = CreateFile(string,
                            accessMode,
                            shareMode,
                            NULL,
                            OPEN_EXISTING,
                            0,
                            NULL);

    //file handle除錯
    if (fileHandle == INVALID_HANDLE_VALUE)
    {
        errorCode = GetLastError();
        printf("Error opening %s. Error: %d\n",string, errorCode);
        PrintError(errorCode);
        return;
    }

    */
    
    if (strcmp(operation, "read") == 0)
    {
        SCSI_PASS_THROUGH_WITH_BUFFERS readCommand;
        FillRead16Command(&readCommand, lba, sector);
        if (DeviceIoControl(fileHandle,
                        IOCTL_SCSI_PASS_THROUGH,
                        &readCommand,
                        sizeof(SCSI_PASS_THROUGH_WITH_BUFFERS),
                        &readCommand,
                        sizeof(SCSI_PASS_THROUGH_WITH_BUFFERS),
                        NULL,
                        NULL)) {
        _tprintf(_T("SCSI command sent successfully.\n"));
        else {
            DWORD errorCode = GetLastError();
            _tprintf(_T("Error sending SCSI command. Error: %d\n"), errorCode);
            PrintError(errorCode);
        }


    }
    else if (strcmp(operation, "write") == 0)
    {
        SCSI_PASS_THROUGH_WITH_BUFFERS writeCommand;
        FillWrite16Command(&writeCommand, lba, sector);
        if (DeviceIoControl(fileHandle,
                            IOCTL_SCSI_PASS_THROUGH,
                            &writeCommand,
                            sizeof(SCSI_PASS_THROUGH_WITH_BUFFERS),
                            &writeCommand,
                            sizeof(SCSI_PASS_THROUGH_WITH_BUFFERS),
                            NULL,
                            NULL)) {
            _tprintf(_T("Write(16) command sent successfully.\n"));
    }
    else
    {
        printf("Invalid operation. Use 'read' or 'write'\n");
        return 1;
    }

    return 0;
}
