# Modbus RTU CRC Calculator

A simple command-line tool to calculate CRC-16 checksums for Modbus RTU commands.

## Features

- ✅ Calculate Modbus RTU CRC-16 checksums
- ✅ Display complete command with CRC appended
- ✅ Pre-calculated common commands
- ✅ Interactive mode for custom commands
- ✅ Cross-platform (Windows, Linux, macOS)

---

## Prerequisites

### Windows
- **MinGW-w64** (GCC compiler for Windows)
  - Download: https://github.com/niXman/mingw-builds-binaries/releases
  - Get: `x86_64-*-release-posix-seh-ucrt-*.7z`
  - Extract to `C:\mingw64`
  - Add `C:\mingw64\bin` to System PATH

### Linux
```bash
sudo apt update
sudo apt install build-essential
```

### macOS
```bash
xcode-select --install
```

**Verify installation:**
```bash
g++ --version
```

---

## Step 1: Download or Create the Project

### Option A: Clone Repository (if available)
```bash
git clone https://github.com/hanifr/crc-calculator
cd crc-calculator
```

### Option B: Create Manually

**Create project structure:**
```
CRCCalculator/
└── main.cpp
```

**Copy the C++ code into `main.cpp`**

---

## Step 2: Compile the Program

Open terminal/command prompt in the project directory and run:
```bash
g++ -std=c++11 main.cpp -o crc_calculator
```

**What this does:**
- `g++` - C++ compiler
- `-std=c++11` - Use C++11 standard
- `main.cpp` - Source file
- `-o crc_calculator` - Output executable name

**Expected output:** No output means successful compilation!

---

## Step 3: Run the Program

### Windows:
```bash
./crc_calculator
```
or
```bash
crc_calculator.exe
```

### Linux/macOS:
```bash
./crc_calculator
```

---

## Usage

### Pre-calculated Commands

When you run the program, it displays common Modbus commands with CRC:
```
=======================================
     Modbus RTU CRC Calculator
=======================================

Common Commands:

Slave 5, Read 2 registers
Input:    05 03 00 00 00 02
Complete: 05 03 00 00 00 02 C4 F5

Slave 55, Read 4 registers
Input:    37 03 00 00 00 04
Complete: 37 03 00 00 00 04 85 8C

Slave 55, Read 10 registers
Input:    37 03 00 00 00 0A
Complete: 37 03 00 00 00 0A 68 C4

Slave 2, Read 2 registers
Input:    02 03 00 00 00 02
Complete: 02 03 00 00 00 02 44 F9

=======================================
```

### Interactive Mode

After displaying pre-calculated commands, you can enter your own:
```
Enter hex bytes (e.g., 37 03 00 00 00 0A)
Or type 'exit' to quit
> 05 03 00 01 00 01

Input:          05 03 00 01 00 01 
CRC (hex):      D409
CRC Low Byte:   09
CRC High Byte:  D4

Complete Command: 05 03 00 01 00 01 D4 09
```

### Exit the Program

Type one of the following:
- `exit`
- `quit`
- `q`

Or press `Ctrl+C`

---

## Common Modbus Commands Reference

| Slave ID | Registers | Command Bytes | Full Command with CRC |
|----------|-----------|---------------|----------------------|
| 1 | 2 | `01 03 00 00 00 02` | `01 03 00 00 00 02 C4 0B` |
| 2 | 2 | `02 03 00 00 00 02` | `02 03 00 00 00 02 44 F9` |
| 5 | 2 | `05 03 00 00 00 02` | `05 03 00 00 00 02 C4 F5` |
| 5 | 10 | `05 03 00 00 00 0A` | `05 03 00 00 00 0A 68 C4` |
| 55 (0x37) | 4 | `37 03 00 00 00 04` | `37 03 00 00 00 04 85 8C` |
| 55 (0x37) | 10 | `37 03 00 00 00 0A` | `37 03 00 00 00 0A 68 C4` |

---

## Understanding Modbus RTU Commands

**Command structure:**
```
[Slave ID] [Function Code] [Start Address Hi] [Start Address Lo] [Num Registers Hi] [Num Registers Lo] [CRC Lo] [CRC Hi]
```

**Example: `05 03 00 00 00 02 C4 F5`**
- `05` - Slave ID: 5
- `03` - Function Code: Read Holding Registers
- `00 00` - Starting Address: 0
- `00 02` - Number of Registers: 2
- `C4 F5` - CRC-16 Checksum (calculated)

---

## Troubleshooting

### Problem: `g++: command not found`
**Solution:** Install GCC compiler (see Prerequisites section)

### Problem: Permission denied on Linux/macOS
**Solution:** Make executable:
```bash
chmod +x crc_calculator
./crc_calculator
```

### Problem: Compilation warnings about C++11
**Solution:** Use the `-std=c++11` flag as shown in Step 2

### Problem: Program doesn't run on Windows
**Solution:** Try:
```bash
crc_calculator.exe
```
or
```bash
.\crc_calculator.exe
```

---

## For Dragino RS485-LN Users

Use the complete commands with CRC for your AT commands:

### pH Sensor (Slave ID 5)
```bash
AT+COMMAND1=0503000000C4F5,0
```

### DO Sensor (Slave ID 55)
```bash
AT+COMMAND1=37030000000485C8,0
```

### Test Manually
```bash
AT+CFGDEV=0503000000C4F5,0
```

---

## Building with Different Options

### With optimization
```bash
g++ -std=c++11 -O2 main.cpp -o crc_calculator
```

### With debug symbols
```bash
g++ -std=c++11 -g main.cpp -o crc_calculator
```

### With all warnings
```bash
g++ -std=c++11 -Wall -Wextra main.cpp -o crc_calculator
```

### All options combined
```bash
g++ -std=c++11 -Wall -Wextra -O2 main.cpp -o crc_calculator
```

---

## License

MIT License - Feel free to use and modify

---

## Contributing

Contributions are welcome! Please feel free to submit a Pull Request.

---

## Support

For issues or questions, please open an issue on GitHub or contact the maintainer.

---

## Changelog

### Version 1.0.0
- Initial release
- Basic CRC calculation
- Pre-calculated common commands
- Interactive mode

---

**Made for RS485 Modbus RTU sensor communication** 🚀