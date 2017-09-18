OUT = rlcLab
CC = g++
CFLAGS = -Wall -Werror -g -I/include 
LDFLAGS = 
SOURCES = ./src/*

all:
	$(CC) $(SOURCES) $(CFLAGS) $(LDFLAGS) -o $(OUT)
clean:
	rm -rfv $(OUT)




