#ifndef BOARDVECTOR_H
#define BOARDVECTOR_H

#include<vector>
#include"abstractBoard.h"
using namespace std;

namespace classesOfBoard{
    class boardVector : public AbstractBoard{
        public:
            boardVector(int argc,char **argv,char *fileName,int check);
            boardVector(int xVal,int yVal);
            void print();
            void readFromFile(int argc,char **argv,char *fileName,int check);
            void writeToFile();
            void reset();
            void setSize(int xVal,int yVal);
            void move(char c);
            bool isSolved();
            int& operator()(int row, int column);
            bool operator==(const AbstractBoard& rightSide);
        private:
            vector<int>boardVec;
    };
}

#endif
