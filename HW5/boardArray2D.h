#ifndef BOARDARRAY2D_H
#define BOARDARRAY2D_H

#include"abstractBoard.h"
using namespace std;

namespace classesOfBoard{
    class boardArray2D : public AbstractBoard{
        public:
            boardArray2D(int argc,char **argv,char *fileName,int check);
            boardArray2D(int xVal,int yVal);
            boardArray2D(const boardArray2D& rightSide);
            void print();
            void readFromFile(int argc,char **argv,char *fileName,int check);
            void writeToFile();
            void syncAll();
            void reset();
            void setSize(int xVal,int yVal);
            void move(char c);
            bool isSolved();
            int& operator()(int row, int column);
            bool operator==(const AbstractBoard& rightSide);
            ~boardArray2D();
        private:
            int** boardArr2D;
    };
}

#endif
