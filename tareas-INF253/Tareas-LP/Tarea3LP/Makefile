JAVAC = javac
JAVA = java
SRC = $(wildcard *.java) $(wildcard mapa/*.java) $(wildcard entidades/*.java) $(wildcard componentes/*.java)

all:
	$(JAVAC) $(SRC)

run:
	$(JAVA) Main

clean:
	rm -f *.class mapa/*.class entidades/*.class componentes/*.class