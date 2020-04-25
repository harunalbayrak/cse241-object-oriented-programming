/* Gebze Technical University         */
/* Computer Engineering               */
/* Kodu hazirlayan : Harun ALBAYRAK   */
/* Numara : 171044014                 */
/* 5.HOMEWORK                         */
#include<iostream>
#include<vector>
#include<cstdlib>
#include"abstractBoard.h"
#include"boardVector.h"
#include"boardArray1D.h"
#include"boardArray2D.h"

using namespace std;
using namespace classesOfBoard;

void testGame(int argc,char** argv);  /* Normal oyunu test eder. */
void testValidity(int argc, char** argv); /* "isValid" fonksiyonunun kullanıldığı test fonksiyonu */
bool isValid(AbstractBoard **sequenceOfMoves,int size); /* Geçerli bir çözüm olup olmadığını kontrol eder */


int main(int argc, char** argv){
    srand(time(NULL));
    int input=0;
    char repeat;
    
    /* 1 e basarsanız oyunu test eder 2 ye basarsanız validity i test eder */
    do{
        cout << "Test the game : press 1\n";
        cout << "Test the validity : press 2\n";
        do{
            cin >> input;
            if(input <= 0 || input > 2)
                cout << "Wrong Input. Try Again..." << endl;
        }while(input <= 0 || input > 2);
        switch (input){
            case 1:
                testGame(argc,argv);
                break;
            case 2:
                testValidity(argc,argv);
                break;
        }
        cout << "Do you want to repeat? (Y / N)\n";  /* isterseniz tekrar edebilirsiniz. */
        do{
            cin >> repeat;
            if(repeat != 'Y' && repeat != 'N' && repeat != 'y' && repeat != 'n')
                cout << "Wrong Input. Try Again..." << endl;
        }while(repeat != 'Y' && repeat != 'N' && repeat != 'y' && repeat != 'n');
    }while(repeat == 'Y' || repeat == 'y');
    

    return 0;
}


void testGame(int argc,char** argv){
    char input;
    int boardSize=0,input2=0;
    AbstractBoard *board;
    if(argc == 1){
        cout << "TEST with vector : press 1\n"; // Vectorle test etmek için 1 e basınız.
        cout << "TEST with 1 dimensional array : press 2\n"; // 1 boyutlu arrayle test etmek için 1 e basınız.
        cout << "TEST with 2 dimensional array : press 3\n"; // 2 boyutlu arrayle etmek için 1 e basınız.
        do{
            cin >> input2;
            if(input2 <= 0 || input2 > 3)
                cout << "Wrong Input. Try Again..." << endl;
        }while(input2 <= 0 || input2 > 3);

        cout << "Please enter the board size: "; // Takes the board size.
        do{
            cin >> boardSize;
            if(boardSize < 3 || boardSize > 9)
                cout << "Wrong Input. Try Again..." << endl;
        }while(boardSize < 3 || boardSize > 9);
        
        
        switch(input2){
            case 1:
                board = new boardVector(boardSize,boardSize);  // Vector oluşturur.
                break;
            case 2:
                board = new boardArray1D(boardSize,boardSize); // 1 boyutlu array oluşturur.
                break;
            case 3:
                board = new boardArray2D(boardSize,boardSize); // 2 boyutlu array oluşturur.
                break;
        }
    }
    else{ // Eğer konsolda dosya ismi girilidiyse buraya girer.
        cout << "Read from file operation with vector : press 1\n"; // Dosyayı vektör ile açar.
        cout << "Read from file operation with 1 dimensional array : press 2\n"; // Dosyayı 1 boyutlu array ile açar.
        cout << "Read from file operation with 2 dimensional array : press 3\n"; // Dosyayı 2 boyutlu array ile açar.
        do{
            cin >> input2;
            if(input2 <= 0 || input2 > 3)
                cout << "Wrong Input. Try Again..." << endl;
        }while(input2 <= 0 || input2 > 3);

        switch(input2){
            case 1:
                board = new boardVector(argc,argv,argv[0],0); // Vector oluşturur.
                break;
            case 2: 
                board = new boardArray1D(argc,argv,argv[0],0); // 1 boyutlu array oluşturur.
                break;
            case 3:
                board = new boardArray2D(argc,argv,argv[0],0); // 2 boyutlu array oluşturur.
                break;
        }
    }

    board->print();
    while(!board->isSolved()){  // Board çözülene kadar oyunu sürdürür(q ya basarsanız çıkar.)
        cout << "Your move : " ;
        cin >> input;
        if(input == 'o' || input == 'O') // Dosyadan board okur.
            board->readFromFile(argc,argv,argv[0],2);
        else if(input == 'e' || input == 'E') // Board� dosyaya kaydeder.
            board->writeToFile();            
        else
            board->move(input);

        if(input=='l' || input=='L' || input=='r' || input=='R' || input=='d'
        || input=='D' || input=='u' || input=='U' || input=='e' || input=='E'
        || input=='o' || input=='O'){
            board->print();
        }
    }
    if(board->isSolved()){  // Board çözülürse buraya girer.
        cout << "Congrulations !!! You win the game! \n";
        cout << "Number of moves : " << board->numberOfMoves() << endl;
    }
    
}
void testValidity(int argc, char** argv){
    int input=0,size=0;

    cout << "TEST with vector : press 1\n"; // Vektörle test etmek için 1 e basın.
    cout << "TEST with 1 dimensional array : press 2\n"; // 1 boyutlu arrayle test etmek için 1 e basın.
    cout << "TEST with 2 dimensional array : press 3\n"; // 2 boyutlu arrayle test etmek için 1 e basın.
    do{
        cin >> input;
        if(input <= 0 || input > 3)
            cout << "Wrong Input. Try Again..." << endl;
    }while(input <= 0 || input > 3);

    cout << "How many size would you like? : ";  // Kaç dosyadan validity kontrol edilecek?
    cin >> size;

    AbstractBoard **boards = new AbstractBoard*[size]; // size kadar board oluşturur.
    switch(input){
        case 1:
            for(int i=0;i<size;i++){
                cout << "for " << i+1 << ".FILE ";  
                boards[i] = new boardVector(argc,argv,argv[0],2); // Vektör ile oluşturur.
            }
            if(size > 0 && isValid(boards,size))
                cout << "Valid \n";
            else
                cout << "Not Valid \n";
            break;
        
        case 2:
            for(int i=0;i<size;i++){
                cout << "for " << i+1 << ".FILE "; 
                boards[i] = new boardArray1D(argc,argv,argv[0],2); // 1 boyutlu array ile oluşturur.
            }
            if(size > 0 && isValid(boards,size))
                cout << "Valid \n";
            else
                cout << "Not Valid \n";
            break;

        case 3:
            for(int i=0;i<size;i++){
                cout << "for " << i+1 << ".FILE ";
                boards[i] = new boardArray2D(argc,argv,argv[0],2); // 2 boyutlu array ile oluşturur.
            }
            if(size > 0 && isValid(boards,size))
                cout << "Valid \n";
            else
                cout << "Not Valid \n";
            break;
    }
    
}
bool isValid(AbstractBoard **sequenceOfMoves,int size){
    int x = sequenceOfMoves[0]->getX();
    int y = sequenceOfMoves[0]->getY();
    vector<int>blank_cell_x; // boş cellin x ekseninin tutulduğu değişken
    vector<int>blank_cell_y; // boş cellin y ekseninin tutulduğu değişken
    int new_blank_x=0,new_blank_y=0,old_blank_x=0,old_blank_y,newVal=0,control=0;
    int leftVal=0,rightVal=0,upVal=0,downVal=0; // etrafındaki değerleri tutar
    bool leftCheck=true,rightCheck=true,upCheck=true,downCheck=true; // ne tarafa gidilip gidilemeyeceğini test eder


    for(int k=0;k<size;k++){
        for(int i=0;i<x;i++){
            for(int j=0;j<y;j++){
                if(sequenceOfMoves[k]->operator()(i,j) == 99){
                    blank_cell_x.push_back(i);   // boş cell in x ve y sini bulur.
                    blank_cell_y.push_back(j);
                }
            }
        }
        
        if(k >= 1){ // etrafındaki kısımların eğer gidebiliyorsa değerlerini tutar.
            if(blank_cell_x[k-1] != 0 && sequenceOfMoves[k-1]->operator()(blank_cell_x[k-1]-1,blank_cell_y[k-1]) != 0)
                upVal = sequenceOfMoves[k-1]->operator()(blank_cell_x[k-1]-1,blank_cell_y[k-1]);
            else
                upCheck = false;
            if(blank_cell_y[k-1] != 0 && sequenceOfMoves[k-1]->operator()(blank_cell_x[k-1],blank_cell_y[k-1]-1) != 0)
                leftVal = sequenceOfMoves[k-1]->operator()(blank_cell_x[k-1],blank_cell_y[k-1]-1);
            else
                leftCheck = false;
            if(blank_cell_y[k-1] != y-1 && sequenceOfMoves[k-1]->operator()(blank_cell_x[k-1],blank_cell_y[k-1]+1) != 0)
                rightVal = sequenceOfMoves[k-1]->operator()(blank_cell_x[k-1],blank_cell_y[k-1]+1);
            else
                rightCheck = false;
            if(blank_cell_x[k-1] != x-1 && sequenceOfMoves[k-1]->operator()(blank_cell_x[k-1]+1,blank_cell_y[k-1]) != 0)
                downVal = sequenceOfMoves[k-1]->operator()(blank_cell_x[k-1]+1,blank_cell_y[k-1]);
            else
                downCheck = false;

            old_blank_x = blank_cell_x[k-1];
            old_blank_y = blank_cell_y[k-1];
            new_blank_x = blank_cell_x[k];
            new_blank_y = blank_cell_y[k];
            if(k >= 1){
                control = 0;
                if(new_blank_x == old_blank_x-1 && new_blank_y == old_blank_y && upCheck){  // üst tarafı kontrol eder.
                    newVal = sequenceOfMoves[k]->operator()(new_blank_x+1,new_blank_y);
                    if(upVal == newVal)
                        control = 1;
                    else
                        control = 0;
                }
                else if(new_blank_x == old_blank_x && new_blank_y == old_blank_y-1 && leftCheck){ // sağ tarafı kontrol eder.
                    newVal = sequenceOfMoves[k]->operator()(new_blank_x,new_blank_y+1);
                    if(leftVal == newVal)
                        control = 1;
                    else
                        control = 0;
                }
                else if(new_blank_x == old_blank_x && new_blank_y == old_blank_y+1 && rightCheck){ // sol tarafı kontrol eder.
                    newVal = sequenceOfMoves[k]->operator()(new_blank_x,new_blank_y-1);
                    if(rightVal == newVal)
                        control = 1;
                    else
                        control = 0;
                }
                else if(new_blank_x == old_blank_x+1 && new_blank_y == old_blank_y && downCheck){ // alt tarafı kontrol eder.
                    newVal = sequenceOfMoves[k]->operator()(new_blank_x-1,new_blank_y);
                    if(downVal == newVal)
                        control = 1;
                    else
                        control = 0;
                }
                if(control == 1 && k == size-1){  
                    return sequenceOfMoves[k]->isSolved();  // eğer hamleler "valid" ise ve son board "solved" ise "true" döndülür. Aksi takdirde "false" döner.
                }
                if(control == 0 || k == size-1){
                    return control; // hamleler valid değilse buraya girer. ve 0 döndürür.
                }
            }
        }
        
    }
    
}