output: 171044014.o abstractBoard.o boardVector.o boardArray1D.o boardArray2D.o
	g++ 171044014.o abstractBoard.o boardVector.o boardArray1D.o boardArray2D.o -o output

171044014.o: 171044014.cpp
	g++ -c 171044014.cpp

abstractBoard.o: abstractBoard.cpp abstractBoard.h
	g++ -c abstractBoard.cpp

boardVector.o: boardVector.cpp boardVector.h
	g++ -c boardVector.cpp

boardArray1D.o: boardArray1D.cpp boardArray1D.h
	g++ -c boardArray1D.cpp

boardArray2D.o: boardArray2D.cpp boardArray2D.h
	g++ -c boardArray2D.cpp

target: dependencies
	action

clean:
	rm *.o output