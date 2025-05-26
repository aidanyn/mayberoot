# Mayberoot

[![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg)](https://opensource.org/licenses/MIT)

A lightweight C utility that detects permission errors in command outputs and offers to re-run them with sudo.

## Features
- 🚦 Detects common permission-denied error patterns
- 🖥️ Native performance (no bash/POSIX dependencies)
- 🎨 Highlights error messages in terminal colors
- 🔍 Safe command argument parsing

## Installation
```bash
git clone https://github.com/aidanyn/mayberoot
cd mayberoot
make && sudo make install
```

## Usage
```bash
mayberoot <command> [args...]

# Example
mayberoot touch /etc/protected_file
```

## Building from Source
Requires
 - C compiler (gcc/clang)
 - GNU Make

```bash
make debug  # Build with debug symbols
make test   # Run test suite 
```

## Contributing 
PRs welcome! Please do!

## License
MIT © [Aidan Young] - See [LICENSE](./LICENSE) for details.
