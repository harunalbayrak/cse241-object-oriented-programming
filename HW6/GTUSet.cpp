#include<iostream>
#include"GTUSet.h"
#include"GTUIterator.h"
#include"GTUIteratorConst.h"

#define SIZE 9999

namespace GTUContainers{
    using namespace std;

    template<typename T>
    GTUSet<T>::GTUSet() : GTUContainer<T>(){
        data = nullptr;
        count = 0;
    }

    template<typename T>
    GTUSet<T>::GTUSet(T ptr) : GTUContainer<T>(){
        (*data)[0] = ptr;
        count = 1;
    }

    template<typename T>
    bool GTUSet<T>::empty(){
        return (count == 0);
    }

    template<typename T>
    int GTUSet<T>::size(){
        return count;
    }

    template<typename T>
    int GTUSet<T>::max_size(){
        return SIZE; 
    }

    template<typename T>
    void GTUSet<T>::insert(const T& new_element){
        if(count < SIZE){
            if(data == nullptr){
                data = make_shared<T*>(new T[SIZE]);
                (*data)[0] = new_element;
                count = 1;
                return;
            }
            T temp;
            int cntrl=1;
            for(int i=0;i<count;i++){
                if(new_element == (*data)[i]){
                    cntrl=0;
                }else if(i == count-1 && cntrl){
                    cntrl=1;
                }
            }    
            if(cntrl){
                (*data)[count] = new_element;
                count++; 
                for (int i=0;i<count-1;i++){
                    for (int j=0;j<count-i-1;j++){
                        if((*data)[j] > (*data)[j+1]){
                            temp =  (*data)[j];
                            (*data)[j] = (*data)[j+1];
                            (*data)[j+1] = temp;
                        }
                    }
                }
            }else{
                try{
                    throw "\nERROR : The same number already exists.\n";
                }
                catch(const char *error){
                    cout << error;
                }
            }
        }   
    }

    template<typename T>
    void GTUSet<T>::erase(const T& element){
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
    void GTUSet<T>::clear(){
        for(int i=0;i<count;i++){
            (*data)[i] = 0;
        }
        data = nullptr;
        count = 0;
    }

}