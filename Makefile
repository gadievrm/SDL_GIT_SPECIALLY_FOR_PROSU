###############
### FOLDERS ###
###############
SOURCE_DIR  = src
BUILD_DIR   = build
INCLUDE_DIR = include
LIBRARY_DIR = lib

###############
#### FILES ####
###############
TARGET = final/main.exe
OBJS = $(addprefix $(BUILD_DIR)/,$(notdir $(addsuffix .o,$(basename $(wildcard $(SOURCE_DIR)/*.cpp))))) # src/%.cpp > build/%.o
HEADERS = $(wildcard $(SOURCE_DIR)/*.h)

###############
# COMPILATION #
###############
CPP = g++
LIBS = -L$(LIBRARY_DIR) -lSDL2Main -lSDL2_Mixer -lSDL2_Image -lSDL2
LFLAGS = $(LIBS) # -mwindows ## To disable console
CFLAGS = -I$(INCLUDE_DIR) $(LIBS)

###############
#### RULES ####
###############
# .cpp -> .o  #
$(BUILD_DIR)/%.o: $(SOURCE_DIR)/%.cpp $(HEADERS)
	$(CPP) $(CFLAGS) -c $< -o $@

#     Main    #
$(TARGET): $(OBJS) Makefile
	$(CPP) -o $(TARGET) $(BUILD_DIR)/*.o $(LFLAGS)

################
### COMMANDS ###
################
# Remove temp files
clean:
	rm -f $(BUILD_DIR)/*.o
	rm -f $(TARGET)

# Launch
run: $(TARGET)
	(cd $(dir $(TARGET)); ./$(notdir $(TARGET)))

## (Default)
all: $(TARGET)