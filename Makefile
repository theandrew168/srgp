.POSIX:
.SUFFIXES:

AR      = ar
CC      = cc
CFLAGS  = -std=c99 -fPIC -Isrc/
CFLAGS += -Wall -Wextra -Wpedantic
CFLAGS += -g -Og -march=native -mtune=native
CFLAGS += -DX11
LDLIBS  = -lX11

sources =             \
  src/geom.c          \
  src/srgp_attrib.c   \
  src/srgp_canvas.c   \
  src/srgp_color_X.c  \
  src/srgp_cursor.c   \
  src/srgp_echo_X.c   \
  src/srgp_error.c    \
  src/srgp_font.c     \
  src/srgp_input.c    \
  src/srgp_input_X.c  \
  src/srgp_inquire.c  \
  src/srgp_marker.c   \
  src/srgp_output.c   \
  src/srgp_pattern.c  \
  src/srgp_raster.c   \
  src/srgp_state.c    \
  src/srgp_state_X.c
objects = $(sources:.c=.o)
examples =              \
  show_patterns         \
  testcolor_and_resize
#  testeditkeyboard      \
#  test_keyboard         \
#  test_locator          \
#  testmodifiers         \
#  testpaint             \
#  testpixmap            \
#  testrubber            \
#  testtimestamp         \
#  X_demo_anim

all: libsrgp.a libsrgp.so $(examples)
libsrgp.a: $(objects)
	$(AR) rcs $@ $(objects)
libsrgp.so: $(objects)
	$(CC) -shared -o $@ $(objects) $(LDLIBS)

src/geom.o: src/geom.c
src/srgp_attrib.o: src/srgp_attrib.c
src/srgp_canvas.o: src/srgp_canvas.c
src/srgp_color_X.o: src/srgp_color_X.c
src/srgp_cursor.o: src/srgp_cursor.c
src/srgp_echo_X.o: src/srgp_echo_X.c
src/srgp_error.o: src/srgp_error.c
src/srgp_font.o: src/srgp_font.c
src/srgp_input.o: src/srgp_input.c
src/srgp_input_X.o: src/srgp_input_X.c
src/srgp_inquire.o: src/srgp_inquire.c
src/srgp_marker.o: src/srgp_marker.c
src/srgp_output.o: src/srgp_output.c
src/srgp_pattern.o: src/srgp_pattern.c
src/srgp_raster.o: src/srgp_raster.c
src/srgp_state.o: src/srgp_state.c
src/srgp_state_X.o: src/srgp_state_X.c

.SUFFIXES: .c .o
.c.o:
	$(CC) $(CFLAGS) -c -o $@ $<

show_patterns: examples/show_patterns.c libsrgp.a
	$(CC) $(CFLAGS) -o $@ examples/show_patterns.c libsrgp.a $(LDLIBS)

testcolor_and_resize: examples/testcolor_and_resize.c libsrgp.a
	$(CC) $(CFLAGS) -o $@ examples/testcolor_and_resize.c libsrgp.a $(LDLIBS)

.PHONY: clean
clean:
	rm -f libsrgp.a libsrgp.so $(objects) $(examples)
