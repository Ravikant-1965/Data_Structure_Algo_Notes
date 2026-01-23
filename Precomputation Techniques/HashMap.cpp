#include <iostream>
#include <string>
#include <map>

using namespace std;

// Ordered map ki implementation Balanced tree se hoti hai
// isiliye voh searching, inserting, deletion ka O(log n) time leta hai

// Unorderd map ki implementation Arrays (ya kahi kahi hash map bhi keh dete hai)
// se hoti hai isiliye voh O(1) TC leta hai
void printm(map<int, string> &mpp){
    // Declare iterator to print the map because it is not stored like array 
    map<int, string> :: iterator it;
    for (it = mpp.begin(); it != mpp.end(); it++){
        cout << (*it).first << " " << (*it).second << endl;
    }
    // OR
    for(auto &pr : mpp){  // so no copy variable is created in map each time
        cout << "From second print : " << pr.first << " " << pr.second << endl;
    }
}

void print_um(unordered_map<int, string> &ump){
    // Declare iterator to print the map because it is not stored like array
    unordered_map<int, string> :: iterator it;
    for (it = ump.begin(); it != ump.end(); it++){
        cout << (*it).first << " " << (*it).second << endl;
    }
}


int main(){

    int n;
    cin >> n;
    int arr[n];
    for(int i = 0; i<n; i++){
        cin >> arr[i];
    }

    // Count the number of Times a specific value appears in an array.
    // For this naive approach would be to declare a function that would take the array and the number as
    // Parameter and then using count variable and for loop you will return count.
    // This will be of TC : O(n) and suppose there are n numbers in an array and then TC : n x O(n).

    // So to avoid this we use the Concept of Hashing
    // Hashing is the process of mapping data to a fixed-size value (hash code).

    // Processing of Hashing
    int hash[13] = {0};             // 13 is the maximum value of the element in the array
    for (int i = 0; i<n ; i++){
        hash[arr[i]] += 1;
    }

    int q;
    cin >> q;
    while(q--){
        int number;
        cin >> number;
        // fetch
        cout << hash[number] << endl;
    }

// -------------------------------------------------------------------------------------------------------

    // Hash map is a data structure that uses hashing to store (in sorted order w.r.t key) and retrieve data.
    // Unorderd map stores elements in not sorted order
    // Array hashing me agr 13 ki frequency store karni hai toh total 14 size array bana na padega 
    // but HashMap ke Hashing me Hash map unhi elements ki values ko store karega jinki frequency
    // tumhe pata karni hai
    // (at first agr koi element hash map me nahi hogga, toh voh automatically store karr dega uski value)

    int n;
    cin >> n;
    int arr[n];
    for(int i = 0; i<n; i++){
        cin >> arr[i];
    }
    map<int, int> mpp;
    for (int i = 0; i<n ; i++){
        mpp[arr[i]] += 1;
    }

    
            // mpp[nums[i]]++;
            // This line is doing two things at once:
            
            // Access or create the entry in the map with key nums[i]
            
            // Increment the value associated with that key
            
    
    // OR
    int n;
    cin >> n;
    map<int, int> mpp;
    int arr[n];
    for(int i = 0; i<n; i++){
        cin >> arr[i];
        mpp[arr[i]] += 1;
    }

    int q;
    cin >> q;
    while(q--){
        int number;
        cin >> number;
        // fetch
        cout << mpp[number] << endl;
    }


    //===================================================== LUV YOUTUBE ==========================================================================


    // (keys are unique in Ordered map) i.e can't insert multiple keys of same type
    map<int, string> mp;  // creation of map
    // map[key] = value;      storing values in map
    mp[1] = "abc";
    mp[2] = "bcd";
    mp[3] = "cde";
    // mpp[3] = "zxy"; will update the existing value

    // or by insert method
    mp.insert({4, "deg"});
    mp[5];  // ye initialize karne ki hi TC : O(log(n)) hai.. or value me default values chali jaati hai (0 , "empty string"...etc)


    // More Basic Functions on map
    // find, return an iterator if key is found and return mpp.end(last ke agla iterator) if no key is found
    auto it = mpp.find(3);  // TC : log(n)
    if(it == mpp.end()){
        cout << "No Value";
    } else{
        cout << (*it).first << " " << (*it).second << endl;
    }

    // erase, earases the key and values (can takes both key and an iteraror as a input)
    mpp.erase(1);
    if(it != mpp.end()){ // erase gives segmentaion fault if a non existing key or an iterartor is passed, so to avoid this we use
        mpp.erase(it);
    }
    printm(mp);

    // Important
    map<string, string> mpp1;
    mpp1["abcde"] = "abc";      // this will take string.size() * log(n) TC, because internally ordered map me jab values 
                                // store hoti hai toh voh order me ho isliye existing values se comapre karnme ke baad hoti hai
                                // ab ek string ko duusre string se compare karne me log(n) time toh lagega hi, that's why




    /*
    Queistion : Given N strings, print Unique Strings in Lexiographical order with their frequency
    N <= 10^5
    |S| < = 100
    */

    // So without using maps this question would be hard
    // 1) you will need to find Unique strings
    // 2) then you have to find their frequency
    // So we use map

    map<string, int> mpp2;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++){
        string s;
        cin >> s;
        mpp2[s]++;
    }
    for(auto it : mpp2){
        cout << it.first << " " << it.second << endl;
    }



    // Important
    unordered_map<string, int> mp1;
    // int value = mp[key]; // This will insert the key if it doesn't exist!

    cout << mp1.count("apple") << endl; // 0

    int val = mp1["apple"]; // 👈 Inserts "apple" with value 0
    cout << "val: " << val << endl;    // val: 0

    cout << mp1.count("apple") << endl; // 1 ✅ Now "apple" exists


// =======================================================================================================================================
    // Unorederd map : Use if oreder is not necessary
    // Difference from ordered map :   1) Inbuilt implementation    :- using hash
    //                                 2) Time Complexity           :- O(1)
    //                                 3) Valid Keys datatype       :- can use only simple data types (int, bool, string ) NO pairs etc..
    //                                 4) Prints in any random order
    unordered_map<int, string> ump;
    ump[1] = "abc";  // TC : O(1)
    ump[2] = "bcd";
    ump[3] = "cde";
    ump[4] = "ghi";
    ump[5] = "jkl";
    print_um(ump);
    
    // In unordered_map the TC : of find , erase, search, insert is :- O(1)

}