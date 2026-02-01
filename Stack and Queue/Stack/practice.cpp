#include <iostream>
#include <numeric>  // for accumulate
using namespace std;

/*
If you have done a question in O(n^2) and int the for loops if 'j' is dependent on 'i' like j is going from

|-----------------------------|
0             i               n

j ----> 0 to i   j++
j ----> i to n   j++
j ----> i to 0   j--
j ----> n to i   j--

Then there must be a better solution using stack
*/


// Question 1 :- Next greater to the right  (leetcode 503 similar)
vector<int> nextGreaterRight(vector<int> arr) {
    vector<int> ans;
    stack<int> st;

    for (int i = arr.size() - 1; i >= 0; i--) {

        // remove the elements less than or equal to arr[i]
        while (!st.empty() && st.top() <= arr[i]) {
            st.pop();
        }

        // If stack is empty, no greater element push -1
        if (st.empty()) {
            ans.push_back(-1);
        } else {
            ans.push_back(st.top());  // This is the next greater element
        }

        st.push(arr[i]);  // Push current element
    }

    reverse(ans.begin(), ans.end());
    return ans;
}

// 54321

// Question 2 :- Next greater to the left
vector<int> nextGreaterLeft(vector<int> arr) {
    vector<int> ans;
    stack<int> st;

    for(int i = 0; i < arr.size(); i++){
        
        while(!st.empty() && st.top() <= arr[i]){
            st.pop();
        }

        // If stack is empty, no greater element to the left push -1
        if (st.empty()) {
            ans.push_back(-1);
        } else {
            ans.push_back(st.top());  // This is the next greater element
        }

        st.push(arr[i]);  // Push current element
    }

    return ans;
}


// Question 3 :- Next smallest element to the left
vector<int> nextSmallerLeft(vector<int> arr) {
    vector<int> ans;
    stack<int> st;

    for(int i = 0; i < arr.size(); i++){
        
        while(!st.empty() && st.top() >= arr[i]){
            st.pop();
        }

        if (st.empty()) {
            ans.push_back(-1);
        } else {
            ans.push_back(st.top());
        }

        st.push(arr[i]);
    }

    return ans;
}


// Question 4 :- Next smallest element to the right
vector<int> nextSmallestRight(vector<int> arr) {
    vector<int> ans;
    stack<int> st;

    for (int i = arr.size() - 1; i >= 0; i--) {

        while (!st.empty() && st.top() >= arr[i]) {
            st.pop();
        }

        if (st.empty()) {
            ans.push_back(-1);
        } else {
            ans.push_back(st.top());
        }

        st.push(arr[i]);
    }

    reverse(ans.begin(), ans.end());
    return ans;
}


// Question 5 :- Given an array of stock prices, for each day, you need to find the maximum number of consecutive days (including today) 
//              the price was less than or equal to today's price.

// Approach 1 :-  Find the index of the previous greater element to the left, and 
//              Compute i - previous_greater_index for each element i, which gives the number of consecutive smaller or equal elements ending at i.
vector<int> nextGreaterLeftIndex(vector<int>& arr) {
    vector<int> indices;
    stack<int> st; // stack stores indices

    for (int i = 0; i < arr.size(); i++) {
        while (!st.empty() && arr[st.top()] <= arr[i]) {
            st.pop();
        }

        if (st.empty()) {
            indices.push_back(-1);
        } else {
            indices.push_back(st.top());
        }

        st.push(i);
    }

    return indices;
}

vector<int> calculateSpan(vector<int>& arr) {
    vector<int> ans;
  
    // Get indices of previous greater elements
    vector<int> prevGreaterIndex = nextGreaterLeftIndex(arr);
  
    for (int i = 0; i < arr.size(); i++) {
        if (prevGreaterIndex[i] == -1) {
            ans.push_back(i + 1);  // No greater element to the left
        } else {
            ans.push_back(i - prevGreaterIndex[i]);
        }
    }
  
    return ans;
}
// Appraoch 2 :- For each index i, compute span[i] = i - prev_greater_index (or i + 1 if none found).
vector<int> calculateSpan2(vector<int>& arr) {

    vector<int> span(arr.size());
    stack<int> st;

    for (int i = 0; i < arr.size(); i++) {
        
        while (!st.empty() && arr[st.top()] <= arr[i]) {
            st.pop();
        }

        if (st.empty()) {  // stack agr khaali hai iska matlab koi bhi element left me bada nahi hai current arr[i] se, so i + 1;
            span[i] = i + 1;
        } else {
            span[i] = i - st.top();
        }

        st.push(i);
    }

    return span;
}



// Question 6 : Leetcode 84 - Maximum area in an Histogram (leetcode 907 similar)
vector<int> prevSmallerIndex(vector<int>& heights){
    int n = heights.size();
    vector<int> ans;
    stack<int> st;

    for(int i = 0; i < n; i++){
        while(!st.empty() && heights[st.top()] >= heights[i]){
            st.pop();
        }

        if(st.empty()){
            ans.emplace_back(-1);
        }else{
            ans.emplace_back(st.top());
        }

        st.push(i);
    }
    return ans;
}
vector<int> nextSmallerIndex(vector<int>& heights) {
    int n = heights.size();
    vector<int> ans(n);  // Pre-allocate with size n
    stack<int> st;
    
    for (int i = n - 1; i >= 0; i--) {
        while (!st.empty() && heights[st.top()] >= heights[i]) {
            st.pop();
        }
        ans[i] = st.empty() ? n : st.top();  // Direct assignment
        st.push(i);
    }
    return ans;  // No reverse needed
}
int largestRectangleArea(vector<int>& heights) {
    vector<int> psi = prevSmallerIndex(heights);
    vector<int> nsi = nextSmallerIndex(heights);

    int max_area = 0;

    for (int i = 0; i < heights.size(); i++) {
        int width = nsi[i] - psi[i] - 1;
        int area = heights[i] * width;
        max_area = max(max_area, area);
    }

    return max_area;
}

// Appraoch 2
int largestRectangleArea2(vector<int>& heights) {
    stack<int> st;  // Stack to store indices  [2,1,5,6,2,3]
    int maxArea = 0;
    int n = heights.size();

    for (int i = 0; i <= n; i++) {
        // Use 0 as sentinel value when i == n
        int currentHeight = (i == n) ? 0 : heights[i];
        
        // Pop from stack while current height is less than stack top height
        while (!st.empty() && currentHeight < heights[st.top()]) {
            int height = heights[st.top()];
            st.pop();
            
            // Calculate width: if stack is empty, width is i (0 to i-1)
            // Otherwise, width is from (stack.top() + 1) to (i - 1)
            int width = st.empty() ? i : (i - st.top() - 1);
            
            maxArea = max(maxArea, height * width);
        }
        
        st.push(i);
    }
    
    return maxArea;
}


// Question 7 :- Leetcode 85.
// Version for integer matrix
int maximalRectangle(vector<vector<int>>& matrix) {
    int n = matrix.size();
    int m = matrix[0].size();

    // Initialize array with size m
    vector<int> arr(m);
    
    // Initialize first row - copy integer values directly
    for(int i = 0; i < m; i++){
        arr[i] = matrix[0][i];
    }

    int maxi = largestRectangleArea2(arr);

    for(int i = 1; i < n; i++){
        for(int j = 0; j < m; j++){
            // Compare with integer 0
            if(matrix[i][j] == 0){
                arr[j] = 0;
            }else{
                arr[j] = arr[j] + matrix[i][j];  // Add the integer value
            }
        }

        maxi = max(maxi, largestRectangleArea2(arr));
    }
    
    return maxi;
}


// Questio 8 :- Leetcode 42 (Trapping the rain water)
// Approach 1 :----- water[i] = min(maxL, maxR) - arr[i];
int trap(vector<int>& height) {
    // Aaditya verma
    int size = height.size();

    vector<int> mxl(size);
    vector<int> mxr(size);

    mxl[0] = height[0];
    for(int i = 1; i < size; i++){
        mxl[i] = max(mxl[i-1], height[i]);
    }

    mxr[size-1] = height[size - 1];
    for(int i = size-2; i >= 0; i--){
        mxr[i] = max(mxr[i+1], height[i]);
    }

    vector<int> water(size);
    for(int i = 0; i < size; i++){
        water[i] = min(mxr[i], mxl[i]) - height[i];
    }

    return accumulate(water.begin(), water.end(), 0);
}

// Appraoch 2 : -----Using two Pointer
int trap2(vector<int>& height) {

    int left = 0, right = height.size() - 1;
    int left_max = 0, right_max = 0;
    int total_water = 0;

    while (left < right) {
        if (height[left] <= height[right]) {
            if (height[left] >= left_max){
                left_max = height[left];
            }
            else{
                total_water += left_max - height[left];
            }

            left++;
        } else {
            if (height[right] >= right_max){
                right_max = height[right];
            }
            else{
                total_water += right_max - height[right];
            }
            right--;
        }
    }

    // left_max - height[left] represents the amount of water that can be trapped above the current bar at index left.

    // Why?
    // Think about it like this:

    // left_max is the tallest wall we've seen so far on the left side.

    // height[left] is the current wall height.

    // Since height[left] is shorter than left_max, water can sit on top of it.
    // But it can't be taller than left_max — so the water trapped is:

    return total_water;
}


// Question 9 :- Minimum element in a stack at any time (with extra space)
class MinStack {
    private:
        stack<int> st;
        stack<int> ss; // Auxiliary stack to keep track of minimums
    
    public:
        // Push operation
        void push(int a) {
            st.push(a);
            if (ss.empty() || ss.top() >= a) {
                ss.push(a);
            }
        }
    
        // Pop operation
        int pop() {
            if (st.empty()) return -1;
    
            int ans = st.top();
            st.pop();
            if (ss.top() == ans) {
                ss.pop();
            }
            return ans;
        }
    
        // Get minimum element
        int getMin() {
            if (ss.empty()) return -1;
            return ss.top();
        }
    
        // Optional: check if the stack is empty
        bool empty() {
            return st.empty();
        }
};


// Question 10 :-
// Minimum element in a stack at any time (without extra space)
class MinStack2 {
    private:
        stack<int> st;
        int minElement;
    
    public:
        // Get the current minimum element
        int getMin() {
            if (st.empty()) return -1;
            return minElement;
        }
    
        // Push operation
        void push(int a) {
            if (st.empty()) {
                st.push(a);
                minElement = a;
            } else {
                if (a >= minElement) {
                    st.push(a);
                } else {
                    // Push encoded value
                    st.push(2 * a - minElement);
                    minElement = a;
                }
            }
        }
    
        // Pop operation
        void pop() {
            if (st.empty()) return;
    
            if (st.top() >= minElement) {
                st.pop();
            } else {
                // Decoding the previous minElement
                minElement = 2 * minElement - st.top();
                st.pop();
            }
        }
    
        // Top operation
        int top() {
            if (st.empty()) return -1;
    
            if (st.top() >= minElement) {
                return st.top();
            } else {
                // The real top is the current minElement
                return minElement;
            }
        }
};


int main(){

    
    // Quesrion 1:-
    // vector<int> ans = nextGreaterRight({1,3,2,4});
    // for(int i = 0; i < ans.size(); i++){
    //     cout << ans[i] << " ";
    // }

    // Question 2:-
    // vector<int> ans = nextGreaterLeft({4,3,1,6,3});
    // for(int i = 0; i < ans.size(); i++){
    //     cout << ans[i] << " ";
    // }

    // Question 3:-
    // vector<int> ans = nextGreaterLeft({4,3,1,6,3});
    // for(int i = 0; i < ans.size(); i++){
    //     cout << ans[i] << " ";
    // }

    // Question 4:- 
    // vector<int> ans = nextSmallestRight({4, 5, 2, 10, 8});
    // for(int i = 0; i < ans.size(); i++){
    //     cout << ans[i] << " ";
    // }

    // Question 5 :-
    // vector<int> arr = {100, 80, 60, 70, 60, 75, 85};
    // vector<int> span = calculateSpan2(arr);
    // for(int i = 0; i < span.size(); i++){
    //     cout << span[i] << " ";
    // }

    // Question 6 :-
    // vector<int> heights = {2, 1, 5, 6, 2, 3};
    // int ans = largestRectangleArea(heights);
    // cout << ans;



    // Question 9 :-
    // MinStack ms;
    // ms.push(5);
    // ms.push(2);
    // ms.push(2);
    // ms.push(1);
    // ms.push(3);
    // cout << "Min: " << ms.getMin() << endl; // 1
    // ms.pop(); // pops 3
    // ms.pop(); // pops 1
    // cout << "Min after popping: " << ms.getMin() << endl; // 2


    // Question 10 :-
    // MinStack ms;
    // ms.push(5);   // minElement = 5
    // ms.push(3);   // pushes encoded(3), minElement = 3
    // ms.push(7);   // normal push
    // ms.getMin();  // returns 3
    // ms.pop();     // pops 7
    // ms.getMin();  // still 3
    // ms.pop();     // pops encoded(3), minElement becomes 5
    // ms.getMin();  // returns 5

}