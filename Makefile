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
	-del *.o *.exe