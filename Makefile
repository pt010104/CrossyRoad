SRCS = $(wildcard src/*.cpp *.cpp)
OBJS = $(SRCS:.cpp=.o)

.PHONY: all run clean

all: CrossyRoad.exe run

run: CrossyRoad.exe
	./CrossyRoad.exe

CrossyRoad.exe: $(OBJS)
	g++ $^ -o $@ -Llib -lsfml-graphics -lsfml-window -lsfml-system

%.o: %.cpp
	g++ -Iinclude -c $< -o $@

clean:
	del *.o *.exe