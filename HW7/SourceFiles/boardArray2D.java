import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Random;
import java.util.Scanner;

/**
 * The type Board array 2d.
 */
public class boardArray2D extends abstractBoard {
    private int[][] board2D = new int[9][9];

    /**
     * Instantiates a new Board array 2d.
     *
     * @param file the file
     */
    public boardArray2D(String file){
        super(0,0);
        readFromFile(file);
    }

    /**
     * Instantiates a new Board array 2d.
     *
     * @param xVal the x val
     * @param yVal the y val
     */
    public boardArray2D(int xVal,int yVal){
        super(xVal,yVal);
        Random random = new Random();
        int[] blankIndexes = new int[2];
        int randomNum2=0,blankIndex=0,size=x;
        int randomNum = random.nextInt(x*20 + y*20) + 50;

        for(int i=0;i<x;i++)
            for(int j=0;j<y;j++)
                board2D[i][j] = 1;
        reset();

        for(int i=0;i<x;i++){
            for(int j=0;j<y;j++){
                if(board2D[i][j] == -99){
                    blankIndexes[0] = i;
                    blankIndexes[1] = j;
                }
            }
        }

        while(randomNum != 0){
            randomNum2 = random.nextInt(4);
            if(randomNum2 == 0 && !(blankIndexes[1] != 0 && board2D[blankIndexes[0]][blankIndexes[1]-1] != 0))
                continue;
            else if(randomNum2 == 1 && !(blankIndexes[1] != y-1 && board2D[blankIndexes[0]][blankIndexes[1]+1] != 0))
                continue;
            else if(randomNum2 == 2 && !(blankIndexes[0] != 0 && board2D[blankIndexes[0]-1][blankIndexes[1]] != 0))
                continue;
            else if(randomNum2 == 3 && !(blankIndexes[0] != x-1 && board2D[blankIndexes[0]+1][blankIndexes[1]] != 0))
                continue;

            switch(randomNum2){
                case 0:
                    board2D[blankIndexes[0]][blankIndexes[1]] = board2D[blankIndexes[0]][blankIndexes[1]-1];
                    blankIndexes[1]--;
                    break;
                case 1:
                    board2D[blankIndexes[0]][blankIndexes[1]] = board2D[blankIndexes[0]][blankIndexes[1]+1];
                    blankIndexes[1]++;
                    break;
                case 2:
                    board2D[blankIndexes[0]][blankIndexes[1]] = board2D[blankIndexes[0]-1][blankIndexes[1]];
                    blankIndexes[0]--;
                    break;
                case 3:
                    board2D[blankIndexes[0]][blankIndexes[1]] = board2D[blankIndexes[0]+1][blankIndexes[1]];
                    blankIndexes[0]++;
                    break;
            }
            board2D[blankIndexes[0]][blankIndexes[1]] = -99;
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
        int k = 1;
        for(int i=0;i<x;i++)
            for(int j=0;j<y;j++)
                if(board2D[i][j] != 0)
                    board2D[i][j] = k++;

        board2D[x-1][y-1] = -99;
    }

    @Override
    public void move(char c) {
        int temp=0;
        int[] blankIndexes = new int[2];

        for(int i=0;i<x;i++){
            for(int j=0;j<y;j++){
                if(board2D[i][j] == -99){
                    blankIndexes[0] = i;
                    blankIndexes[1] = j;
                }
            }
        }

        switch(c) {
            case 'l':
            case 'L': // Sol tarafta boÅŸluk var ise sol tarafa hareket eder.
                if (blankIndexes[1] != 0 && board2D[blankIndexes[0]][blankIndexes[1] - 1] != 0) {
                    temp = board2D[blankIndexes[0]][blankIndexes[1] - 1];
                    board2D[blankIndexes[0]][blankIndexes[1] - 1] = board2D[blankIndexes[0]][blankIndexes[1]];
                    board2D[blankIndexes[0]][blankIndexes[1]] = temp;
                    _numberOfMoves++;
                    _lastMove = 'L';
                } else {
                    System.out.println("There is no room on the left side"); /* Solda yer yok ise hareket edilmiyor. */
                }
                break;
            case 'r':
            case 'R': // SaÄŸ tarafta boÅŸluk var ise sol tarafa hareket eder.
                if (blankIndexes[1] != y - 1 && board2D[blankIndexes[0]][blankIndexes[1] + 1] != 0) {
                    temp = board2D[blankIndexes[0]][blankIndexes[1] + 1];
                    board2D[blankIndexes[0]][blankIndexes[1] + 1] = board2D[blankIndexes[0]][blankIndexes[1]];
                    board2D[blankIndexes[0]][blankIndexes[1]] = temp;
                    _numberOfMoves++;
                    _lastMove = 'R';
                } else {
                    System.out.println("There is no room on the right side"); /* Sağda yer yok ise hareket edilmiyor. */
                }
                break;
            case 'u':
            case 'U': // Yukarda boÅŸluk var ise sol tarafa hareket eder.
                if (blankIndexes[0] != 0 && board2D[blankIndexes[0] - 1][blankIndexes[1]] != 0) {
                    temp = board2D[blankIndexes[0] - 1][blankIndexes[1]];
                    board2D[blankIndexes[0] - 1][blankIndexes[1]] = board2D[blankIndexes[0]][blankIndexes[1]];
                    board2D[blankIndexes[0]][blankIndexes[1]] = temp;
                    _numberOfMoves++;
                    _lastMove = 'U';
                } else {
                    System.out.println("There is no room upstairs"); /* Yukarıda yer yok ise hareket edilmiyor. */
                }
                break;
            case 'd':
            case 'D': // AÅŸaÄŸÄ±da boÅŸluk var ise sol tarafa hareket eder.
                if (blankIndexes[0] != x - 1 && board2D[blankIndexes[0] + 1][blankIndexes[1]] != 0) {
                    temp = board2D[blankIndexes[0] + 1][blankIndexes[1]];
                    board2D[blankIndexes[0] + 1][blankIndexes[1]] = board2D[blankIndexes[0]][blankIndexes[1]];
                    board2D[blankIndexes[0]][blankIndexes[1]] = temp;
                    _numberOfMoves++;
                    _lastMove = 'D';
                } else {
                    System.out.println("There is no room downstairs"); /* Aşşağıda yer yok ise hareket edilmiyor. */
                }
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
        int[][] solvedBoard = new int[x][y];
        for(int i=0;i<x;i++){
            for(int j=0;j<y;j++){
                solvedBoard[i][j] = board2D[i][j];
            }
        }
        for(int i=0;i<x;i++){
            for(int j=0;j<y;j++){
                if(solvedBoard[i][j] != 0)
                    solvedBoard[i][j] = k++;
            }
        }

        solvedBoard[x-1][y-1] = -99;

        for(int i=0;i<x;i++){
            for(int j=0;j<y;j++){
                if(board2D[i][j] != solvedBoard[i][j]){
                    status = false;
                    break;
                }else{
                    if(i == x-1 && j == y-1)
                        status = true;
                }
            }
        }
        return status;
    }

    public int cell(int _x,int _y){
        int val = 0;
        try{
            if(x*y > _x*_y){
                val = board2D[_x][_y];
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

        boardArray2D objBoard2D = (boardArray2D) obj;

        for(int i=0;i<x;i++){
            for(int j=0;j<y;j++){
                if(board2D[i][j] != objBoard2D.board2D[i][j]){
                    return false;
                } else{
                    if(i == x-1 && j == y-1 && x == objBoard2D.x && y == objBoard2D.y){
                        return true;
                    }
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
        int[] board1D = new int[81];
        int i=0;
        int elements=0;
        try{
            elements = elementNum(file);

            Scanner scanner = new Scanner(new File(file));
            while (scanner.hasNextLine()) {
                String line = scanner.nextLine();
                String[] dizi = line.split(" ");
                x++;
                for(int z=0;z<dizi.length;z++){
                    try{
                        board1D[i++] = Integer.parseInt(dizi[z]);
                    }catch(Exception e){
                        board1D[i-1] = -99;
                    }
                }
            }
            scanner.close();
            y = elements / x;
            setSize(x,y);

            for(int j=0;j<x;j++){
                for(int m=0;m<y;m++){
                    board2D[j][m] = board1D[j*y + m];
                }
            }
        }
        catch(FileNotFoundException e){
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
     * String of board string.
     *
     * @param vol indicates which function
     * @return the string of Board
     */
    public String stringOfBoard(int vol){
        String printBoard="";
        for(int i=0;i<x;i++){
            for(int j=0;j<y;j++){
                if(board2D[i][j] == -99){
                    if(vol==1)
                        printBoard += "   ";
                    if(vol==2)
                        printBoard += "bb ";
                }
                else if(board2D[i][j] >= 0 && board2D[i][j] < 10){
                    printBoard += "0";
                    printBoard += board2D[i][j];
                    printBoard += " ";
                }
                else{
                    printBoard += board2D[i][j];
                    printBoard += " ";
                }
            }
            printBoard += "\n";
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