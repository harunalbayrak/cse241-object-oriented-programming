import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Scanner;
import java.util.Random;

/**
 * The type Board array 1d.
 */
public class boardArray1D extends abstractBoard{
    private int[] board1D = new int[81];

    /**
     * Instantiates a new Board array 1d.
     *
     * @param file the file
     */
    public boardArray1D(String file){
        super(0,0);
        readFromFile(file);
    }

    /**
     * Instantiates a new Board array 1d.
     *
     * @param xVal the x val
     * @param yVal the y val
     */
    public boardArray1D(int xVal,int yVal){
        super(xVal,yVal);
        Random random = new Random();
        int randomNum2=0,blankIndex=0,size=x;
        int randomNum = random.nextInt(x*20 + y*20) + 50;

        for(int i=0;i<x*y;i++)
            board1D[i] = 1;
        reset();
        for(int i=0;i<x*y;i++)
            if(board1D[i] == -99)
                blankIndex = i;

        while(randomNum != 0){
            randomNum2 = random.nextInt(4);
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
                    board1D[blankIndex] = board1D[blankIndex-1];
                    blankIndex--;
                    break;
                case 1:
                    board1D[blankIndex] = board1D[blankIndex+1];
                    blankIndex++;
                    break;
                case 2:
                    board1D[blankIndex] = board1D[blankIndex-size];
                    blankIndex -= size;
                    break;
                case 3:
                    board1D[blankIndex] = board1D[blankIndex+size];
                    blankIndex += size;
                    break;
            }
            board1D[blankIndex] = -99;
            randomNum--;
        }
    }

    @Override
    public String toString() {
        String Board = stringOfBoard(1);
        return Board;
    }

    @Override
    public void readFromFile(String file) {
        try{
            read(file);
        }
        catch(Exception e){
            System.out.println(e.getMessage());
        }
    }

    @Override
    public void writeFromFile(String file) {
        try{
            String Board = stringOfBoard(2);
            FileWriter myFile = new FileWriter(file);
            myFile.write(Board);
            myFile.close();
            System.out.println("It was successfully written to the file.");
        } catch (IOException e){
            e.printStackTrace();
        }
    }

    @Override
    public void reset() {
        int k=1;
        for(int i=0;i<x*y;i++){
            if(board1D[i] != 0)
                board1D[i] = k++;
        }
        board1D[x*y-1] = -99;
    }

    @Override
    public void move(char c) {
        int temp=0,blankIndex=0;

        for(int i=0;i<x*y;i++)
            if(board1D[i] == -99)
                blankIndex = i;
        switch(c){
            case 'l':
            case 'L':
                if(blankIndex % y != 0 && board1D[blankIndex-1] != 0){
                    temp = board1D[blankIndex-1];
                    board1D[blankIndex-1] = board1D[blankIndex];
                    board1D[blankIndex] = temp;
                    _numberOfMoves++;
                    _lastMove = 'L';
                }else
                    System.out.println("There is no room on the left side"); /* Solda yer yok ise hareket edilmiyor. */
                break;
            case 'r':
            case 'R':
                if(blankIndex % y != y-1 && board1D[blankIndex+1] != 0){
                    temp = board1D[blankIndex+1];
                    board1D[blankIndex+1] = board1D[blankIndex];
                    board1D[blankIndex] = temp;
                    _numberOfMoves++;
                    _lastMove = 'R';
                }else
                    System.out.println("There is no room on the right side"); /* Sagda yer yok ise hareket edilmiyor. */
                break;
            case 'u':
            case 'U':
                if(blankIndex >= y && board1D[blankIndex-y] != 0){
                    temp = board1D[blankIndex-y];
                    board1D[blankIndex-y] = board1D[blankIndex];
                    board1D[blankIndex] = temp;
                    _numberOfMoves++;
                    _lastMove = 'U';
                }else
                    System.out.println("There is no room upstairs"); /* Yukarida yer yok ise hareket edilmiyor.. */
                break;
            case 'd':
            case 'D':
                if(blankIndex < (x*y)-y && board1D[blankIndex+y] != 0){
                    temp = board1D[blankIndex+y];
                    board1D[blankIndex+y] = board1D[blankIndex];
                    board1D[blankIndex] = temp;
                    _numberOfMoves++;
                    _lastMove = 'D';
                }else
                    System.out.println("There is no room downstairs"); /* Assagida yer yok ise hareket edilmiyor. */
                break;
            case 'q':
            case 'Q':
                /* ï¿½ï¿½kma iï¿½lemi */
                System.out.println("Exiting...");
                System.exit(0);
            default :
                /* Yanlï¿½ï¿½ deï¿½er girilirse diye. */
                System.out.println("Wrong Input. Try Again...");
        }
    }

    @Override
    public boolean isSolved() {
        int k=1;
        boolean status=false;
        int[] solvedBoard = new int[x*y];
        for(int i=0;i<x*y;i++){
            solvedBoard[i] = board1D[i];
        }
        for(int i=0;i<x*y;i++)
            if(solvedBoard[i] != 0)
                solvedBoard[i] = k++;

        solvedBoard[x*y-1] = -99;

        for(int i=0;i<x*y;i++){
            if(board1D[i] != solvedBoard[i]){
                status = false;
                break;
            }else{
                if(i == x*y-1)
                    status = true;
            }
        }
        return status;
    }

    public int cell(int _x,int _y){
        int val = 0;
        try{
            if(x*y > _x*_y){
                val = board1D[_x*y+_y];
            }else{
                throw new IndexOutOfBoundsException();
            }
        }
        catch (IndexOutOfBoundsException e){
            e.printStackTrace();
        }
        return val;
    }

    @Override
    public boolean Equals(Object obj) {
        if(this == obj)
            return true;
        if(obj == null || getClass() != obj.getClass())
            return false;

        boardArray1D objBoard1D = (boardArray1D) obj;

        for(int i=0;i<x*y;i++){
            if(board1D[i] != objBoard1D.board1D[i]){
                return false;
            } else{
                if(i == x*y-1 && x == objBoard1D.x && y == objBoard1D.y){
                    return true;
                }
            }
        }

        return false;
    }

    /**
     * Finds how many elements in board file.
     *
     * @param file the file name of the board
     * @return the element number
     */
    public int elementNum(String file){
        int element_num = 0;
        try{
            Scanner scanner0 = new Scanner(new File(file));
            while(scanner0.hasNext()){
                element_num++;
                if (scanner0.hasNextInt())
                    scanner0.nextInt();
                else
                    scanner0.next();
            }
            scanner0.close();
        } catch (FileNotFoundException e){
            e.getMessage();
        }

        return element_num;
    }

    /**
     * The file is read and transferred to the array.
     *
     * @param file the file
     */
    public void read(String file){
        String filename="";
        Scanner input = new Scanner(System.in);
        int i=0;
        int elements=0;
        try {
            elements = elementNum(file);

            Scanner scanner = new Scanner(new File(file));
            while (scanner.hasNextLine()) {
                String line = scanner.nextLine();
                String[] dizi = line.split(" ");
                x++;
                for (int z = 0; z < dizi.length; z++) {
                    try {
                        board1D[i++] = Integer.parseInt(dizi[z]);
                    } catch (Exception e) {
                        board1D[i - 1] = -99;
                    }
                }
            }
            scanner.close();
            y = elements / x;
            setSize(x, y);
        } catch (FileNotFoundException e) {
            while(true){
                System.out.println("You have entered the wrong file name.");
                System.out.println("Enter the file name again('press 1 to exit'): ");
                filename = input.nextLine();
                if (filename.equals("1"))
                    System.exit(1);
                if(isFileValid(filename)){
                    read(filename);
                    break;
                }
            }
        }

    }

    /**
     * String of board the string.
     *
     * @param vol indicates which function
     * @return the string of Board
     */
    public String stringOfBoard(int vol){
        String printBoard="";
        for(int i=0;i<x*y;i++){
            if(i % y == 0 && i!=0)
                printBoard += "\n";
            if(board1D[i] == -99){
                if(vol==1)
                    printBoard += "   ";
                if(vol==2)
                    printBoard += "bb ";
            }
            else{
                if(board1D[i] < 10){
                    printBoard += "0";
                    printBoard += board1D[i];
                    printBoard += " ";
                }
                else{
                    printBoard += board1D[i];
                    printBoard += " ";
                }
            }
        }
        printBoard += "\n";

        return printBoard;
    }

    /**
     * Checks whether the File is exists.
     *
     * @param filename the filename
     * @return true or false
     */
    public boolean isFileValid(String filename){
        File file = new File(filename);
        if(file.exists()){
            return true;
        }
        else{
            return false;
        }
    }

}