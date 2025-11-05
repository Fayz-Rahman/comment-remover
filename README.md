# commentRemover

commentRemover is a tiny command-line tool that removes comments from source files.
Currently, it supports C source and header files (.c, .h). More languages may be added in future releases.

When you run it on a file, it creates a new file in the same directory with this name format:

`commentless__<original-filename>`

## Features
- Keeps code formatting intact
- Does not modify the original file. Creates a new `commentless__` copy instead

## Download and installation

### Linux (from release archive)
1) Download the latest release from the Releases page. The file name will look something like:

`cmrmv-linux-x86_64.tar.gz`

2) (Optional) Verify the file:

```bash
sha256sum -c cmrmv-linux-x86_64.sha256
```

3) Extract and install:

```bash
tar -xzf cmrmv-linux-x86_64.tar.gz
chmod +x install.sh
./install.sh
```

Use `sudo ./install.sh` if you want to install it system-wide (to `/usr/local/bin`).

### Windows
Windows builds will be available in future releases. Once available, installation will typically involve:

- Downloading `cmrmv-windows-x86_64.zip`
- Extracting it to a folder
- Running the `install.ps1` script

## Build from source
If you prefer to build it yourself:

```bash
# clone this repo or download the ZIP
# then from the project directory
gcc commentRemover.c -o cmrmv
sudo cp cmrmv /usr/local/bin/   # optional
```

### Static build 

Single binary with no runtime dependencies:

```bash
gcc -static -Os -s -o cmrmv commentRemover.c
```

## Usage
Once installed, use `cmrmv <filename>` to run it:

```bash
cmrmv file.c
```

This generates:

```text
commentless__file.c
```

You can then open `commentless__file.c` to view your code without comments.

## Example

Input file (`example.c`):

```c
// this is a comment
int main() {
    /* initialize */
    int x = 5; // set x
    return 0;
}
```

Output (`commentless__example.c`):

```c
int main() {
    
    int x = 5;
    return 0;
}
```

## How it works (in short)
- Reads the file character by character
- Skips comment by detecting delimiters while respecting strings and escape sequences
- Writes everything else to a new file

## Releases
Prebuilt binaries for each platform will be listed under the Releases section. Each release includes:

- Compiled binaries (for supported platforms)
- An install script
- A SHA-256 checksum for file verification

## Future plans
- Support for more languages
- Smarter comment parsing that handles tricky edge cases
- Cross-platform builds (Windows, macOS)

## License
Licensed under the MIT License. See the LICENSE file for full terms.
