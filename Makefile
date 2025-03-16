SRC 	= ./src
DST 	= ./bin
PRODUCT = mem_disk_speedtest
BUFFER = buffers

# Build project
all:	$(PRODUCT)
# Compile and link memtest.o, main.c and disktest.h(auto) by -O3: -p not report error when directory already exist
$(PRODUCT): memtest.o
	mkdir -p $(DST) $(BUFFER)
	c++ -std=c++11 -lpthread -O3 $(SRC)/main.cpp $(SRC)/memtest.o -o $(DST)/$(PRODUCT)
# Compile memtest.c by -O3
memtest.o:
	c++ -std=c++11 -c -O3 $(SRC)/memtest.cpp -o $(SRC)/memtest.o
# disktest.o:
# 	c++ -c -O0 $(SRC)/disktest.cpp -o $(SRC)/disktest.o
# Clean all generated files: -f not report error 
clean:
	rm -f $(SRC)/memtest.o
	rm -rf $(DST)
	rm -rf buffers/
	rm -rf .vscode/