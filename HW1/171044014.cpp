/* Gebze Technical University         */
/* Computer Engineering               */
/* Kodu hazirlayan : Harun ALBAYRAK   */
/* Numara : 171044014                 */
#include <iostream>
#include <cstdlib> 
#include <ctime>
using namespace std;

int takeBoardSize();
void createRandomTable(int board[],int size);
void showBoard(int board[],int size);
bool solvabilityOfTheTable(int board[],int size);
void gameCycle(int board[],int size);
void action(int board[],int size);
void shuffle(int board[],int size);
void intelligent(int board[],int size);
void intelligentAction(int board[],int size,int status[],int th);

int main() {
    int boardSize=0;
    int board1D[9*9]; /* Normalde malloc kullanmıştım fakat Yusuf Sinan hoca 9*9 boyutunda yapın dediği için böyle yaptım. iki(2) boyutlu bir array olusturma gereksinimi hissetmedim. */
    srand(time(NULL));
    
    cout << "Please enter the board size: ";
    
    /* Eger yanlis input girilirse buradan tekrar girilmesi saglaniyor. */
    boardSize = takeBoardSize();
    
    /* Arrayin tum elemanlari 0 a esitleniyor. */
    for(int i=0;i<boardSize*boardSize;i++)
                board1D[i] = 0;

	/* Random bir sekilde board olusturuluyor ve cozulebilirligi kontrol ediliyor eger
	cozulebilir degilse cozulebilir bir board olusturana kadar islem tekrar ediliyor.*/
    while(1){
        createRandomTable(board1D,boardSize);

        if(solvabilityOfTheTable(board1D,boardSize)){
            cout << "Your initial random board is " << endl;
        }

        if(!solvabilityOfTheTable(board1D,boardSize)){
            for(int i=0;i<boardSize*boardSize;i++)
                board1D[i] = 0;
        }else{
            break;
        }
    }
    
    /* Oyunun oynanma dongusu burada. Oyunun bitip bitmedigi kontrol ediliyor ve eger oyun
	bitmisse oyundan cikiliyor. */
    gameCycle(board1D,boardSize);


    return 0;
}

int takeBoardSize(){
    /* Board Size'ı alıyor. */
    int n;
    do{
        cin >> n;
        if(n < 3 || n > 9 && n != 0)
            cout << "Wrong Input. Try Again..." << endl;
    }while(n < 3 || n > 9);

    return n;
}

void createRandomTable(int board[],int size){
    int randomNum=0,control=1;
    int i=0,j=0;
    const int squareOfBoardSize = size*size;

	/* Ayni sayinin atanip atanmadiğini burada kontrol ediyorum ve tüm sayilarin farkli olmasini sagliyorum */
    do{
        randomNum = rand() % squareOfBoardSize + 1; /* 1 den size*size a kadar random say� atan�yor */
        for(i=0;i<squareOfBoardSize;i++){
            if(board[i] == randomNum){ /* Eger random sayi onceki sayilar ile ayniysa tekrar sayi ataniyor ta ki onceki sayilar ile ayni sayi denk gelmeyene dek. */
                control = 1;
                break;
            }else{
                control = 0;
            }
        }
        if(control == 0){
            board[j++] = randomNum;
        }
    }while(control || j!=squareOfBoardSize );

    /* for(i=0;i<squareOfBoardSize;i++){
        cout << board[i] << " ";
    } */
}

void showBoard(int board[],int size){
	/* Board burada bastiriliyor. */
    for(int i=0;i<size*size;i++){
        if(i % size == 0)
            cout << endl;
        if(board[i] == size*size)
            cout << " \t";
        else
            cout << board[i] << "\t"; 
    }
    cout << endl;
}

bool solvabilityOfTheTable(int board[],int size){
	/* Olusturulan random boardin cozulebilir olup olmadigini burada kontrol ediyorum eger
	board cozulemeyen bir board ise tekrar board olusturuluyor(cozulebilir board olusana kadar.) */
	
    int numberOfInversion=0,positionXfromBottom=0;
    /* Inversion sayisini burdaki dongoler sayesinde buluyorum */
    for(int i=0;i<size*size;i++){
        for(int j=i+1;j<=size*size;j++){
            if(board[i] > board[j] && board[i] != size*size)
                ++numberOfInversion;
        }
    }

	/* X in assagidan kac blok yukarida oldu�unu buradan buluyorum */
    if(size % 2 == 0){
        for(int i=0;i<size*size;i++){
            if(board[i] == size*size){
                positionXfromBottom = i / size;
                positionXfromBottom = size - positionXfromBottom;
                break;
            }
        }
    }
    // cout << numberOfInversion << endl;
    // cout << positionXfromBottom << endl;

	/* cozulebilir olup olmadigini donduren kisimlar */
    if(size % 2 == 1){
        if(numberOfInversion % 2 == 0)
            return true;
        else
            return false;        
    }else{
        if(positionXfromBottom % 2 == 1){
            if(numberOfInversion % 2 == 0)
                return true;
            else
                return false;
        }else{
            if(numberOfInversion % 2 == 0)
                return true;
            else
                return false;
        }
    }
}

void gameCycle(int board[],int size){
    /* Oyunun cycle i burada. */
    int totalNumberOfMoves=0,control=0;
    do{
    	++totalNumberOfMoves;
    	control = 0;
    	showBoard(board,size);
    	action(board,size);
    	
    	for(int i=0;i<size*size;i++){
    		if(board[i] == i+1)
    			control++;
		}
		
		if(control == size*size){
			showBoard(board,size);
			cout << "Congratulations.!!! You are winner.!!!" << endl;
			cout << "Total Number of Moves : " << totalNumberOfMoves << endl;	
			break;
		}
	}while(control != size*size);
}

void action(int board[],int size){
	/* Hareket bu fonksiyon sayesinde olusturuluyor. */
    char input;
    int emptyCell=0,temp=0;
    cout << "Your Move: ";
    cin >> input;

	/* Bos blogun nerede oldugunu buluyorum */
    for(int i=0;i<size*size;i++){
        if(board[i] == size*size)
            emptyCell = i;
    }

	/* Hareket bolmesi */
    switch(input){
        case 'l':
        case 'L': 
            if(emptyCell % size != 0){
                temp = board[emptyCell-1];
                board[emptyCell-1] = board[emptyCell];
                board[emptyCell] = temp;
            }else
                cout << "There is no room on the left side" << endl; /* Solda yer yok ise hareket edilmiyor. */
            
            break;
        case 'r':
        case 'R': 
            if(emptyCell % size != size-1){
                temp = board[emptyCell+1];
                board[emptyCell+1] = board[emptyCell];
                board[emptyCell] = temp;
            }else
                cout << "There is no room on the right side" << endl; /* Sagda yer yok ise hareket edilmiyor.*/
            
            break;
        case 'u':
        case 'U': 
            if(emptyCell >= size){
                temp = board[emptyCell-size];
                board[emptyCell-size] = board[emptyCell];
                board[emptyCell] = temp;
            }else
                cout << "There is no room upstairs" << endl; /* Yukarida yer yok ise hareket edilmiyor.. */
            
            break;
        case 'd':
        case 'D': 
            if(emptyCell < (size*size)-size){
                temp = board[emptyCell+size];
                board[emptyCell+size] = board[emptyCell]; 
                board[emptyCell] = temp;
            }else
                cout << "There is no room downstairs" << endl; /* Assagida yer yok ise hareket edilmiyor. */
            
            break;
        /* Boardi yeniden karistirma islemi burada yap�l�yor(bir fonksiyon yardimiyla) */
		case 's':
		case 'S':
			shuffle(board,size);
        	break;
        case 'i':
		case 'I':
			intelligent(board,size);
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

void shuffle(int board[],int size){
	int temp=0,randomNumber=0,randomNumber2=0,numberOfMoves=size*size,control=0;
	
	/* Board cozulmus hale getiriliyor. */
	for(int i=0;i<size*size;i++)
        board[i] = (i+1);

	/* size*size kadar rastgele hareket sa�lan�yor. */
    while(numberOfMoves != 0){
    	do{
    		randomNumber = rand()%(size*size); /* 1.say�n�n indisi */
    		randomNumber2 = rand()%(size*size); /* 2.say�n�n indisi. 1.say� ile 2.say�daki de�erler yer de�i�tiriyor. */
    		
    		/* E�er randomsay�lar ayn� ise i�lemler tekrar ediliyor ve yeniden 2 random say� �ekiliyor */
    		if(randomNumber == randomNumber2)
    			control=1;
    		else
    			control=0;
		}while(control);
		
		temp = board[randomNumber];
    	board[randomNumber] = board[randomNumber2];
    	board[randomNumber2] = temp;
    	
    	/* hareket say�s� 0 olana dek devam ediyor. */
    	--numberOfMoves;
	}            
    
}

void intelligent(int board[],int size){
    /* intelligent move burada olusturuluyor */
    int emptyCell=0,i=0,j=0,temp=0,howMany=0,randomNum=0,control=1;
    int *num = NULL;
    int status[4]={};

    /* bos blok bulunuyor */
    for(int i=0;i<size*size;i++)
        if(board[i] == size*size)
            emptyCell = i;

    
    if(emptyCell % size != 0)
        intelligentAction(board,size,status,0); /* eger sola hareket edilebiliyorsa baska fonksiyona degerler gonderiliyor */
    if(emptyCell % size != size-1)
        intelligentAction(board,size,status,1); /* eger saga hareket edilebiliyorsa baska fonksiyona degerler gonderiliyor */
    if(emptyCell >= size)
        intelligentAction(board,size,status,2); /* eger yukariya hareket edilebiliyorsa baska fonksiyona degerler gonderiliyor */
    if(emptyCell < (size*size)-size)
        intelligentAction(board,size,status,3); /* eger assagiya hareket edilebiliyorsa baska fonksiyona degerler gonderiliyor */

    /* kac olumlu hamle var onu buluyor */
    for(i=0;i<4;i++)
        if(status[i]==1)
            howMany++;

    /* eger olumlu hamle sayısı 0 ise rastgele bir hareket yapıyor */
    if(howMany == 0){
        do{
            randomNum = rand() % 4;
            if(emptyCell % size != 0 && randomNum == 0){
                temp = board[emptyCell-1];
                board[emptyCell-1] = board[emptyCell];
                board[emptyCell] = temp;
                control = 0;
            }else if(emptyCell % size != size-1 && randomNum == 1){
                temp = board[emptyCell+1];
                board[emptyCell+1] = board[emptyCell];
                board[emptyCell] = temp;
                control = 0;
            }else if(emptyCell >= size && randomNum == 2){
                temp = board[emptyCell-size];
                board[emptyCell-size] = board[emptyCell];
                board[emptyCell] = temp;
                control = 0;
            }else if(emptyCell < (size*size)-size && randomNum == 3){
                temp = board[emptyCell+size];
                board[emptyCell+size] = board[emptyCell]; 
                board[emptyCell] = temp;
                control = 0;
            }
        }while(control);
    
    /* eger olumlu hamle sayısı 1 ise olumlu taraf neresi ise o tarafa hareket ediyor */
    }else if(howMany == 1){
        num = (int *)malloc(sizeof(int));
        for(i=0;i<4;i++)
            if(status[i]==1)
                *num=i;
            
        if(*num==0){
            temp = board[emptyCell-1];
            board[emptyCell-1] = board[emptyCell];
            board[emptyCell] = temp;
        }else if(*num==1){
            temp = board[emptyCell+1];
            board[emptyCell+1] = board[emptyCell];
            board[emptyCell] = temp;
        }else if(*num==2){
            temp = board[emptyCell-size];
            board[emptyCell-size] = board[emptyCell];
            board[emptyCell] = temp;
        }else if(*num==3){
            temp = board[emptyCell+size];
            board[emptyCell+size] = board[emptyCell];
            board[emptyCell] = temp;
        }

    /* eger olumlu hamle sayisi 1 den fazla ise ozaman olumlu hamleler arasında rastgele secim yapiyor*/
    }else if(howMany > 1){
        num = (int *)malloc(howMany*sizeof(int));
        for(i=0;i<4;i++){
            if(status[i]==1){
                num[j]=i;
                j++;
            }
        }
        randomNum = rand() % j;
        
        if(num[randomNum] == 0){
            temp = board[emptyCell-1];
            board[emptyCell-1] = board[emptyCell];
            board[emptyCell] = temp;
        }else if(num[randomNum] == 1){
            temp = board[emptyCell+1];
            board[emptyCell+1] = board[emptyCell];
            board[emptyCell] = temp;
        }else if(num[randomNum] == 2){
            temp = board[emptyCell-size];
            board[emptyCell-size] = board[emptyCell];
            board[emptyCell] = temp;
        }else if(num[randomNum] == 3){
            temp = board[emptyCell+size];
            board[emptyCell+size] = board[emptyCell];
            board[emptyCell] = temp;
        }
               
    }

}

void intelligentAction(int board[],int size,int status[],int th){
    /* Bu fonksiyonda soldaki sagdaki yukaridaki assagidaki bloklarin asıl yerlerine olan uzakliklari bulunuyor ve o taraflara gidilmesi halinde olumlu yada olumsuz bir hamle olduguna
    bakiliyor */
    int emptyCell=0;
    int controlNums=0,firstDistance=0,secondDistance=0,modOfDistance1=0,modOfDistance2=0;

    for(int i=0;i<size*size;i++)
        if(board[i] == size*size)
            emptyCell = i;

    if(th == 0){
        controlNums = board[emptyCell-1];
        firstDistance = abs( ((controlNums-1) - (emptyCell-1)) );
        secondDistance = abs( ((controlNums-1) - (emptyCell)) );
    }else if(th == 1){
        controlNums = board[emptyCell+1];
        firstDistance = abs( ((controlNums-1) - (emptyCell+1)) );
        secondDistance = abs( ((controlNums-1) - (emptyCell)) );
    }else if(th == 2){
        controlNums = board[emptyCell-size];
        firstDistance = abs( ((controlNums-1) - (emptyCell-size)) );
        secondDistance = abs( ((controlNums-1) - (emptyCell)) );
    }else if(th == 3){
        controlNums = board[emptyCell+size];
        firstDistance = abs( ((controlNums-1) - (emptyCell+size)) );
        secondDistance = abs( ((controlNums-1) - (emptyCell)) );
    }

    if(firstDistance >= size){
        modOfDistance1 = (firstDistance / size) + (firstDistance % size);
    }else{
        modOfDistance1 = firstDistance;
    }
    if(secondDistance >= size){
        modOfDistance2 = (secondDistance / size) + (secondDistance % size);
    }else{
        modOfDistance2 = secondDistance;
    }
    status[th] = modOfDistance1 - modOfDistance2;
}