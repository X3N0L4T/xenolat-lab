<div align="center">

<img src="Vesper/Assets/vesper.png" width="300"/>

![Status](https://img.shields.io/badge/status-in%20development-red?style=flat-square)
![Platform](https://img.shields.io/badge/platform-Windows-blue?style=flat-square)
![Language](https://img.shields.io/badge/language-C%2B%2B%20%2F%20CLR-informational?style=flat-square)
![IDE](https://img.shields.io/badge/IDE-Visual%20Studio-purple?style=flat-square)
![Type](https://img.shields.io/badge/type-Red%20Team%20Tool-critical?style=flat-square)

</div>

---

## Overview

Vesper is an offensive security multi-tool built in C++ using Windows Forms (CLR). Reconnaissance, network analysis, exploitation assistance, and post-exploitation — one interface.

> For authorized penetration testing and security research only.

---

## Modules

| Module | Status |
|---|---|
| Splash Screen | Complete |
| Main Window Shell | Complete |
| Sidebar Navigation | Complete |
| Top Bar | Complete |
| Dashboard | Complete |
| Tray Icon | Complete |
| Reconnaissance | Planned |
| Network Analysis | Planned |
| Exploitation Assistance | Planned |
| Post Exploitation | Planned |
| Reporting | Planned |

---

## Structure
Vesper/
├── Vesper.cpp
├── SplashScreen.h
├── SplashScreen.cpp
├── MainWindow.h
├── MainWindow.cpp
├── Modules/
│   └── Dashboard.h
├── Assets/
├── Vesper.vcxproj
└── Vesper.sln

---

## Build

```bash
git clone https://github.com/X3N0L4T/xenolat-lab.git
cd xenolat-lab/Vesper
```

Open `Vesper.sln` in Visual Studio and press **F5**.

**Requirements**
- Windows 10 / 11
- Visual Studio with C++/CLR workload
- .NET Framework 4.7.2+

---

## Stack

| Component | Technology |
|---|---|
| UI | Windows Forms (C++/CLR) |
| Language | C++/CLI |
| Build | MSVC / Visual Studio |

---

## Roadmap

- [x] Project scaffold
- [x] Animated logo splash screen
- [x] Sidebar navigation
- [x] Top bar with search and task button
- [x] Dashboard module
- [x] System tray icon with context menu
- [ ] Nav button routing between modules
- [ ] Reconnaissance module
- [ ] Network analysis module
- [ ] Exploitation assistance module
- [ ] Post exploitation module
- [ ] Reporting and export

---

## Disclaimer

Vesper is built for authorized security research and penetration testing only. The author holds no responsibility for misuse. Always obtain proper written authorization before engaging any system.

---

<div align="center">
<sub>Vesper · C++ · Windows · 2026</sub>
</div>
