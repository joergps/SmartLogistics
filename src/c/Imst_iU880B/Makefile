# Makefile to build the LoRa sender
# see: http://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/
CC=gcc
CFLAGS=-I.
CXXFLAGS=-std=c++11

lorasender: SerialDevice.o slip.o crc16.o WiMOD_HCI_Layer.o WiMOD_LoRaWAN_API.o main.o
	${CC} -std=c++11 -o LoRaSender SerialDevice.o slip.o crc16.o WiMOD_HCI_Layer.o WiMOD_LoRaWAN_API.o main.o ${CFLAGS}

clean:
	rm *.o LoRaSender LoRaSender.exe
