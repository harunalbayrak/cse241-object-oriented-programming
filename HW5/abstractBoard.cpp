#include"abstractBoard.h"


namespace classesOfBoard{
    int AbstractBoard::_numberOfBoards = 0;
    int AbstractBoard::numberOfBoards() const{
        return _numberOfBoards;
    }
    int AbstractBoard::getX() const{
        return x;
    }
    int AbstractBoard::getY() const{
        return y;
    }
    char AbstractBoard::lastMove() const{
        return _numberOfBoards;
    }
    int AbstractBoard::numberOfMoves() const{
        return _numberOfMoves;
    }
    AbstractBoard::~AbstractBoard(){
        cout << "hey";
    }
}