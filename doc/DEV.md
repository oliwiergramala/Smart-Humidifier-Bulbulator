# ESP-IDF Development Guide

This project uses **ESP-IDF** and the `idf.py` command-line tool for building, configuring, flashing, and monitoring the ESP32.

All `idf.py` commands should be executed from the `src` directory:

```bash
cd src
```

## Building the project

To build the project, run:

```bash
idf.py build
```

The compiled project will be placed in the `src/build` directory.

## ESP32 configuration

To open the ESP-IDF configuration menu, run:

```bash
idf.py menuconfig
```

This opens an interactive configuration interface where you can change ESP32 and project-specific settings.

The configuration is stored in the project's `sdkconfig` file.

## Flashing the ESP32

To build and flash the firmware, run:

```bash
idf.py flash
```

ESP-IDF will try to automatically detect a connected ESP32 serial port.

When connecting the ESP32, you may need to **hold the BOOT button** to put the board into download/bootloader mode. If the board does not enter the bootloader, flashing will fail.

If automatic port detection does not work, you can specify the port manually:

```bash
idf.py -p /dev/ttyUSB0 flash
```

or, depending on the board:

```bash
idf.py -p /dev/ttyACM0 flash
```

## Finding serial ports on Linux

To list common USB serial devices:

```bash
ls /dev/ttyUSB* /dev/ttyACM*
```

You can also check which serial device appeared after connecting the ESP32 with:

```bash
dmesg | tail
```

## Serial port permissions on Linux

Your user should be a member of the `dialout` group to access serial devices without running ESP-IDF as root.

Check your current groups:

```bash
groups
```

If `dialout` is missing, add your user to it:

```bash
sudo usermod -aG dialout $USER
```

After doing this, **log out and log back in** for the new group membership to take effect.

You can verify it with:

```bash
groups
```

## Serial monitor

To open the ESP32 serial monitor:

```bash
idf.py monitor
```

To exit the monitor, press:

```text
Ctrl + ]
```

You can also flash the ESP32 and immediately open the monitor with:

```bash
idf.py flash monitor
```

## Quick reference

| Command                | Description                            |
| ---------------------- | -------------------------------------- |
| `idf.py build`         | Build the project                      |
| `idf.py menuconfig`    | Open ESP-IDF configuration             |
| `idf.py flash`         | Flash the connected ESP32              |
| `idf.py monitor`       | Open the serial monitor                |
| `idf.py flash monitor` | Flash and immediately start monitoring |
| `Ctrl + ]`             | Exit the serial monitor                |

