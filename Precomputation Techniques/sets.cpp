#include <iostream>
#include <set>
#include <unordered_set>

using namespace std;

// to print
void print(set<string> &s){
    // using range based loop
    for(auto it : s){
        cout << it << endl;
    }
    // using iterator
    for(auto it = s.begin(); it != s.end(); it++){
        cout << (*it) << endl;
    }
}

void print(unordered_set<string> &s){
    // using range based loop
    for(auto it : s){
        cout << it << endl;
    }
    // using iterator
    for(auto it = s.begin(); it != s.end(); it++){
        cout << (*it) << endl;
    }
}

int main(){
    set<string> s;

    // for insertion (stores unique elements in sorted order)
    s.insert("abs");  // log(n)
    s.insert("abc");
    s.insert("abd");

    // for searching there is no rectangular brackets like map, you have to do it using find(returns an iterator)
    auto it = s.find("abs");   // log(n)
    if(it != s.end()){
        cout << (*it) << endl;
        s.erase(it);
    }
    // or
    s.erase("abc");   // erase can take both iterator and stirng as input


    print(s);



    // ===================================================== Question 1 =============================================================
    /*
    Given N strings, print unique strings in lexiographical order
    N <= 10^5;
    |S| <= 100000
    */
   

    set<string> s;
    int n;
    cout << "Enter the number of strings queries : ";
    cin >> n;
    
    for(int i = 0; i < n; i++){
        string str;
        cin >> str;
        s.insert(str);
    }
    cout << "Unique strings are :- ";
    for(auto it : s){
        cout << it << " ";
    }
    


    // ================================================ Unordered Sets =============================================================
    // (stores unique elements in non soted order) so use it only when the order is not your concern.
    // use it when you only have to chekck if there is an element present in set or not


    unordered_set<string> s;
    s.insert("abs");  // O(1)
    s.insert("abc");
    s.insert("abd");

    // for searching there is no rectangular brackets like map, you have to do it using find(returns an iterator)
    auto it = s.find("abs");   // O(1)
    if(it != s.end()){
        cout << (*it) << endl;
        s.erase(it);
    }
    // or
    s.erase("abc");   // erase can take both iterator and stirng as input

    print(s);



    // ===================================================== Question 2 =============================================================
    /*
    Given N strings and Q queries.
    In each query you are given a string
    print yes if string is present else print no.

    N <= 10^6
    |S| <= 100
    Q <= 10^6
    */

    unordered_set<string> s;
    int n;
    cout << "Enter the number of string queries: ";
    cin >> n;

    cout << "Enter the strings:\n";
    for (int i = 0; i < n; i++) {
        string str;
        cin >> str;
        s.insert(str);
    }

    int q;
    cout << "Enter the number of queries to check: ";
    cin >> q;

    cout << "Enter query strings:\n";
    while(q--){
        string str;
        cin >> str;
        if(s.find(str) == s.end()){
            cout << "no\n";
        }else{
            cout << "yes\n";
        }
    }

    
}

