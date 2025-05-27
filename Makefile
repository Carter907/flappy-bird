build: main.cpp
	mkdir build
	clang++ -g -Wall -Werror main.cpp -o my_game -lraylib -lGL -lpthread -ldl -lrt -lX11 -lm
	mv my_game ./build

debug: clean build
	gdb ./build/my_game

run: clean build
	./build/my_game

clean:
	rm -rf ./build

