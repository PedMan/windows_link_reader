![Version](https://img.shields.io/badge/Version-ALPHA-red) ![C](https://img.shields.io/badge/C-GCC-purple)
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

> **Note:** Older compilers may encounter issues with the use of the `//` style comments present in this code. If you're facing compilation issues, you might want to replace these comments with the traditional `/* ... */` style. Alternatively, consider upgrading to a modern compiler version, such as GCC.

[Capture vidéo du 24-09-2023 01:32:40.webm](https://github.com/SECRET-GUEST/windows_link_reader/assets/92639080/f92222d6-e028-4166-8e6d-a9c7bd40f144)

> **Note:** In this video, it might seem slow because I was waiting for you to read the titles. This program opens .lnk links almost instantly, faster than Windows.

---
---
---

## 📋 Table of Contents

1. [Features](#-features)
2. [Prerequisites](#-prerequisites)
3. [Usage](#-usage)
4. [Recommendations](#-recommendations)
5. [Installation](#-installation)
6. [License](#-license)
7. [Support & Questions](#-support--questions)
<!-- 3. [to do](#-todo) -->
## 🌟 Features

1. **Binary to ASCII Conversion**:
    - The program can convert binary data to its ASCII representation. This is especially handy for extracting textual information from binary data.

2. **RegEx-based Path Extraction**:
    - Uses regular expressions to extract the longest valid file path from the ASCII representation of the `.lnk` file.

3. **OS Notification System**:
   - Detects the underlying operating system (Linux or macOS).
   - On Linux it tries several backends in order: `notify-send`, `zenity`, `kdialog`, `xmessage`.
   - On macOS it uses `osascript`.
   - If none are available, it falls back to printing the error in the terminal (`stderr`).

4. **Path Normalization**:
    - Transforms any Windows-style backslashes in paths (`\`) to UNIX-style forward slashes (`/`), ensuring compatibility with non-Windows systems.

5. **Mounted Path Detection**:
    - If the direct path extracted from the `.lnk` file doesn't exist on the file system, the program will attempt to find a corresponding mounted path (useful for systems with mounted Windows filesystems).

6. **Default System Program Path Opening**:
    - Once a valid path is identified, the program attempts to open it using the default program of the OS. If the path is not directly accessible, it will try to open its parent directory.

7. **Fast install** :
   - You can install it faster with the script setup.sh
  
## 🔍 Prerequisites

Before you begin, ensure you have the following installed:

- GCC (GNU Compiler Collection) to compile the source code.
- Linux or macOS (other Unix-like systems may work but are not officially supported).
- On Linux, you may need `libnotify-bin` and `xdg-utils` installed to support desktop notifications.

## 💎 Recommendations  

In your quest for more tools to enhance your desktop productivity, these additional repositories are worth a look:

- [File organizer](https://github.com/SECRET-GUEST/file_organizer) : A versatile tool for sorting and organizing files efficiently, ideal for managing recovered data.

Looking for more? Discover user-friendly, GUI-free script here: 
- [Tiny Scripts](https://github.com/SECRET-GUEST/tiny-scripts)

If you're a 3D animator, consider:
- [Animation](https://github.com/SECRET-GUEST/animation)




## 📥 Installation

### **LINUX Systems:**

0. **Simply run setup.sh in the same directory as lnkReader.c**  
   On Debian/Ubuntu, this will also install the needed dependencies (`libnotify-bin`, `xdg-utils`):
   
```bash
chmod +x setup.sh
./setup.sh
 ```
   For Fedora:

```bash
sudo dnf install libnotify xdg-utils
```

  For Arch:

```bash
sudo pacman -S libnotify xdg-utils
```

  But if you prefere a manual installation you can follow steps behind :


2. **Clone the repository**:
    ```bash
    git clone https://github.com/SECRET-GUEST/windows_link_reader.git
    ```

3. **Navigate to the project folder**:
    ```bash
    cd REPOSITORY
    ```

4. **Compile the program**:
    ```bash
    gcc lnkReader.c -o open_lnk
    ```

5. **Try the program**:
    ```bash
    ./open_lnk YOUR_FILE.lnk
    ```

### **Debian Systems - Creating a `.desktop` Application to run lnk by simple click**

1. **Create a new `.desktop` file**:
    ```bash
    vim ~/.local/share/applications/open_lnk.desktop
    ```
> **Note:** use vim nano or whatever else txt editor
   
3. **Add the following content to the file**, adjusting paths as necessary:
    ```
    [Desktop Entry]
    Version=1.0
    Name=Open LNK
    Comment=Open a Windows .lnk file
    Exec=/path_to_compiled_program/open_lnk %U
    Terminal=true
    Type=Application
    Categories=Utility;
    ```

4. **Make the `.desktop` file executable**:
    ```bash
    chmod +x ~/.local/share/applications/open_lnk.desktop
    ```

5. Now, you just have to use the program by default for .lnk files, by **"open with"** or in the properties.


### **MacOS Systems:**

  ###### I don't know why am I doing this tutorial but let's go ;

1. **Ensure you have the Xcode command line tools installed**. This provides you with the necessary compilers:
    ```bash
    xcode-select --install
    ```

2. **Compile the program as indicated in the General Setup**.

3. **To run the program, you can use the Terminal as in the General Setup** or create a simple script or Automator application for easier access.

## 📜 License

This repository is released under the [MIT License](LICENSE). Please see the `LICENSE` file for more information.


## ❓ Support & Questions

If you have any questions or need support, please feel free to open an issue, a new discussion, or join my twitter.


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
