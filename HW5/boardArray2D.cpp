#include<iostream>
#include<vector>
#include<fstream>
#include<ctime>
#include<cstdlib>
#include"boardArray2D.h"

namespace classesOfBoard{
    /* Dosyadan board okur */
    boardArray2D::boardArray2D(int argc,char **argv,char *fileName,int check) : AbstractBoard(){
        _numberOfBoards++;
        readFromFile(argc,argv,fileName,check);
    }
    /* Girilen değerleri x ve y si olacak şekilde rastgele board oluşturur. */
    boardArray2D::boardArray2D(int xVal,int yVal) : AbstractBoard(){
        _numberOfBoards++;
        int randomNum=0,randomNum2=0,k=1,blankIndexes[2]={},size=xVal,temp=0;
        setSize(xVal,yVal); 
        reset();

        randomNum = (rand() % 100) + 50;

        for(int i=0;i<x;i++){
            for(int j=0;j<y;j++){
                if(boardArr2D[i][j] == 99){
                    blankIndexes[0] = i;
                    blankIndexes[1] = j;
                } 
            }
        }
        while(randomNum != 0){
            randomNum2 = rand() % 4;
            if(randomNum2 == 0 && !(blankIndexes[1] != 0 && boardArr2D[blankIndexes[0]][blankIndexes[1]-1] != 0))
                continue;
            else if(randomNum2 == 1 && !(blankIndexes[1] != y-1 && boardArr2D[blankIndexes[0]][blankIndexes[1]+1] != 0))
                continue;
            else if(randomNum2 == 2 && !(blankIndexes[0] != 0 && boardArr2D[blankIndexes[0]-1][blankIndexes[1]] != 0))
                continue;
            else if(randomNum2 == 3 && !(blankIndexes[0] != x-1 && boardArr2D[blankIndexes[0]+1][blankIndexes[1]] != 0))
                continue;

            switch(randomNum2){
                case 0:
                    boardArr2D[blankIndexes[0]][blankIndexes[1]] = boardArr2D[blankIndexes[0]][blankIndexes[1]-1];
                    blankIndexes[1]--;
                    break;
                case 1:
                    boardArr2D[blankIndexes[0]][blankIndexes[1]] = boardArr2D[blankIndexes[0]][blankIndexes[1]+1];
                    blankIndexes[1]++;
                    break;
                case 2:
                    boardArr2D[blankIndexes[0]][blankIndexes[1]] = boardArr2D[blankIndexes[0]-1][blankIndexes[1]];
                    blankIndexes[0]--;
                    break;
                case 3:
                    boardArr2D[blankIndexes[0]][blankIndexes[1]] = boardArr2D[blankIndexes[0]+1][blankIndexes[1]];
                    blankIndexes[0]++;
                    break; 
            }
            boardArr2D[blankIndexes[0]][blankIndexes[1]] = 99;
            randomNum--;
        }        
    }
    /* Copy Constructor */
    boardArray2D::boardArray2D(const boardArray2D& rightSide){
        _numberOfBoards++;
        x = rightSide.x;
        y = rightSide.y;
        _lastMove = rightSide._lastMove;
        _numberOfBoards = rightSide._numberOfBoards;
        _numberOfMoves = rightSide._numberOfMoves;
        delete[] boardArr2D;
        boardArr2D = new int*[x];
        for (int i = 0; i < x; ++i)
            boardArr2D[i] = new int[y];
        for(int i=0;i<x;i++)
            for(int j=0;j<y;j++)
                boardArr2D[i][j] = rightSide.boardArr2D[i][j]; 
    }
    /* Print fonksiyonu */
    void boardArray2D::print(){
        for(int i=0;i<x;i++){
            for(int j=0;j<y;j++){
                if(boardArr2D[i][j] == 99)
                    cout << "  " << " ";
                else if(boardArr2D[i][j] >= 0 && boardArr2D[i][j] < 10)
                    cout << "0" << boardArr2D[i][j] << " ";
                else
                    cout << boardArr2D[i][j] << " ";
            }
            cout << endl;
        }
    }
    /* Dosyadan okuma işlemi */
    void boardArray2D::readFromFile(int argc,char **argv,char *fileName,int check){
        int i=0,j=-1,arr[9][9];
        char fileName2[30];
        char bb[2];
        string mystr;
        ifstream myfile;
        y=0;
        if(check == 0){
            if(argc == 1){
                cout << "\nEnter the name of the file: ";
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
        }else if(check == 2){
            cout << "\nEnter the name of the file: ";
            cin >> fileName2;
            
            myfile.open(fileName2,ios::in);
            while(myfile.fail()){
                cout << "You have entered the wrong file name." << endl; 
                cout << "Enter the file name again('press 1 to exit'): ";
                cin >> fileName2;
                
                myfile.open(fileName2,ios::in);
                if(*fileName2 == '1')
                    exit(1);
            };
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
            }else{
                j++;
            }
            arr[i][j] = atoi(bb);
            if(bb[0] == 'b' && bb[1] == 'b'){
                arr[i][j] = 99;
            }
        } 
        setSize(i+1,j+1);

        if(boardArr2D == NULL){
            boardArr2D = new int*[x];
            for (int i = 0; i < x; ++i)
                boardArr2D[i] = new int[y];
        }else{
            delete[] boardArr2D;
            boardArr2D = new int*[x];
            for (int i = 0; i < x; ++i)
                boardArr2D[i] = new int[y];
        }

        for(int z=0;z<i+1;++z){
            for(int l=0;l<j+1;l++){
                boardArr2D[z][l] = arr[z][l];
            }
        }

        myfile.close();
    }
    /* Dosyaya yazma işlemi */
    void boardArray2D::writeToFile(){
        ofstream myfile;
        char fileName[50];

        cout << "Enter the name of the file: ";
        cin >> fileName;

        myfile.open(fileName);

        for(int i=0;i<x;i++){
            for(int j=0;j<y;j++){
                if(boardArr2D[i][j] == 99)
                    myfile << "bb" << " ";
                else if(boardArr2D[i][j] >= 0 && boardArr2D[i][j] < 10)
                    myfile << "0" << boardArr2D[i][j] << " ";
                else
                    myfile << boardArr2D[i][j] << " ";
            }
            myfile << endl;
        }

        cout << fileName << " was created. " << endl;

        myfile.close();
    }
    /* Board çözüme getirilir. Resetlenir. */
    void boardArray2D::reset(){
        int k = 1;   
        
        for(int i=0;i<x;i++)
            for(int j=0;j<y;j++)
                boardArr2D[i][j] = 1;
      
        for(int i=0;i<x;i++)
            for(int j=0;j<y;j++)
                if(boardArr2D[i][j] != 0)
                    boardArr2D[i][j] = k++;              
        
        boardArr2D[x-1][y-1] = 99;
    }
    /* x ve y değerlerine parametreler atanır. */
    void boardArray2D::setSize(int xVal,int yVal){
        x = xVal;
        y = yVal;
        boardArr2D = new int*[x];
        for (int i = 0; i < x; ++i)
            boardArr2D[i] = new int[y];
        _lastMove = 'S';
        _numberOfMoves = 0;
    }
    /* Move fonksiyonu */
    void boardArray2D::move(char c){
        int temp=0,blankIndexes[2]={};

        for(int i=0;i<x;i++){
            for(int j=0;j<y;j++){
                if(boardArr2D[i][j] == 99){
                    blankIndexes[0] = i;
                    blankIndexes[1] = j;
                } 
            }
        }

        switch(c){
            case 'l':
            case 'L': // Sol tarafta boşluk var ise sol tarafa hareket eder.
                if(blankIndexes[1] != 0 && boardArr2D[blankIndexes[0]][blankIndexes[1]-1] != 0){
                    temp = boardArr2D[blankIndexes[0]][blankIndexes[1]-1];
                    boardArr2D[blankIndexes[0]][blankIndexes[1]-1] = boardArr2D[blankIndexes[0]][blankIndexes[1]];
                    boardArr2D[blankIndexes[0]][blankIndexes[1]] = temp;
                    _numberOfMoves++;
                    _lastMove = 'L';
                }else{
                    cout << "There is no room on the left side" << endl;
                }
                break;
            case 'r':
            case 'R': // Sağ tarafta boşluk var ise sol tarafa hareket eder.
                if(blankIndexes[1] != y-1 && boardArr2D[blankIndexes[0]][blankIndexes[1]+1] != 0){
                    temp = boardArr2D[blankIndexes[0]][blankIndexes[1]+1];
                    boardArr2D[blankIndexes[0]][blankIndexes[1]+1] = boardArr2D[blankIndexes[0]][blankIndexes[1]];
                    boardArr2D[blankIndexes[0]][blankIndexes[1]] = temp;
                    _numberOfMoves++;
                    _lastMove = 'R';
                }else{
                    cout << "There is no room on the right side" << endl;
                }
                break;
            case 'u':
            case 'U': // Yukarda boşluk var ise sol tarafa hareket eder.
                if(blankIndexes[0] != 0 && boardArr2D[blankIndexes[0]-1][blankIndexes[1]] != 0){
                    temp = boardArr2D[blankIndexes[0]-1][blankIndexes[1]];
                    boardArr2D[blankIndexes[0]-1][blankIndexes[1]] = boardArr2D[blankIndexes[0]][blankIndexes[1]];
                    boardArr2D[blankIndexes[0]][blankIndexes[1]] = temp;
                    _numberOfMoves++;
                    _lastMove = 'U';
                }else{
                    cout << "There is no room upstairs" << endl;
                }
                break;
            case 'd':
            case 'D': // Aşağıda boşluk var ise sol tarafa hareket eder.
                if(blankIndexes[0] != x-1 && boardArr2D[blankIndexes[0]+1][blankIndexes[1]] != 0){
                    temp = boardArr2D[blankIndexes[0]+1][blankIndexes[1]];
                    boardArr2D[blankIndexes[0]+1][blankIndexes[1]] = boardArr2D[blankIndexes[0]][blankIndexes[1]];
                    boardArr2D[blankIndexes[0]][blankIndexes[1]] = temp;
                    _numberOfMoves++;
                    _lastMove = 'D';
                }else{
                    cout << "There is no room downstairs" << endl;
                }
                break;
            /* boardArr2Di yeniden karistirma islemi burada yap�l�yor(bir fonksiyon yardimiyla) */
            case 's':
            case 'S':
                //shuffle(boardArr2D,size);
                break;
            case 'i':
            case 'I':
                //intelligent(boardArr2D,size);
                break;
            case 'q':
            case 'Q':
                /* ��kma i�lemi */
                cout << "Exiting..." << endl;
                exit(1);
            default :
                /* Yanl�� de�er girilirse diye. */
                cout << "Wrong Input. Try Again..." << endl;
        }
    }
    /* Boardın solved olup olmadığına bakan fonksiyon */
    bool boardArray2D::isSolved(){
        int** solvedBoard,k=1;
        solvedBoard = new int*[x];
        for (int i = 0; i < x; ++i)
            solvedBoard[i] = new int[y];

        for(int i=0;i<x;i++)
            for(int j=0;j<y;j++)
                solvedBoard[i][j] = 1;
      
        for(int i=0;i<x;i++)
            for(int j=0;j<y;j++)
                if(solvedBoard[i][j] != 0)
                    solvedBoard[i][j] = k++;              
        
        solvedBoard[x-1][y-1] = 99;

        for(int i=0;i<x;i++){
            for(int j=0;j<y;j++){
                if(boardArr2D[i][j] != solvedBoard[i][j]){
                    return false;
                }else{
                    if(i == x-1 && j == y-1)
                        return true;
                }
            }
        }  
        for(int i=0;i<y;++i) {
            delete[] solvedBoard[i];   
        }
        delete[] solvedBoard;      
    }
    /* row ve column u girince oradaki değeri döndüren fonksiyon */
    int& boardArray2D::operator()(int row,int column){
        if(x*y > row+column){
            return boardArr2D[row][column];
        }else{
            cout << "Wrong entered row or column...Exiting..." << endl;
            exit(1);
        }
        
    }
    /* İki boardın eşit olup olmadığını kontrol eden fonksiyon */
    bool boardArray2D::operator==(const AbstractBoard& rightSide){
        const boardArray2D *arr2D = dynamic_cast<const boardArray2D*>(&rightSide); // Downcast yaparak AbstractBoard objesini bizim objemize dönüştürürüz.
        if (arr2D == NULL){
            return false;
        }else{
            if(x != arr2D->x || y != arr2D->y){
                return false;
            }else{
                for(int i=0;i<x;i++){
                    for(int j=0;j<y;j++){
                        if(boardArr2D[i][j] != arr2D->boardArr2D[i][j]){
                            return false;
                        }else{
                            if(i==x-1 && j==y-1){
                                return true;
                            }
                        }
                    }
                }
            }
        }
            
    }
    /* Destructor */
    boardArray2D::~boardArray2D(){
        for(int i=0; i<x; i++) {
            delete [] boardArr2D[i];
        }
        delete[] boardArr2D;
    }
}