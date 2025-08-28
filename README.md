# PocketBase Watcher

A tiny native Windows watcher for [PocketBase](https://pocketbase.io/) that automatically restarts  
`pocketbase.exe serve --dev` whenever files in the `pb_hooks` folder change.

---

## ✨ Features
- Watches the `pb_hooks` folder using the native Windows API
- Restarts PocketBase instantly when a file created/modified/deleted
---

## ▶️ Usage
Run `pbw.exe` from the same folder as `pocketbase.exe`:

## 🛠 Building from Source

### Requirements
Visual Studio with Desktop development with C++ workload

Windows SDK installed

### Steps
Open x64 Native Tools Command Prompt for VS
Compile:
```cl pbw.c /Fe:pbw.exe```

Alternatively, with MinGW:
```gcc -static -o pbw.exe pbw.c```
