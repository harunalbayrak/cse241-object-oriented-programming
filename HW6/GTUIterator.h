#ifndef GTUITERATOR_H
#define GTUITERATOR_H

#include<iostream>
#include<memory>

namespace GTUContainers{
    using namespace std;
    template<typename T>
    class GTUIterator{
        private:
            T* ptr;
        public:
            GTUIterator(T* _ptr); // Constructor
            T& operator*() const; // * operator overloading
            T* operator->() const; // -> operator overloading
            GTUIterator& operator=(const GTUIterator& rightS); // assignment operator overloading
            GTUIterator operator++(); // prefix ++ operator overloading
            GTUIterator operator++(int jk); // postfix ++ operator overloading
            GTUIterator operator--(); // prefix -- operator overloading
            GTUIterator operator--(int jk);// postfix -- operator overloading
            bool operator==(const GTUIterator& rightS); // == operator overloading
            bool operator!=(const GTUIterator& rightS); // != operator overloading
    };
}

#endif
