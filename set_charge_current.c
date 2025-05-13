#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define PATH "/sys/class/power_supply/battery/constant_charge_current_max"
#define PERMISSION_CMD_SET "chmod 666 /sys/class/power_supply/battery/constant_charge_current_max"
#define PERMISSION_CMD_RESTORE "chmod 444 /sys/class/power_supply/battery/constant_charge_current_max"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <current_mA>\n", argv[0]);
        printf("Example: %s 2000  # for 2A (2000 mA)\n", argv[0]);
        return 1;
    }

    // Konversi miliampere (mA) ke mikroampere (uA)
    int current_mA = atoi(argv[1]);
    int current_uA = current_mA * 1000;  // 1 mA = 1000 uA

    // Set permission agar bisa write
    if (system(PERMISSION_CMD_SET) != 0) {
        perror("Failed to set permissions");
        return 1;
    }

    int fd = open(PATH, O_WRONLY);
    if (fd < 0) {
        perror("Failed to open file");
        // Kembalikan permission jika gagal
        system(PERMISSION_CMD_RESTORE);
        return 1;
    }

    // Tulis nilai current sebagai string
    char buffer[20];
    snprintf(buffer, sizeof(buffer), "%d", current_uA);

    // Menulis nilai ke sysfs (sebagai string)
    if (write(fd, buffer, strlen(buffer)) < 0) {
        perror("Failed to write current");
        close(fd);
        // Kembalikan permission jika gagal
        system(PERMISSION_CMD_RESTORE);
        return 1;
    }

    printf("Charging current set to %d mA (%d uA)\n", current_mA, current_uA);

    close(fd);

    // Kembalikan permission ke semula
    if (system(PERMISSION_CMD_RESTORE) != 0) {
        perror("Failed to restore permissions");
        return 1;
    }

    printf("Permissions restored to read-only.\n");

    return 0;
}