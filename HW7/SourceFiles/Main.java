import java.util.*;

/**
 * This class is the main class of homework 7.
 *
 * @author Harun Albayrak
 * @version 1.0 January,2020.
 */
public class Main {

    /**
     * The main fuction of the class and homework 7.
     *
     * @param args the input arguments
     */
    public static void main(String[] args) {
        testAll();
    }

    /**
     * The test function of the game and the validity of the board.
     */
    public static void testAll(){
        int input=0;
        String repeat="";
        Scanner inputUser = new Scanner(System.in);

        /* 1 e basarsanÄ±z oyunu test eder 2 ye basarsanÄ±z validity i test eder */
        do{
            System.out.println("***This is the Test Function***");
            System.out.println("* Press 1 : Test the game     *");
            System.out.println("* Press 2 : Test the validity *");
            do{
                input = inputUser.nextInt();
                inputUser.nextLine();
                if(input <= 0 || input > 2)
                    System.out.println("Wrong input. Try again...");
            }while(input <= 0 || input > 2);
            switch (input){
                case 1:
                    testGame();
                    break;
                case 2:
                    testValidity();
                    break;
            }
            System.out.println("Do you want to repeat? (Y / N)");
            /* isterseniz tekrar edebilirsiniz. */
            do{
                repeat = inputUser.next();
                if(!repeat.equals("Y") && !repeat.equals("N") && !repeat.equals("y") && !repeat.equals("n"))
                    System.out.println("Wrong input. Try again...");
            }while(!repeat.equals("Y") && !repeat.equals("N") && !repeat.equals("y") && !repeat.equals("n"));
        }while(repeat.equals("Y") || repeat.equals("y"));
    }

    /**
     * The test function of the game
     */
    public static void testGame(){
        String nameFile;
        String input;
        int boardSize=0,input2=0;
        Scanner inputUser = new Scanner(System.in);
        abstractBoard board = null;

        System.out.println("* Press 1 : To create the board by taking size from the user *");
        System.out.println("* Press 2 : To read the board from the file                  *");
        input2 = inputUser.nextInt();
        inputUser.nextLine();

        if(input2 == 1){
            System.out.println("* Press 1 : TEST with 1 Dimensional Array *");
            System.out.println("* Press 2 : TEST with 2 Dimensional Array *");
            do{
                input2 = inputUser.nextInt();
                inputUser.nextLine();
                if(input2 <= 0 || input2 > 2)
                    System.out.println("Wrong Input. Try Again...");
            }while(input2 <= 0 || input2 > 2);

            System.out.println("Please enter the board size: ");
            do{
                boardSize = inputUser.nextInt();
                inputUser.nextLine();
                if(boardSize < 3 || boardSize > 9)
                    System.out.println("Wrong Input. Try Again...");
            }while(boardSize < 3 || boardSize > 9);


            switch(input2){
                case 1:
                    board = new boardArray1D(boardSize,boardSize); // 1 boyutlu array oluÅŸturur.
                    break;
                case 2:
                    board = new boardArray2D(boardSize,boardSize); // 2 boyutlu array oluÅŸturur.
                    break;
            }
        }
        else if(input2 == 2) { // EÄŸer konsolda dosya ismi girilidiyse buraya girer.
            System.out.println("* Press 1 : Read from file operation with 1 Dimensional Array *");
            System.out.println("* Press 2 : Read from file operation with 2 Dimensional Array *");
            do{
                input2 = inputUser.nextInt();
                inputUser.nextLine();
                if(input2 <= 0 || input2 > 2)
                    System.out.println("Wrong Input. Try Again...");
            }while(input2 <= 0 || input2 > 2);

            switch (input2) {
                case 1:
                    System.out.print("Please enter the name of the file: ");
                    nameFile = inputUser.nextLine();
                    board = new boardArray1D(nameFile); // 1 boyutlu array oluÅŸturur.
                    break;
                case 2:
                    System.out.print("Please enter the name of the file: ");
                    nameFile = inputUser.nextLine();
                    board = new boardArray2D(nameFile); // 2 boyutlu array oluÅŸturur.
                    break;
            }
        }
        System.out.println(board);
        while(!board.isSolved()){  // Board Ã§Ã¶zÃ¼lene kadar oyunu sÃ¼rdÃ¼rÃ¼r(q ya basarsanÄ±z Ã§Ä±kar.)
            try {
                System.out.print("Your move: ");
                input = inputUser.nextLine();
                if (input.equals("o") || input.equals("O")) { // Dosyadan board okur.
                    nameFile = inputUser.nextLine();
                    board.readFromFile(nameFile);
                } else if (input.equals("e") || input.equals("E")) { // Boardï¿½ dosyaya kaydeder.
                    System.out.println("Enter the name of the file to save the board: ");
                    nameFile = inputUser.nextLine();
                    board.writeFromFile(nameFile);
                } else
                    board.move(input.charAt(0));

                if (input.equals("l") || input.equals("L") || input.equals("r") || input.equals("R") || input.equals("d")
                        || input.equals("D") || input.equals("u") || input.equals("U") || input.equals("e") || input.equals("E")
                        || input.equals("o") || input.equals("O")) {
                    System.out.println(board);
                }
            }
            catch (Exception e){
                System.out.println(e.getMessage());
            }
        }
        if(board.isSolved()){  // Board Ã§Ã¶zÃ¼lÃ¼rse buraya girer//
            System.out.println("Congrulations !!! You win the game!");
            System.out.println("Number of moves : " + board.numberOfMoves());
            System.out.println("Last Move : " + board.lastMove());
            System.out.println(boardArray1D.NumberOfBoards() + " Boards have been created so far.");
        }
    }

    /**
     * The test function of the validity of the board.
     */
    public static void testValidity(){
        Scanner inputUser = new Scanner(System.in);
        String nameFile = "";
        int input=0,size=0;

        System.out.println("* TEST with 1 Dimensional Array : press 1 *");
        System.out.println("* TEST with 2 Dimensional Array : press 2 *");

        do{
            input = inputUser.nextInt();
            inputUser.nextLine();
            if(input <= 0 || input > 2)
                System.out.println("Wrong Input. Try Again...");
        }while(input <= 0 || input > 2);

        System.out.println("How many size would you like? : ");
        size = inputUser.nextInt();
        inputUser.nextLine();

        abstractBoard[] boards= new abstractBoard[size]; // size kadar board oluÅŸturur.
        switch(input){
            case 1:
                for(int i=0;i<size;i++){
                    System.out.println("for "+ (i+1) + ".FILE ");
                    System.out.print("Please enter the name of the file: ");
                    nameFile = inputUser.nextLine();
                    boards[i] = new boardArray1D(nameFile); // 1 boyutlu array ile oluÅŸturur.
                }
                if(size > 0 && isValid(boards))
                    System.out.println("Valid");
                else
                    System.out.println("Not Valid");

                break;

            case 2:
                for(int i=0;i<size;i++){
                    System.out.println("for "+ (i+1) + ".FILE ");
                    nameFile = inputUser.nextLine();
                    boards[i] = new boardArray2D(nameFile); // 2 boyutlu array ile oluÅŸturur.
                }
                if(size > 0 && isValid(boards))
                    System.out.println("Valid");
                else
                    System.out.println("Not Valid");

                break;
        }
    }

    /**
     * Checks whether boards are valid.
     *
     * @param sequenceOfMoves Sequence of moves, in an other saying array of the boards.
     * @return boolean Return boolean because it must be true or false.
     */
    public static boolean isValid(abstractBoard[] sequenceOfMoves){
        int x = sequenceOfMoves[0].getX();
        int y = sequenceOfMoves[0].getY();
        int[] blank_cell_x = new int[x*y];
        int[] blank_cell_y = new int[x*y];
        int new_blank_x=0,new_blank_y=0,old_blank_x=0,old_blank_y,newVal=0,control=0,countX=0,countY=0;
        int leftVal=0,rightVal=0,upVal=0,downVal=0; // etrafÄ±ndaki deÄŸerleri tutar
        boolean leftCheck=true,rightCheck=true,upCheck=true,downCheck=true; // ne tarafa gidilip gidilemeyeceÄŸini test eder


        for(int k=0;k<sequenceOfMoves.length;k++) {
            for (int i = 0; i < x; i++) {
                for (int j = 0; j < y; j++) {
                    if (sequenceOfMoves[k].cell(i,j) == -99){
                        blank_cell_x[countX++] = i;
                        blank_cell_y[countY++] = j;
                        // boÅŸ cell in x ve y sini bulur.
                    }
                }
            }

            if (k >= 1) { // etrafÄ±ndaki kÄ±sÄ±mlarÄ±n eÄŸer gidebiliyorsa deÄŸerlerini tutar.
                if (blank_cell_x[k-1] != 0 && sequenceOfMoves[k - 1].cell(blank_cell_x[k-1]-1,blank_cell_y[k-1]) != 0){
                    upVal = sequenceOfMoves[k - 1].cell(blank_cell_x[k-1]-1,blank_cell_y[k-1]);
                }else{
                    upCheck = false;
                }

                if (blank_cell_y[k-1] != 0 && sequenceOfMoves[k - 1].cell(blank_cell_x[k-1],blank_cell_y[k-1]-1) != 0){
                    leftVal = sequenceOfMoves[k - 1].cell(blank_cell_x[k-1],blank_cell_y[k-1]-1);
                }else{
                    leftCheck = false;
                }

                if (blank_cell_y[k-1] != y-1 && sequenceOfMoves[k - 1].cell(blank_cell_x[k-1],blank_cell_y[k-1]+1) != 0){
                    rightVal = sequenceOfMoves[k - 1].cell(blank_cell_x[k-1],blank_cell_y[k-1]+1);
                }else{
                    rightCheck = false;
                }

                if (blank_cell_x[k-1] != x-1 && sequenceOfMoves[k - 1].cell(blank_cell_x[k-1]+1,blank_cell_y[k-1]) != 0){
                    downVal = sequenceOfMoves[k - 1].cell(blank_cell_x[k-1]+1,blank_cell_y[k-1]);
                }else{
                    downCheck = false;
                }

                old_blank_x = blank_cell_x[k - 1];
                old_blank_y = blank_cell_y[k - 1];
                new_blank_x = blank_cell_x[k];
                new_blank_y = blank_cell_y[k];
                if (k >= 1) {
                    control = 0;
                    if (new_blank_x == old_blank_x - 1 && new_blank_y == old_blank_y && upCheck) {  // Ã¼st tarafÄ± kontrol eder.
                        newVal = sequenceOfMoves[k].cell(new_blank_x+1,new_blank_y);
                        if (upVal == newVal)
                            control = 1;
                        else
                            control = 0;
                    } else if (new_blank_x == old_blank_x && new_blank_y == old_blank_y - 1 && leftCheck) { // saÄŸ tarafÄ± kontrol eder.
                        newVal = sequenceOfMoves[k].cell(new_blank_x,new_blank_y+1);
                        if (leftVal == newVal)
                            control = 1;
                        else
                            control = 0;
                    } else if (new_blank_x == old_blank_x && new_blank_y == old_blank_y + 1 && rightCheck) { // sol tarafÄ± kontrol eder.
                        newVal = sequenceOfMoves[k].cell(new_blank_x,new_blank_y-1);
                        if (rightVal == newVal)
                            control = 1;
                        else
                            control = 0;
                    } else if (new_blank_x == old_blank_x + 1 && new_blank_y == old_blank_y && downCheck) { // alt tarafÄ± kontrol eder.
                        newVal = sequenceOfMoves[k].cell(new_blank_x-1,new_blank_y);
                        if (downVal == newVal)
                            control = 1;
                        else
                            control = 0;
                    }
                    if (control == 1 && k == sequenceOfMoves.length - 1) {
                        return sequenceOfMoves[k].isSolved(); // eÄŸer hamleler "valid" ise ve son board "solved" ise "true" dÃ¶ndÃ¼lÃ¼r. Aksi takdirde "false" dÃ¶ner.
                    }
                    if (control == 0 || k == sequenceOfMoves.length - 1) {
                        return false; // hamleler valid deÄŸilse buraya girer. ve 0 dÃ¶ndÃ¼rÃ¼r.
                    }
                }
            }
        }
        return false;
    }


}
