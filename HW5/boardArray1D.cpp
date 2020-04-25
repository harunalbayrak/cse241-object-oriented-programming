#include<iostream>
#include<vector>
#include<fstream>
#include<ctime>
#include<cstdlib>
#include"boardArray1D.h"

namespace classesOfBoard{
    /* Dosyadan board okur */
    boardArray1D::boardArray1D(int argc,char **argv,char *fileName,int check) : AbstractBoard(){
        _numberOfBoards++;
        readFromFile(argc,argv,fileName,check);
    }
    /* Girilen değerleri x ve y si olacak şekilde rastgele board oluşturur. */
    boardArray1D::boardArray1D(int xVal,int yVal) : AbstractBoard(){
        _numberOfBoards++;
        int randomNum=0,randomNum2=0,k=1,blankIndex=0,size=xVal,temp=0;
        setSize(xVal,yVal); 
        reset();

        randomNum = (rand() % 100) + 50;

        for(int i=0;i<x*y;i++)
            if(boardArr1D[i] == 99)
                blankIndex = i;

        while(randomNum != 0){
            randomNum2 = rand() % 4;
            if(randomNum2 == 0 && (blankIndex % size == 0))
                continue;
            else if(randomNum2 == 1 && (blankIndex % size == size-1))
                continue;
            else if(randomNum2 == 2 && (blankIndex < size))
                continue;
            else if(randomNum2 == 3 && (blankIndex >= (size*size)-size))
                continue;

            switch(randomNum2){
                case 0:
                    boardArr1D[blankIndex] = boardArr1D[blankIndex-1];
                    blankIndex--;
                    break;
                case 1:
                    boardArr1D[blankIndex] = boardArr1D[blankIndex+1];
                    blankIndex++;
                    break;
                case 2:
                    boardArr1D[blankIndex] = boardArr1D[blankIndex-size];
                    blankIndex -= size;
                    break;
                case 3:
                    boardArr1D[blankIndex] = boardArr1D[blankIndex+size];
                    blankIndex += size;
                    break; 
            }
            boardArr1D[blankIndex] = 99;
            randomNum--;
        }
    }
    /* Copy Constructor */
    boardArray1D::boardArray1D(const boardArray1D& rightSide){
        _numberOfBoards++;
        x = rightSide.x;
        y = rightSide.y;
        _lastMove = rightSide._lastMove;
        _numberOfBoards = rightSide._numberOfBoards;
        _numberOfMoves = rightSide._numberOfMoves;
        delete[] boardArr1D;
        boardArr1D = new int[x*y];
        for(int i=0;i<x*y;i++)
            boardArr1D[i] = rightSide.boardArr1D[i];
    }
    /* Print fonksiyonu */
    void boardArray1D::print(){
        for(int i=0;i<x*y;i++){
            if(i % y == 0)
                cout << endl;
            if(boardArr1D[i] == 99)
                cout << "   ";   
            else{
                if(boardArr1D[i] < 10)
                    cout << "0" << boardArr1D[i] << " ";
                else
                    cout << boardArr1D[i] << " ";
            } 
        }
        cout << endl; 
    }
    /* Dosyadan okuma işlemi */
    void boardArray1D::readFromFile(int argc,char **argv,char *fileName,int check){
        int i=0,j=-1,arr[81],m=-1;
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
                i++;
                m++;
                j=0;
            }else{
                j++;
                m++;
            }
            arr[m] = atoi(bb);
            if(bb[0] == 'b' && bb[1] == 'b'){
                arr[m] = 99;
            }
        } 
        setSize(i+1,j+1);
        
        if(boardArr1D == NULL){
            boardArr1D = new int[x*y];
        }else{
            delete[] boardArr1D;
            boardArr1D = new int[x*y];
        }

        for(i=0;i<m+1;i++)
            boardArr1D[i] = arr[i];

        myfile.close();
    }
    /* Dosyaya yazma işlemi */
    void boardArray1D::writeToFile(){
        ofstream myfile;
        char fileName[50];

        cout << "Enter the name of the file: ";
        cin >> fileName;

        myfile.open(fileName);
        if(myfile.fail()==1)
            exit(1);
            

        for(int i=0;i<x*y;i++){
            if(boardArr1D[i] == 99)
                myfile << "bb" << " ";
            else if(boardArr1D[i] >= 0 && boardArr1D[i] < 10)
                myfile << "0" << boardArr1D[i] << " ";
            else
                myfile << boardArr1D[i] << " ";
            
            if(i % y == y-1)
                myfile << endl;
        }

        cout << fileName << " was created. " << endl;

        myfile.close();
    }
    /* Board çözüme getirilir. Resetlenir. */
    void boardArray1D::reset(){
        int k=1;
        for(int i=0;i<x*y;i++)
            boardArr1D[i] = 1;
        for(int i=0;i<x*y;i++)
            boardArr1D[i] = k++;
        
        boardArr1D[x*y-1] = 99;
    }
    /* x ve y değerlerine parametreler atanır. */
    void boardArray1D::setSize(int xVal,int yVal){
        x = xVal;
        y = yVal;
        boardArr1D = new int[x*y];
        _lastMove = 'S';
        _numberOfMoves = 0;
    }
    /* Move fonksiyonu */
    void boardArray1D::move(char c){
        int temp=0,blankIndex=0;

        for(int i=0;i<x*y;i++)
            if(boardArr1D[i] == 99)
                blankIndex = i;
        cout << blankIndex << endl;
        switch(c){
            case 'l':
            case 'L': 
                if(blankIndex % y != 0 && boardArr1D[blankIndex-1] != 0){
                    temp = boardArr1D[blankIndex-1];
                    boardArr1D[blankIndex-1] = boardArr1D[blankIndex];
                    boardArr1D[blankIndex] = temp;
                    _numberOfMoves++;
                    _lastMove = 'L';
                }else
                    cout << "There is no room on the left side" << endl; /* Solda yer yok ise hareket edilmiyor. */
                
                break;
            case 'r':
            case 'R': 
                if(blankIndex % y != y-1 && boardArr1D[blankIndex+1] != 0){
                    temp = boardArr1D[blankIndex+1];
                    boardArr1D[blankIndex+1] = boardArr1D[blankIndex];
                    boardArr1D[blankIndex] = temp;
                    _numberOfMoves++;
                    _lastMove = 'R';
                }else
                    cout << "There is no room on the right side" << endl; /* Sagda yer yok ise hareket edilmiyor.*/
                
                break;
            case 'u':
            case 'U': 
                if(blankIndex >= y && boardArr1D[blankIndex-y] != 0){
                    temp = boardArr1D[blankIndex-y];
                    boardArr1D[blankIndex-y] = boardArr1D[blankIndex];
                    boardArr1D[blankIndex] = temp;
                    _numberOfMoves++;
                    _lastMove = 'U';
                }else
                    cout << "There is no room upstairs" << endl; /* Yukarida yer yok ise hareket edilmiyor.. */
                
                break;
            case 'd':
            case 'D': 
                if(blankIndex < (x*y)-y && boardArr1D[blankIndex+y] != 0){
                    temp = boardArr1D[blankIndex+y];
                    boardArr1D[blankIndex+y] = boardArr1D[blankIndex]; 
                    boardArr1D[blankIndex] = temp;
                    _numberOfMoves++;
                    _lastMove = 'D';
                }else
                    cout << "There is no room downstairs" << endl; /* Assagida yer yok ise hareket edilmiyor. */
                
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
    bool boardArray1D::isSolved(){
        int* solvedBoard,k=1;
        solvedBoard = new int[x*y];
        for(int i=0;i<x*y;i++)
            solvedBoard[i] = 1;
        for(int i=0;i<x*y;i++)
            solvedBoard[i] = k++;
        solvedBoard[x*y-1] = 99;
        
        for(int i=0;i<x*y;i++){
            if(boardArr1D[i] != solvedBoard[i]){
                return false;
            }else{
                if(i == x*y-1)
                    return true;
            }
        }
        delete[] solvedBoard;
    }
    /* row ve column u girince oradaki değeri döndüren fonksiyon */
    int& boardArray1D::operator()(int row,int column){
        if(x*y > row+column){
            return boardArr1D[(row*y)+column];
        }else{
            cout << "Wrong entered row or column...Exiting..." << endl;
            exit(1);
        }
        
    }
    /* İki boardın eşit olup olmadığını kontrol eden fonksiyon */
    bool boardArray1D::operator==(const AbstractBoard& rightSide){
        const boardArray1D *arr1D = dynamic_cast<const boardArray1D*>(&rightSide); // Downcast yaparak AbstractBoard objesini bizim objemize dönüştürürüz.
        if (arr1D == NULL){
            return false;
        }else{
            if(x != arr1D->x || y != arr1D->y){
                return false;
            }else{
                for(int i=0;i<x*y;i++){
                    if(boardArr1D[i] != arr1D->boardArr1D[i]){
                        return false;
                    }else{
                        if(i == x*y-1){
                            return true;
                        }
                    }
                }
            }
        }
            
    }
    /* Destructor */
    boardArray1D::~boardArray1D(){
       delete[] boardArr1D;
    }
}