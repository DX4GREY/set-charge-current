# Nama target executable
TARGET = setcurrent

# Nama file sumber
SRC = set_charge_current.c

# Compiler dan opsi kompilasi
CC = gcc
CFLAGS = -Wall -Wextra

# Path install tergantung OS
ifeq ($(shell uname -o 2>/dev/null),Android)
    INSTALL_PATH = $(HOME)/../usr/bin
else
    INSTALL_PATH = /usr/local/bin
endif

# Proses build
all: $(TARGET)

$(TARGET): $(SRC)
	@echo "  CC      $(SRC)"
	@$(CC) $(CFLAGS) -o $(TARGET) $(SRC)
	@echo "  LD      $(TARGET)"

# Clean up file yang dihasilkan
clean:
	@echo "  CLEAN   $(TARGET)"
	@rm -f $(TARGET)
	@echo "  CLEAN   magisk_module"
	@rm -rf magisk_module
	@echo "  CLEAN   magisk_module.zip"
	@rm -f magisk_module.zip
	@echo "Cleaned up all generated files"

# Target untuk menginstal
install: $(TARGET)
	@echo "  INSTALL $(TARGET) -> $(INSTALL_PATH)"
	@cp $(TARGET) $(INSTALL_PATH)
	@echo "Installed to $(INSTALL_PATH)/$(TARGET)"

# Uninstall
uninstall:
	@echo "  UNINSTALL $(TARGET) from $(INSTALL_PATH)"
	@rm -f $(INSTALL_PATH)/$(TARGET)
	@echo "Uninstalled from $(INSTALL_PATH)/$(TARGET)"

# Untuk menjalankan program setelah build
run: $(TARGET)
	@echo "  RUN      $(TARGET)"
	@./$(TARGET)

# Menampilkan informasi build
info:
	@echo "Build using: $(CC)"
	@echo "Source file: $(SRC)"
	@echo "Target executable: $(TARGET)"
	@echo "Install path: $(INSTALL_PATH)"

# Target untuk membangun Magisk module
magisk_module: $(TARGET)
	@echo "  MKDIR    magisk_module"
	@rm -rf magisk_module
	@cp -r module_template magisk_module
	@mkdir -p magisk_module/system/bin
	@echo "  COPY     $(TARGET) -> magisk_module/system/bin/"
	@cp $(TARGET) magisk_module/system/bin/
	@echo "  CONFIG   module.prop"
	@sed -i 's/{id}/set-charge-current/' magisk_module/module.prop
	@sed -i 's/{name}/Set Charge Current/' magisk_module/module.prop
	@sed -i 's/{version}/1.0/' magisk_module/module.prop
	@sed -i 's/{versionCode}/1/' magisk_module/module.prop
	@sed -i 's/{author}/dx4white/' magisk_module/module.prop
	@sed -i 's/{description}/A Magisk module to set charge current/' magisk_module/module.prop
	@echo "  ZIP      magisk_module -> magisk_module.zip"
	@cd magisk_module && zip -r ../magisk_module.zip . > /dev/null
	@echo "Magisk module built and zipped as magisk_module.zip"

.PHONY: clean install uninstall run info magisk_module