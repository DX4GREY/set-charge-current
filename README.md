# Set Charge Current

A simple C program to set the charging current for your device by modifying the `constant_charge_current_max` value in the sysfs directory. Ideal for rooted Android devices or Linux systems where manual tuning of charge current is needed.

## Features

- Set charging current dynamically (in milliamps).
- Automatically manages file permissions for safe writes.
- Compatible with Android (Termux) and standard Linux.
- Includes Makefile with `install`, `uninstall`, `info`, and `run` targets.

## Requirements

- **Root Access** â€” Required to modify sysfs charging parameters.
- **Linux or Android** â€” Works on rooted Android (via Termux) or any Linux-based system.

## Installation

```bash
git clone https://github.com/DX4GREY/set-charge-current.git
cd set-charge-current
make
```

### Optional: Install binary system-wide

```bash
make install
```

*This will detect your OS and install to the correct location:*

- Android (Termux): `~/../usr/bin`
- Linux: `/usr/local/bin`

## Usage

```bash
sudo ./setcurrent <current_in_mA>
```

Example:
```bash
sudo ./setcurrent 2000  # Sets charging current to 2000 mA (2A)
```

### Help

```bash
./setcurrent help
```

### Uninstall

```bash
make uninstall
```

### Clean up build files

```bash
make clean
```

## Troubleshooting

- **Permission Denied**: Make sure to run the binary as root (`sudo`) and ensure your device allows sysfs writes.
- **Invalid Argument**: Your hardware might not support the value you're trying to set. Try lower values like `1000`, `1500`, etc.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.