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

void gameCycle(int argc,char **argv);  // Oyunun asýl olarak döndüðü fonksiyon.

class NPuzzle{
    public:
        void print();
        void printReport(int num);
        void readFromFile(int argc,char **argv);
        void writeFromFile();
        void shuffle(int N);
        void reset();
        void setSize(int value_x,int value_y);
        inline void moveRandom();
        inline void moveIntelligent();
        inline void move(char character_of_movement);
        int solvePuzzle();
    private:
    class Board{
        public:
            int createBoard();  // Bir board oluþturuyor.
            void initialShuffle();  // Oluþturulan boardý karýþtýrýyor.
            void syncAll();  // Boardýn düzgün resetlenebilmesi için senkronize bir sayý atýyorum.
            void print();
            void readFromFile(int argc,char **argv);
            void writeFromFile();
            void reset();
            void setSize(int value_x,int value_y);
            inline void move(char character_of_movement);
            bool isSolved();
        private:
            int board[9][9];
            int x,y,blank_x,blank_y;
    };
    public:
        NPuzzle::Board board2d;
};

int main(int argc, char** argv){
    srand(time(NULL));
    gameCycle(argc,argv);
    
    return 0;
}

void gameCycle(int argc,char **argv){
    int boardSize=0,intelligentMove=0,numberOfMoves=0;
    char input;
    NPuzzle game;
    
    if(argc == 1){  // Girilen output argüvaný 1 ise buraya girer ve random board oluþturup karýþtýrýr.
        boardSize = game.board2d.createBoard();
        game.setSize(boardSize,boardSize);
        game.board2d.syncAll();
        game.reset();
        game.board2d.initialShuffle();
        game.print();
    }else{  // Girilen output argüvaný 1 den fazla ise buraya girer.
        game.readFromFile(argc,argv);
        game.print();
    }

    while(!game.board2d.isSolved()){
        cout << "Your move : " ;
        cin >> input;
        if(input == 'o' || input == 'O') // Dosyadan board okur.
            game.readFromFile(argc,argv);
        else if(input == 'e' || input == 'E') // Boardý dosyaya kaydeder.
            game.writeFromFile();
        else if(input == 'i' || input == 'I'){ // Intelligent move yapar(3 intelligent + 2 random move þeklinde)
            if(intelligentMove % 3 == 0)
                game.move('i');
            else
                for(int i=0;i<2;i++)
                    game.moveRandom();
            intelligentMove++;
        }
        else if(input == 'v' || input == 'V')  // Boardý çözmeye çalýþýr.
            numberOfMoves += game.solvePuzzle() - 1;  
        else if(input == 't' || input == 'T'){  // Kaç hamle kaldýðýný yazdýrýr ve boardýn çözülüp çözülmediðine bakar.
            game.printReport(numberOfMoves+1);
            numberOfMoves--;
        }    
        else if(input == 's' || input == 'S'){  // Shuffle yapar.
            game.board2d.reset();
            game.move('s');
        }             
        else if(input == 'X'){  // random harekete girer
            do{
                cout << "Please try again : ";
                cin >> input;
            }while(input == 'X');  // kullanýcýnýn buraya girmesini engeller.
            numberOfMoves--;
        }
        else
            game.move(input);

        if(input=='l' || input=='l' || input=='r' || input=='R' || input=='d'
        || input=='D' || input=='u' || input=='U' || input=='v' || input=='V'
        || input=='t' || input=='T' || input=='e' || input=='E' || input=='o'
        || input=='O' || input=='i' || input=='I' || input=='s' || input=='S'){
            game.print();
            numberOfMoves++;
        }
    }
    if(game.board2d.isSolved()){
        cout << "Congratulations you won the game in " << numberOfMoves << " moves. !";
    }
}

void NPuzzle::print(){
    board2d.print();
}

void NPuzzle::printReport(int num){
    cout << num << " moves have been done so far." << endl;
    if(!board2d.isSolved())
        cout << "No solutions found yet." << endl;
    else
        cout << "The solution are already found." << endl;
}

void NPuzzle::reset(){
    board2d.reset();
}

void NPuzzle::setSize(int value_x,int value_y){
    board2d.setSize(value_x,value_y);
}

void NPuzzle::readFromFile(int argc,char **argv){
    board2d.readFromFile(argc,argv);
}

void NPuzzle::writeFromFile(){
    board2d.writeFromFile();
}

void NPuzzle::shuffle(int N){
    board2d.reset();
    board2d.move('s');
}

inline void NPuzzle::moveRandom(){
    board2d.move('X');
}

inline void NPuzzle::moveIntelligent(){
    board2d.move('i');
}

inline void NPuzzle::move(char character_of_movement){
    board2d.move(character_of_movement);
}

int NPuzzle::solvePuzzle(){
    int intelligentMove = 0;
    long long moveNumber = 0;
    do{
        if(intelligentMove % 3 == 0)
            board2d.move('i');
        else
            for(int i=0;i<1;i++)
                board2d.move('X');
        intelligentMove++;
        moveNumber++;
    }while(!board2d.isSolved() && moveNumber < 1000000);
    if(moveNumber == 1000000 && !board2d.isSolved())
        cout << "Sorry solution not found in " << moveNumber << " moves..:(" << endl;

    return moveNumber;
}

int NPuzzle::Board::createBoard(){
    int boardSize=0;
   
    cout << "Please enter the board size: "; // Takes the board size.
    do{
        cin >> boardSize;
        if(boardSize < 3 || boardSize > 9)
            cout << "Wrong Input. Try Again..." << endl;
    }while(boardSize < 3 || boardSize > 9);

    return boardSize;
}

void NPuzzle::Board::initialShuffle(){
    int randomNum=0,randomNum2=0;

    randomNum = (rand() % 300) + 200;
    // SÄ±ralÄ± bir board oluÅŸturduktan sonra karÄ±ÅŸtÄ±rmak iÃ§in 300 ile 500 arasÄ±nda hamle yapar.
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

void NPuzzle::Board::syncAll(){
    for(int i=0;i<x;i++)
        for(int j=0;j<y;j++)
            board[i][j] = 1;
}

void NPuzzle::Board::print(){
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

void NPuzzle::Board::reset(){
    int k = 1;
    board[blank_x][blank_y] = 1;    
    for(int i=0;i<x;i++){
        for(int j=0;j<y;j++){
            if(board[i][j] != 0)
                board[i][j] = k++;            
        }
    }
    blank_x = x-1;
    blank_y = y-1;
}

void NPuzzle::Board::setSize(int value_x,int value_y){
    x = value_x;
    y = value_y;
    blank_x=x-1;
    blank_y=y-1;
}

void NPuzzle::Board::readFromFile(int argc,char **argv){
    int i=0,j=-1,control=0;
    char fileName[30];
    char bb[2];
    string mystr;
    ifstream myfile;

    if(argc == 1){
        cout << "Enter the name of the file: ";
        cin >> fileName;
        
        myfile.open(fileName,ios::in);
    }else{
        myfile.open(argv[1],ios::in);
    }

    while(myfile.fail()){
        cout << "You have entered the wrong file name." << endl; 
        cout << "Enter the file name again('press 1 to exit'): ";
        cin >> fileName;
        
        myfile.open(fileName,ios::in);
        if(*fileName == '1')
            exit(1);
    };
    

    if( getline( myfile, mystr)) 
        y = mystr.size();
    
    y= y/3 + 1;

    myfile.clear();
    myfile.seekg(0, ios::beg);

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
    // DosyayÄ± aÃ§ar ve arrayin iÃ§ini dosyadakiler ile doldurur.  
    x = i+1;
    y = j+1;
    myfile.close();
}

void NPuzzle::Board::writeFromFile(){
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

inline void NPuzzle::Board::move(char character_of_movement){
    int numberOfMoves=x*y,randomNum=0,move=1;
    int currentNum=0,original_x=0,original_y=0,dif=0,new_dif=0,status[4]={},i=0,j=0,k=1,howMany=0;
    switch(character_of_movement){
        case 'l':
        case 'L': // Sol tarafta boÅŸluk var ise sol tarafa hareket eder.
            if(blank_y != 0 && board[blank_x][blank_y-1] != 0){
                board[blank_x][blank_y] = board[blank_x][blank_y-1];
                blank_y--;
            }else{
                cout << "There is no room on the left side" << endl;
            }
            break;
        case 'r':
        case 'R': // SaÄŸ tarafta boÅŸluk var ise sol tarafa hareket eder.
            if(blank_y != y-1 && board[blank_x][blank_y+1] != 0){
                board[blank_x][blank_y] = board[blank_x][blank_y+1];
                blank_y++;
            }else{
                cout << "There is no room on the right side" << endl;
            }
            break;
        case 'u':
        case 'U': // Yukarda boÅŸluk var ise sol tarafa hareket eder.
            if(blank_x != 0 && board[blank_x-1][blank_y] != 0){
                board[blank_x][blank_y] = board[blank_x-1][blank_y];
                blank_x--;
            }else{
                cout << "There is no room upstairs" << endl;
            }
            break;
        case 'd':
        case 'D': // AÅŸaÄŸÄ±da boÅŸluk var ise sol tarafa hareket eder.
            if(blank_x != x-1 && board[blank_x+1][blank_y] != 0){
                board[blank_x][blank_y] = board[blank_x+1][blank_y];
                blank_x++;
            }else{
                cout << "There is no room downstairs" << endl;
            }
            break;
        case 'i':
        case 'I': // Yapay zekaya gÃ¶re hareket eder.
            if(blank_y != 0 && board[blank_x][blank_y-1] != 0){
                currentNum = board[blank_x][blank_y-1];
                k=0;
                for(i=0;i<x;i++){
                    for(j=0;j<y;j++){
                        if(board[i][j] != 0){
                            k++;
                            if(k==currentNum){
                                original_x = i;
                                original_y = j;
                            }
                        }
                    }
                }
                dif = abs(original_x - blank_x) + abs(original_y - blank_y-1);
                new_dif = abs(original_x - blank_x) + abs(original_y - blank_y);
                if(dif > new_dif)
                    status[0] = -1;
                else
                    status[0] = 1;
            }
            if(blank_y != y-1 && board[blank_x][blank_y+1] != 0){
                currentNum = board[blank_x][blank_y+1];
                k=0;
                for(i=0;i<x;i++){
                    for(j=0;j<y;j++){
                        if(board[i][j] != 0){
                            k++;
                            if(k==currentNum){
                                original_x = i;
                                original_y = j;
                            }
                        }
                    }
                }
                dif = abs(original_x - blank_x) + abs(original_y - blank_y+1);
                new_dif = abs(original_x - blank_x) + abs(original_y - blank_y);
                if(dif > new_dif)
                    status[1] = -1;
                else
                    status[1] = 1;
            }
            if(blank_x != 0 && board[blank_x-1][blank_y] != 0){
                currentNum = board[blank_x-1][blank_y];
                k=0;
                for(i=0;i<x;i++){
                    for(j=0;j<y;j++){
                        if(board[i][j] != 0){
                            k++;
                            if(k==currentNum){
                                original_x = i;
                                original_y = j;
                            }
                        }
                    }
                }
                dif = abs(original_x - blank_x-1) + abs(original_y - blank_y);
                new_dif = abs(original_x - blank_x) + abs(original_y - blank_y);
                if(dif > new_dif)
                    status[2] = -1;
                else
                    status[2] = 1;
            }
            if(blank_x != x-1 && board[blank_x+1][blank_y] != 0){
                currentNum = board[blank_x+1][blank_y];
                k=0;
                for(i=0;i<x;i++){
                    for(j=0;j<y;j++){
                        if(board[i][j] != 0){
                            k++;
                            if(k==currentNum){
                                original_x = i;
                                original_y = j;
                            }
                        }
                    }
                }
                dif = abs(original_x - blank_x+1) + abs(original_y - blank_y);
                new_dif = abs(original_x - blank_x) + abs(original_y - blank_y);
                if(dif > new_dif)
                    status[3] = -1;
                else
                    status[3] = 1;
            }
            
            for(i=0;i<4;i++)
                if(status[i] == 1)
                    howMany++;

            do{
               randomNum = rand() % 4;
               if(howMany == 0)
                break;
            }while (status[randomNum] != 1);

            if(howMany == 0){
                do{
                    randomNum = rand() % 4;
                }while (status[randomNum] != -1);
            }

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

            break;

        case 'X':
            do{
                randomNum = rand() % 4;

                if(randomNum == 0 && !(blank_y != 0 && board[blank_x][blank_y-1] != 0))
                    continue;
                else if(randomNum == 1 && !(blank_y != y-1 && board[blank_x][blank_y+1] != 0))
                    continue;
                else if(randomNum == 2 && !(blank_x != 0 && board[blank_x-1][blank_y] != 0))
                    continue;
                else if(randomNum == 3 && !(blank_x != x-1 && board[blank_x+1][blank_y] != 0))
                    continue;

                if(randomNum == 0){
                    board[blank_x][blank_y] = board[blank_x][blank_y-1];
                    blank_y--;
                }else if(randomNum == 1){
                    board[blank_x][blank_y] = board[blank_x][blank_y+1];
                    blank_y++;
                }else if(randomNum == 2){
                    board[blank_x][blank_y] = board[blank_x-1][blank_y];
                    blank_x--;
                }else if(randomNum == 3){
                    board[blank_x][blank_y] = board[blank_x+1][blank_y];
                    blank_x++;
                }
                move--;
            }while(move >= 1);
            move = 1;
            break;
        case 's':
        case 'S': // KarÄ±ÅŸtÄ±rÄ±r.
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

                if(randomNum == 0){
                    board[blank_x][blank_y] = board[blank_x][blank_y-1];
                    blank_y--;
                }else if(randomNum == 1){
                    board[blank_x][blank_y] = board[blank_x][blank_y+1];
                    blank_y++;
                }else if(randomNum == 2){
                    board[blank_x][blank_y] = board[blank_x-1][blank_y];
                    blank_x--;
                }else if(randomNum == 3){
                    board[blank_x][blank_y] = board[blank_x+1][blank_y];
                    blank_x++;
                }

                numberOfMoves--;
            }
            break;    
        
        case 'q':
        case 'Q': // Ã‡Ä±kar.
        	cout << "Exiting..." << endl;
        	exit(1);
        default :
        	cout << "Wrong Input. Try Again..." << endl;
    }
} 

bool NPuzzle::Board::isSolved(){
    int control=0,k=1;
    int solvedBoard2d[x][y]={},solved_blank_x=0,solved_blank_y=0;
    
    solvedBoard2d[blank_x][blank_y] = 1;
    for(int i=0;i<x;i++)
        for(int j=0;j<y;j++)
            if(board[i][j] != 0 || (i==blank_x && j==blank_y)) 
                solvedBoard2d[i][j] = k++;

    solved_blank_x = x-1;
    solved_blank_y = y-1;

    for(int i=0;i<x;i++){
        for(int j=0;j<y;j++){
            if(i == blank_x && j == blank_y && i==solved_blank_x && j == solved_blank_y){
                control=0;
            }else if(board[i][j] == solvedBoard2d[i][j]){
                control=0;
            }else if(board[i][j] != solvedBoard2d[i][j]){
                control=1;
              
                break;
            }
            if(control == 1)
                break;
        }
        if(control == 1)
            break;
    }

    if(!control)
        return true;
    else
        return false;
} 
