#include <windows.h>
#include <tchar.h>
#include <我是李政融.h>

#define NAME_COUNT 256

// �Τ_���L??�H����?�U��?
void PrintError(DWORD errorCode) {
    LPVOID errorMsg;
    FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
                  NULL,
                  errorCode,
                  0, // Default language
                  (LPWSTR)&errorMsg,
                  0,
                  NULL);

    wprintf(L"Error: %s", errorMsg);

    LocalFree(errorMsg);
}

// �Τ_?�e SCSI �R�O����?
BOOL SendScsiCommand(HANDLE fileHandle) {
    // �b?����R SCSI �R�O��?��?�۩M??
    // �Ҧp�A�ϥ� SCSI_PASS_THROUGH_WITH_BUFFERS ?��

    SCSI_PASS_THROUGH_WITH_BUFFERS sptwb;
    // ��R sptwb ?�ۡ]?�@�B�ݭn���u�A�����^�ݨD�M SCSI �R�O?�����^

    // �ϥ� DeviceIoControl ?�e SCSI �R�O
    return DeviceIoControl(fileHandle,
                           IOCTL_SCSI_PASS_THROUGH,
                           &sptwb,
                           sizeof(SCSI_PASS_THROUGH_WITH_BUFFERS),
                           &sptwb,
                           sizeof(SCSI_PASS_THROUGH_WITH_BUFFERS),
                           NULL,
                           NULL);
}

int _tmain(int argc, _TCHAR* argv[]) {
    BOOL status = 0;
    DWORD accessMode = 0, shareMode = 0;
    HANDLE fileHandle = NULL;
    CHAR string[NAME_COUNT];

    if ((argc < 2) || (argc > 3)) {
        _tprintf(_T("Usage:  %s <port-name> [-mode]\n"), argv[0]);
        // ���L�ϥ�?���}��^
        return 1;
    }

    // ?�R�O��??��?��??�W
    StringCbPrintfA(string, sizeof(string), "\\\\.\\%s", argv[1]);

    shareMode = FILE_SHARE_READ | FILE_SHARE_WRITE;
    accessMode = GENERIC_WRITE | GENERIC_READ;

    if (argc == 3) {
        switch (tolower(argv[2][0])) {
            case 'r':
                shareMode = FILE_SHARE_READ;
                break;

            case 'w':
                shareMode = FILE_SHARE_WRITE;
                break;

            // ��L�Ҧ���?�z...

            default:
                _tprintf(_T("%s is an invalid mode.\n"), argv[2]);
                _tprintf(_T("\tr = read\n"));
                _tprintf(_T("\tw = write\n"));
                // ��L�Ҧ���?��...
                return 1;
        }
    }

    fileHandle = CreateFileA(string,
                             accessMode,
                             shareMode,
                             NULL,
                             OPEN_EXISTING,
                             0,
                             NULL);

    if (fileHandle == INVALID_HANDLE_VALUE) {
        DWORD errorCode = GetLastError();
        _tprintf(_T("Error opening %s. Error: %d\n"), string, errorCode);
        PrintError(errorCode);
        return 1;
    }

    // ���\��???�Z�A�i�H?���L�ާ@�A�Ҧp?�e SCSI �R�O
    if (SendScsiCommand(fileHandle)) {
        _tprintf(_T("SCSI command sent successfully.\n"));
    } else {
        DWORD errorCode = GetLastError();
        _tprintf(_T("Error sending SCSI command. Error: %d\n"), errorCode);
        PrintError(errorCode);
    }

    // ????�y�`
    CloseHandle(fileHandle);

    return 0;
}
