output: 171044014.o GTUContainer.o GTUSet.o GTUVector.o
	g++ -g 171044014.o GTUContainer.o GTUSet.o GTUVector.o -o output

171044014.o: 171044014.cpp
	g++ -c -g -std=c++11 171044014.cpp

GTUContainer.o: GTUContainer.cpp GTUContainer.h
	g++ -c -g -std=c++11 GTUContainer.cpp

GTUSet.o: GTUSet.cpp GTUSet.h
	g++ -c -g -std=c++11 GTUSet.cpp

GTUVector.o: GTUVector.cpp GTUVector.h
	g++ -c -g -std=c++11 GTUVector.cpp

target: dependencies
	action

clean:
	rm *.o output
