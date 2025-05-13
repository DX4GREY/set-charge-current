#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

#define SYSFS_PATH "/sys/class/power_supply/battery/constant_charge_current_max"
#define INSTALL_PATH "/usr/local/bin/setcurrent"

void print_help(const char *prog) {
    printf("Usage: %s <current_mA>\n", prog);
    printf("Example: %s 2000    # Set 2000 mA (2A)\n", prog);
    printf("\nOptions:\n");
    printf("  --help, -h        Show this help message\n");
    printf("  --uninstall       Remove this tool from /usr/local/bin\n");
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        print_help(argv[0]);
        return 1;
    }

    if (strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-h") == 0) {
        print_help(argv[0]);
        return 0;
    }

    if (strcmp(argv[1], "--uninstall") == 0) {
        if (remove(INSTALL_PATH) == 0) {
            printf("Uninstalled successfully from %s\n", INSTALL_PATH);
            return 0;
        } else {
            perror("Failed to uninstall");
            return 1;
        }
    }

    int mA = atoi(argv[1]);
    if (mA <= 0) {
        fprintf(stderr, "Invalid input. Please enter a positive current value in mA.\n");
        return 1;
    }

    int uA = mA * 1000;

    // Save original permission
    struct stat st;
    if (stat(SYSFS_PATH, &st) != 0) {
        perror("Failed to stat the sysfs file");
        return 1;
    }
    mode_t original_mode = st.st_mode & 0777;

    // Change permission to allow writing
    if (chmod(SYSFS_PATH, 0666) != 0) {
        perror("Failed to change permission");
        return 1;
    }

    // Open and write to the sysfs file
    FILE *fp = fopen(SYSFS_PATH, "w");
    if (!fp) {
        perror("Failed to open file");
        chmod(SYSFS_PATH, original_mode);
        return 1;
    }

    if (fprintf(fp, "%d", uA) < 0) {
        perror("Failed to write current");
        fclose(fp);
        chmod(SYSFS_PATH, original_mode);
        return 1;
    }

    fclose(fp);

    // Restore original permission
    chmod(SYSFS_PATH, original_mode);

    printf("Charge current set to %d mA (%d uA)\n", mA, uA);
    return 0;
}