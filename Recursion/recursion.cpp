// When a Function calls itself directly or in directly it is called recursion
// When to apply : If in a Question the solution of bigger problem is depending upon the solution of smaller problem of same type
// How to apply : 1) Base case jo aapko pata hai (mandatory)
//                2) Recursive relation (How the data are dependent on each other)
//                3) Processing (The equation like : int ans = n * fact(n-1)) (This steps's order is important, Count of numbers)
// If you dont Know the Base case then you can find using Recursive tree method (see pic)


#include <iostream>
#include <limits.h>
#include <vector>
using namespace std;

// Count numbers using Recursion
// void count(int n){
//     if(n == 1){
//         cout << n << " ";
//         return;
//     }
//     cout << n << " ";
//     count(--n);   // this function is ending with recursive relation so it is called tail recursion
// }
void count(int n){
    if(n == 0){
        return;
    }
    count(n-1);       // recursive statement pehle aa rahi hai, processing ke
    // count(--n);    // understand the difference between the above and this line
    cout << n << " "; // This Function is ending with processing of the recursion, so it is called head recursion
}


int factorial(int n){
    int ans = 1;
    while(n > 0){
        ans = ans * n;
        n--;
    }
    return ans;
}

// Using Recursion
int factorial1(int n){
    if(n == 1 || n == 0){
        return 1;
    }
    int ans = n * factorial1(n - 1);
    return ans;
}



// Power of two using Recursion
int pow_2(int n){
    if(n == 0){
        return 1;
    }
    int ans = 2 * pow_2(n - 1);
    return ans;
}



// Fibbonacci Using Recursion
int fibbo(int n){
    if(n == 0){
        return 0;
    }
    else if(n == 1){
        return 1;
    }
    int ans = fibbo(n - 1) + fibbo(n - 2);
    return ans;
}



// Sum using Recursion
int sum(int n){
    if(n == 1){
        return 1;
    }
    int ans = n + sum(n - 1);
    return ans;
}

 

// Printing an array using Recursion
void print_arr(int *arr, int size, int i){ // Find out why

    // Base case
    if(i >= size){
        return;
    }

    // Processing            // If the processing case is after the recursive case then it will print in reverse order
    cout << arr[i] << " ";

    // recursive relation
    print_arr(arr, size, i + 1);
}



// Searching in an array Using recursiuon
bool search(int arr[], int size, int i, int target){

    // Base case
    if(arr[i] == target){
        return true;
    }
    else if(i >= size){
        return false;
    }

    // Recursive relation
    bool ans = search(arr, size, i + 1, target);
    return ans;
}



void findmin(int arr[], int size, int i, int &mini){  // Actual mini (int mini) se compare karane ke liye by Refrence
    // Base case
    if(i >= size){
        return;
    }

    // Processing
    mini = min(mini, arr[i]);

    // Recursive Relation
    findmin(arr, size, i + 1, mini);
}



// Printing Digits using Recursion 
void print_digits(int num){
    // base case
    if(num == 0){
        return;
    }

    // Processing
    int digit = num % 10;

    // Recursive Relation
    print_digits(num/10);

    // Processing
    cout << digit << " "; // Hame ulta print karna hai so head recursion
}



// Check if array is Sorted or not Using recursion
bool check_sort(int arr[], int size, int ind){
    // Base case
    if(ind >= size){
        return true;
    }

    // Processing
    if(arr[ind] > arr[ind-1]){
        return check_sort(arr, size, ind + 1);
    }
    return false;
}



// Binary search using Recursion TC : log(n)
int search_bin(int arr[], int start, int end, int target){
    // Base case
    if(start > end){
        return -1;
    }

    // Processing
    int mid = start + (end - start) / 2;
    if (arr[mid] == target){
        return mid;
    }

    // Recursive relation
    if(arr[mid] < target){
        return search_bin(arr, mid+1, end, target);
    }
    else if(arr[mid]>target){
        return search_bin(arr, start, mid-1, target);
    }

    return -1; // Should never reach here, but avoids warning
}



//  Sub Sequence using Recursion (Understand this)
//  The Concept of Include exclude (Love babbar class 3)
void findSubSequence(string str, string output, int i){

    if(i >= str.length()){
        // ans jo h, vo output string me build ho chupka h
        // so print kardo
        cout << "-->  " << output << endl;
        return;
    }

    // char ch = str[i];

    //Exclude
    findSubSequence(str, output, i + 1);

    // Include
    // Output string me ch character ko include kardo
    // output.push_back(ch);
    findSubSequence(str, output + str[i], i + 1);
}


// Important to understand Backtracking
// DNC week class 2 Love babbar
void printPermutation(string &str, int index) {
	//base case
	if(index >= str.length() ) {
		cout << str << " ";
		return;
	}

	for(int j = index; j<str.length(); j++) {
		swap(str[index], str[j]);
		//recursion
		printPermutation(str, index+1);
		//backtracking
		swap(str[index], str[j]);
	}
	
}




int main(){

    // count(9);


    // Find SubSequence
    // string str = "abc";
    // string output = " ";
    // int index = 0;
    // findSubSequence(str, output, index);


    // Binary search using recursion
    // int arr[7] = {10, 20, 30, 40, 50, 60, 70};
    // int start = 0;
    // int end = 6;
    // int target = 20;
    // int ans = search_bin(arr, start, end, target);
    // cout << ans << endl;



    // Find if array is sorted or not
    // int arr[7] = {10, 20, 30, 40, 50, 60, 70};
    // int size = 7;
    // int ind = 0;
    // bool ans = check_sort(arr, size, ind);
    // if(ans){
    //     cout << "Array is Sorted" << endl;
    // }
    // else{
    //     cout << "Array is not Sorted" << endl;
    // }



    // int num = 65474;
    // print_digits(num);


    // int n;
    // cout << "Enter the number : ";
    // cin >> n;

    // int ans = fibbo(n);
    // cout << ans;



    // int arr[] = {1, 2, 3, 4, 5};
    // int size = sizeof(arr) / sizeof(arr[0]);
    // int i = 0;
    // // int target = 5;
    // int mini = INT_MAX;
    // findmin(arr, size, i, mini);
    // cout << "Minimum number is : " << mini;


    // bool ans = search(arr, size, i, target);
    // cout << "Fount or not ? " << ans;
    // print_arr(arr, size, i);

    string str = "abc";
	int index = 0;
	printPermutation(str, index);


}