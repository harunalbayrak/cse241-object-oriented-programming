/* Gebze Technical University         */
/* Computer Engineering               */
/* Name Surname : Harun ALBAYRAK      */
/* Student Number : 171044014         */
#include<iostream>
#include<ctime>
#include<cstdlib>
#include<string>
#include<fstream>

using namespace std;

void createBoard(int board[][9],int &x,int &y,int &blank_x,int &blank_y); // Creates a random board
void take_y(char *fileName,int &y);  // Finds the number of columns.
void takeBoardTheFile(int board[][9],int &x,int &y,int &blank_x, int &blank_y); // Retrieves the board from the file.
void showBoard(int board[][9],int x,int y,int blank_x,int blank_y); // Prints the board.
void action(int board[][9],int &x,int &y,int &blank_x,int &blank_y,int &previousOne,int &numberOfMoves); // Takes action according to the entered letter.
void saveTheBoardTheFile(int board[][9],int x,int y,int blank_x,int blank_y); // Saves the board to file. 
void solvedTable(int board[][9],int x,int y,int &blank_x,int &blank_y); // Solves the board.
void shuffle(int board[][9],int x,int y,int &blank_x,int &blank_y); // Shuffling.
void gameCycle(int board[][9],int &x,int &y,int &blank_x,int &blank_y,int &previousOne,int &numberOfMoves); // It is game cycle function.
void newIntelligentAlgorithm(int board[][9],int x,int y,int &blank_x,int &blank_y,int &previousOne); // Intelligent algorithm to solve the board.
inline void solveTheProblem(int board[][9],int x,int y,int &blank_x,int &blank_y,int &previousOne); // Tries to solve the problem.
void howManyMoves(int board[][9],int x,int y,int &blank_x,int &blank_y,int &previousOne,int &numberOfMoves); // Tells how many moves have been done.

int main(){
    int board[9][9]={};
    int x=0,y=0,blank_x=0,blank_y=0,previousOne=-1,numberOfMoves=0;
    srand(time(NULL));

    createBoard(board,x,y,blank_x,blank_y);

    gameCycle(board,x,y,blank_x,blank_y,previousOne,numberOfMoves);

    return 0;
}


void createBoard(int board[][9],int &x,int &y,int &blank_x,int &blank_y){ // Creates a random board
    int boardSize=0,k=1,randomNum=0,randomNum2=0;
    cout << "Please enter the board size: "; // Takes the board size.
    do{
        cin >> boardSize;
        if(boardSize < 3 || boardSize > 9)
            cout << "Wrong Input. Try Again..." << endl;
    }while(boardSize < 3 || boardSize > 9);
    x=boardSize;
    y=boardSize;

    for(int i=0;i<boardSize;i++){
        for(int j=0;j<boardSize;j++){
            board[i][j] = k;
            k++;
        }
    } 
    blank_x = boardSize-1; 
    blank_y = boardSize-1;

    randomNum = (rand() % 300) + 200;
    // Sıralı bir board oluşturduktan sonra karıştırmak için 300 ile 500 arasında hamle yapar.
    while(randomNum != 0){
        randomNum2 = rand() % 4;
        if(randomNum2 == 0 && !(blank_y != 0 && board[blank_x][blank_y-1] != 0))
            continue;
        else if(randomNum2 == 1 && !(blank_y != y-1 && board[blank_x][blank_y+1] != 0))
            continue;
        else if(randomNum2 == 2 && !(blank_x != 0 && board[blank_x-1][blank_y] != 0))
            continue;
        else if(randomNum2 == 3 && !(blank_x != x-1 && board[blank_x+1][blank_y] != 0))
            continue;

        switch(randomNum2){
            case 0:
                board[blank_x][blank_y] = board[blank_x][blank_y-1];
                blank_y--;
                break;
            case 1:
                board[blank_x][blank_y] = board[blank_x][blank_y+1];
                blank_y++;
                break;
            case 2:
                board[blank_x][blank_y] = board[blank_x-1][blank_y];
                blank_x--;
                break;
            case 3:
                board[blank_x][blank_y] = board[blank_x+1][blank_y];
                blank_x++;
                break;
        }

        randomNum--;
    }
}

void take_y(char *fileName,int &y){ // Gets the number of columns
    string mystr;
    ifstream myfile;
    myfile.open(fileName,ios::in);

    if( getline( myfile, mystr)) 
        y = mystr.size();
    
    y= y/3 + 1;
    myfile.close();
}

void takeBoardTheFile(int board[][9],int &x,int &y,int &blank_x, int &blank_y){
    int i=0,j=-1,k=0,l=0,control=0;
    char fileName[30];
    char bb[2];
    ifstream myfile;

    cout << "Enter the name of the file: ";
    cin >> fileName;
    
    myfile.open(fileName,ios::in);

    take_y(fileName,y);

    while (myfile >> bb) {  
        if(j == y-1){
            ++i;
            j=0;
            control = 0;
        }else{
            j++;
            control = 1;
        }
        board[i][j] = atoi(bb);
        if(bb[0] == 'b' && bb[1] == 'b'){
            blank_x = i;
            blank_y = j;
        }
    } 
    // Dosyayı açar ve arrayin içini dosyadakiler ile doldurur.  
    x = i+1;
    y = j+1;
    myfile.close();

}

void showBoard(int board[][9],int x,int y,int blank_x,int blank_y){
    // Boardı bastırır.
    for(int i=0;i<x;i++){
        for(int j=0;j<y;j++){
            if(i == blank_x && j == blank_y)
                cout << "  " << " ";
            else if(board[i][j] >= 0 && board[i][j] < 10)
                cout << "0" << board[i][j] << " ";
            else
                cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

void action(int board[][9],int &x,int &y,int &blank_x,int &blank_y,int &previousOne,int &numberOfMoves){
    char input;
    cout << "Your Move: ";
    cin >> input;

    switch(input){
        case 'l':
        case 'L': // Sol tarafta boşluk var ise sol tarafa hareket eder.
            if(blank_y != 0 && board[blank_x][blank_y-1] != 0){
                board[blank_x][blank_y] = board[blank_x][blank_y-1];
                blank_y--;
            }else{
                cout << "There is no room on the left side" << endl;
            }
            break;
        case 'r':
        case 'R': // Sağ tarafta boşluk var ise sol tarafa hareket eder.
            if(blank_y != y-1 && board[blank_x][blank_y+1] != 0){
                board[blank_x][blank_y] = board[blank_x][blank_y+1];
                blank_y++;
            }else{
                cout << "There is no room on the right side" << endl;
            }
            break;
        case 'u':
        case 'U': // Yukarda boşluk var ise sol tarafa hareket eder.
            if(blank_x != 0 && board[blank_x-1][blank_y] != 0){
                board[blank_x][blank_y] = board[blank_x-1][blank_y];
                blank_x--;
            }else{
                cout << "There is no room upstairs" << endl;
            }
            break;
        case 'd':
        case 'D': // Aşağıda boşluk var ise sol tarafa hareket eder.
            if(blank_x != x-1 && board[blank_x+1][blank_y] != 0){
                board[blank_x][blank_y] = board[blank_x+1][blank_y];
                blank_x++;
            }else{
                cout << "There is no room downstairs" << endl;
            }
            break;
        case 'i':
        case 'I': // Yapay zekaya göre hareket eder.
            newIntelligentAlgorithm(board,x,y,blank_x,blank_y,previousOne);
            break;
        case 'v':
        case 'V': // Problemi çözmeye çalışır.
            solveTheProblem(board,x,y,blank_x,blank_y,previousOne);
            break;
        case 't':
        case 'T': // Şu ana kadar kaç hamle yapıldığını gösterir.
            howManyMoves(board,x,y,blank_x,blank_y,previousOne,numberOfMoves);
            break;
        case 'e':
        case 'E': // Boardı dosyaya kaydeder.
            saveTheBoardTheFile(board,x,y,blank_x,blank_y);
            break;
        case 'y':
        case 'Y': // Dosyadan board alır.
            takeBoardTheFile(board,x,y,blank_x,blank_y);
            break;
        case 's':
        case 'S': // Karıştırır.
            shuffle(board,x,y,blank_x,blank_y);
            break;
        case 'q':
        case 'Q': // Çıkar.
        	cout << "Exiting..." << endl;
        	exit(1);
        default :
        	cout << "Wrong Input. Try Again..." << endl;
    }
}

void saveTheBoardTheFile(int board[][9],int x,int y,int blank_x,int blank_y){
    ofstream myfile;
    char fileName[50];

    cout << "Enter the name of the file: ";
    cin >> fileName;

    myfile.open(fileName);

    for(int i=0;i<x;i++){
        for(int j=0;j<y;j++){
            if(i == blank_x && j == blank_y)
                myfile << "bb" << " ";
            else if(board[i][j] >= 0 && board[i][j] < 10)
                myfile << "0" << board[i][j] << " ";
            else
                myfile << board[i][j] << " ";
        }
        myfile << endl;
    }

    cout << fileName << " was created. " << endl;

    myfile.close();
}

void solvedTable(int board[][9],int x,int y,int &blank_x,int &blank_y){
    int k=1;
    board[blank_x][blank_y] = 1;
    blank_x = x-1;
    blank_y = y-1;
    for(int i=0;i<x;i++){
        for(int j=0;j<y;j++){
            if(board[i][j] != 0){
                board[i][j] = k;
                k++;
            }
        }
    }
}

void gameCycle(int board[][9],int &x,int &y,int &blank_x,int &blank_y,int &previousOne,int &numberOfMoves){
    int solvedBoard[9][9] = {};
    int solved_blank_x=blank_x,solved_blank_y=blank_y,control=1;

    
    showBoard(board,x,y,blank_x,blank_y);
    cout << endl;
    do{
        for(int i=0;i<x;i++){
            for(int j=0;j<y;j++){
                solvedBoard[i][j] = board[i][j];
            }
        }
        solvedTable(solvedBoard,x,y,solved_blank_x,solved_blank_y);
        numberOfMoves++;
        action(board,x,y,blank_x,blank_y,previousOne,numberOfMoves);
        showBoard(board,x,y,blank_x,blank_y);
        for(int i=0;i<x;i++){
            for(int j=0;j<y;j++){
                if(i == blank_x && j == blank_y && i==solved_blank_x && j == solved_blank_y){
                    control=0;
                }else if(board[i][j] == solvedBoard[i][j]){
                    control=0;
                }else if(board[i][j] != solvedBoard[i][j]){
                    control=1;
                    break;
                }
            }
        }
        
    }while(control);

    if(control == 0){
        cout << "You won the game in " << numberOfMoves << " moves !!!" << endl;
    }

}

void shuffle(int board[][9],int x,int y,int &blank_x,int &blank_y){
    const int x_times_y = x*y;
    int numberOfMoves=x_times_y,randomNumber=0,control=1,randomNum=0;

    solvedTable(board,x,y,blank_x,blank_y);

    while(numberOfMoves != 0){
        randomNum = rand() % 4;
        if(randomNum == 0 && !(blank_y != 0 && board[blank_x][blank_y-1] != 0))
            continue;
        else if(randomNum == 1 && !(blank_y != y-1 && board[blank_x][blank_y+1] != 0))
            continue;
        else if(randomNum == 2 && !(blank_x != 0 && board[blank_x-1][blank_y] != 0))
            continue;
        else if(randomNum == 3 && !(blank_x != x-1 && board[blank_x+1][blank_y] != 0))
            continue;

        switch(randomNum){
            case 0:
                board[blank_x][blank_y] = board[blank_x][blank_y-1];
                blank_y--;
                break;
            case 1:
                board[blank_x][blank_y] = board[blank_x][blank_y+1];
                blank_y++;
                break;
            case 2:
                board[blank_x][blank_y] = board[blank_x-1][blank_y];
                blank_x--;
                break;
            case 3:
                board[blank_x][blank_y] = board[blank_x+1][blank_y];
                blank_x++;
                break;
        }

        numberOfMoves--;
    }


}

void newIntelligentAlgorithm(int board[][9],int x,int y,int &blank_x,int &blank_y,int &previousOne){
    int x_y_positions[4][2] = {};
    int solvedBoard[9][9] = {};
    int oldDif[4]={},newDif[4]={},oldMinusNew[4]={},control[4]={};
    int solved_blank_x=blank_x,solved_blank_y=blank_y,i=0,direction=0,_control=1,_control2=1,lessThanZero=0;
    int currentNumber=0,maximumPositivity=0,howMany=0,k=0,randomNumber=0;

    for(int i=0;i<x;i++){
        for(int j=0;j<y;j++){
            solvedBoard[i][j] = board[i][j];
        }
    }

    solvedTable(solvedBoard,x,y,solved_blank_x,solved_blank_y);

    if(blank_y != 0 && board[blank_x][blank_y-1] != 0){
        currentNumber = board[blank_x][blank_y-1];
        for(int i=0;i<x;i++){
            for(int j=0;j<y;j++){
                if(currentNumber == solvedBoard[i][j]){
                    x_y_positions[0][0] = i;
                    x_y_positions[0][1] = j;
                }
            }
        }
        oldDif[0] = abs(x_y_positions[0][0]-blank_x) + abs(x_y_positions[0][1]-blank_y-1); 
        newDif[0] = abs(x_y_positions[0][0]-blank_x) + abs(x_y_positions[0][1]-blank_y); 
        oldMinusNew[0] = newDif[0] - oldDif[0];
        control[0] = 1;
    }
    if(blank_y != y-1 && board[blank_x][blank_y+1] != 0){
        currentNumber = board[blank_x][blank_y+1];
        for(int i=0;i<x;i++){
            for(int j=0;j<y;j++){
                if(currentNumber == solvedBoard[i][j]){
                    x_y_positions[1][0] = i;
                    x_y_positions[1][1] = j;
                }
            }
        }
        oldDif[1] = abs(x_y_positions[1][0]-blank_x) + abs(x_y_positions[1][1]-blank_y+1); 
        newDif[1] = abs(x_y_positions[1][0]-blank_x) + abs(x_y_positions[1][1]-blank_y);
        oldMinusNew[1] = newDif[1] - oldDif[1];
        control[1] = 1;
    }
    if(blank_x != 0 && board[blank_x-1][blank_y] != 0){
        currentNumber = board[blank_x-1][blank_y];
        for(int i=0;i<x;i++){
            for(int j=0;j<y;j++){
                if(currentNumber == solvedBoard[i][j]){
                    x_y_positions[2][0] = i;
                    x_y_positions[2][1] = j;
                }
            }
        }
        oldDif[2] = abs(x_y_positions[2][0]-blank_x-1) + abs(x_y_positions[2][1]-blank_y); 
        newDif[2] = abs(x_y_positions[2][0]-blank_x) + abs(x_y_positions[2][1]-blank_y); 
        oldMinusNew[2] = newDif[2] - oldDif[2];
        control[2] = 1;
    }
    if(blank_x != x-1 && board[blank_x+1][blank_y] != 0){
        currentNumber = board[blank_x+1][blank_y];
        for(int i=0;i<x;i++){
            for(int j=0;j<y;j++){
                if(currentNumber == solvedBoard[i][j]){
                    x_y_positions[3][0] = i;
                    x_y_positions[3][1] = j;
                }
            }
        }
        oldDif[3] = abs(x_y_positions[3][0]-blank_x+1) + abs(x_y_positions[3][1]-blank_y); 
        newDif[3] = abs(x_y_positions[3][0]-blank_x) + abs(x_y_positions[3][1]-blank_y); 
        oldMinusNew[3] = newDif[3] - oldDif[3];
        control[3] = 1;
    }

    for(int i=0;i<4;i++)
        if(control[i] == 0)
            oldMinusNew[i] = -2;

    for(i=0;i<4;i++){
        if(oldMinusNew[i] > 0)
            howMany++;
        else if(oldMinusNew[i] == -2)
            lessThanZero++;
    }
    
    do{
        randomNumber = rand() % 4;
        if(oldMinusNew[randomNumber] < 0 && howMany>0)
            _control = 1;
        else if(oldMinusNew[randomNumber] < 0 && howMany==0 && lessThanZero==0)
            _control=0;
        else if(oldMinusNew[randomNumber] < 0 && howMany==0 && lessThanZero>0){
            if(oldMinusNew[randomNumber] == -2)
                _control = 1;
            else
                _control = 0;
        }
        else
            _control = 0;

        if(previousOne = -1){
            do{
                randomNumber = rand() % 4;
                if(oldMinusNew[randomNumber] == -2)
                    _control2=1;
                else
                    _control2=0;
            }while(_control2);
            _control = 0;
        } 
        else if(previousOne == 0 && oldMinusNew[randomNumber] == 1){
            do{
                randomNumber = rand() % 4;
                if(oldMinusNew[randomNumber] != -2)
                    _control2=0;
                else if(oldMinusNew[randomNumber] == 1)
                    _control2=1;
                else
                    _control2=1;
            }while(_control2);
        }
        else if(previousOne == 1 && oldMinusNew[randomNumber] == 0){
            do{
                randomNumber = rand() % 4;
                if(oldMinusNew[randomNumber] != -2)
                    _control2=0;
                else if(oldMinusNew[randomNumber] == 0)
                    _control2=1;
                else
                    _control2=1;
            }while(_control2);
        }
        else if(previousOne == 2 && oldMinusNew[randomNumber] == 3){
            do{
                randomNumber = rand() % 4;
                if(oldMinusNew[randomNumber] != -2)
                    _control2=0;
                else if(oldMinusNew[randomNumber] == 3)
                    _control2=1;
                else
                    _control2=1;
            }while(_control2);
        }
        else if(previousOne == 3 && oldMinusNew[randomNumber] == 2){
            do{
                randomNumber = rand() % 4;
                if(oldMinusNew[randomNumber] != -2)
                    _control2=0;
                else if(oldMinusNew[randomNumber] == 2)
                    _control2=1;
                else
                    _control2=1;
            }while(_control2);
        }
    
    }while(_control);

    
    previousOne = randomNumber;
    if(lessThanZero >= 2){
        previousOne = -1;
    }
    
    switch(randomNumber){
        case 0:
            board[blank_x][blank_y] = board[blank_x][blank_y-1];
            blank_y--;
            cout << "The left side was chosen by new intelligent Algorithm." << endl;
            previousOne = 0;
            break;
        case 1:
            board[blank_x][blank_y] = board[blank_x][blank_y+1];
            blank_y++;
            cout << "The right side was chosen by new intelligent Algorithm." << endl;
            previousOne = 1;
            break;
        case 2:
            board[blank_x][blank_y] = board[blank_x-1][blank_y];
            blank_x--;
            cout << "The upside was chosen by new intelligent Algorithm." << endl;
            previousOne = 2;
            break;
        case 3:
            board[blank_x][blank_y] = board[blank_x+1][blank_y];
            blank_x++;
            cout << "The down side was chosen by new intelligent Algorithm." << endl;
            previousOne = 3;
            break;
    }    
    
}

inline void solveTheProblem(int board[][9],int x,int y,int &blank_x,int &blank_y,int &previousOne){
    int solvedBoard[9][9] = {}; 
    int solved_blank_x=blank_x,solved_blank_y=blank_y,control=1;
    long long int moves=0;

    for(int i=0;i<x;i++){
        for(int j=0;j<y;j++){
            solvedBoard[i][j] = board[i][j];
        }
    }
    solvedTable(solvedBoard,x,y,solved_blank_x,solved_blank_y);

    do{
        
        moves++;
        newIntelligentAlgorithm(board,x,y,blank_x,blank_y,previousOne);
        for(int i=0;i<x;i++){
            for(int j=0;j<y;j++){
                if(i == blank_x && j == blank_y && i==solved_blank_x && j == solved_blank_y){
                    control=0;
                }else if(board[i][j] == solvedBoard[i][j]){
                    control=0;
                }else if(board[i][j] != solvedBoard[i][j]){
                    control=1;
                    break;
                }
            }
            if(control)
                break;
        } 
    }while(control && moves < 500000);

    if(control){
        cout << "The algorithm could not find solution in " << moves << " moves. :(" << endl;
    }else{
        cout << "The algorithm found solution in " << moves << " moves. :!!!" << endl;
    }

}   

void howManyMoves(int board[][9],int x,int y,int &blank_x,int &blank_y,int &previousOne,int &numberOfMoves){
    cout << numberOfMoves << " moves have been done so far." << endl;
    
    cout << "No solutions found yet." << endl;
}