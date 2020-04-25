#include<iostream>
#include"GTUVector.h"
#include"GTUIterator.h"
#include"GTUIteratorConst.h"

#define SIZE 9999

namespace GTUContainers{
    using namespace std;

    template<typename T>
    GTUVector<T>::GTUVector() : GTUContainer<T>(){
        data = nullptr;
        count = 0;
    }

    template<typename T>
    GTUVector<T>::GTUVector(T ptr) : GTUContainer<T>(){
        (*data)[0] = ptr;
        count = 1;
    }

    template<typename T>
    T GTUVector<T>::operator[](int index){
        if(index < 0){
            try{
                throw "\nERROR : Index cannot be less than 0\n";
            }
            catch(const char* error){
                cout << error;
            }
        }else{
            return (*data)[index];
        }
    }

    template<typename T>
    bool GTUVector<T>::empty(){
        return (count == 0);
    }

    template<typename T>
    int GTUVector<T>::size(){
        return count;
    }

    template<typename T>
    int GTUVector<T>::max_size(){
        return SIZE;
    }

    template<typename T>
    void GTUVector<T>::insert(const T& new_element){
        if(count < SIZE){
            if(data == nullptr){
                data = make_shared<T*>(new T[SIZE]);
                (*data)[0] = new_element;
                count = 1;
                return;
            }else{
                (*data)[count] = new_element;
                count++;
            }
        }
    }

    template<typename T>
    void GTUVector<T>::erase(const T& element){
        int cntrl=0,cntrl2=1;
        for(int i=0,k=0;i<count;i++,k++){
            if(element == (*data)[i]){
                if(cntrl2)
                    k++;
                cntrl=1;
                cntrl2=0;
            }
            (*data)[i] = (*data)[k];
        }
        if(cntrl){
            (*data)[count-1] = 0;
            count--; 
        }
}

    template<typename T>
    void GTUVector<T>::clear(){
        for(int i=0;i<count;i++){
            (*data)[i] = 0;
        }
        data = nullptr;
        count = 0;
    }

}