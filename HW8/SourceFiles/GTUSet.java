/**
 * The type GTUSet
 *
 * @param <T> the type parameter
 */
public class GTUSet<T> extends GTUContainer<T>{
    /**
     * Instantiates a new GTUSet(Empty).
     */
    public GTUSet() {
        data = null;
        size = 0;
    }

    /**
     * Instantiates a new GTUSet(with One data).
     *
     * @param _data the data
     */
    public GTUSet(T _data) {
        size = 1;
        T[] temp = (T[]) new Object[size];
        temp[0] = _data;
        data = temp;
    }

    /**
     * Instantiates a new GTUSet(with T array).
     *
     * @param _data the data
     */
    public GTUSet(T[] _data) {
        data = _data;
        size = _data.length;
    }

    @Override
    public void insert(T element) {
        try {
            if(size >= max_size)
                throw new Exception("Maximum size reached. No more elements can be added.");
            boolean cntrl = true;
            T[] temp;
            for (int i = 0; i < size; i++)
                if (element.equals(data[i]))
                    cntrl = false;

            if(!cntrl)
                throw new Exception("The element failed to add since it is already in the set.");

            if (cntrl) {
                temp = (T[]) new Object[size + 1];
            } else {
                temp = (T[]) new Object[size];
            }
            for (int i = 0; i < size; i++) {
                temp[i] = data[i];
            }
            if (cntrl)
                temp[size++] = element;

            data = temp;
        }
        catch(Exception e){
            System.out.println(e.getMessage());
        }
    }

    @Override
    public void insertArray(T[] array) {
        boolean cntrl=true;
        T[] temp;
        for(int j=0;j<array.length;++j){
            try {
                if(size >= max_size)
                    throw new Exception("Maximum size reached. No more elements can be added.");
                for (int i = 0; i < size; i++)
                    if (array[j].equals(data[i]))
                        cntrl = false;

                if(!cntrl)
                    throw new Exception("The element failed to add since it is already in the set.");

                if (cntrl) {
                    temp = (T[]) new Object[size + 1];
                } else {
                    temp = (T[]) new Object[size];
                }
                for (int i = 0; i < size; i++) {
                    temp[i] = data[i];
                }
                if (cntrl)
                    temp[size++] = array[j];

                data = temp;
            }
            catch(Exception e){
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
