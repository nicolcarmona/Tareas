# Compilador y flags
CC = gcc
CFLAGS = -std=c11 -Wall

# Nombre del ejecutable
TARGET = destronado

# Regla principal
all: $(TARGET)

# Compilar el programa
destronado: main.o tablero.o piezas.o armas.o
	$(CC) $(CFLAGS) main.o tablero.o piezas.o armas.o -o destronado

main.o: main.c main.h
	$(CC) $(CFLAGS) -c main.c

tablero.o: tablero.c tablero.h
	$(CC) $(CFLAGS) -c tablero.c

piezas.o: piezas.c piezas.h
	$(CC) $(CFLAGS) -c piezas.c

armas.o: armas.c armas.h
	$(CC) $(CFLAGS) -c armas.c

# Limpiar archivos compilados
clean:
	rm -f *.o destronado

# Ejecutar el programa
run: $(TARGET)
	./$(TARGET)

# Declarar targets que no son archivos
.PHONY: all clean run