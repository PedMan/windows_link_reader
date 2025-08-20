![C](https://img.shields.io/badge/C-GCC-purple)
![Version](https://img.shields.io/badge/LINUX-yellow) ![Version](https://img.shields.io/badge/MacOS-white) 
```
██╗     ███╗   ██╗██╗  ██╗    ██████╗ ███████╗ █████╗ ██████╗ ███████╗██████╗ 
██║     ████╗  ██║██║ ██╔╝    ██╔══██╗██╔════╝██╔══██╗██╔══██╗██╔════╝██╔══██╗
██║     ██╔██╗ ██║█████╔╝     ██████╔╝█████╗  ███████║██║  ██║█████╗  ██████╔╝
██║     ██║╚██╗██║██╔═██╗     ██╔══██╗██╔══╝  ██╔══██║██║  ██║██╔══╝  ██╔══██╗
███████╗██║ ╚████║██║  ██╗    ██║  ██║███████╗██║  ██║██████╔╝███████╗██║  ██║
╚══════╝╚═╝  ╚═══╝╚═╝  ╚═╝    ╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝╚═════╝ ╚══════╝╚═╝  ╚═╝
                                                                              
```

# LNK Reader 🖥️

This program is made to **read and open Windows `.lnk` shortcut files on Linux/macOS**.
The first version was a quick regex hack I made for practice, but since then I’ve reworked it to follow the official Microsoft SHLLINK spec for proper parsing.

That means it now supports:

* LocalBasePath, RelativePath, WorkingDir, Arguments, IconLocation (ANSI/Unicode)
* Windows drive → Linux mount mapping
* Proper handling of spaces, multiple spaces, and encoding quirks

It won’t cover 100% of exotic edge cases (e.g. weird *ExtraData blocks*, UNC network shares, or rare Unicode surrogate pairs), but it should handle **almost all `.lnk` files without bugs**.

[Demo video](https://github.com/SECRET-GUEST/windows_link_reader/assets/92639080/f92222d6-e028-4166-8e6d-a9c7bd40f144)

> ⚡ Note: The video looks slow because I left time for you to read — in reality it opens links almost instantly, even faster than Windows.

---

## 📋 Table of Contents

1. [Features](#-features)
2. [Prerequisites](#-prerequisites)
3. [Installation](#-installation)
4. [Usage](#-usage)
5. [Uninstallation](#-uninstallation)
6. [License](#-license)
7. [Support](#-support)

---

## 🌟 Features

* ✅ Full spec parsing (no more fragile regex)
* ✅ Path normalization (`\` → `/`)
* ✅ Mount detection (map Windows drives on Linux)
* ✅ Multi-backend notifications:

  * Linux: `notify-send`, `zenity`, `kdialog`, `xmessage`
  * macOS: `osascript`
  * Fallback: stderr
 
* ✅ Opens with system default program (or parent dir if target missing)
* ✅ Installer/uninstaller scripts

---

## 🔍 Prerequisites

* GCC (or Clang) to compile
* Linux or macOS
* On Linux:

  * `libnotify-bin` (for notifications)
  * `xdg-utils` (for opening files)

---

## 📥 Installation

```bash
git clone https://github.com/SECRET-GUEST/windows_link_reader.git
cd windows_link_reader
chmod +x setup.sh
./setup.sh
```

This will:

* Compile `lnkreader.c` into `open_lnk`
* Install required deps (if missing)
* Create a `.desktop` file and register `.lnk` MIME type

Now you can **double-click `.lnk` files** and they’ll open directly.

---

## ▶️ Usage

From terminal:

```bash
./open_lnk path/to/file.lnk
```

Or just double-click a `.lnk` file once installed.

---

## 🗑️ Uninstallation

```bash
chmod +x uninstall.sh
./uninstall.sh
```

This will remove the binary and `.desktop` entry.

---

## 📜 License

Released under [MIT License](LICENSE).

---

## ❓ Support

Open an [issue](https://github.com/SECRET-GUEST/windows_link_reader/issues) or reach me on Twitter.


```
     _ ._  _ , _ ._            _ ._  _ , _ ._    _ ._  _ , _ ._      _ ._  _ , _ .__  _ , _ ._   ._  _ , _ ._   _ , _ ._   .---.  _ ._   _ , _ .__  _ , _ ._   ._  _ , _ ._      _ ._  _ , _ .__  _ , _ . .---<__. \ _
   (_ ' ( `  )_  .__)        (_ ' ( `  )_  .__ (_ ' ( `  )_  .__)  (_ '    ___   ._( `  )_  .__)  ( `  )_  .__)   )_  .__)/     \(_ ' (    )_  ._( `  )_  .__)  ( `  )_  .__)  (_ ' ( `  )_  ._( `` )_  . `---._  \ \ \
 ( (  (    )   `)  ) _)    ( (  (    )   `)  ) (  (    )   `)  ) _ (  (   (o o) )     )   `)  ) _    )   `)  ) _    `)  ) \.@-@./(  (    )   `)     )   `)  ) _    )   `)  ) _ (  (    )   `)         `) ` ),----`- `.))  
(__ (_   (_ . _) _) ,__)  (__ (_   (_ . _) _) _ (_   (_ . _) _) ,__ (_   (  V  ) _) (_ . _) _) ,_  (_ . _) _) ,_ . _) _) ,/`\_/`\ (_   (  . _) _) (_ . _) _) ,_  (_ . _) _) ,__ (_   (_ . _) _) (__. _) _)/ ,--.   )  |
    `~~`\ ' . /`~~`           `~~`\ ' . /`~~`   `~~`\ ' . /`~~`     `~~`/--m-m- ~~`\ ' . /`~~`   `\ ' . /`~~`  `\ ' . /  //  _  \\ ``\ '  . /`~~`\ ' . /`~~`   `\ ' . /`~~`     `~~`\ ' . /`~~`\ ' . /`~~/_/    >     |
         ;   ;                     ;   ;             ;   ;               ;   ;      ;   ;          ;   ;         ;   ;  | \     )|_   ;    ;      ;   ;          ;   ;               ;   ;      ;   ;    |,\__-'      |
         /   \                     /   \             /   \               /   \      /   \          /   \         /   \ /`\_`>  <_/ \  /    \      /   \          /   \               /   \      /   \     \__         \
________/_ __ \___________________/_ __ \___________/_ __ \______ __ ___/_ __ \____/_ __ \________/_ __ \_______/_ __ \\__/'---'\__/_/_  __ \____/_ __ \________/_ __ \_____ _______/_ __ \____/_ __ \____ __\___      )
```
