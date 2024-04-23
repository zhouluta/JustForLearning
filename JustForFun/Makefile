objects = main.o rect.o shape.o
CXX = g++

a : $(objects)
	$(CXX) -o a $(objects)

main.o : main.cpp rect.h shape.h
rect.o : rect.cpp rect.h
shape.o : shape.cpp shape.h

.PHONY : clean
clean :
	-rm a $(objects)