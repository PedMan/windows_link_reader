#!/bin/bash
set -euo pipefail

# Build
gcc lnkReader.c -o open_lnk -Wall -Wextra -O2

# Install dependencies on debian if available
if command -v apt-get >/dev/null 2>&1; then
  sudo apt-get update
  sudo apt-get install -y libnotify-bin xdg-utils
fi

# Create the .desktop 
cat > open_lnk.desktop <<EOF
[Desktop Entry]
Name=Open LNK
Exec=$(pwd)/open_lnk %U
Type=Application
MimeType=application/x-ms-shortcut
NoDisplay=false
Terminal=false
EOF

# Install the .desktop
sudo cp open_lnk.desktop /usr/share/applications/

# Update MIME database if present and set default handler
sudo update-mime-database /usr/share/mime || true
xdg-mime default open_lnk.desktop application/x-ms-shortcut
