/**
 * The abstract class of GTUContainers.
 *
 * @param <T> the type parameter
 */
public abstract class GTUContainer<T> {
    /**
     * The Data.
     */
    protected T[] data;
    /**
     * The Size.
     */
    protected int size;
    /**
     * The Max size.
     */
    protected final int max_size=500;

    /**
     * Checks whether container is empty.
     *
     * @return the boolean
     */
    public boolean empty(){ return (size==0); }

    /**
     * Size of the container.
     *
     * @return the int
     */
    public int size(){ return size; }

    /**
     * Max size of the container.
     *
     * @return the int
     */
    public int max_size(){ return max_size; }

    /**
     * Insert element to the container.
     *
     * @param element the element
     */
    public abstract void insert(T element);

    /**
     * Insert array to the container.
     *
     * @param array the array of the elements
     */
    public abstract void insertArray(T[] array);

    /**
     * Erase element from the container.
     *
     * @param element the element
     */
    public abstract void erase(T element);

    /**
     * Clearing operation.
     */
    public void clear(){
        data = null;
        size = 0;
    }

    /**
     * Iterator of the GTUIterator.
     *
     * @return the GTUIterator
     */
    public abstract GTUIterator<T> iterator();

    /**
     * Checks whether the container contains the object.
     *
     * @param o the object
     * @return the boolean
     */
    public boolean contains(Object o){
        T temp = (T) o;
        for(int i=0;i<size;i++)
            if(data[i].equals(temp))
                return true;
        return false;
    }

    /**
     * The container converts to array.
     *
     * @return the t[ ]
     */
    public T[] toArray(){
        T[] temp = (T[]) new Object[size];
        for(int i=0;i<size;i++){
            temp[i] = data[i];
        }
        return temp;
    }
}
