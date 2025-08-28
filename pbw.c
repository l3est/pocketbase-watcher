#include <windows.h>
#include <stdio.h>
#include <tlhelp32.h>

PROCESS_INFORMATION pi = {0};

void KillPocketBase() {
    if (pi.hProcess) {
        TerminateProcess(pi.hProcess, 0);
        CloseHandle(pi.hThread);
        CloseHandle(pi.hProcess);
        pi.hProcess = NULL;
    }
}

void StartPocketBase(const char* exePath) {
    KillPocketBase();

    STARTUPINFO si = {0};
    si.cb = sizeof(si);

    // Run pocketbase.exe serve --dev in same console
    char cmd[512];
    snprintf(cmd, sizeof(cmd), "\"%s\\pocketbase.exe\" serve --dev", exePath);

    if (!CreateProcessA(NULL, cmd, NULL, NULL, TRUE, 0, NULL, exePath, &si, &pi)) {
        printf("[ERROR] Failed to start PocketBase (%lu)\n", GetLastError());
    } else {
        printf("[INFO] PocketBase started (PID %lu)\n", pi.dwProcessId);
    }
}

int main() {
    char exePath[MAX_PATH];
    GetModuleFileNameA(NULL, exePath, MAX_PATH);
    char* lastSlash = strrchr(exePath, '\\');
    if (lastSlash) *lastSlash = '\0'; // strip exe name

    char hooksPath[MAX_PATH];
    snprintf(hooksPath, sizeof(hooksPath), "%s\\pb_hooks", exePath);

    // Start PocketBase initially
    StartPocketBase(exePath);

    // Set up directory watcher
    HANDLE hDir = CreateFileA(
        hooksPath, FILE_LIST_DIRECTORY,
        FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
        NULL, OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS, NULL
    );

    if (hDir == INVALID_HANDLE_VALUE) {
        printf("[ERROR] Cannot open pb_hooks directory\n");
        return 1;
    }

    char buffer[1024];
    DWORD bytesReturned;

    printf("[INFO] Watching %s for changes...\n", hooksPath);

    while (1) {
        if (ReadDirectoryChangesW(
                hDir, buffer, sizeof(buffer), TRUE,
                FILE_NOTIFY_CHANGE_LAST_WRITE | FILE_NOTIFY_CHANGE_FILE_NAME,
                &bytesReturned, NULL, NULL)) {
            printf("[INFO] Change detected, restarting PocketBase...\n");
            StartPocketBase(exePath);
        } else {
            Sleep(1000);
        }
    }

    CloseHandle(hDir);
    KillPocketBase();
    return 0;
}
