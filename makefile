makefile:
all:SHA1.o Tool.o ThreadAction.o  UsbStressTester.o
	g++ SHA1.o Tool.o ThreadAction.o UsbStressTester.o -lpthread -o UsbStressTester

sha1:SHA1.cpp
	g++ -c SHA1.cpp -o SHA1.o 

tool:Tool.cpp
	g++ -c Tool.cpp -o Tool.o 

thread:ThreadAction.cpp
	g++ -c ThreadAction.cpp -o ThreadAction.o 

usb:UsbStressTester.cpp
	g++ -c UsbStressTester.cpp -o UsbStressTester.o 