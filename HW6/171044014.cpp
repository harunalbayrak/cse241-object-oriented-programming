/* Gebze Technical University         */
/* Computer Engineering               */
/* Harun ALBAYRAK                     */
/* 171044014                          */
/* 6.HOMEWORK                         */
#include<iostream>
#include<cctype>
#include"GTUIterator.h"
#include"GTUContainer.h"
#include"GTUSet.h"
#include"GTUVector.h"
#include"GTUSet.cpp"
#include"GTUVector.cpp"
#include"GTUContainer.cpp"
#include"GTUIterator.cpp"
#include"GTUIteratorConst.cpp"

using namespace std;
using namespace GTUContainers; // Namespace of the my classes

// Function Find, if there is the sent element in between first iterator and last iterator, This function will return the element,Otherwise last iterator will be returned.
template<typename T>
GTUIterator<T> find(GTUIterator<T> first,GTUIterator<T> last,const T& element);

// Function Find_if,The function is applied to the values between the two iterators, and if the function returns true, the find_if function returns that value. 
template<typename T,typename Func>
GTUIterator<T> find_if(GTUIterator<T> first,GTUIterator<T> last,Func element);

// Function For_each, The function we send to the values between two iterators is applied one by one.
template<typename T,typename Func>
Func for_each(GTUIterator<T> first,GTUIterator<T> last,Func element);

void testFunction(); // Test everything.
GTUSet<int> testSet(); // Test Set
GTUVector<int> testVector(); // Test Vector
void testFind(); // Test Find function
void testFind_if(); // Test Find_if function
void testFor_each(); // Test For_each function

bool IsOdd(int x) {  // The function we sent to find_if
    return ((x%2)==1);
}

void twoTimes(int x) { // The function we sent to for_each
    cout << x*2 << " ";
}

int main(){

    testFunction();

    return 0;
}

template<typename T>
GTUIterator<T> find(GTUIterator<T> first,GTUIterator<T> last,const T& element){
    for(auto it = first;it != last;++it){
        if(*it == element){
            return it;
        }
    }
    return last;
}

template<typename T,typename Func>
GTUIterator<T> find_if(GTUIterator<T> first,GTUIterator<T> last,Func element){
    for(auto it = first;it != last;++it){
        if(element(*it)){
            return it;
        }
    }
    return last;
}

template<typename T,typename Func>
Func for_each(GTUIterator<T> first,GTUIterator<T> last,Func element){
    for(auto it = first;it != last;++it){
        element(*it);
    }
    return element;
}

void testFunction(){
    int input=0;
    char repeat;

    cout << "***---------------------- NOTE ----------------------***\n";
    cout << "***-- Test functions are written for integer only. --***\n";
    do{
        cout << "Press 1 to test SET" << endl;
        cout << "Press 2 to test VECTOR" << endl;
        cout << "Press 3 to test FIND function" << endl;
        cout << "Press 4 to test FIND_IF function" << endl;
        cout << "Press 5 to test FOR_EACH function" << endl;
        do{
            try{
                cin >> input;
                if(isalpha(input + '0')){
                    throw "\nERROR : Input has to be integer.(for Test Function)\n";
                }
            }
            catch(const char* error){
                cout << error;
                exit(1);
            }
            
            if(input <= 0 || input > 5)
                cout << "Wrong Input. Try Again..." << endl;
        }while(input <= 0 || input > 5);
        switch (input){
            case 1:
                testSet();
                cout << endl;
                break;
            case 2:
                testVector();
                cout << endl;
                break;
            case 3:
                testFind();
                cout << endl;
                break;
            case 4:
                testFind_if();
                cout << endl;
                break;
            case 5:
                testFor_each();
                cout << endl;
                break;
        }
        cout << "Do you want to repeat? (Y / N)\n";  /* isterseniz tekrar edebilirsiniz. */
        do{
            cin >> repeat;
            if(repeat != 'Y' && repeat != 'N' && repeat != 'y' && repeat != 'n')
                cout << "Wrong Input. Try Again..." << endl;
        }while(repeat != 'Y' && repeat != 'N' && repeat != 'y' && repeat != 'n');
    }while(repeat == 'Y' || repeat == 'y');
}

GTUSet<int> testSet(){
    int max=0,element=0;
    GTUSet<int> test;

    cout << "Please enter number of elements do you want: ";
    cin >> max; // throw koy.
    
    for(int i=0;i<max;i++){
        cout << "Please enter the elements of set: "; // exception
        cin >> element;
        test.insert(element);
    }
    cout << "THE SET: "; 
    for(auto i = test.begin(); i != test.end();++i){
        cout << *i << " ";
    }
    cout << endl;
    return test;
}

GTUVector<int> testVector(){
    int max=0,element=0;
    
    cout << "Please enter number of elements do you want: ";
    cin >> max; // throw koy.

    cout << "Please enter the elements of vector: "; // exception
    cin >> element;
    GTUVector<int> test(element);

    for(int i=1;i<max;i++){
        cout << "Please enter the elements of vector: "; // exception
        cin >> element;
        test.insert(element);
    }
    cout << "THE VECTOR: "; 
    for(auto x = test.begin(); x != test.end();++x){
        cout << *x << " ";
    }
    cout << endl;

    return test;
}

void testFind(){
    int input=0,input2=0,element=0;
    GTUSet<int> test_set;
    GTUVector<int> test_vector;

    cout << "Press 1 to test with GTUSet" << endl;
    cout << "Press 2 to test with GTUVector" << endl;
    do{
        cin >> input;
        if(input <= 0 || input > 2)
            cout << "Wrong Input. Try Again..." << endl;
    }while(input <= 0 || input > 2);

    if(input == 1){
        test_set = testSet();

        cout << "Please enter the number do you want to find: ";
        cin >> input2;

        auto it = find (test_set.begin(), test_set.end(), input2);
        if (it != test_set.end())
            cout << "Element found in GTUSet: " << *it << '\n';
        else
            cout << "Element not found in GTUSet\n";
    }   
    else if(input == 2){
        test_vector = testVector();

        cout << "Please enter the number do you want to find: ";
        cin >> input2;

        auto it = find (test_vector.begin(), test_vector.end(), input2);
        if (it != test_vector.end())
            cout << "Element found in GTUVector: " << *it << '\n';
        else
            cout << "Element not found in GTUVector\n";
    }   
}

void testFind_if(){
    int input=0,input2=0,element=0;
    GTUSet<int> test_set;
    GTUVector<int> test_vector;

    cout << "Press 1 to test with GTUSet" << endl;
    cout << "Press 2 to test with GTUVector" << endl;
    do{
        cin >> input;
        if(input <= 0 || input > 2)
            cout << "Wrong Input. Try Again..." << endl;
    }while(input <= 0 || input > 2);

    if(input == 1){
        test_set = testSet();

        cout << "NOTE : The test is prepared with the \'isOdd\' function. \n";

        GTUSet<int>::iterator gt_it = find_if(test_set.begin(),test_set.end(),IsOdd);
        if(gt_it == test_set.end())
            cout << "Odd number not found" << endl;
        else
            cout << "The first odd value is: " << *gt_it << endl;
    }   
    else if(input == 2){
        test_vector = testVector();

        cout << "NOTE : The test is prepared with the \'isOdd\' function. \n";

        GTUVector<int>::iterator gt_it = find_if(test_vector.begin(),test_vector.end(),IsOdd);
        if(gt_it == test_vector.end())
            cout << "Odd number not found" << endl;
        else
            cout << "The first odd value is: " << *gt_it << endl;
        
    }
}

void testFor_each(){
    int input=0,input2=0,element=0;
    GTUSet<int> test_set;
    GTUVector<int> test_vector;

    cout << "Press 1 to test with GTUSet" << endl;
    cout << "Press 2 to test with GTUVector" << endl;
    do{
        cin >> input;
        if(input <= 0 || input > 2)
            cout << "Wrong Input. Try Again..." << endl;
    }while(input <= 0 || input > 2);

    if(input == 1){
        test_set = testSet();

        cout << "NOTE : The test is prepared with the \'twoTimes\' function. \n";

        for_each (test_set.begin(), test_set.end(), twoTimes);
        cout << endl;
    }   
    else if(input == 2){
        test_vector = testVector();

        cout << "NOTE : The test is prepared with the \'twoTimes\' function. \n";

        for_each (test_vector.begin(), test_vector.end(), twoTimes);
        cout << endl;
    }
}