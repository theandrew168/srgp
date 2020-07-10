# Request POSIX Make behavior and disable any default suffix-based rules
.POSIX:
.SUFFIXES:


# Declare compiler tools and flags
AR      = ar
CC      = cc
CFLAGS  = -std=c99 -D_POSIX_C_SOURCE=200809L
CFLAGS += -fPIC -g -Og
CFLAGS += -Wall -Wextra -Wpedantic
CFLAGS += -Wno-unused-parameter
CFLAGS += -Isrc/
LDFLAGS =
LDLIBS  = -lX11


# Declare which targets should be built by default
default: srgp
all: libsrgp.a libsrgp.so srgp


# Declare static / shared library sources
libsrgp_sources = src/srgp.c
libsrgp_objects = $(libsrgp_sources:.c=.o)

# Express dependencies between object and source files
src/srgp.o: src/srgp.c src/srgp.h

# Build the static library
libsrgp.a: $(libsrgp_objects)
	@echo "STATIC  $@"
	@$(AR) rcs $@ $(libsrgp_objects)

# Build the shared library
libsrgp.so: $(libsrgp_objects)
	@echo "SHARED  $@"
	@$(CC) $(LDFLAGS) -shared -o $@ $(libsrgp_objects) $(LDLIBS)


# Build the main binary
srgp: src/main.c libsrgp.a
	@echo "EXE     $@"
	@$(CC) $(CFLAGS) $(LDFLAGS) -o $@ src/main.c libsrgp.a $(LDLIBS)


# Helper target that cleans up build artifacts
.PHONY: clean
clean:
	rm -fr srgp *.a *.so src/*.o


# Default rule for compiling .c files to .o object files
.SUFFIXES: .c .o
.c.o:
	@echo "CC      $@"
	@$(CC) $(CFLAGS) -c -o $@ $<
