CC = g++

INC = include
SRC = src
OBJ = obj
BIN = bin

EXE = $(BIN)/binary

CFLAGS = -Wall -Wextra -I$(INC) -std=c++17 -g

$(EXE): $(OBJ)/memlog.o $(OBJ)/url.o $(OBJ)/linkedlist.o $(OBJ)/linkedqueue.o $(OBJ)/escalonador.o $(OBJ)/main.o
		$(CC) -o $(EXE) $(OBJ)/*.o

$(OBJ)/memlog.o: $(INC)/memlog.hpp $(SRC)/memlog.cpp
		$(CC) $(CFLAGS) -c $(SRC)/memlog.cpp -o $(OBJ)/memlog.o

$(OBJ)/url.o: $(INC)/url.hpp $(SRC)/url.cpp
		$(CC) $(CFLAGS) -c $(SRC)/url.cpp -o $(OBJ)/url.o

$(OBJ)/linkedlist.o: $(INC)/msgassert.hpp $(INC)/cell.hpp $(INC)/url.hpp $(INC)/linearlist.hpp $(INC)/linkedlist.hpp $(SRC)/linkedlist.cpp
		$(CC) $(CFLAGS) -c $(SRC)/linkedlist.cpp -o $(OBJ)/linkedlist.o

$(OBJ)/linkedqueue.o: $(INC)/msgassert.hpp $(INC)/linearlist.hpp $(INC)/site.hpp $(INC)/linkedqueue.hpp $(SRC)/linkedqueue.cpp
		$(CC) $(CFLAGS) -c $(SRC)/linkedqueue.cpp -o $(OBJ)/linkedqueue.o

$(OBJ)/escalonador.o: $(INC)/msgassert.hpp $(INC)/linkedqueue.hpp $(INC)/escalonador.hpp $(SRC)/escalonador.cpp
		$(CC) $(CFLAGS) -c $(SRC)/escalonador.cpp -o $(OBJ)/escalonador.o

$(OBJ)/main.o: $(INC)/msgassert.hpp $(INC)/escalonador.hpp $(SRC)/main.cpp
		$(CC) $(CFLAGS) -c $(SRC)/main.cpp -o $(OBJ)/main.o

clean:
	rm -rI $(OBJ)/* $(BIN)/*
