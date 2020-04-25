/**
 * This is the abstract class of the board.
 *
 * @author Harun Albayrak
 * @version 1.0 January,2020.
 */
public abstract class abstractBoard{

    /**
     * The X value of the board.
     */
    protected int x, /**
     * The Y value of the board.
     */
    y;
    /**
     * The Last move of the board.
     */
    protected char _lastMove;
    /**
     * The Number of moves.
     */
    protected int _numberOfMoves;
    /**
     * The Number of boards.
     */
    protected static int _numberOfBoards = 0;

    /**
     * Instantiates a new Abstract board.
     *
     * @param xVal the x val
     * @param yVal the y val
     */
    public abstractBoard(int xVal,int yVal){
        x = xVal;
        y = yVal;
        _lastMove = 'S';
        _numberOfMoves = 0;
        _numberOfBoards++;
    }

    /**
     * Get x value of the board.
     *
     * @return X
     */
    public int getX(){
        return x;
    }

    /**
     * Get y value of the board.
     *
     * @return Y
     */
    public int getY(){
        return y;
    }
    public abstract String toString();

    /**
     * Reads the board from the file given as function parameter.
     *
     * @param file Name of the file.
     */
    public abstract void readFromFile(String file);

    /**
     * Writes the board to the file given as function parameter
     *
     * @param file Name of the file.
     */
    public abstract void writeFromFile(String file);

    /**
     * Resets the board to the solution.
     */
    public abstract void reset();

    /**
     * Set the board size to given values.
     *
     * @param xVal X
     * @param yVal Y
     */
    public void setSize(int xVal,int yVal){ x = xVal; y = yVal; }

    /**
     * Makes a move according to the given char parameter.
     *
     * @param c The char parameter of operation.
     */
    public abstract void move(char c);

    /**
     * Checks whether the board is solved.
     *
     * @return Returns solved or not
     */
    public abstract boolean isSolved();

    /**
     * Takes two indexes and returns the corresponding cell content. Terminates program if the indexes are not valid.
     *
     * @param _x X
     * @param _y Y
     * @return Corresponding cell content
     */
    public abstract int cell(int _x,int _y);

    /**
     * Compare the two abstractBoard objects.
     *
     * @param obj the object of boardArray1D or boardArray2D.
     * @return Returns the same or not.
     */
    public abstract boolean Equals(Object obj);

    /**
     * Number of boards.
     *
     * @return the int
     */
    public static int NumberOfBoards(){
        return _numberOfBoards;
    }

    /**
     * Last move.
     *
     * @return the int
     */
    public char lastMove(){
        return _lastMove;
    }

    /**
     * Number of moves.
     *
     * @return the int
     */
    public int numberOfMoves(){
        return _numberOfMoves;
    }

}