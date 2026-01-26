#include <iostream>
#include <unordered_set>

using namespace std;

/*
Recursion    -> choices + decision       -> answer is usually in the leaf node
DP           -> Optimization Problems   -> answer is in the root node or (last box of mem table)

Backtracking -> - Controled recursion + some constraints + pass by refrance
                - Control recursion means eliminating some branches
                - Used when you have multiple solutions and you want all those solutions (where asked about all the combinations)
                - The solution is all the PATHS of the state space tree.
                - We implement a "Bounding function" to implement a condition to satisfy the constraints.
                - The constrained applied to find the solution is called Bounding function.
                - Backtracking follows Depth-First Search method.
                - Branch and Bound is also a Brute Force approach, which uses Breadth-First Search method.


Tips :  - In backtraking question the no. of choices is larger than recursion + variable choices can be there
        - The time coplexity is higher in these approaches, like 2^n , n^d , n! , so the constraint (n) would be mostly
          a single digit number so to satisfy the constraints
          so agr single digit dikh toh backtracking ki possiblity ka socho 
        - Kabhi kabhi backtracking ke questions greddy se bhi ho jaate hai
*/

// In pass by Value -> the backtracking step is redundant (see Aadiya verma 2nd vedio for best explanation)
// We can do the backtracking questions without it using pass by value only
// But in pass by value each sub call generates its seperate function calls. Which takes a lot of memory
// that's why we add "pass by refrance" and thats why we have to backtrack to make the changes to the root node backtrack

/*
Posibilty of backtraking Problems :-
        1) Choices + decisions
        2) All combinations
        3) Controlled Recursions
        4) Number of choices
        5) Size of Constraints
        6) Don't be greedy
*/




// Question 1 :- All the permutation of strings, Given a string (no duplicate characters) store all the permutations of that string
//               in a vector and return it.
void permute(string input, string output, vector<string> &ans){
	if(input.size() == 0){
		ans.push_back(output);
		return;
	}

	for(int i = 0; i < input.size(); i++){
		string newInput = input.substr(0, i) + input.substr(i+1);
		string newOutput = output + input[i];
		permute(newInput, newOutput, ans);
	}
}
// Appraoch 2 :- If there are duplicates in the output string
void permute2(string input, string output, vector<string> &ans){
	if(input.size() == 0){
		ans.push_back(output);
		return;
	}

	unordered_set<char> mp;

	for(int i = 0; i < input.size(); i++){
		if (mp.find(input[i]) == mp.end()) {
			mp.insert(input[i]);
			string newInput = input.substr(0, i) + input.substr(i+1);
			string newOutput = output + input[i];
			permute2(newInput, newOutput, ans);
		}
	}
}

// Appraoch 3 :- Using Backtracking
// Intution :- instead of generating new string each time we can just do it in place using swap
// (this is where backtracking comes in picture)
void recurPermute(int start, string &s, vector<string> &ans) {
	if (start == s.size()) {
		ans.push_back(s);
		return;
	}

	unordered_set<char> used; // track chars used at this level
	for (int i = start; i < s.size(); i++) {
		if (used.count(s[i])) continue; // skip duplicate char for this index
		used.insert(s[i]);              // if not present then add the char in the set

		swap(s[start], s[i]);
		recurPermute(start + 1, s, ans);
		// backtrack
		swap(s[start], s[i]);
	}
}




// Question 2 :- Largest number in K swaps (it can be done using greedy, only if there is no duplicate)
string largestNumberWithKSwaps(string num, int k) {
    int n = num.size();

    for (int i = 0; i < n && k > 0; i++) {
        // Find position of the largest digit from i to end
        int maxPos = i;
        for (int j = n - 1; j > i; j--) {
            if (num[j] > num[maxPos]) {
                maxPos = j;
            }
        }
        // If we found a bigger digit, swap
        if (maxPos != i) {
            swap(num[i], num[maxPos]);
            k--;
        }
    }
    return num;
}

//Appraoch 2 :- using Backtracking
void solve(string &s, int k, string &res, int start) {
    if (k == 0 || start == s.size() - 1) {
        return;
    }

    char maxDigit = *max_element(s.begin() + start + 1, s.end());  // start index should not be included that's why start + 1

    // If the current digit is already the largest in the remaining substring, skip
	// for case like s = 7321
    if (maxDigit <= s[start]) {
        solve(s, k, res, start + 1);  // k would not be used
        return;
    }

    for (int i = start + 1; i < s.size(); i++) {
        if (s[i] == maxDigit) {
            swap(s[start], s[i]);

			// we can get the answer at any node (not necesaaty at leaf node), so we compare and save at every node
            if (s.compare(res) > 0) { // lexicographical ordering
                res = s;
            }

            solve(s, k - 1, res, start + 1);

            swap(s[start], s[i]); // backtrack
        }
    }
}




/*Question 3 :- Problem Statement

You are given a positive integer n.
Return a vector containing all n-digit integers whose digits are in strictly increasing order from left to right.
	1) Digits must be unique and in ascending sequence.
	2) The number cannot have leading zeros.
	3) Example: for n = 3, valid numbers include 123, 145, 789, but invalid numbers include 112 (repeated digit) and 321 (not increasing).

Example 1
Input:  n = 2  
Output: [12, 13, 14, 15, 16, 17, 18, 19,  
         23, 24, 25, 26, 27, 28, 29,  
         34, 35, 36, 37, 38, 39,  
         45, 46, 47, 48, 49,  
         56, 57, 58, 59,  
         67, 68, 69,  
         78, 79,  
         89]

Example 2
Input:  n = 1  
Output: [1, 2, 3, 4, 5, 6, 7, 8, 9]

Constraints :-
	1 <= n <= 9
	Output numbers must have exactly n digits.
	Digits are taken from 1 to 9 without repetition, in strictly increasing order.
*/
class Question3 {
	public:
		void solve(int n, vector<int> &temp, vector<int> &ans){
			// Base case: we formed a number with n digits
			if (n == 0) {
				int num = 0;
				for (int digit : temp) {
					num = num * 10 + digit;
				}
				ans.push_back(num);
				return;
			}
	
			for(int i = 1; i <= 9; i++){
				// to eliminate the redundant nodes Only allow strictly increasing digits... just consider those which are larger than the current one
				if (temp.empty() || i > temp.back()) {  // if the number is 45...then after 5 we can only take 6,7....9
					// agr vector me kuch bhi nahi hai toh last element se farak nahi padtta kuch bhi daal do
					temp.push_back(i);
					solve(n-1, temp, ans);
					// backtrack
					temp.pop_back();
				}
			}
		}
	
		vector<int> nDigitNumbers(int n){
			vector<int> ans;
	
			if(n == 1){
				for(int i = 0; i <= 9; i++){
					ans.emplace_back(i);
					return ans;
				}
			}
	
			// else bigger number, then first digit can not be 0
			vector<int> temp;
			solve(n, temp, ans);
			return ans;
		}
	};




// Question 4 :- Rat in maze
class Solution {
    public:
        void solve(vector<vector<int>>& maze, int n, int x, int y, string &path, vector<string> &ans) {
            // Base case: destination reached
            if (x == n-1 && y == n-1) {
                ans.push_back(path);
                return;
            }
    
            // Mark current cell as visited
            maze[x][y] = 0;
    
            // Directions in lexicographic order: D, L, R, U
            // Down
            if (x+1 < n && maze[x+1][y] == 1) {
                path.push_back('D');
                solve(maze, n, x+1, y, path, ans);
                path.pop_back();
            }
            // Left
            if (y-1 >= 0 && maze[x][y-1] == 1) {
                path.push_back('L');
                solve(maze, n, x, y-1, path, ans);
                path.pop_back();
            }
            // Right
            if (y+1 < n && maze[x][y+1] == 1) {
                path.push_back('R');
                solve(maze, n, x, y+1, path, ans);
                path.pop_back();
            }
            // Up
            if (x-1 >= 0 && maze[x-1][y] == 1) {
                path.push_back('U');
                solve(maze, n, x-1, y, path, ans);
                path.pop_back();
            }
    
            // Unmark cell for other paths
            maze[x][y] = 1;
        }
  
        vector<string> ratInMaze(vector<vector<int>>& maze) {
            int n = maze.size();
            vector<string> ans;
            string path = "";
  
            if (maze[0][0] == 0 || maze[n-1][n-1] == 0){
                return ans; // No path possible
            }
  
            solve(maze, n, 0, 0, path, ans);
  
            return ans;
      }
};

// Appraoch 2 :- Aaditya verma
class Solution2 {
public:

    struct Choice {
        char dname; // Direction name
        int dx, dy;
    };

    bool isSolved(int x, int y, int n) {
        return x == n - 1 && y == n - 1;
    }

    bool isValid(int x, int y, int n, const vector<vector<int>> &arr) {
        return x >= 0 && x < n && y >= 0 && y < n && arr[x][y] == 1;
    }

    void solve(int x, int y, const int n, vector<string> &res, string &path, vector<vector<int>> &arr, const vector<Choice> &choices) {

        if (isSolved(x, y, n)) {
            res.push_back(path);
            return;
        }

        for (const auto &choice : choices) {
            int newX = x + choice.dx;
            int newY = y + choice.dy;

            if (isValid(newX, newY, n, arr)) {
                // Mark the current cell as visited
                arr[x][y] = 0;
                path.push_back(choice.dname);

                solve(newX, newY, n, res, path, arr, choices);

                // Restore original state
                arr[x][y] = 1;
                path.pop_back();
            }
        }
    }

    vector<string> findPath(vector<vector<int>> &arr, int n) {
        vector<string> res;
        string path;

        if (arr[0][0] == 0 || arr[n - 1][n - 1] == 0) return res;

        // Directions in lexicographic order
        vector<Choice> choices = {
            {'D', 1, 0},   // Down
            {'L', 0, -1},  // Left
            {'R', 0, 1},   // Right
            {'U', -1, 0}   // Up
        };

        solve(0, 0, n, res, path, arr, choices);
        return res;
    }
};




// Question 5 :- Palindrome partitioning (Leetcode 131)
class Solution3 {
    public:
        vector<vector<string>> ans;
    
        bool isPlaindrome(string &str){
            int i = 0, j = str.size()-1;
    
            while(i < j){
                if(str[i] != str[j]){
                    return false;
                }
                i++;
                j--;
            }
            return true;
        }
    
        void helper(string &s, vector<string> &temp, int index){
            if(index == s.size()){
                ans.push_back(temp);
                return;
            }
    
            string pal_string;
            for(int i = index; i < s.size(); i++){
                pal_string += s[i];
                if(isPlaindrome(pal_string)){  // if the intial partition is palindrome then only you have to explore further path
                    temp.push_back(pal_string);
                    helper(s, temp, i+1);
                    // backtracking
                    temp.pop_back();
                }
            }
        }
    
        vector<vector<string>> partition(string s) {
            vector<string> temp;
            helper(s, temp, 0);
            return ans;
        }
    };

// Appraoch 2 :- Using MCM (Do after Aaditya verma's MCM)
class Solution4 {
    public:
        void solve(string &s, vector<vector<string>> &ans, vector<string> &temp,
                   int i, int j, vector<vector<bool>> &isPal) {
            if (i > j) {
                ans.push_back(temp);
                return;
            }
            for (int k = i; k <= j; k++) {
                if (isPal[i][k]) {
                    temp.push_back(s.substr(i, k - i + 1));
                    solve(s, ans, temp, k + 1, j, isPal);
                    temp.pop_back();
                }
            }
        }
    
        vector<vector<string>> partition(string s) {
            int n = s.size();
            vector<vector<bool>> isPal(n, vector<bool>(n, false));
    
            for (int len = 1; len <= n; len++) {
                for (int i = 0; i <= n - len; i++) {
                    int j = i + len - 1;
                    if (len == 1) {
                        isPal[i][j] = true;
                    } else if (len == 2) {
                        isPal[i][j] = (s[i] == s[j]);
                    } else if (s[i] == s[j]) {
                        isPal[i][j] = isPal[i + 1][j - 1];
                    }
                }
            }
    
            vector<vector<string>> ans;
            vector<string> temp;
            solve(s, ans, temp, 0, n - 1, isPal);
            return ans;
        }
    };




// Question 6 :- Word break same as Question 5 solution3 (leetcode 139)
class Solution5 {
    public:
    
        bool isPresent(string &temp, vector<string> &wordDict) {
            return find(wordDict.begin(), wordDict.end(), temp) != wordDict.end();
        }
        
        void solve(string &s, vector<string> &wordDict, int index, bool &ans) {
            // index aahkri me jab hi jayega jab partition ho chuka hogga (see solve function)
            if (index == s.size()) {
                ans = true;
                return;
            }
            
            string temp = "";
            for (int i = index; i < s.size(); i++) {
                temp += s[i];
                if (isPresent(temp, wordDict)) {
                    solve(s, wordDict, i + 1, ans);
                    if (ans) return; // Early stop if found
                }
            }
        }
    
        bool wordBreak(string s, vector<string>& wordDict) {
            bool flag = false;
            solve(s, wordDict, 0, flag);
            return flag;
        }
};




// Question 7 :- Letter combination of a phone number (Leetcode 17)
class Solution6 {
    public:
    
        vector<string> result;
    
        void solve(int idx, string &digits, string &temp, unordered_map<char, string> &mp){
            if(idx == digits.size()){
                result.push_back(temp);
                return;
            }
    
            char ch = digits[idx];
            string str = mp[ch];
    
            for(int i = 0; i < str.size(); i++){
                temp += str[i];
                // note :- idx + 1 not "i+1" (see codeStroyWithMIK)
                solve(idx + 1, digits, temp, mp);
                // backtrack
                temp.pop_back();
            }
        }
    
        vector<string> letterCombinations(string digits) {
            if(digits.length() == 0){
                return {};
            }
    
            unordered_map<char, string> mp;
    
            mp['2'] = "abc";
            mp['3'] = "def";
            mp['4'] = "ghi";
            mp['5'] = "jkl";
            mp['6'] = "mno";
            mp['7'] = "pqrs";
            mp['8'] = "tuv";
            mp['9'] = "wxyz";
    
            string temp = "";
            solve(0, digits, temp, mp);
    
            return result;
        }
    };




// Question 8 :- N queens (code stroy with MIK)
class Solution7 {
    public:
        // remember ham upr(0th row) se start karr rahe hai and harr col me ek ek baar pehla queen rakh rahe hai
        // then usske hisaab se check karr rahe hai ki baaki rakh sakte hai ki nahi
        // this is why we ar only checking the validity for upwards , not downwards
        vector<vector<string>> ans;
        int N;
    
        bool isValid(vector<string> &board, int row, int col){
            // dekho ki kya upr koi queen toh nahi
            for(int i = row-1; i >= 0; i--){
                if(board[i][col] == 'Q'){
                    return false;
                }
            }
            // left-upward digonal toh nahi
            for(int i = row-1, j = col-1; i >= 0 && j >=0; i--, j--){
                if(board[i][j] == 'Q'){
                    return false;
                }
            }
            // right-upward digonal toh nahi
            for(int i = row-1, j = col+1; i >= 0 && j < N; i--, j++){
                if(board[i][j] == 'Q'){
                    return false;
                }
            }
            return true;
        }
    
        void solve(vector<string> &board, int row){
            // base case
            if(row >= N){
                ans.push_back(board);
                return;
            }
            for(int col = 0; col < N; col++){
    
                if(isValid(board, row, col)){
                    // row = row ke harr col me rakh ke check karr rahe hai that's why col is iterating (row is iterating using recursion)
                    board[row][col] = 'Q';      // maan lo hamne ek row me ek queen rakh diya
                    solve(board, row + 1);      // ab dekho ki agle row me kaha rakh sakte ho
                    // backtrack
                    board[row][col] = '.';
                }
    
            }
        }
    
        vector<vector<string>> solveNQueens(int n) {
            N = n;
            vector<string> board(n, string(n, '.'));
    
            solve(board, 0);
    
            return ans;
        }
    };

//Approach-2
/*
Approach 1 me har baar board scan karke check karte the ki Queen safe hai ya nahi.
Ye kaam O(N) time lagta tha, kyunki har baar column aur diagonals traverse karne padte the.

Approach 2 me humne 3 unordered_set use kiye:
    cols       -> track kare kaunsa column occupied hai
    diags      -> (row - col) se track kare kaunsa main diagonal occupied hai
    antiDiags  -> (row + col) se track kare kaunsa anti-diagonal occupied hai

Property: 
    - Same column => same col index
    - Same main diagonal => (row - col) same hota hai
    - Same anti-diagonal => (row + col) same hota hai

In sets me lookup O(1) hota hai, isliye har placement check fast ho gaya.
Board scan ki zarurat nahi padti, directly check karke place/remove karte hain.

Result: Time complexity me improvement kyunki har step pe O(N) scan remove ho gaya.
*/
//T.C : O(N!) in worst case it explores all possible configurations
//S.C : O(N) for result and also for storing, cols, diags and antidiags
class Solution8 {
    public:
        vector<vector<string>> result;
        void solve(vector<string>& board, int row, unordered_set<int>& cols, unordered_set<int>& diags, unordered_set<int>& antiDiags) {
            if(row == board.size()) {
                result.push_back(board);
                return;
            }
            
            /*
                For a square (i, j) :
                Diagonally (i-j)      is constant
                Anti diagonally (i+j) is constant
                
                We can use this to find which square(i, j)
                has a risk of being attacked by another queen
                placed already in 'diagonal', or 'anti-diagonal'
                or 'column'
            */
            
            for(int col = 0; col<board.size(); col++) {
                int diag_id       = row-col;
                int anti_diag_id  = row+col;
                
                /*
                    If the col, or diagonal or anti_diaonal
                    are used, means one of them has a Queen placed
                    already which can attack, so look for other column
                */
                if(cols.find(col) != cols.end() ||
                  diags.find(diag_id) != diags.end() ||
                  antiDiags.find(anti_diag_id) != antiDiags.end())
                    continue;
                
                cols.insert(col);
                diags.insert(diag_id);
                antiDiags.insert(anti_diag_id);
                board[row][col] = 'Q';
                
                
                solve(board, row+1, cols, diags, antiDiags);
    
                cols.erase(col);
                diags.erase(diag_id);
                antiDiags.erase(anti_diag_id);
                board[row][col] = '.';
            }
        }
        vector<vector<string>> solveNQueens(int n) {
            if(n == 0)
                return {};
            vector<string> board(n, string(n, '.')); 
            //For, n = 3, board = {"...", "...", "..."} initially
            
            int start_row = 0;
            unordered_set<int> cols;
            unordered_set<int> diags;
            unordered_set<int> antiDiags;
            solve(board, start_row, cols, diags, antiDiags);
            
            return result;
        }
    };




// Question 9 :- Sudoku Solver (Leetcode 37)
class Solution {
    public:
        int N;
        // Khud se bina kisi help ke kiya BenStokes
    
        bool canPlace(vector<vector<char>>& board, int row, int col, char num) {
            // Check row
            for (int j = 0; j < N; j++) {
                if (board[row][j] == num) return false;
            }
    
            // Check column
            for (int i = 0; i < N; i++) {
                if (board[i][col] == num) return false;
            }
    
            // Check 3x3 subgrid
            int startRow = (row / 3) * 3;
            int startCol = (col / 3) * 3;
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    if (board[startRow + i][startCol + j] == num) return false;
                }
            }
    
            return true;
        }
    
        bool solve(vector<vector<char>>& board, int row, int col) {
            // Base cases
            // If we reached end row, sudoku is solved
            if (row == N) return true;
            // Move to next row if end of column is reached
            if (col == N) return solve(board, row + 1, 0);
    
    
            // Skip cells filled with numbers by going on next col (col + 1)
            if (board[row][col] != '.') {
                return solve(board, row, col + 1);
            }
    
            // dekho ko 1 se 9 takk me koun sa number rakh sakte ho
            for (char num = '1'; num <= '9'; num++) {
                if (canPlace(board, row, col, num)) {
                    board[row][col] = num;   // if wecan place..then place it
    
                    if (solve(board, row, col + 1)){
                        // check if we can solve the puzzle
                        // after palcing that number or not
                        return true;  // if we can solve then return true;
                    }
                    // if we cann't solve by palcing that number, then backtrack
                    // and see by placing another number
                    // Backtrack
                    board[row][col] = '.';
                }
            }
    
            return false; // No valid number found
        }
    
        void solveSudoku(vector<vector<char>>& board) {
            N = board.size();
            solve(board, 0, 0);
        }
    };
    
    


// Question 10 :- Word Search (Leetcode 79)
class Solution {
    public:
        int M, N;
        
        bool find(vector<vector<char>>& board, string& word, int idx, int row, int col) {
            // base case: pura word match ho gaya
            if (idx == word.size()) return true;
    
            // out of bounds ya mismatch
            if (row < 0 || row >= M || col < 0 || col >= N || board[row][col] != word[idx]) {
                return false;
            }
    
            // mark visited
            char temp = board[row][col];
            board[row][col] = '#';
    
            // 4 directions explore
            bool found = find(board, word, idx+1, row+1, col) || // niche vale box me
                         find(board, word, idx+1, row-1, col) || // upr vaale box me
                         find(board, word, idx+1, row, col+1) || // agle box me
                         find(board, word, idx+1, row, col-1);   // pichle box me
    
            // backtrack (undo mark)
            board[row][col] = temp;
            return found;
        }
    
        bool exist(vector<vector<char>>& board, string word) {
            M = board.size();
            N = board[0].size();
    
            for (int i = 0; i < M; i++) {
                for (int j = 0; j < N; j++) {
                    // word ka pehla char dhundho....and jasie hi voh i,j me mill jaye ab vaha
                    // se baaki ke next characters dhundho
                    if (board[i][j] == word[0] && find(board, word, 0, i, j)) {
                        return true;
                    }
                }
            }
            return false;
        }
    };



    

int main(){
	// Question 1 :-
	// string s = "abc";
    // vector<string> ans;
    // permute2(s, "", ans);
    // for (auto &p : ans) {
    //     cout << p << "\n";
    // }




	// Question 2 :-
	// string num = "2736";
    // int k = 1;
    // cout << largestNumberWithKSwaps(num, k) << endl; // Output: 7236




	// Queston 3 :-
	// Question3 obj;
    // int n = 2;
    // vector<int> res = obj.nDigitNumbers(n);

    // for (int num : res) {
    //     cout << num << " ";
    // }
    // cout << endl;




    // Question 4 :-
    // vector<vector<int>> maze = {
    //     {1, 0, 0, 0},
    //     {1, 1, 0, 1},
    //     {1, 1, 0, 0},
    //     {0, 1, 1, 1}
    // };

    // Solution obj;
    // vector<string> paths = obj.ratInMaze(maze);

    // if (paths.empty()) {
    //     cout << "No path found\n";
    // } else {
    //     for (auto &p : paths) {
    //         cout << p << "\n";
    //     }
    // }



    
    // Question 5 :- 
    // Solution3 sol;
    // string s = "aab";
    // vector<vector<string>> res = sol.partition(s);

    // for (auto &vec : res) {
    //     for (auto &str : vec) {
    //         cout << str << " ";
    //     }
    //     cout << "\n";
    // }


    // Question 6 :-

}