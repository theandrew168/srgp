# This sample Makefile allows you to make any SRGP application
#   whose source is exactly one .c file.
#
# To use this Makefile, you must type:
#
#        make PROG=xxxx
#                  ----
# where
#       xxxx.c is the name of the file you wish to compile.
#       ----

CC = gcc

GCCFLAGS = -fpcc-struct-return
CFLAGS = -g

INCLUDE = -I../include

LDLIBS =  -lsrgp -lX11
LDFLAGS = -L../lib


$(PROG):
	$(CC) $(GCCFLAGS) $(INCLUDE) $(CFLAGS) $(PROG).c $(LDFLAGS) $(LDLIBS) -o $(PROG)
