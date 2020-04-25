#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<ctime>
#include<cstdlib>
#include"boardVector.h"

namespace classesOfBoard{
    /* Dosyadan board okur */
    boardVector::boardVector(int argc,char **argv,char *fileName,int check) : AbstractBoard(){
        _numberOfBoards++;
        readFromFile(argc,argv,fileName,check);
    }
    /* Girilen değerleri x ve y si olacak şekilde rastgele board oluşturur. */
    boardVector::boardVector(int xVal,int yVal) : AbstractBoard(){
        _numberOfBoards++;
        int randomNum=0,randomNum2=0,k=1,blankIndex=0,size=xVal,temp=0;
        setSize(xVal,yVal); 
        reset();

        randomNum = (rand() % 100) + 50;

        for(int i=0;i<x*y;i++)
            if(boardVec[i] == 99)
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
                    boardVec[blankIndex] = boardVec[blankIndex-1];
                    blankIndex--;
                    break;
                case 1:
                    boardVec[blankIndex] = boardVec[blankIndex+1];
                    blankIndex++;
                    break;
                case 2:
                    boardVec[blankIndex] = boardVec[blankIndex-size];
                    blankIndex -= size;
                    break;
                case 3:
                    boardVec[blankIndex] = boardVec[blankIndex+size];
                    blankIndex += size;
                    break; 
            }
            boardVec[blankIndex] = 99;
            randomNum--;
        }
    }
    /* Print fonksiyonu */
    void boardVector::print(){
        for(int i=0;i<x*y;i++){
            if(i % y == 0)
                cout << endl;
            if(boardVec[i] == 99)
                cout << "   ";   
            else{
                if(boardVec[i] < 10)
                    cout << "0" << boardVec[i] << " ";
                else
                    cout << boardVec[i] << " ";
            }
        }
        cout << endl; 
    }
    /* Dosyadan okuma işlemi */
    void boardVector::readFromFile(int argc,char **argv,char *fileName,int check){
        int i=0,j=-1,m=-1,arr[81];
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
                m++;
                ++i;
                j=0;
            }else{
                m++;
                j++;
            }
            arr[m] = atoi(bb);
            if(bb[0] == 'b' && bb[1] == 'b'){
                arr[m] = 99;
            }
        } 
        setSize(i+1,j+1);

        for(int i=0;i<m+1;i++)
            boardVec.push_back(arr[i]);

        myfile.close();
    }
    /* Dosyaya yazma işlemi */
    void boardVector::writeToFile(){
        ofstream myfile;
        char fileName[50];

        cout << "Enter the name of the file: ";
        cin >> fileName;

        myfile.open(fileName);

        for(int i=0;i<boardVec.size();i++){
            if(boardVec[i] == 99)
                myfile << "bb" << " ";
            else if(boardVec[i] >= 0 && boardVec[i] < 10)
                myfile << "0" << boardVec[i] << " ";
            else
                myfile << boardVec[i] << " ";
            
            if(i % y == y-1)
                myfile << endl;
        }

        cout << fileName << " was created. " << endl;

        myfile.close();
    }
    /* Board çözüme getirilir. Resetlenir. */
    void boardVector::reset(){
        int k=1;
        boardVec.clear();
        for(int i=0;i<x*y;i++)
            boardVec.push_back(k++);
        
        boardVec[x*y-1] = 99;
    }
    /* x ve y değerlerine parametreler atanır. */
    void boardVector::setSize(int xVal,int yVal){
        x = xVal;
        y = yVal;
        _lastMove = 'S';
        _numberOfMoves = 0;
    }
    /* Move fonksiyonu */
    void boardVector::move(char c){
        int temp=0,blankIndex=0;

        for(int i=0;i<x*y;i++)
            if(boardVec[i] == 99)
                blankIndex = i;

        switch(c){
            case 'l':
            case 'L': 
                if(blankIndex % y != 0 && boardVec[blankIndex-1] != 0){
                    temp = boardVec[blankIndex-1];
                    boardVec[blankIndex-1] = boardVec[blankIndex];
                    boardVec[blankIndex] = temp;
                    _numberOfMoves++;
                    _lastMove = 'L';
                }else
                    cout << "There is no room on the left side" << endl; /* Solda yer yok ise hareket edilmiyor. */
                
                break;
            case 'r':
            case 'R': 
                if(blankIndex % y != y-1 && boardVec[blankIndex+1] != 0){
                    temp = boardVec[blankIndex+1];
                    boardVec[blankIndex+1] = boardVec[blankIndex];
                    boardVec[blankIndex] = temp;
                    _numberOfMoves++;
                    _lastMove = 'R';
                }else
                    cout << "There is no room on the right side" << endl; /* Sagda yer yok ise hareket edilmiyor.*/
                
                break;
            case 'u':
            case 'U': 
                if(blankIndex >= y && boardVec[blankIndex-y] != 0){
                    temp = boardVec[blankIndex-y];
                    boardVec[blankIndex-y] = boardVec[blankIndex];
                    boardVec[blankIndex] = temp;
                    _numberOfMoves++;
                    _lastMove = 'U';
                }else
                    cout << "There is no room upstairs" << endl; /* Yukarida yer yok ise hareket edilmiyor.. */
                
                break;
            case 'd':
            case 'D': 
                if(blankIndex < (x*y)-y && boardVec[blankIndex+y] != 0){
                    temp = boardVec[blankIndex+y];
                    boardVec[blankIndex+y] = boardVec[blankIndex]; 
                    boardVec[blankIndex] = temp;
                    _numberOfMoves++;
                    _lastMove = 'D';
                }else
                    cout << "There is no room downstairs" << endl; /* Assagida yer yok ise hareket edilmiyor. */
                
                break;
            /* boardVeci yeniden karistirma islemi burada yap�l�yor(bir fonksiyon yardimiyla) */
            case 's':
            case 'S':
                //shuffle(boardVec,size);
                break;
            case 'i':
            case 'I':
                //intelligent(boardVec,size);
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
    bool boardVector::isSolved(){
        vector<int>solvedBoard;
        for(int i=0;i<x*y;i++)
            solvedBoard.push_back(i+1);
        solvedBoard[x*y-1] = 99;

        if(boardVec == solvedBoard)
            return true;
        else
            return false;
    }
    /* row ve column u girince oradaki değeri döndüren fonksiyon */
    int& boardVector::operator()(int row,int column){
        if(boardVec.size() > row+column){
            return boardVec[(row*y)+column];
        }else{
            cout << "Wrong entered row or column...Exiting..." << endl;
            exit(1);
        }
        
    }
    /* İki boardın eşit olup olmadığını kontrol eden fonksiyon */
    bool boardVector::operator==(const AbstractBoard& rightSide){
        const boardVector *rightVec = dynamic_cast<const boardVector*>(&rightSide); // Downcast yaparak AbstractBoard objesini bizim objemize dönüştürürüz.
        if (rightVec == NULL){
            return false;
        }else{
            if(x != rightVec->x || y != rightVec->y){
                return false;
            }else{
                for(int i=0;i<x*y;i++){
                    if(boardVec[i] != rightVec->boardVec[i]){
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
}