SRCS = $(wildcard src/*.cpp *.cpp)
OBJS = $(SRCS:.cpp=.o)

all: CrossyRoad.exe

CrossyRoad.exe: $(OBJS)
	g++ $^ -o $@ -Llib -lsfml-graphics -lsfml-window -lsfml-system

%.o: %.cpp
	g++ -Iinclude -c $< -o $@

clean:
	del *.o *.exe