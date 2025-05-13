# Set Charge Current

A simple C program to set the charging current for your device by modifying the `constant_charge_current_max` value in the sysfs directory. This program is useful for fine-tuning battery charging settings on devices with root access.

## Features
- Set the charging current for your device's battery (in mA or micro-amps).
- Adjust the current dynamically and automatically restore file permissions after use.
- Safe approach to modify charging parameters with built-in permission management.

## Requirements
- **Root Access**: Required to write to the `/sys/class/power_supply/battery/constant_charge_current_max` file.
- **Linux-based OS**: This program is designed for devices running Linux-based systems (e.g., Android with root access, or Linux distributions like Ubuntu).

## Installation

1. **Clone this repository**:
   ```bash
   git clone https://github.com/DX4GREY/set-charge-current.git
   cd set-charge-current
   ```

2. **Build the program using Makefile**:
   ```bash
   make
   ```

3. **Install the program (optional)**:
   You can copy the executable to a global directory like `/usr/local/bin/` for easy access.
   ```bash
   sudo make install
   ```

## Usage

### Set Charging Current:
To set the charging current, run the program with the desired current in milliamps (mA):
```bash
sudo ./setcurrent <current_mA>
```
Example:
```bash
sudo ./setcurrent 2000  # Sets 2A (2000 mA) charging current
```

### Restoring Permissions:
The program will automatically restore the file permissions of `/sys/class/power_supply/battery/constant_charge_current_max` after setting the charging current, so no further action is required.

### Clean Up:
To clean up the compiled files, use the following command:
```bash
make clean
```

## Troubleshooting

- **Permission Issues**: If you get a "Permission Denied" error, ensure that you have root access and the correct permissions set for writing to the sysfs file.
- **Invalid Argument Error**: If the current value is too high or incompatible with your device, the program may fail to write. Try reducing the current or check if your device supports the current value.

## Contributing

Feel free to fork this repository and submit pull requests with improvements, bug fixes, or new features. Contributions are always welcome!

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.