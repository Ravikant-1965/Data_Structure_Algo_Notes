#include <iostream>
#include <list>
using namespace std;



// Recursive Hypothesis: “Assume that the recursive function works correctly for all inputs smaller than the current one.”

// 1. Why do we need a hypothesis in recursion?
// Whenever you write a recursive function, you break a problem of size n into one or more smaller subproblems.
// To be sure your overall function is correct, you need to know:
        // 1) Base case(s): That the function works correctly for the smallest inputs (e.g. n = 0 or n = 1).
        // 2) Recursive step: If you assume it works for inputs smaller than n (the recursive hypothesis), then you can show it works for input n itself.
// This mirrors the structure of a mathematical induction proof:
        // Base case: Show P(0) (or P(1)) is true.
        // Inductive step: Assume P(k) is true for all k < n, then show P(n) holds.
// By carrying that assumption—the recursive hypothesis—you avoid having to re‑prove correctness of every smaller subproblem from scratch.


// In the context of recursion, induction refers to the “step” in your reasoning (or proof) where you show:
// “If the function works correctly on all smaller inputs, then it also works correctly on the current input.”
// This mirrors mathematical induction, which has two parts:
    // 1) Base Case
    // You prove the statement is true for the simplest input(s)—for example, n = 0 or n = 1.
    // 2) Inductive (Recursive) Step
    // You assume the statement holds for all cases up to some size k (that’s your inductive hypothesis), and then prove it for k + 1.





// Ways to approach resursion problem...
    // 1) Input Output / inslude exclude method
    // 2) Base case, Induction and Hypothesis step
    // 3) choice diagram DP


// Question 1 :-------------->> Print 1 - n
void print1ton(int n){
    if(n <= 1){
        cout << n;
        return;
    }

    print1ton(n-1);

    cout << n;
}



// Insert function used in Below to insert back the Poped element
void Insert(vector<int> &a, int t){
    // Base case
    if(a.size() == 0 || a[a.size() - 1] <= t){  // if either the array is empty then push back or if the element is >= to the largest element of the array
        a.push_back(t);
        return;
    }

    int value = a[a.size()-1];  //store the last value
    a.pop_back();               //remove from vector , making the input size smaller

    Insert(a, t);               //insert k at its correct position

    a.push_back(value);         //finally insert the last value that is stored before
}
// Question 2 :------------------>> Sort an array using Recursion
void sortArr(vector<int> &arr){
    int size = arr.size();
    if(size == 1 || size == 0) return;   // base case

    // Hypothesis
    int temp = arr[size - 1];  // store the last index value
    arr.pop_back();            // remove it from vector
    sortArr(arr);              // sort for remaining elements  (here assume that the remaining elements are sorted)

    // Induction step of this function
    Insert(arr, temp);         //insert the stored value at its correct position
    // * Impotant (You can do the iduction step using loop also to decrease the TC, bu as we are studying recursion so we will do it using reursion only)
}



void insertStack(stack<int> &st, int temp){
    if(st.size()==0 || st.top() <= temp){
        st.push(temp);
        return;
    }

    int temp2 = st.top();
    st.pop();
    insertStack(st, temp);

    st.push(temp2);
}
// Question 3 :------------------>> Sorting a stack using Recursion
void sortStack(stack<int> &st){
    if(st.empty() || st.size() == 1){
        return;
    }

    int temp1 = st.top();
    st.pop();
    sortStack(st);

    insertStack(st, temp1);
}



// Question 4 :------------------>> Delete middle element of a stack using recursion
void delMid(stack<int> &st, int mid){  // mid = (size / 2) + 1;
    // Base case 
    // 1) on stack
    if(st.empty() || st.size()==1){
        return;
    }
    // 2) on mid
    if(mid == 1){   // mid = position of the number to be deleted from the top
        st.pop();
        return;
    }

    // Hypothesis
    int temp = st.top();
    st.pop();
    delMid(st, --mid);

    // Induction
    st.push(temp);
}



// Question 5 :------------------>> Reverse a stack using recursion
void insert(stack<int> &st, int temp){
    // Base Case
    if(st.empty()){
        st.push(temp);
        return;
    }

    // Hypothesis
    int temp2 = st.top();
    st.pop();
    insert(st, temp);

    // Induction
    st.push(temp2);
}
// Reverse a stack using Recursion without extra stack or sapce
void Reverse(stack<int> &st){
    // Base case
    if(st.size() == 0 || st.size() == 1){
        return;
    }
    // Hypothesis
    int temp1 = st.top();
    st.pop();
    Reverse(st);

    // induction
    insert(st, temp1);
}


// ---------------------------------------------------Pattern of include exclude-------------------------------------------------------------------------------------

//  Question 6
void subSet(string input, string output){
    if(input.length() == 0){
        cout << output << " ";
        return;
    }

    string output1 = output;
    string output2 = output;

    output2.push_back(input[0]);
    input.erase(input.begin()+0);

    subSet(input, output1);
    subSet(input, output2);
    return;
}
// Recursive function to print all subsets
void printSubsetsRecursive(string str, string output, int index) {
    // Base case: when the index reaches the end of the string
    if (index == str.length()) {
        cout << output << endl;
        return;
    }

    // Exclude the current character and move to the next
    printSubsetsRecursive(str, output, index + 1);

    // Include the current character and move to the next
    printSubsetsRecursive(str, output + str[index], index + 1);
}


// Question 2 -----> print spaces with Permutation 
void solvePermutation(string input, string output){
    if(input.length() == 0){
        cout << output << endl;
        return;
    }

    string output1 = output;
    string output2 = output;

    output1.push_back('_');
    output1.push_back(input[0]);
    output2.push_back(input[0]);

    input.erase(input.begin() + 0);

    solvePermutation(input, output1);
    solvePermutation(input, output2);
}


// Question 3 ------> Permutation with case change (inputs are in small case only)
void caseChange(string input, string output){
    if(input.length() == 0){
        cout << output << endl;
        return;
    }

    string output1 = output;
    string output2 = output;
    output1.push_back(input[0]);
    output2.push_back(toupper(input[0]));
    input.erase(input.begin() + 0);

    caseChange(input, output1);
    caseChange(input, output2);
}


// Question 4 ------> Permutation with case change (input can be in any case, and digits are also included)
void caseChange2(string input, string output){
    if(input.length() == 0){
        cout << output << endl;
        return;
    }

    string output1 = output;
    string output2 = output;

    if(isalpha(input[0])){
        output2.push_back(tolower(input[0]));
        output1.push_back(toupper(input[0]));
        input.erase(input.begin() + 0);
        caseChange2(input, output1);
        caseChange2(input, output2);
    }
    else{
        string output1 = output;
        output1.push_back(input[0]);
        input.erase(input.begin() + 0);
        caseChange2(input, output1);
    }

    return;
}


// Qustion 5 --------> Generate all Balanced Paranthesis
void balancedParanthesis(int open, int close, string output){
    if(open == 0 && close == 0){
        cout << output << endl;
        return;
    }

    if(open > 0){   // Opening ki choice toh hamesha mill rahi hai hame jab takk ki opening khatam nahi ho jata
        string output1 = output;
        output1.push_back('(');
        balancedParanthesis(open-1, close, output1);
    }

    if(close > open){
        string op2 = output;
        op2.push_back(')');
        balancedParanthesis(open, close-1, op2);
    }
}




// Joseph's Problem
class Solution {
    public:
      int usingList(int n, int k){
          list<int> people;
          for (int i = 1; i <= n; i++)
              people.push_back(i);
      
          auto it = people.begin();
      
          while (people.size() > 1) {
              // move k-1 steps
              for (int count = 1; count < k; count++) {
                  it++;
                  if (it == people.end())
                      it = people.begin();
              }
      
              // erase kth person
              it = people.erase(it);
      
              // wrap if needed
              if (it == people.end())
                  it = people.begin();
          }
      
          return people.front();
      }
      
      int usingRecursion(int n, int k){
          
          if (n == 1) {
              return 0; // 0-indexed position
          }
          return (usingRecursion(n - 1, k) + k) % n;
      }
      
      int usingSimulation(int n, int k){
          // just do what have been told
          vector<int> people;
          for (int i = 1; i <= n; i++) {
              people.push_back(i);
          }
          
          int index = 0;
          while (people.size() > 1) {
              // Count k positions (k-1 because we include current)
              index = (index + k - 1) % people.size();
              people.erase(people.begin() + index);
              // After removal, index is already at the next position
              index = index % people.size();
          }
          
          return people[0];
      }
      
      int josephus(int n, int k) {
          // code here
          return usingSimulation(n, k);
          
          return usingList(n, k);
          
          return usingRecursion(n, k);
          
          
      }
  };



  
int main(){

    // Question 1:-
    // print1ton(6);


    // Question 2 :- Sort an array using recursion

    // vector<int> arr = {1, 2, 5, 7, 0};
    // int s = arr.size();
    // for(int i = 0; i<s; i++){
    //     cout << arr[i] << " ";
    // }
    // cout << endl;
    // sortArr(arr);
    // for(int i = 0; i<s; i++){
    //     cout << arr[i] << " ";
    // }


    // Question 3 :-

    // stack<int> st;
    // for (int x : {34, 3, 31, 98, 92, 23}){  // this is something new
    //     st.push(x);
    // }
    // sortStack(st);
    // // Print sorted stack (smallest on top)
    // cout << "Sorted stack (top to bottom): ";
    // while (!st.empty()) {
    //     cout << st.top() << ' ';
    //     st.pop();
    // }



    // Question 4 :-

    // stack<int> st;
    // int size;
    // cout << "Enter the size of the Stack : ";
    // cin >> size;

    // cout << "Enter " << size << " elements for Stack" << endl;
    // for(int i = 0; i< size; i++){
    //     int x;
    //     cin >> x;
    //     st.push(x);
    // }
    // int mid = size / 2 + 1;
    // delMid(st, mid);
    // while (!st.empty()) {
    //     cout << st.top() << ' ';
    //     st.pop();
    // }


    // Question 5 :-

    // stack<int> st;
    // // push some values
    // for (int x : {1, 2, 3, 4, 5})
    //     st.push(x);
    
    // // Reverse it
    // Reverse(st);

    // // Print reversed stack (top to bottom)
    // cout << "Reversed stack (top to bottom): ";
    // while (!st.empty()) {
    //     cout << st.top() << ' ';
    //     st.pop();
    // }
    // cout << '\n';



    // Question 6 :-

    // Print SubSet
    // string input;
    // cin >> input;
    // string output = " ";
    // printSubsetsRecursive(input, output, 0);



    // Question 2 ---> Print String with Space Permutation
    // string input;
    // cout << "Enter the string : ";
    // cin >> input;
    // string output = "";
    // output.push_back(input[0]);     // See the pattern, first charater se pehle koi space nahi chahiye
    // input.erase(input.begin() + 0); // input se 1st character hatao, uske baad us function me daalo
    // solvePermutation(input, output);


    // Question 3 ------> Permutation with Case change
    // string input;
    // cout << "Enter the string : ";
    // cin >> input;
    // string output = "";
    // caseChange(input, output);


    // Question 4
    // string input;
    // cout << "Enter the string : ";
    // cin >> input;
    // string output = "";
    // caseChange2(input, output);


    // Qustion 5
    // cout << "Enter the length of the pair of Paranthesis : ";
    // int n;
    // cin >> n;
    // int open = n;
    // int close = n;
    // string st = "";
    // balancedParanthesis(open, close, st);

    return 0;
}