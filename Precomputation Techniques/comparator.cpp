#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
void print(vector<pair<int, int>> &arr){
    for(auto &it: arr){
        cout << it.first << "-> " << it.second << endl;
    }
}



bool myCmp1(int a, int b){
    if(a > b){
        return true;
    }
    return false;

    // or just return what you want
    // return a > b;
}

// sort in descending order based on both key and value
bool myCmp2(pair<int, int> p1, pair<int, int> p2){
    if(p1.first == p2.first){
        return p1.second > p2.second;
    }
    return p1.first > p2.first;
}


int main(){
    vector<int> vec = {1, 3, 5, 6, 2};

    // increasing order
    sort(begin(vec), end(vec));

    // for decreasing order
    sort(vec.begin(), vec.end(), greater<int>());

    // using own comparator function
    sort(vec.begin(), vec.end(), myCmp1);



    // for vector of pair
    vector<pair<int, int>> arr = {{1,9}, {3,4}, {6,4}, {9,2}};

    sort(arr.begin(), arr.end());
    // this will sort the array in ascending order but based on key only not value....and if the keys are same then
    // it will sort based on value
    
    // using own comparator in descending order
    sort(arr.begin(), arr.end(), myCmp2);
    print(arr);

    
    

// ======================================================  Functors  ====================================================================

    // A function object (or functor) is any object that can be called like a function, typically by overloading the operator().
    struct MyFunctor {
        void operator()() const {
            cout << "Hello from functor!\n";
        }
    };

    MyFunctor f;
    f(); 



    // 🧠 Why Use Function Objects?
    // They’re more flexible than regular functions because:
        // 1) They can hold state (store data inside the object).
        // 2) They can be passed to STL algorithms like sort, for_each, etc.
        // 3) They can be customized using constructors.

    
    // Use Cases
    // 1. Custom Sorting with sort
    struct Descending {
        bool operator()(int a, int b) const {
            return a > b;
        }
    };    
    sort(vec.begin(), vec.end(), Descending());


    // 2. Capturing State
    struct Counter {
        int count = 0;

        void operator()(int x) {
            if (x % 2 == 0) ++count;
        }
    };

    // Use with for_each
    vector<int> nums = {1, 2, 3, 4, 5};
    Counter c = for_each(nums.begin(), nums.end(), Counter());
    cout << "Even numbers: " << c.count << "\n";

    // 3. Replacing Function Pointers
    // Function objects can be more efficient and type-safe than function pointers, especially with templates.

    // ⚡ Bonus: Lambda Functions
    // In modern C++ (C++11 and later), lambdas are syntactic sugar for function objects:

    std::sort(vec.begin(), vec.end(), [](int a, int b) {
        return a > b;
    });

    // Summary
        // Aspect	                                    Function Object (Functor)

        // Syntax	                                      Object with operator()
        // Stores State?	                                        Yes
        // Use with STL?	                            Yes (sort, for_each, etc.)
        // Replaceable by?	                        Lambda expressions (in modern C++)



// =================================================  Lambda Expression  =================================================================
 
    // syntax
    auto lambda = [](int a, int b){
        return a > b;
    };
    // 🧠 Lambda Expressions in C++ (introduced in C++11)
        // A lambda expression is an anonymous function you can define inline, especially useful for short operations
        // like sorting, filtering, or callbacks.

    
    // ✅ Example
    auto add = [](int a, int b) {
        return a + b;
    };
    cout << add(2, 3);  // Output: 5


    // 🔍 Parts of a Lambda
    //  Part	                              Description

    // [capture]	                  Captures external variables
    // (parameters)	                    Function parameters
    // -> return_type	            (Optional) Explicit return type
    // { body }	                        The function's logic



    // 🎯 Common Use Case: Sorting
    vector<int> v = {4, 2, 5, 1};

    sort(v.begin(), v.end(), [](int a, int b) {
        return a > b;  // sort in descending order
    });




    // 📦 Capturing Variables
    // You can capture variables from the surrounding scope:
    int threshold = 10;
    auto isLarge = [threshold](int x) {
        return x > threshold;
    };

    // Capture modes:
    // Capture	                    Meaning
    // [=]	                    Capture all by value
    // [&]	                    Capture all by reference
    // [x]	                    Capture only x by value
    // [&x]	                    Capture only x by reference

}