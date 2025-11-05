#!/usr/bin/env bash
set -euo pipefail

# Usage: ./install.sh

EXE_NAME="cmrmv"
TARGET_DIR="$HOME/bin"

if [ -f "./$EXE_NAME" ]; then
    EXE_PATH="./$EXE_NAME"
else
    echo "Error: expected a local '$EXE_NAME' executable in the current directory." >&2
    echo "If you downloaded a packaged release, verify you extracted the archive into this folder or re-download the release from the project's Releases page." >&2
    echo "To build from source instead, run: gcc -o $EXE_NAME commentRemover.c" >&2
    exit 1
fi

if [ $(id -u) -eq 0 ]; then
    INSTALL_DIR="/usr/local/bin"
else
    INSTALL_DIR="$TARGET_DIR"
fi

echo "Installing $EXE_PATH to $INSTALL_DIR as $EXE_NAME"

if [ "$INSTALL_DIR" = "$TARGET_DIR" ]; then
    mkdir -p "$TARGET_DIR"
    cp "$EXE_PATH" "$INSTALL_DIR/$EXE_NAME"
    chmod +x "$INSTALL_DIR/$EXE_NAME"

    echo "Installed to $INSTALL_DIR as $EXE_NAME"
else
    cp "$EXE_PATH" "$INSTALL_DIR/$EXE_NAME"
    chmod +x "$INSTALL_DIR/$EXE_NAME"

    echo "Installed system-wide to $INSTALL_DIR as $EXE_NAME"
fi

if echo "$PATH" | tr ':' '\n' | grep -qx "$INSTALL_DIR"; then
    echo "All set. Run $EXE_NAME <file.c>"
else
    echo "Done, but $INSTALL_DIR is not in your PATH."
    echo "Run it directly using $INSTALL_DIR/$EXE_NAME <file.c>"
    echo "or"
    if [ "$INSTALL_DIR" = "$TARGET_DIR" ]; then
    read -r -p "Add $INSTALL_DIR to your PATH now? [y/N]: " answer
        case "$answer" in
            [Yy]*)
                PROFILE="$HOME/.profile"

                if [ -f "$PROFILE" ] && grep -Fq "$INSTALL_DIR" "$PROFILE"; then
                    :
                else
                    printf '%s\n' "export PATH=\"$INSTALL_DIR:\$PATH\"" >> "$PROFILE"
                    echo "Appended PATH update to $PROFILE"
                fi
                export PATH="$INSTALL_DIR:$PATH"
                echo "Updated current shell PATH. You can now run: $EXE_NAME <file.c>"
                ;;
            *)
                echo "To add $INSTALL_DIR to your PATH manually, run:"
                echo "  # add permanently (append to ~/.profile)"
                echo "  echo 'export PATH=\"${INSTALL_DIR}:\$PATH\"' >> ~/.profile"
                echo "  # apply to current shell (optional)"
                echo "  export PATH=\"${INSTALL_DIR}:\$PATH\""
                ;;
        esac
    else
        echo "To make it available for all users, add $INSTALL_DIR to PATH using your distro's standard method."
    fi
fi