#!/bin/bash
set -euo pipefail

# Go to the script's directory
cd "$(dirname "$(realpath "$0")")"

# Build
gcc lnkreader.c -o open_lnk -Wall -Wextra -O2

# Check dependencies only if apt-get exists
if command -v apt-get >/dev/null 2>&1; then
  if ! command -v notify-send >/dev/null 2>&1; then
    echo "Installing libnotify-bin..."
    sudo apt-get update
    sudo apt-get install -y libnotify-bin
  else
    echo "notify-send already available, skipping install."
  fi

  if ! command -v xdg-open >/dev/null 2>&1; then
    echo "Installing xdg-utils..."
    sudo apt-get update
    sudo apt-get install -y xdg-utils
  else
    echo "xdg-open already available, skipping install."
  fi
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
