#!/bin/bash
set -euo pipefail

echo "[*] Removing open_lnk binary..."
sudo rm -f /usr/local/bin/open_lnk

echo "[*] Removing .desktop entry..."
sudo rm -f /usr/share/applications/open_lnk.desktop

echo "[*] Updating MIME database..."
sudo update-mime-database /usr/share/mime || true

echo "[✓] Uninstall complete."
