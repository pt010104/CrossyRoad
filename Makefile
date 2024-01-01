SRCS = $(wildcard src/*.cpp *.cpp)
OBJS = $(SRCS:.cpp=.o)

.PHONY: all run clean

all: CrossyRoad.exe run

run: CrossyRoad.exe
	./CrossyRoad.exe

CrossyRoad.exe: $(OBJS)
	g++ -g $^ -o $@ -Llib -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-system 

%.o: %.cpp
	g++ -g -Iinclude -c $< -o $@

clean:
	del /Q *.exe 2>NUL
	del /Q *.o 2>NUL
	del /Q src\*.o 2>NUL