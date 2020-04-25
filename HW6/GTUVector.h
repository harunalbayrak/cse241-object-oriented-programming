#ifndef GTUVECTOR_H
#define GTUVECTOR_H

#include<iostream>
#include<memory>
#include"GTUContainer.h"
#include"GTUIterator.h"
#include"GTUIteratorConst.h"

#define SIZE 9999

namespace GTUContainers{
    using namespace std;
    template<typename T>
    class GTUVector : public GTUContainer<T>{
        private:
            shared_ptr<T*> data = make_shared<T*>(new T[SIZE]); // pointer holding data
            int count; // size of the data
        public:
            typedef GTUIterator<T> iterator; // iterator
            typedef GTUIteratorConst<T> const_iterator; // const iterator

            GTUVector(); // Default constructor 
            GTUVector(T ptr); // One parameter constructor
            T operator[](int index); // Index operator
            bool empty(); // Checks if empty
            int size(); // Returns size
            int max_size(); // Returns max size
            void insert(const T& new_element); // Inserts
            void erase(const T& element); // Erases one element
            void clear(); // Clears
            iterator begin(){ // Returns begin iterator
                return &((*data)[0]);
            }
            iterator end(){  // Returns end iterator
                return &((*data)[count]);
            }
            const_iterator cbegin(){ // Returns const begin iterator
                return &((*data)[0]);
            }
            const_iterator cend(){ // Returns const end iterator
                return &((*data)[count]);
            }
    };
}


#endif