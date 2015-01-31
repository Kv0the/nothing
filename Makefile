CC        := g++


CFLAGS    := -std=c++11 -Wall
LIBS      := -lsfml-audio -lsfml-graphics -lsfml-system -lsfml-window -lBox2D

SOURCES   := $(shell find ./ -maxdepth 1 -name '*.cpp')
INCLUDES  := $(shell find ./ -maxdepth 1 -name '*.h') $(shell find $(IDIR) -name '*.hpp')

OBJ       := $(addprefix ./,$(SOURCES:./%.cpp=%.o))

EXEC      := app

.PHONY: clean run

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $^ -o $@ $(CFLAGS) $(LIBS)

%.o: %.cpp
	$(CC) -c -o $@ $< $(LIBS) $(CFLAGS)

run: all
	./$(EXEC) &

clean:
	rm -f $(EXEC) *.o *~
