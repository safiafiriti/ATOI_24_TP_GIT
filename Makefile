CC=gcc
CFLAGS=-O3 -g
 
TARGET=test
 
all: $(TARGET)
 
libppm.so : ppm.c
    $(CC) $(CFLAGS)  -fpic -shared $^ -o $@
 
test: main.c libppm.so
    $(CC) $(CFLAGS) $(LDFLAGS) -lppm -L. main.c -o $@
 
clean:
    rm -fr $(TARGET) *.so