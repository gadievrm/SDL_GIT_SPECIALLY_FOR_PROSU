BUILD_DIR = build
SOURCE_DIR = src
INCLUDE_DIR = src/include
LIBRARY_DIR = src/lib
TARGET = $(BUILD_DIR)/main.exe
OBJ = $(addsuffix .o,$(basename $(wildcard $(SOURCE_DIR)/*.cpp))) # All .cpp files in src/ but name ending with .o instead of .cpp
LFLAGS = $(LIBS) # -mwindows ## To disable console
LIBS = -L$(LIBRARY_DIR) -lSDL2 -lSDL2_Image -lSDL2Main
CFLAGS = -I$(INCLUDE_DIR) $(LIBS)

%.o: %.cpp
	g++ $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJ) Makefile
	echo $(OBJ)
	g++ -o $(TARGET) $(SOURCE_DIR)/*.o $(LFLAGS)

clean:
	rm -f $(SOURCE_DIR)/*.o
	rm -f $(TARGET)

run:
	(cd $(dir $(TARGET)); ./$(notdir $(TARGET)))

all: $(TARGET)