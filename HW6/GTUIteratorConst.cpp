#include<iostream>
#include"GTUIteratorConst.h"

namespace GTUContainers{
    using namespace std;

    template<typename T>
    GTUIteratorConst<T>::GTUIteratorConst(T* _ptr) : ptr(_ptr){

    }

    template<typename T>
    const T& GTUIteratorConst<T>::operator*() const{
        return *ptr;
    }

    template<typename T>
    const T* GTUIteratorConst<T>::operator->() const{
        return ptr;
    }

    template<typename T>
    GTUIteratorConst<T>& GTUIteratorConst<T>::operator=(const GTUIteratorConst<T>& rightS){
        ptr = rightS.ptr;
        return *this;
    }

    template<typename T>
    GTUIteratorConst<T> GTUIteratorConst<T>::operator++(){
        ptr++;
        return *this;
    }

    template<typename T>
    GTUIteratorConst<T> GTUIteratorConst<T>::operator++(int jk){
        GTUIteratorConst temp = *this;
        ptr++;
        return temp; 
    }

    template<typename T>
    GTUIteratorConst<T> GTUIteratorConst<T>::operator--(){
        ptr--;
        return *this;
    }

    template<typename T>
    GTUIteratorConst<T> GTUIteratorConst<T>::operator--(int jk){
        GTUIteratorConst temp = *this;
        ptr--;
        return temp; 
    }

    template<typename T>
    bool GTUIteratorConst<T>::operator==(const GTUIteratorConst& rightS){
        return (ptr == rightS.ptr);
    }

    template<typename T>
    bool GTUIteratorConst<T>::operator!=(const GTUIteratorConst& rightS){
        return (ptr != rightS.ptr);
    }
}