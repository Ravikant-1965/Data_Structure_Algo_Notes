#include <iostream>
#include <cmath>
#include <numeric>
using namespace std;

double eps = 1e-6;

// remeber, whenever low and high are 1 distance apart, the mid always falls on mid, always
// (7+8) / 2 = 7........... (1+2) / 2 = 1

/*  
 1. while (start <= end)
 -----------------------

 * Style: “Classic” binary search.
 * You treat [start … end] as a closed interval (both inclusive).
 * You always check mid against the target.
 * Typically update pointers as:
     * start = mid + 1 (when going right)
     * end = mid - 1 (when going left)
 * Loop stops when start > end.
 * ✅ Works well when you’re searching for an exact target index (first occurrence, last occurrence, normal binary search).

 ------------------------------------------------------------------

 2. while (start < end)
 ----------------------

 * Style: Interval [start … end) is considered half-open (end not included), or sometimes [start … end] but we stop when they converge.
 * We don’t let start == end run inside the loop.
 * Typically update pointers as:
     * start = mid + 1 (when discarding left half)
     * end = mid (when discarding right half)
 * Loop stops when start == end.
 * ✅ Works very well when the goal is to find the boundary (like minimum element, first index, lower bound, etc.).

 ------------------------------------------------------------------

 3. Which is “better”?
 ---------------------

 * Use <= (closed interval) when:
     * You are searching for a specific element (like target in sorted array).
     * You want to allow start == end inside the loop.

 * Use < (converging pointers) when:
     * You are looking for boundaries (min, max, pivot, first/last occurrence).
     * You want the loop to stop exactly when the answer is found by convergence.

 ------------------------------------------------------------------

 Most competitive programmers prefer:
 * Exact search (target element) → while (start <= end).
 * Boundary search (first/last/pivot/minimum) → while (start < end).
*/


/*
 Finding an exact target index
 -----------------------------

 This means:

 * You’re searching for a specific known value in the array.
 * Example: "Find the index of target = 7 in [1,3,5,7,9]".
 * You check nums[mid] == target.
 * This is the classical binary search case (while (start <= end)).


 Finding a boundary
 ------------------

 This means:

 * You’re not searching for a known value, but rather the point (boundary) in the array where some condition changes.
 * Examples:
     * First index where value ≥ x (lower_bound).
     * Last index where value ≤ x (upper_bound).
     * Index of the minimum element in a rotated sorted array.
     * Peak element in a mountain array.

 Here, the array can be thought of as having two “regions” separated by a boundary:

 * Before the boundary: one property holds.
 * After the boundary: another property holds.

 Binary search zooms in until start == end, which is the boundary.


 Why is “minimum element in rotated array” a boundary problem?
 ------------------------------------------------------------

 Think about [4,5,6,7,0,1,2].

 * Left side ([4,5,6,7]) → strictly increasing, but greater than the right side.
 * Right side ([0,1,2]) → strictly increasing, but smaller than the left side.

 The pivot (minimum element = 0) is the boundary between these two sorted regions.
 We don’t know its value beforehand — we only know the property:

 "It's the point where the array wraps around".

 That’s why it belongs to the boundary search category, not “exact target search”.


 Summary
 -------

 * Exact target search: You know the value (e.g., “find index of 7”).
 * Boundary search: You don’t know the value, but you know the property (e.g., “first element smaller than its predecessor” = pivot).

 So:

 * "Find index of 7" → exact target.
 * "Find minimum element in rotated array" → boundary (because you’re looking for the transition point).
*/



// Questio 1 :- First and last occurrence of an element in a sorted array
// Function to find first occurrence
int firstOccurrence(vector<int>& arr, int target) {
    int low = 0, high = arr.size() - 1, ans = -1;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (arr[mid] == target) {
            ans = mid;
            high = mid - 1; // keep searching left
        } 
        else if (arr[mid] < target) {
            low = mid + 1;
        } 
        else {
            high = mid - 1;
        }
    }
    return ans;
}
// Function to find last occurrence
int lastOccurrence(vector<int>& arr, int target) {
    int low = 0, high = arr.size() - 1, ans = -1;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (arr[mid] == target) {
            ans = mid;
            low = mid + 1; // keep searching right
        } 
        else if (arr[mid] < target) {
            low = mid + 1;
        } 
        else {
            high = mid - 1;
        }
    }
    return ans;
}



// Question 2 :- Count of element in sorted array
// ans :- (first occurrence - last occurrence + 1)
int countOccurrences(vector<int>& arr, int target) {
    int first = firstOccurrence(arr, target);
    if (first == -1) return 0; // element not found
    int last = lastOccurrence(arr, target);
    return (last - first + 1);
}



// Question 3 :- Number of times a sorted array is rotated (Index of Pivot element)
// appraoch find the index of the smallest element, the index of smallest element would be the answer.
// the smallest element, would be smaller than both of the elements on its right and left.
int numberOfTimes(vector<int>& arr) {
    int start = 0, end = arr.size() - 1;
    int n = arr.size();

    while (start <= end) {
        // Case when subarray is already sorted (<= beacuse there could be a case where all the elements in the array are same)
        if (arr[start] <= arr[end]) {
            return start;
        }

        int mid = start + (end - start) / 2;
        // to prevent out of bound access, and make it rotated.
        int next = (mid + 1) % n;
        int prev = (mid - 1 + n) % n;

        // Pivot check
        if (arr[mid] <= arr[next] && arr[mid] <= arr[prev]) {
            return mid;
        }

        // If right half is sorted → pivot in left
        if (arr[mid] <= arr[end]) {
            end = mid - 1;
        }
        // Else pivot in right half
        else {
            start = mid + 1;
        }
    }
    return 0;
}



// Question 4 :- Find Minimum element in Rotated Sorted Array (Leetcode 153) (see the < in while condition *important)
int findMin(vector<int>& nums) {
    int s = 0;
    int e = nums.size() - 1;
    
    while (s < e) {
        // If current subarray is sorted
        if (nums[s] <= nums[e]) {
            return nums[s];
        }

        int mid = s + (e - s) / 2;
        
        // If left half is sorted, minimum is in the right half
        if (nums[mid] > nums[e]) {
            s = mid + 1;
        } else {
            // Otherwise, minimum is in the left half (including mid)
            e = mid;
        }
    }
    // start == end is the index of the minimum element
    return nums[s];
}
// appraoch 2 :-
int findMin2(vector<int>& nums) {
    int s = 0;
    int e = nums.size() - 1;
    int ans = nums[0]; // track minimum

    while (s <= e) {
        // If current subarray is sorted
        if (nums[s] <= nums[e]) {
            ans = min(ans, nums[s]);
            break;
        }

        int mid = s + (e - s) / 2;

        // Left part is sorted
        if (nums[mid] >= nums[s]) {
            ans = min(ans, nums[s]); 
            s = mid + 1; // exclude mid
        }
        // Right part is unsorted → pivot is here
        else {
            ans = min(ans, nums[mid]);
            e = mid - 1; // exclude mid
        }
    }

    return ans;
}


// Question 5:- Find an element in rotated Sorted array.
int searchInRotatedSortedArray(vector<int>& arr, int target) {
    int start = 0, end = arr.size() - 1;

    while (start <= end) {
        int mid = start + (end - start) / 2;

        // Found target
        if (arr[mid] == target) {
            return mid;
        }

        // Check if left half is sorted
        if (arr[start] <= arr[mid]) {
            if (arr[start] <= target && target < arr[mid]) {
                end = mid - 1;  // target lies in left half
            } else {
                start = mid + 1;  // target lies in right half
            }
        }
        // Otherwise right half is sorted
        else {
            if (arr[mid] < target && target <= arr[end]) {
                start = mid + 1;  // target lies in right half
            } else {
                end = mid - 1;  // target lies in left half
            }
        }
    }

    return -1; // target not found
}



// Question 6 :- Search in nearly sorted array (means jo element ith pe honna chahiye tha voh i-1, i , i+1 pe mill sakta hai)
int searchNearlySorted(vector<int>& arr, int target) {
    int start = 0, end = arr.size() - 1;

    while (start <= end) {
        int mid = start + (end - start) / 2;

        // Check mid, mid-1, mid+1
        if (arr[mid] == target) return mid;
        if (mid - 1 >= start && arr[mid - 1] == target) return mid - 1;
        if (mid + 1 <= end && arr[mid + 1] == target) return mid + 1;

        // Move search space
        if (target < arr[mid]) {
            end = mid - 2; // skip mid and mid-1
        } else {
            start = mid + 2; // skip mid and mid+1
        }
    }
    return -1; // target not found
}



// Question 7 :- Find floor of an element in sorted array.
int findFloor(vector<int>& arr, int x) {
    int start = 0, end = arr.size() - 1;
    int ans = -1; // default when no floor exists

    while (start <= end) {
        int mid = start + (end - start) / 2;

        if (arr[mid] == x) {
            return arr[mid]; // exact match is the floor
        }
        else if (arr[mid] < x) {
            ans = arr[mid];   // possible floor
            start = mid + 1;  // try to find a larger one
        }
        else {
            end = mid - 1;    // arr[mid] > x, so move left
        }
    }

    return ans;
}
// If you want the clean < style, do this:
int findFloor2(vector<int>& arr, int x) {
    int start = 0, end = arr.size(); // end is exclusive

    while (start < end) {
        int mid = start + (end - start) / 2;

        if (arr[mid] <= x) {
            start = mid + 1;   // floor is at mid or right
        } else {
            end = mid;         // floor is on left
        }
    }

    // floor is start-1 (if valid)
    return (start > 0 ? arr[start - 1] : -1);
}



// Question 8 :- Find Ciel of an element in sorted array.
int findCeil(vector<int>& arr, int x) {
    int start = 0, end = arr.size() - 1;
    int ans = -1;

    while (start <= end) {
        int mid = start + (end - start) / 2;

        if (arr[mid] == x) {
            return arr[mid]; // exact match is also ceil
        }
        else if (arr[mid] < x) {
            start = mid + 1; // move right
        }
        else {
            ans = arr[mid];  // possible ceil
            end = mid - 1;   // move left
        }
    }
    return ans;
}
// If you prefer the < style (like STL’s lower_bound):
int findCeil2(vector<int>& arr, int x) {
    int start = 0, end = arr.size(); // end exclusive

    while (start < end) {
        int mid = start + (end - start) / 2;

        if (arr[mid] < x) {
            start = mid + 1; // need bigger
        } else {
            end = mid;       // candidate
        }
    }

    // start == end → position of first >= x
    return (start < arr.size() ? arr[start] : -1);
}



// Question 9 :- Next Alphabetical Element
// given array of alphabets and an alphabet "alpha". You have to find the next alphabet of the "alpha" in the array
char nextAlphabet(vector<char>& arr, char alpha) {
    int start = 0, end = arr.size() - 1;
    char ans = '\0'; // default: no answer

    while (start <= end) {
        int mid = start + (end - start) / 2;

        if (arr[mid] > alpha) {
            ans = arr[mid];    // possible answer
            end = mid - 1;     // but check left side for smaller valid
        } else {
            start = mid + 1;   // arr[mid] <= alpha, move right
        }
    }

    return (ans != '\0' ? ans : '-'); 
    // return '-' or any sentinel when no greater element exists
}
// STL-style "lower_bound style"
char nextAlphabet2(vector<char>& arr, char alpha) {
    int start = 0, end = arr.size(); // end exclusive

    while (start < end) {
        int mid = start + (end - start) / 2;

        if (arr[mid] <= alpha) {
            start = mid + 1;   // skip smaller/equal
        } else {
            end = mid;         // candidate
        }
    }

    return (start < arr.size() ? arr[start] : '-'); 
}



// Question 10 :- Find the position of an element in an Infinite sorted array
// This is an Interview Question :- not implementable question
/**
 Problem:
 --------
 You are given an infinite sorted array (sorted in ascending order).
 You need to find the index of a given element `x`.

 Challenge:
 ----------
 - The array is infinite, so you cannot use normal `end = arr.size()-1`.
 - Instead, you must first find a search range that definitely contains `x`,
   then apply binary search.

 Approach:
 ---------
 1. Start with a small window:
      start = 0, end = 1

 2. Expand the window exponentially until `x` lies within [start, end]:
      While arr[end] < x:
          start = end
          end = end * 2

 3. Now `x` must lie between start and end.

 4. Apply binary search in this window.
*/
int binarySearch(vector<int>& arr, int start, int end, int x) {
    while (start <= end) {
        int mid = start + (end - start) / 2;
        if (arr[mid] == x) return mid;
        else if (arr[mid] < x) start = mid + 1;
        else end = mid - 1;
    }
    return -1; // not found
}
// main Function starts here
int findInInfiniteArray(vector<int>& arr, int x) {
    int start = 0, end = 1;

    // Step 1: Expand window until arr[end] >= x
    while (end < arr.size() && arr[end] < x) {  // in practice we simulate infinite with finite
        start = end;
        end = end * 2;
        if (end >= arr.size()) end = arr.size() - 1; // avoid going out of bounds (for simulation)
    }

    // Step 2: Binary search in found window
    return binarySearch(arr, start, end, x);
}



// Question 11 :- Find the index of the First '1', in an infinite sorted binary array
/**
 Problem:
 --------
 You are given an infinite sorted binary array (all 0's come first, then 1's).
 Find the index of the FIRST occurrence of 1.

 Approach:
 ---------
 1. Start with start = 0, end = 1
 2. Expand end exponentially until arr[end] == 1
    (so we know 1 lies in the range [start, end])
 3. Apply binary search in this range to find the first 1

 Time Complexity:
 ----------------
 - Expanding phase: O(log p), where p is the position of first 1
 - Binary search: O(log p)
 - Total: O(log p)
*/
int firstOneInInfiniteArray(vector<int>& arr) {
    int start = 0, end = 1;

    // Step 1: Find a range where 1 exists
    while (end < arr.size() && arr[end] == 0) {
        start = end;
        end = end * 2;
        if (end >= arr.size()) end = arr.size() - 1; // safeguard (for finite simulation)
    }

    // Step 2: Binary search to find first 1
    int ans = -1;
    while (start <= end) {
        int mid = start + (end - start) / 2;

        if (arr[mid] == 1) {
            ans = mid;      // candidate answer
            end = mid - 1;  // move left to find earlier 1
        } else {
            start = mid + 1;
        }
    }
    return ans;
}



// Question 12 :- Minimum Absolute Difference Element in a Sorted Array. Find an element in the array such that
// abs(element - key) is minimum.
// answer :- use "Find Ceil" and "Find Floor" and find the minimum of them and then the answer.
// or better :- Use binary search to find the position where "key" would be inserted.
    // Binary search apply karne ke badd
    // agr key nahi milti hai kisi array me , toh at the end binary search ke baad,
    // end jo hai voh element jaha honna chahiye tha uss se exact pehle point karta hai and start uske exact baad
/**
 Problem:
 --------
 You are given:
   - A sorted integer array
   - An integer "key"

 Approach:
 ---------
 1. Use binary search to find the position where "key" would be inserted.
 2. At the end of binary search:
      - "end" will point to the largest element <= key
      - "start" will point to the smallest element >= key
 3. Compare abs(arr[start] - key) and abs(arr[end] - key)
    → whichever is smaller is the answer.

 Time Complexity: O(log n)
*/
int minAbsDiffElement(vector<int>& arr, int key) {
    int start = 0, end = arr.size() - 1;

    // Normal binary search
    while (start <= end) {
        int mid = start + (end - start) / 2;

        if (arr[mid] == key) {
            return arr[mid]; // exact match, difference = 0
        } else if (arr[mid] < key) {
            start = mid + 1;
        } else {
            end = mid - 1;
        }
    }

    // At this point:
    // "end" points to floor (largest <= key)
    // "start" points to ceil (smallest >= key)

    // Handle boundaries
    if (end < 0) return arr[0]; // key < smallest element
    if (start >= arr.size()) return arr[arr.size() - 1]; // key > largest element

    // Choose closer one
    if (abs(arr[start] - key) < abs(arr[end] - key)) {
        return arr[start];
    }
    return arr[end];
}



// ------------------------------------------------------------ Binary search on answer -------------------------------------------------------------

// actually the main concept is that binary search can be applied on any function
// that is monotonically increasing or monotonically decreasing.


// Question 13 :-  Given an unsorted array of integers. A peak element is strictly greater than both of its neighbors.
                // For the first element, it will be considered a peak if it is greater than the second element.
                // For the last element, it will be considered a peak if it is greater than the second last element.
                // For arrays with only one element, that element is trivially a peak.
// Write a function to return the index of any one peak element. If multiple peaks exist, returning any one of them is acceptable.
int findPeakElement(vector<int>& nums) {
    // Idea :- A peak always exists (at least at the edges).
    // Since we only need any peak, we can use a modified binary search.
    int low = 0, high = nums.size() - 1;
                
    while (low < high) {
        int mid = low + (high - low) / 2;
                
        if (nums[mid] < nums[mid + 1]) {
            // Peak must be on the right
            low = mid + 1;
        } else {
            // Peak is at mid or on the left
            high = mid;
        }
    }
    return low; // or high (they converge)
}



// Question 14 (Leetcode 162 exact similar):- Find the max element in an bitonic array.....
// (Bitonic means,first strictly monotonically increasing and then decreasing)
/*
This requires a little brainstroming.
If the mid element is the local maximum. Cool! Return.
But if it isn't, then go to that side which have a possiblity of peak
(its like climbing a ranges of mountain and you are asked the coordinates of the peak of any one-Single mountanin)
Now whichever side has the greater element, we can go to that side and
continue the same process.)
*/
// Answer :- Its the peak element code only..(in peak element the number of peaks could have more than one, but here there is only one)
int peakBitonic(vector<int>& nums) {
    // Idea :- A peak always exists (at least at the edges).
    // Since we only need any peak, we can use a modified binary search.
    int low = 0, high = nums.size() - 1;
                
    while (low < high) {
        int mid = low + (high - low) / 2;
                
        if (nums[mid] < nums[mid + 1]) {
            // Peak must be on the right
            low = mid + 1;
        } else {
            // Peak is at mid or on the left
            high = mid;
        }
    }
    return low; // or high (they converge)
}
// (Int this type of questions we will technically only be asked for one feasible answer, not all the ansers)


// Question 15 :- Find an element in Bitonic array
/* You are given:
- A bitonic sequence (first strictly increasing, then strictly decreasing) of n distinct elements.
- An integer x.
Task: Find the index of x in the array in O(log n) time. If x is not present, return -1.

Key Idea

1. Step 1: Find the peak element (maximum) using binary search.
   - This divides the array into two sorted halves:
     - Left side → strictly increasing (ascending order).
     - Right side → strictly decreasing (descending order).

2. Step 2: Perform binary search:
   - On the left half (ascending order).
   - On the right half (descending order).

3. Step 3: Return index if found, else -1.
*/
class BitonicSearch {
    public:
        // Binary search on increasing sequence
        int binarySearchAsc(vector<int>& arr, int low, int high, int x) {
            while (low <= high) {
                int mid = low + (high - low) / 2;
                if (arr[mid] == x) return mid;
                else if (arr[mid] < x) low = mid + 1;
                else high = mid - 1;
            }
            return -1;
        }
    
        // Binary search on decreasing sequence
        int binarySearchDesc(vector<int>& arr, int low, int high, int x) {
            while (low <= high) {
                int mid = low + (high - low) / 2;
                if (arr[mid] == x) return mid;
                else if (arr[mid] > x) low = mid + 1;
                else high = mid - 1;
            }
            return -1;
        }
    
        // Find peak index (maximum element in bitonic array)
        int findPeak(vector<int>& arr) {
            int low = 0, high = arr.size() - 1;
            while (low < high) {
                int mid = low + (high - low) / 2;
                if (arr[mid] < arr[mid + 1]) {
                    low = mid + 1;  // go right
                } else {
                    high = mid;     // go left
                }
            }
            return low; // peak index
        }
    
        // Main function to search x in bitonic array
        int searchBitonic(vector<int>& arr, int x) {
            int peak = findPeak(arr);
    
            // If peak itself is x
            if (arr[peak] == x) return peak;
    
            // Search in increasing part
            int left = binarySearchAsc(arr, 0, peak - 1, x);
            if (left != -1) return left;
    
            // Search in decreasing part
            return binarySearchDesc(arr, peak + 1, arr.size() - 1, x);
        }
    };
    


// Question 16 :- Search in a row-wise and coloumn-wise sorted matrix 
// using :- Staircase Search or Greedy elimination search. (Aaditya Verma)
// TC :- O(n + m), where n = number of rows, and m = number of column
bool searchMatrix(vector<vector<int>>& matrix, int target) {
    int n = matrix.size();
    int m = matrix[0].size();
    
    int i = 0;
    int j = m-1;
    
    while(i >= 0 and i < n and j >= 0 and j < m){
        if(matrix[i][j] == target){
            return true;
        }
    
        else if(matrix[i][j] > target){
            j--;
        }
        else if(matrix[i][j] < target){
            i++;
        }
    }
    
    return false;
}
/** Could we start from other corners?

1. Bottom-left (i=n-1, j=0) ✅
   - Works the same way but directions are swapped:
     - If matrix[i][j] > target → move up (i--).
     - If matrix[i][j] < target → move right (j++).
   - This is just a mirror version of top-right.

2. Top-left (i=0, j=0) ❌
   - Doesn’t work with simple moves:
     - If value < target → you might need to go down or right (two choices, not deterministic).
     - This breaks the O(n+m) guarantee.

3. Bottom-right (i=n-1, j=m-1) ❌
   - Same problem as top-left → you can’t decide uniquely whether to move up or left when the value > target.

So only top-right or bottom-left work, because from those positions one comparison always eliminates an entire row or an entire column.
*/

// Using Binary Search :- By converting 1D-array mid to row and col by formula
bool searchMatrix2(vector<vector<int>>& matrix, int target) {
    int m = matrix.size();
    int n = matrix[0].size();

    int low = 0, high = m * n - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;
        int row = mid / n;
        int col = mid % n;

        if (matrix[row][col] == target) {
            return true;
        } 
        else if (matrix[row][col] < target) {
            low = mid + 1;
        } 
        else {
            high = mid - 1;
        }
    }
    return false;
}




// Question 17 :-  Book Allocation Problem
/* You are given:
- An array of integers arr[] of size n where arr[i] represents the number of pages in the i-th book.
- An integer m representing the number of students.

You need to allocate books to students such that:
1. Each student gets at least one book.
2. Each book is assigned to exactly one student.
3. Books are distributed contiguously (i.e., student 1 gets books arr[l] ... arr[r], 
   student 2 gets arr[r+1] ... arr[k], etc.).
4. The goal is to minimize the maximum number of pages assigned to any student.

If allocation is not possible (i.e., m > n), return -1.
*/

// Function to check if a given maxPages can be allocated
bool isPossible(int arr[], int n, int m, int maxPages) {
    int students = 1;
    int sum = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] > maxPages) return false; // A single book exceeds limit
        if (sum + arr[i] > maxPages) {
            students++;
            sum = arr[i];
            if (students > m) return false;
        } else {
            sum += arr[i];
        }
    }
    return true;
}
// Function to allocate books
int allocateBooks(int arr[], int n, int m) {
    if (m > n) return -1; // Not enough books

    // low is the largest one because :- The minimum possible maximum pages can never be smaller than X.
    // (agr no. of book = no. of students huye toh, answer kya hogga ? Max of array hi toh hogga)
    int low = *max_element(arr, arr + n);
    int high = accumulate(arr, arr + n, 0);
    int result = -1;

    while (low <= high) {
        // mid is repressenting here :-  "What if the maximum number of pages a student is allowed to read is mid?"
        // "current guess" for the maximum pages a student should be allowed.
        int mid = low + (high - low) / 2;
        if (isPossible(arr, n, m, mid)) {
            result = mid;
            high = mid - 1; // Try for a smaller maximum
        } else {
            low = mid + 1;
        }
    }
    return result;
}



// Question 18 :- Leetcode 1901 (Important)
class Solution {
    public:
        vector<int> findPeakGrid(vector<vector<int>>& mat) {
            //for brute : You can simply return the maximum in the entire matrix
            // return usingBruteForce(mat);
            // return usingBruteForce2(mat);
            return usingBianrySearch(mat);
        }
    
        vector<int> usingBruteForce(vector<vector<int>>& mat){
            // brute force
            int n = mat.size();
            int m = mat[0].size();
    
            vector<vector<int>> temp(n+2, vector<int>(m+2, -1));
            
            for(int i = 0; i < n; i++){
                for(int j = 0; j < m; j++){
                    temp[i+1][j+1] = mat[i][j];
                }
            }
    
            for(int i = 1; i <= n; i++){
                for(int j = 1; j <= m; j++){
                    int ele = temp[i][j];
                    int top = temp[i-1][j];
                    int down = temp[i+1][j];
                    int left = temp[i][j-1];
                    int right = temp[i][j+1];
                    if(ele > top && ele > down && ele > left && ele > right){
                        return {i-1, j-1};
                    }
                }
            }
    
            return {-1, -1};
        }
    
    
        vector<int> usingBruteForce2(vector<vector<int>>& mat){
            int m = mat.size();
            int n = mat[0].size();
            
            for (int i = 0; i < m; i++) {
                for (int j = 0; j < n; j++) {
    
                    bool isPeak = true;
    
                    // Up
                    if (i > 0 && mat[i][j] <= mat[i-1][j]) {
                        isPeak = false;
                    }
                    // Down
                    if (i < m-1 && mat[i][j] <= mat[i+1][j]) {
                        isPeak = false;
                    }
                    // Left
                    if (j > 0 && mat[i][j] <= mat[i][j-1]) {
                        isPeak = false;
                    }
                    // Right
                    if (j < n-1 && mat[i][j] <= mat[i][j+1]) {
                        isPeak = false;
                    }
                    
                    if (isPeak) {
                        return {i, j};
                    }
                }
            }
            return {-1, -1};
        }
    
    
        vector<int> usingBianrySearch(vector<vector<int>>& mat){
            // concept same as Peak Element 1
            int n = mat.size();
            int m = mat[0].size();
    
            int s = 0, e = m-1;
    
            while(s <= e){
                int mid = s + (e-s) / 2;
    
                int maxRowIndex = findIndex(mat, mid);
    
                int left = mid-1 >= 0 ? mat[maxRowIndex][mid-1] : -1;
                int right = mid+1 < m ? mat[maxRowIndex][mid+1] : -1;
    
                if (mat[maxRowIndex][mid] > left && mat[maxRowIndex][mid] > right){ 
                    return {maxRowIndex, mid};
                }
                else if(left < mat[maxRowIndex][mid]){
                    s = mid+1;
                }
                else{
                    e = mid-1;
                }
            }
            return {-1, -1};
        }
        int findIndex(vector<vector<int>>& mat, int col){
            int maxi = INT_MIN;
            int index = -1;
            for (int i = 0; i < mat.size(); i++) {
                if (mat[i][col] > maxi) {
                    maxi = mat[i][col];
                    index = i;
                }
            }
            return index;
        }
    
    };


// Luv
/* Question 18 :- Nth Root Finder using Binary Search

You are asked to implement a program that calculates the nth root of a given number `x`.

Details:
- Input: A real number `x` (base) and an integer `n` (the degree of the root).
- Output: The nth root of `x`, computed with a high degree of precision.

Conditions:
1. If `x` is negative and `n` is even → print that the result is imaginary.
2. If `x` is 0 or 1 → the root is trivially `x`.
3. Otherwise, use **binary search** to approximate the value of the nth root.

Implementation Hints:
- Use binary search between `[0, max(1, x)]`.
- Define a helper function `func(base, power)` that raises a number to a power using fast exponentiation.
- Keep iterating until the difference between `low` and `high` is less than some precision `eps` (e.g., 1e-9).
- Finally, print the value of the nth root.
*/
class RootCalculator {
public:
    double func(double base, int power) {
        double ans = 1.0;
        while (power > 0) {
            if (power % 2 == 1) {
                ans *= base;
            }
            base *= base;
            power /= 2;
        }
        return ans;
    }

    void calculateRoot() {
        double x;
        int n;
        cout << "Enter the base and nth root: ";
        cin >> x >> n;

        if (x < 0 && n % 2 == 0) {
            cout << "Even root of negative number is imaginary.\n";
            return;
        }

        if (x == 0 || x == 1) {
            cout << "The value of root is: " << x << endl;
            return;
        }

        double low = 0, high = max(1.0, x), mid;

        while (high - low > eps) {
            mid = low + (high - low) / 2;

            if (func(mid, n) < x) {
                low = mid;
            }
            else {
                high = mid;
            }
        }
        cout << "The value of root is: " << low << endl;
    }
};



int main() {

    // Question 1 :-
    // vector<int> arr = {1, 2, 4, 4, 4, 5, 6, 7};
    // int target = 4;
    // int first = firstOccurrence(arr, target);
    // int last = lastOccurrence(arr, target);
    // if (first != -1) {
    //     cout << "First occurrence of " << target << " at index " << first << endl;
    //     cout << "Last occurrence of " << target << " at index " << last << endl;
    // } else {
    //     cout << "Element not found!" << endl;
    // }


    // Question 4 :-
    // vector<int> arr = {4, 5, 6, 7, 0, 1, 2};
    // cout << "Minimum element: " << findMin(arr) << endl;
    // return 0;



    // Question 6 :-
    vector<int> arr = {10, 3, 40, 20, 50, 80, 70};
    int target = 20;
    int index = searchNearlySorted(arr, target);

    if (index != -1)
        cout << "Element found at index " << index << endl;
    else
        cout << "Element not found." << endl;

    


    // Question :-
    RootCalculator obj;
    obj.calculateRoot(); // calls the function
    return 0;
}
