# Declaration of variables
CC = g++
CC_FLAGS = -w
L_FLAGS = -lsfml-graphics -lsfml-window -lsfml-system 

# File names
EXEC = Pendul
SOURCES = $(wildcard *.cpp)
OBJECTS = $(SOURCES:.cpp=.o)
 
# Main target
$(EXEC): $(OBJECTS)
	$(CC) $(OBJECTS) $(L_FLAGS) -o $(EXEC)
 
# To obtain object files
%.o: %.cpp
	$(CC) -c $(CC_FLAGS) $< -o $@
 
# To remove generated files
clean:
	rm -f $(EXEC) $(OBJECTS)