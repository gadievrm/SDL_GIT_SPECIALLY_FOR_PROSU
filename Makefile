TARGET = build/main.exe

SOURCE_DIR  = src
INCLUDE_DIR = src/include
LIBRARY_DIR = src/lib

LIBS = -L$(LIBRARY_DIR) -lSDL2Main -lSDL2_Mixer -lSDL2_Image -lSDL2
LFLAGS = $(LIBS) # -mwindows ## To disable console
CFLAGS = -I$(INCLUDE_DIR) $(LIBS)


OBJ = $(addsuffix .o,$(basename $(wildcard $(SOURCE_DIR)/*.cpp))) # All .cpp files in src/ but name ending with .o instead of .cpp

#### File conversion rules ####
## .cpp -> .o
%.o: %.cpp
	g++ $(CFLAGS) -c $< -o $@

#### Main ####
$(TARGET): $(OBJ) Makefile
	echo $(OBJ)
	g++ -o $(TARGET) $(SOURCE_DIR)/*.o $(LFLAGS)


##### Commands ####
## Remove all temporary build files
clean:
	rm -f $(SOURCE_DIR)/*.o
	rm -f $(TARGET)

## Start the program
run: $(TARGET)
	(cd $(dir $(TARGET)); ./$(notdir $(TARGET)))

## (Default)
all: $(TARGET)