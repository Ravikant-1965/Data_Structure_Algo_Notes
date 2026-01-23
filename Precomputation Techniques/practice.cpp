/*
In competitive programming (CP), precomputation refers to the technique of calculating and storing results
in advance—before processing queries or before entering the time-critical part of your solution—so that
later lookups or computations can be done in (amortized) constant or otherwise very small time.

Common Precomputation Patterns
    1. Prefix Sums
    Problem: Given an array A[1…N] answer many queries of the form “sum of A[l…r]”.

    Precompute:
        vector<long long> pref(N+1);
        pref[0] = 0;
        for (int i = 1; i <= N; ++i)
            pref[i] = pref[i-1] + A[i];

    2. Sieve of Eratosthenes (Prime Flags / Smallest Prime Factor)
    Problem: Test primality or factor numbers up to 10⁷ quickly, or compute φ(n) for all n.

    Precompute in O(N log log N) or O(N):
    Prime flags: is_prime[i] array.
    SPF (Smallest Prime Factor): spf[i] allows factorization of any number ≤ N in O(log N).


    3. Hashing
*/

#include <iostream>
using namespace std;

namespace factorial_module {
    const int M = 1e9 + 7;
    const int N = 1e5 + 10;

    long long fact[N];

    void run() {
        int t;
        cout << "Enter the number of test cases : "; 
        cin >> t;
        while(t--){
            int n;
            cout << "Enter the number : "; 
            cin >> n;
            long long fact = 1;

            for(int i = 2; i <= n; i++){
                fact = (fact * i) % M;
            }
            cout << fact << endl;
        }

        // TC :- O(T * N) = 10^10 iterations
        // so to reduce this TC we use Precomputation technique like hashing and we will store the value seperate in an aray

        fact[0] = fact[1] = 1;
        for(int i = 2; i < N; i++){
            fact[i] = ( fact[i-1] * i ) % M;
        }
        int t;
        cout << "Enter the number of test cases : "; 
        cin >> t;
        while(t--){
            int n;
            cout << "Enter the number : "; 
            cin >> n;
            // and this time just access the pre-computed number
            cout << fact[n] << endl;
        }

        // TC :- O(N) + O(T) = 10^5 + 10^5
        // reduce to nealry O(N)
    }
}

/*
Question 2 : Given array of N integers. Given Q queries and each and every given L and R
Print sum of array elements form L to R (both included)

Constraints
1 <= N <= 10^5
1 <= a[i] <= 10^9
1 <= Q <= 10^5
1 <= L, R <= N
*/

namespace prefix1D_module {
    const int N = 1e5 + 10;
    int a[N];
    int pf[N];

    void run() {
        int n;
        cout << "Enter the length of the array : ";
        cin >> n;
        cout << "Enter the elements of the array : " << endl;
        for(int i = 1; i <= n; i++){  // loop starts from 1 to avoid out of bound access
            cin >> a[i];
            pf[i] = pf[i-1] + a[i];   // since the array is declared outside, so all the elements are 0;
        }

        int q;
        cout << " Enter the number of queries you wanna perform : ";
        cin >> q;
        while(q--){
            int l, r;
            cin >> l >> r;
            long long sum = 0;
            cout <<"Sum of " << l << r  << "is "<< pf[r] - pf[l-1] << endl;

            /* 
            You can also calculate prefix product :-
            For a query [start, end], the product can be computed as prefix[end] / prefix[start-1] (if start > 0)
            or simply prefix[end] if start == 0.
            */
        }
    }
}

// prefix sum important concept:
    // If the sum of elements from index 0 to j is currSum, and we previously saw a prefix sum of currSum - goal
    // then the subarray between those two indices has sum goal.
// Leetcode 930, 560, 1248

// Solutions that require sequences of elements to meet criteria often utilize prefix sums/cumulative sums.

// leetcode 560 :- Given an array of integers nums and an integer k, return the total number of subarrays whose sum equals to k.
int subarraySum(vector<int>& nums, int k) {
    unordered_map<int, int> mp;
    int result = 0;
    // cumalative sum = 0. pehle se hi present hota hai
    mp.insert({0,1});   // cumSum = 0 is already present at first

    vector<long long> pf(nums.size()+1, 0);

    int cumSum = 0;
    for(int i = 0; i < nums.size(); i++){
        // we can simply use cumSum variable istead of prefixSum array
        // because we are storing the Prefix sum in the map anyways
        cumSum += nums[i];

        // explanation is that :- if past me cumSum - k mujhe mila tha, iska matlab ki vaha se lekar cumSum takk ka sum k raha hogga
        if(mp.find(cumSum - k) != mp.end()){
            result += mp[cumSum - k];
        }

        mp[cumSum]++;
    }

    return result;
}

// ----------------------------------------------------------------- Prefix sum on 2-D arrays --------------------------------------------------------------------

/*
Do leetcode 1074 also after this..
Question : Given 2D array of N*N integers. Given Q queries and in each query given a, b, c, d.
Print the sum of squares represented by (a,b) as top left point and (c,d) as bottom right point.

Constraints : 
1 <= N <= 10^3
1 <= a[i][j] <. 10^9
1 <= Q <= 10^5
1 <= a,b,c,d <= N
*/

namespace prefix2D_module {
    const int N = 1e3 + 10;
    int arr[N][N];
    long long pf[N][N];

    void run() {
        // Part 1:-
        int n;
        cout << "Enter the length of the array : ";
        cin >> n;

        cout << "Enter the elements of the array";
        // make a 1 based 2-D array
        for(int i = 1; i <= n; i++){
            for(int j = 1; j <= n; j++){
                cin >> arr[i][j];
            }
        }

        int q;
        cout << "Enter the number of queries you wanna take : ";
        cin >> q;

        while(q--){
            int a, b, c, d;
            cout << "Enter the value of a, b, c, d : ";
            cin >> a >> b >> c >> d;
            long long sum = 0;
            for(int i = a; i <= c; i++){
                for(int j = b; j <= d; j++){
                    sum += arr[i][j];
                }
            }
            cout << "The sum of the rectangle is : " << sum;
        }
        // TC :- O(N^2) + O(Q * N^2) = 10^5 * 10^6 = 10^11 (Which is not possible in one (10^7))
        // So we will use prefix sum technique to reduce the time complexity

        // part 2:-
        cout << "Enter the length of the array : ";
        cin >> n;

        cout << "Enter the elements of the array" << endl;
        // make a 1 based 2-D array
        for(int i = 1; i <= n; i++){
            for(int j = 1; j <= n; j++){
                cin >> arr[i][j];
                pf[i][j] = arr[i][j] + pf[i-1][j] + pf[i][j-1] - pf[i-1][j-1];
            }
        }

        cout << "Enter the number of queries you wanna take : ";
        cin >> q;

        while(q--){
            int a, b, c, d;
            cout << "Enter the value of a, b, c, d : ";
            cin >> a >> b >> c >> d;
            cout << "The sum of the rectangle is : " << pf[c][d] - pf[a-1][d] - pf[c][b-1] + pf[a-1][b-1] << endl;
        }
        // TC :- O(N^2) + O(Q) = 10^6 + 10^5 = 10^6
    }
}

int main() {
    factorial_module::run();
    prefix1D_module::run();
    prefix2D_module::run();
    return 0;
}
