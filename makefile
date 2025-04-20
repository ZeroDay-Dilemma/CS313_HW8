CC = gcc
CXX = g++
CFLAGS = -std=c99 -m32 -O0
CXXFLAGS = -O0
VALGRIND = valgrind --leak-check=full --track-origins=yes

C_BIN = c_matrixTools
CPP_BIN = matrixTools

C_SRC = c_matrixTools.c
CPP_SRC = matrixTesterCPP.cpp matrixTools.cpp
HEADERS = matrixTools.h

.PHONY: all clean run_c run_cpp valgrind_c valgrind_cpp

all: $(C_BIN) $(CPP_BIN)

$(C_BIN): $(C_SRC)
	$(CC) $(CFLAGS) $< -o $@

$(CPP_BIN): $(CPP_SRC) $(HEADERS)
	$(CXX) $(CXXFLAGS) $(CPP_SRC) -o $(CPP_BIN)

run_c: $(C_BIN)
	./$(C_BIN)

run_cpp: $(CPP_BIN)
	./$(CPP_BIN)

valgrind_c: $(C_BIN)
	$(VALGRIND) ./$(C_BIN)

# Valgrind C++
valgrind_cpp: $(CPP_BIN)
	$(VALGRIND) ./$(CPP_BIN)

clean:
	rm -f $(C_BIN) $(CPP_BIN)

