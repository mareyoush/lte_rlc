OUT = rlcLab
CC = g++
CFLAGS = -Wall -Werror -g -Iinclude 
LDFLAGS = 
SOURCES = ./src/*

all:
	$(CC) $(SOURCES) $(CFLAGS) $(LDFLAGS) -o $(OUT)
clean:
	rm -rfv $(OUT)




