/* Gebze Technical University         */
/* Computer Engineering               */
/* Name Surname : Harun ALBAYRAK      */
/* Student Number : 171044014         */
#include<iostream>
#include<ctime>
#include<cstdlib>
#include<string>
#include<fstream>
#include<vector>

using namespace std;

class NPuzzle{
    public:
        void gameCycle(int argc,char **argv);
        void print(int index);
        void printReport();
        void readFromFile(int index,int argc,char **argv,char *fileName,int check);
        void writeFromFile(int index,char *fileName);
        void shuffle(int index,int N);
        void reset(int index);
        void setSize(int index,int value_x,int value_y);
        inline void moveRandom(int index);
        void move(int index,char character_of_movement);
        void solvePuzzle(int index);
        friend ostream& operator<<(ostream& os, const vector< vector<int> >& game);
        friend istream& operator>>(istream &in, vector< vector<int> >& game);
    private:
    class Board{
        public:
            Board(char *argv);
            Board(char **argv);
            Board(int value_x,int value_y);
            int get_x();
            int get_y();
            bool goLeft();
            bool goRight();
            bool goUp();
            bool goDown();
            void CopyVector(const Board& board1);
            void setNumberOfMoves(int move);
            void initialShuffle();  // Olu�turulan board� kar��t�r�yor.
            void syncAll();  // Board�n d�zg�n resetlenebilmesi i�in senkronize bir say� at�yorum.
            void print();
            void readFromFile(int argc,char **argv,char *fileName,int check);
            void writeFromFile(char *fileName);
            void reset();
            void setSize(int value_x,int value_y);
            inline void move(char character_of_movement);
            bool isSolved();
            Board& leftBoard();
            int NumberOfBoards();
            char lastMove();
            int numberOfMoves();
            int& operator()(int row, int column);
            friend bool operator==(const vector< vector<int> >& left,const vector< vector<int> >& right);
        private:
            vector< vector<int> > board;
            char _lastMove;
            int _numberOfMoves;
    };
    public:
        vector<Board> board2d; 
};

int main(int argc, char** argv){
    NPuzzle game;
    srand(time(NULL));
    game.gameCycle(argc,argv);
    
    return 0;
}

void NPuzzle::gameCycle(int argc,char **argv){
    int boardSize=0,NumberOfMov=0;
    char input,fileName[30];
    ifstream myfile;
    
    if(argc == 1){  // Girilen output arg�van� 1 ise buraya girer ve random board olu�turup kar��t�r�r.
        cout << "Please enter the board size: "; // Takes the board size.
        do{
            cin >> boardSize;
            if(boardSize < 3 || boardSize > 9)
                cout << "Wrong Input. Try Again..." << endl;
        }while(boardSize < 3 || boardSize > 9);
        Board game(boardSize,boardSize);
        board2d.push_back(game);
        print(0);
    }else{  // Girilen output arg�van� 1 den fazla ise buraya girer.
        Board game(argv);
        board2d.push_back(game);
        readFromFile(0,argc,argv,fileName,0);
        print(0);
    }
    while(!board2d[0].isSolved()){
        cout << "Your move : " ;
        cin >> input;
        if(input == 'o' || input == 'O'){// Dosyadan board okur.
            cout << "Enter the name of the file: ";
            cin >> fileName;
            myfile.open(fileName,ios::in);
            while(myfile.fail()){
                cout << "You have entered the wrong file name." << endl; 
                cout << "Enter the file name again('press 1 to exit'): ";
                cin >> fileName;
                
                myfile.open(fileName,ios::in);
                if(*fileName == '1')
                    exit(1);
            };
            myfile.close();
            board2d.clear();
            Board game(fileName);
            board2d.push_back(game);
            readFromFile(0,argc,argv,fileName,1);
        }else if(input == 'e' || input == 'E'){ // Board� dosyaya kaydeder.
            cout << "Enter the name of the file: ";
            cin >> fileName;
            writeFromFile(0,fileName);
        }else if(input == 'v' || input == 'V'){
            solvePuzzle(0); 
        }else if(input == 't' || input == 'T'){  // Ka� hamle kald���n� yazd�r�r ve board�n ��z�l�p ��z�lmedi�ine bakar.
            printReport();
        }else if(input == 's' || input == 'S'){  // Shuffle yapar.          
            reset(0);
            move(0,'s');
        }else if(input == 'X'){  // random harekete girer
            do{
                cout << "Please try again : ";
                cin >> input;
            }while(input == 'X');  // kullan�c�n�n buraya girmesini engeller.
        }else
            move(0,input);

        if(input=='l' || input=='l' || input=='r' || input=='R' || input=='d'
        || input=='D' || input=='u' || input=='U' || input=='v' || input=='V'
        || input=='t' || input=='T' || input=='e' || input=='E' || input=='o'
        || input=='O' || input=='s' || input=='S'){
            print(0);
            NumberOfMov = board2d[0].numberOfMoves();
        }
    }
    NumberOfMov = board2d[0].numberOfMoves();
    if(board2d[0].isSolved()){
       cout << "Congratulations you won the game in " << NumberOfMov << " moves. !";
    }
}

void NPuzzle::print(int index){
    board2d[index].print();
}

void NPuzzle::printReport(){
    int num = board2d[0].numberOfMoves();
    cout << num << " moves have been done so far." << endl;
    if(!board2d[0].isSolved())
        cout << "No solutions found yet." << endl;
    else
        cout << "The solution are already found." << endl;
}

void NPuzzle::readFromFile(int index,int argc,char **argv,char *fileName,int check){
    board2d[index].readFromFile(argc,argv,fileName,check);
}

void NPuzzle::writeFromFile(int index,char *fileName){
    board2d[index].writeFromFile(fileName);
}

void NPuzzle::shuffle(int index,int N){
    board2d[index].reset();
    board2d[index].move('s');
}

void NPuzzle::reset(int index){
    board2d[index].reset();
}

void NPuzzle::setSize(int index,int value_x,int value_y){
    board2d[index].setSize(value_x,value_y);
}

void NPuzzle::moveRandom(int index){
    board2d[index].move('X');
}

void NPuzzle::move(int index,char character_of_movement){
    board2d[index].move(character_of_movement);
}

void NPuzzle::solvePuzzle(int index){
    int numberOfBoards=0,sendIndex=index,turn=0,x=board2d[0].get_x(),y=board2d[0].get_y();
    int num = 100000;
    
    while(num > 0 && !board2d[numberOfBoards].isSolved()){
        if(board2d[index].goLeft()){
            cout << "Left side was selected by the algorithm." << endl;
            numberOfBoards = numberOfBoards + 1;
            Board game(x,y);
            board2d.push_back(game);
            board2d[numberOfBoards].CopyVector(board2d[index]);
            move(numberOfBoards,'L');
            if(board2d[numberOfBoards].isSolved())
                break;
        }
        if(board2d[index].goRight()){
            cout << "Right side was selected by the algorithm." << endl;
            numberOfBoards++;
            Board game(x,y);
            board2d.push_back(game);
            board2d[numberOfBoards].CopyVector(board2d[index]);
            move(numberOfBoards,'R');
            if(board2d[numberOfBoards].isSolved())
                break;
        }
        if(board2d[index].goUp()){
            cout << "Up side was selected by the algorithm." << endl;
            numberOfBoards++;
            Board game(x,y);
            board2d.push_back(game);
            board2d[numberOfBoards].CopyVector(board2d[index]);
            move(numberOfBoards,'U');
            if(board2d[numberOfBoards].isSolved())
                break;
        }
        if(board2d[index].goDown()){
            cout << "Down side was selected by the algorithm." << endl;
            numberOfBoards++;
            Board game(x,y);
            board2d.push_back(game);
            board2d[numberOfBoards].CopyVector(board2d[index]);
            move(numberOfBoards,'D');
            if(board2d[numberOfBoards].isSolved())
                break;
        }
        index++;
        num--;
    }


    if(board2d[numberOfBoards].isSolved()){
        cout << "Table are solved in " << numberOfBoards << " moves by intelligent moves." << endl;
    }else{
        cout << "Table are not solved in " << numberOfBoards << " moves by intelligent moves." << endl;
    }
    board2d[0].CopyVector(board2d[numberOfBoards]);
    board2d[0].setNumberOfMoves(numberOfBoards);
    
}

ostream& operator<<(ostream& os, const vector< vector<int> >& game){
    for(int i=0;i<game.size();i++){
        for(int j=0;j<game[i].size();j++){
            if(game[i][j] == 99)
                os << "  " << " ";
            else if(game[i][j] >= 0 && game[i][j] < 10)
                os << "0" << game[i][j] << " ";
            else
                os << game[i][j] << " ";
        }
        os << endl;
    }
    os << endl;
    return os;
}

istream& operator>>(istream &in, vector< vector<int> >& game){
    in >> game[0][0];

    return in;
}

NPuzzle::Board::Board(char *argv){
    int x=0,y=0;
    string mystr;
    ifstream myfile;
    myfile.open(argv,ios::in);
    while( getline( myfile, mystr)){
        x++;
        y = mystr.size();
    }
    y= y/3 + 1;
    _lastMove = 'S';
    _numberOfMoves = 0;
    myfile.close();
    setSize(x,y);
    reset();
    initialShuffle();
}

NPuzzle::Board::Board(char** argv){
    int x=0,y=0;
    string mystr;
    ifstream myfile;
    myfile.open(argv[0],ios::in);
    while( getline( myfile, mystr)){
        x++;
        y = mystr.size();
    }
    y= y/3 + 1;
    _lastMove = 'S';
    _numberOfMoves = 0;
    myfile.close();
    setSize(x,y);
    reset();
    initialShuffle();
}

NPuzzle::Board::Board(int value_x,int value_y){
    _lastMove = 'S';
    _numberOfMoves = 0;
    setSize(value_x,value_y);
    reset();
    initialShuffle();
}

int NPuzzle::Board::get_x(){
    int temp = board.size();
    return temp;
}

int NPuzzle::Board::get_y(){
    int temp = board[0].size();
    return temp;
}

bool NPuzzle::Board::goLeft(){
    int blank_x=0,blank_y=0;
    int temp = 0;
    for(int i=0;i<board.size();i++){
        for(int j=0;j<board[i].size();j++){
            if(board[i][j] == 99){
                blank_x = i;
                blank_y = j;
            }        
        }
    }
    if(blank_y != 0 && board[blank_x][blank_y-1] != 0)
        return true;
    else
        return false;
}

bool NPuzzle::Board::goRight(){
    int blank_x=0,blank_y=0;
    int temp = 0;
    for(int i=0;i<board.size();i++){
        for(int j=0;j<board[i].size();j++){
            if(board[i][j] == 99){
                blank_x = i;
                blank_y = j;
            }        
        }
    }

    (blank_y != board[0].size()-1 && board[blank_x][blank_y+1] != 0 ? temp=1 : temp=0);

    if(temp == 1)
        return true;
    else
        return false;
}

bool NPuzzle::Board::goUp(){
    int blank_x=0,blank_y=0;
    int temp = 0;
    for(int i=0;i<board.size();i++){
        for(int j=0;j<board[i].size();j++){
            if(board[i][j] == 99){
                blank_x = i;
                blank_y = j;
            }        
        }
    }
    (blank_x != 0 && board[blank_x-1][blank_y] != 0 ? temp=1 : temp=0);

    if(temp == 1)
        return true;
    else
        return false;;
}

bool NPuzzle::Board::goDown(){
    int blank_x=0,blank_y=0;
    int temp = 0;
    for(int i=0;i<board.size();i++){
        for(int j=0;j<board[i].size();j++){
            if(board[i][j] == 99){
                blank_x = i;
                blank_y = j;
            }        
        }
    }
    (blank_x != board.size()-1 && board[blank_x+1][blank_y] != 0 ? temp=1 : temp=0);

    if(temp == 1)
        return true;
    else
        return false;
}

void NPuzzle::Board::CopyVector(const Board& board1){
    for(int i=0;i<board1.board.size();i++){
        for(int j=0;j<board1.board[0].size();j++){
            board[i][j] = board1.board[i][j];
        }
    }
    _numberOfMoves = board1._numberOfMoves;
}

void NPuzzle::Board::setNumberOfMoves(int move){
    _numberOfMoves = move;
}

void NPuzzle::Board::print(){
    cout << board;
}

void NPuzzle::Board::setSize(int value_x,int value_y){
    for(int i=0;i<value_x;i++){
        vector<int>temp;
        for(int j=0;j<value_y;j++){
            temp.push_back(1);
        }
        board.push_back(temp);
    }
}

void NPuzzle::Board::reset(){
    int k = 1;  
    for(int i=0;i<board.size();i++){
        for(int j=0;j<board[i].size();j++){
            if(i == board.size()-1 && j == board[i].size() -1)
                board[i][j] = 99;
            else if(board[i][j] != 0)
                board[i][j] = k++;              
        }
    }
    
}

void NPuzzle::Board::readFromFile(int argc,char **argv,char *fileName,int check){
    int i=0,j=-1,control=0,y=0;
    char fileName2[30];
    char bb[2];
    string mystr;
    ifstream myfile;

    if(check == 0){
        if(argc == 1){
            cout << "Enter the name of the file: ";
            cin >> fileName2;
            
            myfile.open(fileName2,ios::in);
        }else{
            myfile.open(argv[1],ios::in);
        }

        while(myfile.fail()){
            cout << "You have entered the wrong file name." << endl; 
            cout << "Enter the file name again('press 1 to exit'): ";
            cin >> fileName2;
            
            myfile.open(fileName2,ios::in);
            if(*fileName2 == '1')
                exit(1);
        };
    }else if(check == 1){
        myfile.open(fileName,ios::in);
    }
    
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
            board[i][j] = 99;
        }
    } 
    // Dosyayı açar ve arrayin içini dosyadakiler ile doldurur.  
    myfile.close();
}

void NPuzzle::Board::writeFromFile(char *fileName){
    int blank_x=0,blank_y=0;
    ofstream myfile;

    for(int i=0;i<board.size();i++){
        for(int j=0;j<board[i].size();j++){
            if(board[i][j] == 99){
                blank_x = i;
                blank_y = j;
            }        
        }
    }

    myfile.open(fileName);

    for(int i=0;i<board.size();i++){
        for(int j=0;j<board[i].size();j++){
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

void NPuzzle::Board::initialShuffle(){
    int randomNum=0,randomNum2=0,blank_x=0,blank_y=0;
    for(int i=0;i<board.size();i++){
        for(int j=0;j<board[i].size();j++){
            if(board[i][j] == 99){
                blank_x = i;
                blank_y = j;
            }        
        }
    }

    randomNum = (rand() % 300) + 200;
    // Sıralı bir board oluşturduktan sonra karıştırmak için 300 ile 500 arasında hamle yapar.
    while(randomNum != 0){
        randomNum2 = rand() % 4;
        if(randomNum2 == 0 && !(blank_y != 0 && board[blank_x][blank_y-1] != 0))
            continue;
        else if(randomNum2 == 1 && !(blank_y != board.size()-1 && board[blank_x][blank_y+1] != 0))
            continue;
        else if(randomNum2 == 2 && !(blank_x != 0 && board[blank_x-1][blank_y] != 0))
            continue;
        else if(randomNum2 == 3 && !(blank_x != board.size()-1 && board[blank_x+1][blank_y] != 0))
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
    board[blank_x][blank_y] = 99;
}

void NPuzzle::Board::move(char character_of_movement){
    int NOM=board.size()*board[0].size(),randomNum=0,randomNum2=0,move=1,blank_x=0,blank_y=0,temp=0;
    
    for(int i=0;i<board.size();i++){
        for(int j=0;j<board[i].size();j++){
            if(board[i][j] == 99){
                blank_x = i;
                blank_y = j;
            }        
        }
    }
    switch(character_of_movement){
        case 'l':
        case 'L': // Sol tarafta boşluk var ise sol tarafa hareket eder.
            if(blank_y != 0 && board[blank_x][blank_y-1] != 0){
                temp = board[blank_x][blank_y];
                board[blank_x][blank_y] = board[blank_x][blank_y-1];
                board[blank_x][blank_y-1] = temp;
            }else{
                cout << "There is no room on the left side" << endl;
            }
            _lastMove = 'L';
            break;
        case 'r':
        case 'R': // Sağ tarafta boşluk var ise sol tarafa hareket eder.
            if(blank_y != board[0].size()-1 && board[blank_x][blank_y+1] != 0){
                temp = board[blank_x][blank_y];
                board[blank_x][blank_y] = board[blank_x][blank_y+1];
                board[blank_x][blank_y+1] = temp;
            }else{
                cout << "There is no room on the right side" << endl;
            }
            _lastMove = 'R';
            break;
        case 'u':
        case 'U': // Yukarda boşluk var ise sol tarafa hareket eder.
            if(blank_x != 0 && board[blank_x-1][blank_y] != 0){
                temp = board[blank_x][blank_y];
                board[blank_x][blank_y] = board[blank_x-1][blank_y];
                board[blank_x-1][blank_y] = temp;
            }else{
                cout << "There is no room upstairs" << endl;
            }
            _lastMove = 'U';
            break;
        case 'd':
        case 'D': // Aşağıda boşluk var ise sol tarafa hareket eder.
            if(blank_x != board.size()-1 && board[blank_x+1][blank_y] != 0){
                temp = board[blank_x][blank_y];
                board[blank_x][blank_y] = board[blank_x+1][blank_y];
                board[blank_x+1][blank_y] = temp;
            }else{
                cout << "There is no room downstairs" << endl;
            }
            _lastMove = 'D';
            break;
        case 'X':
            do{
                randomNum = rand() % 4;

                if(randomNum == 0 && !(blank_y != 0 && board[blank_x][blank_y-1] != 0))
                    continue;
                else if(randomNum == 1 && !(blank_y != board[0].size()-1 && board[blank_x][blank_y+1] != 0))
                    continue;
                else if(randomNum == 2 && !(blank_x != 0 && board[blank_x-1][blank_y] != 0))
                    continue;
                else if(randomNum == 3 && !(blank_x != board.size()-1 && board[blank_x+1][blank_y] != 0))
                    continue;

                if(randomNum == 0){
                    temp = board[blank_x][blank_y];
                    board[blank_x][blank_y] = board[blank_x][blank_y-1];
                    board[blank_x][blank_y-1] = temp;
                }else if(randomNum == 1){
                    temp = board[blank_x][blank_y];
                    board[blank_x][blank_y] = board[blank_x][blank_y+1];
                    board[blank_x][blank_y+1] = temp;
                }else if(randomNum == 2){
                    temp = board[blank_x][blank_y];
                    board[blank_x][blank_y] = board[blank_x-1][blank_y];
                    board[blank_x-1][blank_y] = temp;
                }else if(randomNum == 3){
                    temp = board[blank_x][blank_y];
                    board[blank_x][blank_y] = board[blank_x+1][blank_y];
                    board[blank_x+1][blank_y] = temp;
                }
                move--;
            }while(move >= 1);
            move = 1;
            break;
        case 's':
        case 'S': // Karıştırır.
            while(NOM != 0){
                randomNum2 = rand() % 4;
                if(randomNum2 == 0 && !(blank_y != 0 && board[blank_x][blank_y-1] != 0))
                    continue;
                else if(randomNum2 == 1 && !(blank_y != board.size()-1 && board[blank_x][blank_y+1] != 0))
                    continue;
                else if(randomNum2 == 2 && !(blank_x != 0 && board[blank_x-1][blank_y] != 0))
                    continue;
                else if(randomNum2 == 3 && !(blank_x != board.size()-1 && board[blank_x+1][blank_y] != 0))
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
                NOM--;
            }
            board[blank_x][blank_y] = 99;
                    break;    
        
        case 'q':
        case 'Q': // Çıkar.
        	cout << "Exiting..." << endl;
        	exit(1);
        default :
        	cout << "Wrong Input. Try Again..." << endl;
    }
} 

bool NPuzzle::Board::isSolved(){
    int control=0,k=1,blank_x=0,blank_y=0;
    int solvedBoard2d[9][9]={},solved_blank_x=0,solved_blank_y=0;
    
    for(int i=0;i<board.size();i++){
        for(int j=0;j<board[i].size();j++){
            if(board[i][j] == 99){
                blank_x = i;
                blank_y = j;
            }        
        }
    }

    solvedBoard2d[blank_x][blank_y] = 1;
    for(int i=0;i<board.size();i++)
        for(int j=0;j<board[i].size();j++)
            if(board[i][j] != 0 || (i==blank_x && j==blank_y)) 
                solvedBoard2d[i][j] = k++;

    solved_blank_x = board.size() - 1;
    solved_blank_y = board[0].size() - 1;

    for(int i=0;i<board.size();i++){
        for(int j=0;j<board[i].size();j++){
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

int& NPuzzle::Board::operator()(int row, int column){
    if(board.size() >= row && board[0].size() >= column){
        return board[row][column];
    }else{
        exit(-1);
    }
}

bool operator==(const vector< vector<int> >& left,const vector< vector<int> >& right){
    int control=0,control2;
    control2 = left.size() * left[0].size() + 2;
    if(left.size() == right.size())
        control++;
    if(left[0].size() == right.size())
        control++;
    for(int i=0;i<left.size();i++){
        for(int j=0;j<left[i].size();j++){
            if(left[i][j] == right[i][j])
                control++;
        }
    }
    if(control == control2)
        return true;
    else
        return false;
}

int NPuzzle::Board::NumberOfBoards(){
    return _numberOfMoves;
}

char NPuzzle::Board::lastMove(){
    return _lastMove;
}

int NPuzzle::Board::numberOfMoves(){
    _numberOfMoves++;
    return _numberOfMoves;
}