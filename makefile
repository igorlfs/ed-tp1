CC = g++

INC = include
SRC = src
OBJ = obj
BIN = bin

EXE = $(BIN)/binary

CFLAGS = -Wall -Wextra -I$(INC) -std=c++17 -g

$(EXE): $(OBJ)/url.o $(OBJ)/main.o
		$(CC) -o $(EXE) $(OBJ)/*.o

$(OBJ)/url.o: $(INC)/url.hpp $(SRC)/url.cpp
		$(CC) $(CFLAGS) -c $(SRC)/url.cpp -o $(OBJ)/url.o

$(OBJ)/main.o: $(INC)/url.hpp $(INC)/cell.hpp $(SRC)/main.cpp
		$(CC) $(CFLAGS) -c $(SRC)/main.cpp -o $(OBJ)/main.o

clean:
	rm -rI $(OBJ)/* $(BIN)/*

