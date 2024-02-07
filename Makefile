SRC 	= ./src
DST 	= ./bin
PRODUCT = mem_disk_speedtest

# Build project
all:	$(PRODUCT)
# Compile and link memtest.o, main.c and disktest.h(auto) by -O3
$(PRODUCT): memtest.o
	mkdir $(DST)
	cc -O3 $(SRC)/main.c $(SRC)/memtest.o $(SRC)/memread.o -o $(DST)/$(PRODUCT)
# Compile memtest.c by -O0
memtest.o: memread.o
	cc -c -O0 $(SRC)/memtest.c -o $(SRC)/memtest.o
memread.o:
	cc -c -O0 $(SRC)/memread.c -o $(SRC)/memread.o
# Clean all generated files
clean:
	rm $(SRC)/memtest.o $(SRC)/memread.o
	rm -rf $(DST)
