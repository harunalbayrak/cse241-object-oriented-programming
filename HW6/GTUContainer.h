#ifndef GTUCONTAINER_H
#define GTUCONTAINER_H

#include"GTUIterator.h"
#include<memory>

namespace GTUContainers{
    using namespace std;
    template<typename T>
    class GTUContainer{
        public:
            typedef GTUIterator<T> iterator;
            GTUContainer();
            virtual bool empty()=0;
            virtual int size()=0;
            virtual int max_size()=0;
            virtual void insert(const T& new_element)=0;
            virtual void erase(const T& element)=0;
            virtual void clear()=0;
            virtual iterator begin()=0;
            virtual iterator end()=0;
    };
}

#endif