OUT = rlcLab
<<<<<<< HEAD
CC = g++ -std=c++11
CFLAGS = -Wall -Werror -g -Iinclude 
=======
CC = g++ 
CFLAGS = -Wall -Werror -g -Iinclude -std=c++11
>>>>>>> 08fa1d6c2ff015660cab7ea41ff7a2f1badfae81
LDFLAGS = 
SOURCES = ./src/*
ARGS = 

all:
	$(CC) $(SOURCES) $(CFLAGS) $(LDFLAGS) -o $(OUT)
clean:
	rm -rfv $(OUT)
run: 
	./${OUT} ${ARGS}



