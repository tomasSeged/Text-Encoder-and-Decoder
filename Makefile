# A simple Makefile
# Tomas Hadush Seged G01300111
# CS262, Lab Section 202
# Project 2
#The compiler: gcc for C programs

CC = gcc

CFLAGS=-g -Wall -std=c89 -pedantic-errors
TARGET = project2_tseged_202
LIBS=-lm
$(TARGET): $(TARGET).c
all: project2_tseged_202.c
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c

clean:
	rm $(TARGET)

