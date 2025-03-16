SRC 	= ./src
DST 	= ./bin
PRODUCT = mem_disk_speedtest

# Build project
all:	$(PRODUCT)
# Compile and link memtest.o, main.c and disktest.h(auto) by -O3
$(PRODUCT): memtest.o
	mkdir $(DST)
	c++ -lpthread -O3 $(SRC)/main.c $(SRC)/memtest.o -o $(DST)/$(PRODUCT)
# Compile memtest.c by -O3
memtest.o:
	c++ -c -O3 $(SRC)/memtest.cpp -o $(SRC)/memtest.o
# Clean all generated files: -f not report error 
clean:
	rm -f $(SRC)/memtest.o
	rm -rf $(DST)
	rm -f buffer.txt buffertarget.txt