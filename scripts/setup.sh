#!/bin/bash

# Compiling lnkReader.c into open_lnk
gcc lnkReader.c -o open_lnk

# Creating the .desktop file
echo "[Desktop Entry]
Name=Open LNK
Exec=$(pwd)/open_lnk %U
Type=Application
MimeType=application/x-ms-shortcut
" > open_lnk.desktop

# Copying the .desktop file to the appropriate directory
sudo cp open_lnk.desktop /usr/share/applications/

# Updating the mime database
sudo update-mime-database /usr/share/mime

# Setting open_lnk as the default application to open .lnk files
xdg-mime default open_lnk.desktop application/x-ms-shortcut
