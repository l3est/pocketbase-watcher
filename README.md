# PocketBase Watcher

A tiny native Windows Hot Reload / Live Reload / Watcher for [PocketBase](https://pocketbase.io/) that automatically restarts  
`pocketbase.exe serve --dev` whenever files in the `pb_hooks` folder change.

## ✨ Features
- Watches the `pb_hooks` folder using the native Windows API
- Restarts PocketBase instantly when a file created/modified/deleted

## ▶️ Usage
Download the [Release](https://github.com/l3est/pocketbase-watcher/releases/tag/v1.0.0) file__
Copy `pbw.exe` to the same folder as `pocketbase.exe` and run it

## 🛠 Building from Source

### Requirements
Visual Studio with Desktop development with C++ workload__
Windows SDK installed

### Steps
Open x64 Native Tools Command Prompt for VS
Compile:
```cl pbw.c /Fe:pbw.exe```

Alternatively, with MinGW:
```gcc -static -o pbw.exe pbw.c```
