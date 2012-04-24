all:
	@g++ *.cpp -o curves -lGL -lGLU -L lib/libglfw.a lib/libopengl32.a -I include/ -ldl -lglfw

clean:
	@rm -Rf *.o curves *.*~
