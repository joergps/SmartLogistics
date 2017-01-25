# Makefile to build the LoRa sender
# see: http://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/
CC=gcc
CFLAGS=-I.

lorasender: crc16.o WiMOD_HCI_Layer.o WiMOD_LoRaWAN_API.o main.o
	${CC} -o LoRaSender crc16.o WiMOD_HCI_Layer.o WiMOD_LoRaWAN_API.o main.o ${CFLAGS}

