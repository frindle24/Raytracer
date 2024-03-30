OBJ = main.o
INC = -I "./"
# The -I flag is used to specify addition directories to be searched for header files during compilation
# When we use -I followed by a directory path, the compiler will search that directory (and its subdirectories) for header files when they are included in the source code using #include directive

Raytracer: $(OBJ)
	g++ $(OBJ) -o Raytracer
	rm -f $(OBJ)
# Delete object file after compiling the program since they may interfere the next time we compile it

main.o:
	g++ -c main.cpp $(INC)

clean:
	rm -f $(OBJ) Raytracer
