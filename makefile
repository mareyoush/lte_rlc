OUT = rlcLab
CC = g++ -std=c++11
CFLAGS = -Wall -Werror -g -Iinclude 
LDFLAGS = 
SOURCES = ./src/*

all:
	$(CC) $(SOURCES) $(CFLAGS) $(LDFLAGS) -o $(OUT)
clean:
	rm -rfv $(OUT)

run:
	./${OUT} ${ARGS}




