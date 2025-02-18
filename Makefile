CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c99 -I$(INCLUDE_DIR)

LIBRARY_NAME = lib54cligc
SRC_DIR = src
INCLUDE_DIR = include
LIBRARY_FILE = $(LIBRARY_NAME).a
SRC = $(SRC_DIR)/lib54cligc.c $(SRC_DIR)/lib54cligc-widgets.c
OBJ = $(SRC:.c=.o)
INSTALL_DIR = /usr/local
LIB_DIR = $(INSTALL_DIR)/lib
INCLUDE_DIR_INSTALL = $(INSTALL_DIR)/include/$(LIBRARY_NAME)

$(LIBRARY_FILE): $(OBJ)
	$(AR) rcs $@ $^

install: $(LIBRARY_FILE)
	mkdir -p $(LIB_DIR)
	cp $(LIBRARY_FILE) $(LIB_DIR)
	mkdir -p $(INCLUDE_DIR_INSTALL)
	cp $(INCLUDE_DIR)/lib54cligc.h $(INCLUDE_DIR_INSTALL)/
	cp $(INCLUDE_DIR)/lib54cligc-widgets.h $(INCLUDE_DIR_INSTALL)/

clean:
	rm -f $(OBJ)

uninstall:
	rm -f $(LIB_DIR)/$(LIBRARY_FILE)
	rm -rf $(INCLUDE_DIR_INSTALL)

show:
	@echo "Library built: $(LIBRARY_FILE)"

.PHONY: install clean uninstall show