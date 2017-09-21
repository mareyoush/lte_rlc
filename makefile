OUT = rlcLab
CC = g++ 
CFLAGS = -Wall -Werror -g -Iinclude -std=c++11
LDFLAGS = 
SOURCES = ./src/*
ARGS = 

all:
	$(CC) $(SOURCES) $(CFLAGS) $(LDFLAGS) -o $(OUT)
clean:
	rm -rfv $(OUT)
run: 
	./${OUT} ${ARGS}



