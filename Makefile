# Nome do executável
EXEC = run_grafo

# Compilador e flags
CXX = g++
CXXFLAGS = -Wall -g -std=c++11

# Arquivos fonte
SRC = main.cpp

# Arquivos objeto
OBJ = $(SRC:.cpp=.o)

# Regra principal
all: $(EXEC)

# Regra para compilar o executável
$(EXEC): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(EXEC) $(OBJ)

# Regra para compilar arquivos .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Regra para rodar o programa com parâmetros
run: $(EXEC)
	./$(EXEC) grafo.txt 0 3

# Limpa os arquivos objeto e o executável
clean:
	rm -f $(OBJ) $(EXEC)
