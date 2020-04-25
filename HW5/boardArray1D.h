#ifndef BOARDARRAY1D_H
#define BOARDARRAY1D_H

#include"abstractBoard.h"
using namespace std;

namespace classesOfBoard{
    class boardArray1D : public AbstractBoard{
        public:
            boardArray1D(int argc,char **argv,char *fileName,int check);
            boardArray1D(int xVal,int yVal);
            boardArray1D(const boardArray1D& rightSide);
            void print();
            void readFromFile(int argc,char **argv,char *fileName,int check);
            void writeToFile();
            void reset();
            void setSize(int xVal,int yVal);
            void move(char c);
            bool isSolved();
            int& operator()(int row, int column);
            bool operator==(const AbstractBoard& rightSide);
            ~boardArray1D();
        private:
            int* boardArr1D;
    };
}

#endif
