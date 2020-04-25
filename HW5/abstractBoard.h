#ifndef ABSTRACTBOARD_H
#define ABSTRACTBOARD_H

#include<iostream>
using namespace std;

namespace classesOfBoard{
    class AbstractBoard{
        public:
            AbstractBoard(): x(0),y(0),_lastMove('S'),_numberOfMoves(0){}
            int getX() const;
            int getY() const;
            virtual void print()=0;
            virtual void readFromFile(int argc,char **argv,char *fileName,int check)=0;
            virtual void writeToFile()=0;
            virtual void reset()=0;
            virtual void setSize(int xVal,int yVal)=0;
            virtual void move(char c)=0;
            virtual bool isSolved()=0;
            virtual int& operator()(int row, int column)=0;
            virtual bool operator==(const AbstractBoard& rightSide)=0;
            int numberOfBoards() const;
            char lastMove() const;
            int numberOfMoves() const;
            virtual ~AbstractBoard()=0;
        protected:
            int x,y;
            char _lastMove;
            int _numberOfMoves;
            static int _numberOfBoards;
    };
}

#endif
