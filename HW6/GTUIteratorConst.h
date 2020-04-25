#ifndef GTUITERATORCONST_H
#define GTUITERATORCONST_H

#include<iostream>
#include<memory>

namespace GTUContainers{
    using namespace std;
    template<typename T>
    class GTUIteratorConst{
        private:
            T* ptr;
        public:
            GTUIteratorConst(T* _ptr); // Constructor
            const T& operator*() const; // * operator overloading
            const T* operator->() const; // -> operator overloading
            GTUIteratorConst& operator=(const GTUIteratorConst& rightS); // assignment operator overloading
            GTUIteratorConst operator++(); // prefix ++ operator overloading
            GTUIteratorConst operator++(int jk); // postfix ++ operator overloading
            GTUIteratorConst operator--(); // prefix -- operator overloading
            GTUIteratorConst operator--(int jk);// postfix -- operator overloading
            bool operator==(const GTUIteratorConst& rightS); // == operator overloading
            bool operator!=(const GTUIteratorConst& rightS); // != operator overloading
    };
}

#endif
