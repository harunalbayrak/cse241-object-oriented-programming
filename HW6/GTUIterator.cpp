#include<iostream>
#include"GTUIterator.h"

namespace GTUContainers{
    using namespace std;

    template<typename T>
    GTUIterator<T>::GTUIterator(T* _ptr) : ptr(_ptr){

    }

    template<typename T>
    T& GTUIterator<T>::operator*() const{
        return *ptr;
    }

    template<typename T>
    T* GTUIterator<T>::operator->() const{
        return ptr;
    }

    template<typename T>
    GTUIterator<T>& GTUIterator<T>::operator=(const GTUIterator<T>& rightS){
        ptr = rightS.ptr;
        return *this;
    }

    template<typename T>
    GTUIterator<T> GTUIterator<T>::operator++(){
        ptr++;
        return *this;
    }

    template<typename T>
    GTUIterator<T> GTUIterator<T>::operator++(int jk){
        GTUIterator temp = *this;
        ptr++;
        return temp; 
    }

    template<typename T>
    GTUIterator<T> GTUIterator<T>::operator--(){
        ptr--;
        return *this;
    }

    template<typename T>
    GTUIterator<T> GTUIterator<T>::operator--(int jk){
        GTUIterator temp = *this;
        ptr--;
        return temp; 
    }

    template<typename T>
    bool GTUIterator<T>::operator==(const GTUIterator& rightS){
        return (ptr == rightS.ptr);
    }

    template<typename T>
    bool GTUIterator<T>::operator!=(const GTUIterator& rightS){
        return (ptr != rightS.ptr);
    }
}