all:
	g++ -I src/include -L src/lib -o build/main src/*.cpp  -lSDL2 -lSDL2_Image