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
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

# Clean up file yang dihasilkan
clean:
	rm -f $(TARGET)

# Target untuk menginstal
install: $(TARGET)
	cp $(TARGET) $(INSTALL_PATH)
	@echo "Installed to $(INSTALL_PATH)/$(TARGET)"

# Uninstall
uninstall:
	rm -f $(INSTALL_PATH)/$(TARGET)
	@echo "Uninstalled from $(INSTALL_PATH)/$(TARGET)"

# Untuk menjalankan program setelah build
run: $(TARGET)
	./$(TARGET)

# Menampilkan informasi build
info:
	@echo "Build using: $(CC)"
	@echo "Source file: $(SRC)"
	@echo "Target executable: $(TARGET)"
	@echo "Install path: $(INSTALL_PATH)"

.PHONY: clean install uninstall run info