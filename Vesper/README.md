<div align="center">
██╗   ██╗███████╗███████╗██████╗ ███████╗██████╗
██║   ██║██╔════╝██╔════╝██╔══██╗██╔════╝██╔══██╗
██║   ██║█████╗  ███████╗██████╔╝█████╗  ██████╔╝
╚██╗ ██╔╝██╔══╝  ╚════██║██╔═══╝ ██╔══╝  ██╔══██╗
╚████╔╝ ███████╗███████║██║     ███████╗██║  ██║
╚═══╝  ╚══════╝╚══════╝╚═╝     ╚══════╝╚═╝  ╚═╝

**An aggressive red team multi-tool — built in C++ for security researchers**

![Status](https://img.shields.io/badge/status-in%20development-red?style=flat-square)
![Platform](https://img.shields.io/badge/platform-Windows-blue?style=flat-square)
![Language](https://img.shields.io/badge/language-C%2B%2B%20%2F%20CLR-informational?style=flat-square)
![IDE](https://img.shields.io/badge/IDE-Visual%20Studio-purple?style=flat-square)
![Type](https://img.shields.io/badge/type-Red%20Team%20Tool-critical?style=flat-square)

</div>

---

## Overview

Vesper is an offensive security multi-tool built in C++ using Windows Forms (CLR). Designed for red team operations, it consolidates reconnaissance, network analysis, exploitation assistance, and post-exploitation utilities into a single dark, minimal interface.

The name is intentional — Vesper, the evening star. The last light before darkness.

> ⚠️ This tool is intended for authorized security research and penetration testing only. Use responsibly.

---

## Current State

| Module | Status |
|---|---|
| Splash Screen | ✅ Complete |
| Main Window Shell | ✅ Complete |
| Reconnaissance | ⏳ Planned |
| Network Analysis | ⏳ Planned |
| Exploitation Assistance | ⏳ Planned |
| Post Exploitation | ⏳ Planned |
| Reporting | ⏳ Planned |

---

## Project Structure
Vesper/
├── Vesper.cpp          — Application entry point
├── SplashScreen.h      — Animated splash screen
├── SplashScreen.cpp    — Splash implementation
├── MainWindow.h        — Main UI shell
├── MainWindow.cpp      — Main window implementation
├── Assets/             — Logo and icons
├── Vesper.vcxproj      — MSVC project file
└── Vesper.sln          — Solution file

---

## Getting Started

### Prerequisites

- Windows 10 / 11
- Visual Studio (with C++/CLR workload)
- .NET Framework 4.7.2+

### Clone & Build
```bash
git clone https://github.com/X3N0L4T/xenolat-lab.git
cd xenolat-lab/Vesper
```

Open `Vesper.sln` in Visual Studio and press **F5**.

---

## Tech Stack

| Component | Technology |
|---|---|
| UI Framework | Windows Forms (C++/CLR) |
| Language | C++/CLI |
| Build System | MSVC / Visual Studio |

---

## Roadmap

- [x] Project scaffold and repo setup
- [x] Animated splash screen with logo
- [x] Main window shell with looping scramble header
- [ ] Reconnaissance module
- [ ] Network analysis module
- [ ] Exploitation assistance module
- [ ] Post exploitation module
- [ ] Reporting and export

---

## Disclaimer

Vesper is developed strictly for authorized penetration testing and security research. The author is not responsible for any misuse or damage caused by this tool. Always obtain proper authorization before testing any system.

---

## License

MIT License — see [`LICENSE`](LICENSE) for details.

---

<div align="center">
<sub>Vesper · Built from scratch · C++ · Windows · 2026</sub>
</div>