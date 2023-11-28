BUILD_DIR = build
SOURCE_DIR = src
TARGET_NAME = main.exe
TARGET_DIR = $(BUILD_DIR)
TARGET = $(TARGET_DIR)/$(TARGET_NAME)
OBJ = $(addprefix $(SOURCE_DIR)/,main.o Entity.o Graphics.o Player.o)
LFLAGS = $(LIBS)
LIBS = -Lsrc/lib -lSDL2 -lSDL2_Image -lSDL2Main
CFLAGS = -Isrc/include $(LIBS)

%.o: %.cpp
	g++ $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJ) Makefile
	g++ -o $(TARGET) $(SOURCE_DIR)/*.o $(LFLAGS)

clean:
	rm -f src/*.o
	rm -f $(TARGET)

run:
	(cd $(TARGET_DIR); ./$(TARGET_NAME))

all: $(TARGET)