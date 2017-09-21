OUT = rlcLab
<<<<<<< HEAD
CC = g++
=======
CC = g++ -std=c++11
>>>>>>> composer
CFLAGS = -Wall -Werror -g -Iinclude 
LDFLAGS = 
SOURCES = ./src/*
ARGS = 

all:
	$(CC) $(SOURCES) $(CFLAGS) $(LDFLAGS) -o $(OUT)
clean:
	rm -rfv $(OUT)
<<<<<<< HEAD
run: 
	./${OUT} ${ARGS}
=======

run:
	./${OUT} ${ARGS}

>>>>>>> composer



