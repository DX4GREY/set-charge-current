#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <time.h>
#include <stdarg.h>
#include <sys/types.h>
#include <errno.h>

#define SYSFS_PATH "/sys/class/power_supply/battery/constant_charge_current_max"
#define INSTALL_PATH_LINUX "/usr/local/bin/setcurrent"
#define INSTALL_PATH_TERMUX "/data/data/com.termux/files/usr/bin/setcurrent"

// Timestamp helper
void print_timestamp() {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    printf("[%02d:%02d %02d-%02d-%04d] ",
        tm.tm_hour, tm.tm_min,
        tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
}

// printf with timestamp
void tprintf(const char *fmt, ...) {
    print_timestamp();
    va_list args;
    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);
}

// perror with timestamp
void tperror(const char *msg) {
    print_timestamp();
    fprintf(stderr, "%s: %s\n", msg, strerror(errno));
}

void print_help(const char *prog) {
    printf("Usage: %s <current_mA>\n", prog);
    printf("Example: %s 2000    # Set 2000 mA (2A)\n", prog);
    printf("\nOptions:\n");
    printf("  --help, -h        Show this help message\n");
    printf("  --uninstall       Remove this tool from system path\n");
    printf("\nThis is a tool to change the charger current, \nsupports almost all androids.\n");
}

int is_termux() {
    const char *prefix = getenv("PREFIX");
    return (prefix && strstr(prefix, "com.termux"));
}

const char* get_install_path() {
    return is_termux() ? INSTALL_PATH_TERMUX : INSTALL_PATH_LINUX;
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
        const char *path = get_install_path();
        if (remove(path) == 0) {
            tprintf("Uninstalled successfully from %s\n", path);
            return 0;
        } else {
            tperror("Failed to uninstall");
            return 1;
        }
    }

    int mA = atoi(argv[1]);
    if (mA <= 0) {
        tprintf("Invalid input. Please enter a positive current value in mA.\n");
        return 1;
    }

    int uA = mA * 1000;

    // Save original permission
    tprintf("Trying to stat the sysfs file: %s...\n", SYSFS_PATH);
    struct stat st;
    if (stat(SYSFS_PATH, &st) != 0) {
        tperror("Failed to stat the sysfs file");
        return 1;
    }
    tprintf("Success stat the sysfs file\n");

    mode_t original_mode = st.st_mode & 0777;

    // Change permission
    tprintf("Changing sysfs file permission...\n");
    if (chmod(SYSFS_PATH, 0666) != 0) {
        tperror("Failed to change permission");
        return 1;
    }
    tprintf("Success change permission\n");

    // Write to sysfs
    tprintf("Reading sysfs file...\n");
    FILE *fp = fopen(SYSFS_PATH, "w");
    if (!fp) {
        tperror("Failed to open file");
        chmod(SYSFS_PATH, original_mode);
        return 1;
    }

    tprintf("Writing current into sysfs file...\n");
    if (fprintf(fp, "%d", uA) < 0) {
        tperror("Failed to write current");
        fclose(fp);
        chmod(SYSFS_PATH, original_mode);
        return 1;
    }

    fclose(fp);
    chmod(SYSFS_PATH, original_mode);

    tprintf("Charge current set to %d mA (%d uA)\n", mA, uA);
    return 0;
}