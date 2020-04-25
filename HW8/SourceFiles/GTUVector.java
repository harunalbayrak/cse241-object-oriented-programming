/**
 * The type GTUVector
 *
 * @param <T> the type parameter
 */
public class GTUVector<T> extends GTUContainer<T> {
    /**
     * Instantiates a new GTUVector(Empty).
     */
    public GTUVector() {
        data = null;
        size = 0;
    }

    /**
     * Instantiates a new GTUVector(with One data);
     *
     * @param _data the data
     */
    public GTUVector(T _data) {
        size = 1;
        T[] temp = (T[]) new Object[size];
        temp[0] = _data;
        data = temp;
    }

    /**
     * Instantiates a new GTUVector(with T array)
     *
     * @param _data the data
     */
    public GTUVector(T[] _data) {
        data = _data;
        size = _data.length;
    }

    @Override
    public void insert(T element) {
        try {
            if(size >= max_size)
                throw new Exception("Maximum size reached. No more elements can be added.");
            T[] temp = (T[]) new Object[size + 1];
            for (int i = 0; i < size; i++) {
                temp[i] = data[i];
            }
            temp[size++] = element;
            data = temp;
        }
        catch (Exception e){
            System.out.println(e.getMessage());
        }
    }

    @Override
    public void insertArray(T[] array) {
        for(int j=0;j<array.length;j++){
            try {
                if(size >= max_size)
                    throw new Exception("Maximum size reached. No more elements can be added.");
                T[] temp = (T[]) new Object[size + 1];
                for (int i = 0; i < size; i++) {
                    temp[i] = data[i];
                }
                temp[size++] = array[j];
                data = temp;
            }
            catch (Exception e){
                System.out.println(e.getMessage());
            }
        }
    }

    @Override
    public void erase(T element) {
        T[] temp = (T[]) new Object[size-1];

        for(int i=0,k=0;i<size;i++,k++){
            if(data[i] != element){
                temp[k] = data[i];
            }else{
                k--;
            }
        }
        size--;
        data = temp;
    }

    @Override
    public GTUIterator<T> iterator() {
        return new GTUIterator<T>(data);
    }

}
