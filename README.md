![Version](https://img.shields.io/badge/PRE_ALPHA-red) ![C](https://img.shields.io/badge/C-GCC-purple)
![Version](https://img.shields.io/badge/LINUX-yellow) ![Version](https://img.shields.io/badge/MacOS-white) 
```
██╗     ███╗   ██╗██╗  ██╗    ██████╗ ███████╗ █████╗ ██████╗ ███████╗██████╗ 
██║     ████╗  ██║██║ ██╔╝    ██╔══██╗██╔════╝██╔══██╗██╔══██╗██╔════╝██╔══██╗
██║     ██╔██╗ ██║█████╔╝     ██████╔╝█████╗  ███████║██║  ██║█████╗  ██████╔╝
██║     ██║╚██╗██║██╔═██╗     ██╔══██╗██╔══╝  ██╔══██║██║  ██║██╔══╝  ██╔══██╗
███████╗██║ ╚████║██║  ██╗    ██║  ██║███████╗██║  ██║██████╔╝███████╗██║  ██║
╚══════╝╚═╝  ╚═══╝╚═╝  ╚═╝    ╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝╚═════╝ ╚══════╝╚═╝  ╚═╝
                                                                              
```


#  LNK reader 🖥️

This program is designed to extract and open a file path from a Windows `.lnk` shortcut file on non-Windows systems. The program reads the binary content of the `.lnk` file, converts it into ASCII, attempts to find the longest valid path, and finally, tries to open the path using the system's default program.

[Capture vidéo du 24-09-2023 01:32:40.webm](https://github.com/SECRET-GUEST/windows_link_reader/assets/92639080/f92222d6-e028-4166-8e6d-a9c7bd40f144)

---
---
---

## 📋 Table of Contents

1. [Features](#-features)
2. [Prerequisites](#-prerequisites)
3. [Usage](#-usage)
4. [License](#-license)
5. [Support & Questions](#-support--questions)
6. [Recommendations](#-recommendations)
7. [Installation](#-installation)
<!-- 3. [to do](#-todo) -->
## 🌟 Features

1. **Binary to ASCII Conversion**:
    - The program can convert binary data to its ASCII representation. This is especially handy for extracting textual information from binary data.

2. **RegEx-based Path Extraction**:
    - Uses regular expressions to extract the longest valid file path from the ASCII representation of the `.lnk` file.

3. **OS Notification System**:
    - Detects the underlying operating system (Linux or MacOS) and notifies the user using an appropriate notification mechanism if there are any errors or issues.

4. **Path Normalization**:
    - Transforms any Windows-style backslashes in paths (`\`) to UNIX-style forward slashes (`/`), ensuring compatibility with non-Windows systems.

5. **Mounted Path Detection**:
    - If the direct path extracted from the `.lnk` file doesn't exist on the file system, the program will attempt to find a corresponding mounted path (useful for systems with mounted Windows filesystems).

6. **Default System Program Path Opening**:
    - Once a valid path is identified, the program attempts to open it using the default program of the OS. If the path is not directly accessible, it will try to open its parent directory.

## 🔍 Prerequisites

Before you begin, ensure you have the following installed:

- GCC (GNU Compiler Collection) to compile the source code.
- Linux or macOS (other Unix-like systems may work but are not officially supported).


<!--
## 🛠️ TODO

1.
2.
-->

## 📜 License

This repository is released under the [MIT License](LICENSE). Please see the `LICENSE` file for more information.


## ❓ Support & Questions

If you have any questions or need support, please feel free to open an issue, a new discussion, or join my twitter.


## 💎 Recommendations  

In your quest for more tools to enhance your desktop productivity, these additional repositories are worth a look:

- [Barcraft](https://github.com/SECRET-GUEST/barcraft) : Create barcodes/QRCodes using an application free from malware, sourced directly from GitHub.

Looking for more? Discover user-friendly, GUI-free script here: 
- [Tiny Scripts](https://github.com/SECRET-GUEST/tiny-scripts)

If you're a 3D animator, consider:
- [Animation](https://github.com/SECRET-GUEST/animation)



## 📥 Installation


Clone the repository
```
git clone https://github.com/USERNAME/REPOSITORY.git
```
Navigate to the project folder
```
cd REPOSITORY
```
Compile the program
```
gcc lnkReader.c -o open_lnk
```
Run the program
```
./open_lnk [PATH_TO_LNK_FILE]
```

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
