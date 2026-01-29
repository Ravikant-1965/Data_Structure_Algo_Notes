#include <iostream>
#include <vector>
using namespace std;

// koi bhi 2 ki power vala number hai, agr usme ek minus karr diya (-1) to uss number me saare bits 1 ho jayenge.
// (1 << number of bits) - 1 :-> a number with number of bits all equal to 1.
                
int main(){
    /*
    Q)1  The minimum number of bits required to represent a positive integer n in binary is (excluding leading zeros).
    Approach 1 :-   Every division by 2 removes one binary digit (bit) from the number.
                    11001 -> 1100 -> 110 -> 11 -> 1 -> 0.
    */
    int n;
    cin >> n;

    int bits = 0;

    while(n){
        bits++;
        n /= 2;
    }
    cout << bits;
    /*
        Appraoch 2 :- log(n) + 1
            1. number of bits=⌊log2​(n)⌋+1
            2. For n = 0, this formula does not work, because log2(0) is undefined.
                → You need to handle it separately: if n == 0, number of bits = 1.

            3. Make sure you use base 2 logarithm (log2), not the natural logarithm log.

            🧩 Example
            n	    Binary	    Bits
            0	    0	        1
            5	    101	        3
            15	    1111	    4
            16	    10000	    5
    */

    int n;
    cin >> n;

    if (n == 0) {
        cout << 1;  // special case
    } else {
        int bits = floor(log2(n)) + 1;
        cout << bits;
    }

    // similary the number of digits in a positive number 'n' is given by
    // digits=[log10 ​(n)] + 1

    int n;
    cin >> n;

    if (n == 0) {
        cout << 1; // special case
    } else {
        int digits = floor(log10(n)) + 1;
        cout << digits;
    }


    /*
    Bitmasking means using the binary representation of numbers to
    store, access, or manipulate subsets of data using bitwise operations.
        1. A bitmask is just an integer where each bit represents some state (true/false, on/off, included/excluded).
        2. By applying bitwise operators (&, |, ^, ~, <<, >>), you can test or change those states efficiently.

    Bitmasking is an operation by which we allow only certain bits o pass through while blocking/masking the rest of the bits
    
    EX :- 
        Q2) Find the kth bit is set in N.
        
            if (N & (1 << k-1 )){

                kth bit is set bit

            }else{
                it would give zero and the
                kth bit is not set bit
            }
    */



    /* Q3) Bitmasking approach to generate all subsets of a set
    Given set S -> {A, B, C}. Create all possible subsets of the Given Set S. */
    char arr[] = {'A', 'B', 'C'};
    int N = sizeof(arr) / sizeof(arr[0]);
    /* For N elements total, subsets combination -> 2^N, 
       0 -> means exclude
       1 -> means include
       0 0 0 -> means eclude all (empty set), 1 1 1 -> means include all (ABC set)
    */
    
    vector<vector<char>> allSubSets;
    for(int mask = 0; mask < (1 << N); mask++){   // all possible mask/subsets
            vector<char> curr;
            for(int j = 0; j < N; j++){   // for all bits in bitmask of N-bits
                if(mask & (1 << j)){      // if the jth bit of the mask is set, then execute the block
                    curr.push_back(arr[j]);
                }
            }
            allSubSets.push_back(curr);
    }

    // Print all the subsets
    for(auto &subset : allSubSets){
        cout << "{ ";
        for(char c : subset){
            cout << c << " ";
        }
        cout << "}" << endl;
    }
    // TC :- O(N 2^N)



    // Q4) Change the ith bit to set bit :- if 0 , make it 1.
    // Logic :- (1 || 0 == 1)  (1 || 1 == 1);
    int n, i;
    cin >> n >> i;
    cout << (n | (1 << i));
    /* Important :- if the ith bit == 0 then , This actually means adding 2^i to n => n + 2^i */


    // Q5) Clear the ith bit :- if 1 , make it 0.
    // Logic :-
    // n        ->   1 0 0 1 1 0 1 0 1
    // 1 << i   ->   0 0 0 0 1 0 0 0 0
    // ~(1<<i)  ->   1 1 1 1 0 1 1 1 1  (mask)
    // now and the 'n' and '~(1<<i)'
    int n, i;
    cin >> n >> i;
    cout << (n & (~(1 << i)));



    /* Q6) Find the number of bits to change to to convert a to b
    Logic :- We will use '^ XOR' operator :- If bits are same -> 0, if bits are different -> 1
    a     -> 1 0 1 1 0
    b     -> 1 1 0 1 1
    a ^ b -> 0 1 1 0 1 (mask)

    so all the bits that we have to change has been set to '1' in the mask,
    now the Question becomes count the number of set bits

    Approach 1 : (basic bit-counting (Brian Kernighan’s simpler variant))
    Now to count the number of set bits in n , right shift n till it becomes 0, and count for the odd numbers
    
    For n = 13 → binary 1101
    Steps:
        n = 13 (1101) → odd → count = 1
        n = 6  (0110) → even → count = 1
        n = 3  (0011) → odd → count = 2
        n = 1  (0001) → odd → count = 3
        n = 0  → stop
    */
    int n;
    cin >> n;
    int count = 0;

    while (n > 0) {
        if (n & 1){  // check if last bit is 1 (odd number)
            count++;
        }
        n = n >> 1;  // right shift by 1
    }

    cout << count;
    // TC :- O(log,2 n) :- n = number of bits, (because n >> 1 means dividing by 2)


    // Appraoch 2 :- Faster manual method (Brian Kernighan’s Algorithm)
    // n & (n-1) this is used to make the least significant set bit to '0'.
    // This method counts set bits in O(number of set bits) instead of O(total bits):

    int n = 9;
    int count = 0;
    while (n) {
        n = n & (n - 1); // removes the last set bit
        count++;
    }
    // count = 2

    /* Why it works:

        Let’s look at what happens in binary when we subtract 1.

        Suppose n looks like this:
        xxxxx1000...000   ← the rightmost 1 bit, then some 0s
        When you do n - 1:
        That rightmost 1 becomes 0.
        All bits after it (to the right) become 1.

        So:
            n       = xxxxx1000...000
            n - 1   = xxxxx0111...111

        Now when you AND them:
            n & (n - 1) = xxxxx0000...000

        The bit at the position of the rightmost 1 is cleared. ✅
        TC :- O(n), where n is number of set bits only */


    // using built-in function :-
    int n = 9;
    int count = __builtin_popcount(n); // count = 2

}


/*
    🔹 Common Bitmask Operations
    Let’s say we have a mask m:

    1.) Toggle a bit (flip element i’s state)

        m ^= (1 << i);

    2.) To know if two numbers share a common set bits or not ?

        bool shareCommonSetBits(int a, int b){
            if((a & b) == 0){
            return true;
        }
        return false;
}
*/