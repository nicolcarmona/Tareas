# Compilador y flags
CXX = g++
CXXFLAGS = -Wall -std=c++11

# Nombre del ejecutable
TARGET = Balatro

# Archivo fuente
SRC = main.cpp

# Regla principal
all: $(TARGET)

# Compilar el programa
$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

# Limpiar archivos compilados
clean:
	rm -f $(TARGET)

# Ejecutar el programa
run: $(TARGET)
	./$(TARGET)

# Declarar targets que no son archivos
.PHONY: all clean run
