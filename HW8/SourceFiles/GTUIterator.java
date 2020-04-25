import java.util.Iterator;

/**
 * The type of GTUIterator
 *
 * @param <T> the type parameter
 */
public class GTUIterator<T> implements Iterator<T> {
    private T[] it;
    private int size;
    private int index;

    /**
     * Instantiates a new GTUIterator.
     *
     * @param data the data
     */
    public GTUIterator(T[] data){
        index = 0;
        it = data;
        size = data.length;
    }

    @Override
    public boolean hasNext() {
        if(index < size)
            return true;
        else
            return false;
    }

    public T next(){
        T temp = (T) "NULL";
        try{
            return it[index++];
        }
        catch (Exception e){
            System.out.println(e.getMessage());
        }
        return temp;
    }
}
