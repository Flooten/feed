CCC = g++
CCFLAGS = -std=c++11 -W -Wall -Wextra -pedantic
LDFLAGS =

SOURCES = $(wildcard *.cpp)
OBJECTS = $(SOURCES:.cpp=.o)

EXEC = feed

all: $(EXEC)

#release: CCFLAGS += -O2
#release: $(EXEC)

#debug: CCFLAGS += -g -DDEBUG
#debug: $(EXEC)

$(EXEC): $(OBJECTS)
	$(CCC) $(OBJECTS) $(LDFLAGS) -o $(EXEC)
    
%.o: %.cpp
	$(CCC) -c $(CCFLAGS) $< -o $@

clean:
	rm -f $(OBJECTS)
	
zap:
	rm -f $(EXEC) $(OBJECTS)