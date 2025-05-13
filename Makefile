# Nama target executable
TARGET = setcurrent

# Nama file sumber
SRC = set_charge_current.c

# Compiler dan opsi kompilasi
CC = gcc
CFLAGS = -Wall -Wextra

# Proses build
all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

# Clean up file yang dihasilkan
clean:
	rm -f $(TARGET)

# Target untuk menginstal (misalnya ke direktori /usr/local/bin)
install: $(TARGET)
	cp $(TARGET) /usr/local/bin/

# Untuk menjalankan program setelah build
run: $(TARGET)
	./$(TARGET)

# Menampilkan informasi build
info:
	@echo "Build using: $(CC)"
	@echo "Source file: $(SRC)"
	@echo "Target executable: $(TARGET)"

.PHONY: clean install run info