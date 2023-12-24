###############
### FOLDERS ###
###############
SOURCE_DIR  = src
BUILD_DIR   = build
INCLUDE_DIRS = -Iinclude/nlohmann -Iinclude/SDL2 -Iinclude/imgui
LIBRARY_DIR = lib

###############
#### FILES ####
###############
TARGET = final/main.exe
OBJS = $(addprefix $(BUILD_DIR)/,$(notdir $(addsuffix .o,$(basename $(wildcard $(SOURCE_DIR)/*.cpp))))) # src/%.cpp > build/%.o
OBJS += $(addprefix $(BUILD_DIR)/imgui/,$(notdir $(addsuffix .o,$(basename $(wildcard imgui/*.cpp)))))
HEADERS = $(wildcard $(SOURCE_DIR)/*.h)

###############
# COMPILATION #
###############
CPP = g++
LIBS = -L$(LIBRARY_DIR) -lSDL2Main -lSDL2_Mixer -lSDL2_Image -lSDL2
LFLAGS = $(LIBS) # -mwindows ## To disable console
CFLAGS = $(INCLUDE_DIRS)

###############
#### RULES ####
###############	

# src/.cpp -> build/.o  #
$(BUILD_DIR)/%.o: $(SOURCE_DIR)/%.cpp $(HEADERS)
	$(CPP) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/imgui/%.o: imgui/%.cpp $(HEADERS)
	$(CPP) $(CFLAGS) -c $< -o $@

#     Main    #
$(TARGET): $(BUILD_DIR) $(BUILD_DIR)/imgui $(OBJS) Makefile
	$(CPP) -o $(TARGET) $(BUILD_DIR)/*.o $(BUILD_DIR)/imgui/*.o $(LFLAGS)

$(BUILD_DIR):
	mkdir $(BUILD_DIR)

$(BUILD_DIR)/imgui:
	mkdir $(BUILD_DIR)/imgui

################
### COMMANDS ###
################
# Remove temp files
clean:
	rm -rf $(BUILD_DIR)

# Launch
run: $(TARGET)
	(cd $(dir $(TARGET)); ./$(notdir $(TARGET)))

## (Default)
all: $(TARGET)