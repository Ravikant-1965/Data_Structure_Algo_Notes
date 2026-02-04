#include <iostream>
#include <stack>
#include <queue>
using namespace std;

class Node{
  public:
	int data;
	Node* left;
	Node* right;

	Node(int val) {
	  this->data = val;
	  this->left = NULL;
	  this->right = NULL;
	}
};
/*
class Node{
    public:
        int data;
        Node *left;
        Node *right;
        // Direct Initialization (Member Initializer List)
        Node(int val) : data(val), left(nullptr), right(nullptr) {}
};
*/

//it returns a pointer to root node of the created tree
Node* createTree() {
	cout << "enter the value for Node: " << endl;
	int data;
	cin >> data;

	if(data == -1) {
		return NULL;
	}
	//Step1: create Node
	Node* root = new Node(data);

	//Step2: Create left subtree
	cout << "Value for left of : " << root->data << "(-1 for no Value)" << endl;
	root->left = createTree();

	//Step3: Craete right subtree
	cout << "Value for right of : " << root->data << "(-1 for no Value)" << endl;
	root->right = createTree();

	return root;
}



// pre Order Traversal Using Recursion
void preOrderTraversal(Node* root) {
	//base case
	if(root == NULL) {
		return;
	}
	// N L R
	//N
	cout << root->data << " ";
	// L
	preOrderTraversal(root->left);
	// R
	preOrderTraversal(root->right);
}

// Iterartive PreOrder using Stack (Striver)
vector<int> preorderTraversal(Node* root){
    // Initialize vector to store
    // the preorder traversal result
    vector<int> preorder;

    if(root == nullptr) {
        return preorder;
    }

    stack<Node*> st;
    // Push the root node
    // onto the stack
    st.push(root);
        
    // Perform iterative preorder traversal
    while(!st.empty()) {
        // Get the current node
        // from the top of the stack
        root = st.top();
        // Remove the node
        // from the stack
        st.pop();
        // Add the node's value to
        // the preorder traversal result
        preorder.push_back(root->data);
        // Push the right child
        // onto the stack if exists
        if(root->right != nullptr) {
            st.push(root->right);
        }
        // Push the left child onto
        // the stack if exists
        if(root->left != nullptr) {
            st.push(root->left);
        }
    }
    // Return the preorder
    // traversal result
    return preorder;
}
// Iterartive PreOrder using Stack (2)
void preorderIterative(Node* root) {
    if (root == nullptr) return;
    
    stack<Node*> s;
    s.push(root);
    
    while (!s.empty()) {
        Node* curr = s.top();
        s.pop();
        cout << curr->data << " ";
        
        // Push right first, then left (stack is LIFO)
        if (curr->right) s.push(curr->right);
        if (curr->left) s.push(curr->left);
    }
}



// in Order Traversal Recursion
void inorderTraversal(Node* root) {
	//LNR
	//base case
	if(root == NULL) {
		return;
	}
	//L
	inorderTraversal(root->left);
	// N
	cout << root->data << " ";
	// R
	inorderTraversal(root->right);
}

// Iterartive InOrder using Stack (Striver)
vector<int> inOrderTraversal(Node *root){
    Node *curr = root;
    stack<Node *> s;

    vector<int> ans;
    while(true){
        if(curr != NULL){
            s.push(curr);
            curr = curr->left;
        }
        else{
            if(s.empty())  break;
            curr = s.top();
            s.pop();
            ans.push_back(curr->data);
            curr = curr->right;
        }
    }
    return ans;
}
// Iterative Inorder Using Stack (2)
void inorderIterative(Node* root) {
    if (root == nullptr) return;
    
    stack<Node*> s;
    Node* curr = root;
    
    while (curr != nullptr || !s.empty()) {
        // Go to leftmost node
        while (curr != nullptr) {
            s.push(curr);
            curr = curr->left;
        }
        
        // Process current node
        curr = s.top();
        s.pop();
        cout << curr->data << " ";
        
        // Move to right subtree
        curr = curr->right;
    }
}



// post Order Traversal Using Recursion
void postOrderTraversal(Node* root) {
	//LRN
	//base case
	if(root == NULL) {
		return;
	}
	//L
	postOrderTraversal(root->left);
	//R
	postOrderTraversal(root->right);
	//N
	cout << root->data << " ";
}

// Post-order Traversal of Binary Tree using 2 stack (Striver)
vector<int> postorderTraversal(Node* root) {
    vector<int> post;
    if (!root) return post;
    
    stack<Node*> s1, s2;
    s1.push(root);
    
    // Process all nodes
    while (!s1.empty()) {
        Node* node = s1.top(); 
        s1.pop();
        s2.push(node);
        
        // Push left first so that right is processed before left
        if (node->left)  s1.push(node->left);
        if (node->right) s1.push(node->right);
    }
    
    // Collect post-order from second stack
    while (!s2.empty()) {
        post.push_back(s2.top()->data);
        s2.pop();
    }
    
    return post;
}

// Iterative Post-order traversal using 1 stack only (Striver)
vector<int> postorderTraversal(Node* root) {
    vector<int> post;
    stack<Node*> st;
    Node* cur = root;
    Node* temp = nullptr;

    while (cur != nullptr || !st.empty()) {
        if (cur != nullptr) {
            st.push(cur);
            cur = cur->left;
        } else {
            temp = st.top()->right;
            if (temp == nullptr) {
                temp = st.top();
                st.pop();
                post.push_back(temp->data);

                // Check if current popped node is right child of top of stack
                while (!st.empty() && temp == st.top()->right) {
                    temp = st.top();
                    st.pop();
                    post.push_back(temp->data);
                }
            } else {
                cur = temp;
            }
        }
    }

    return post;
}
// Iterative Post-order traversal using 1 stack only (2)
void postorderIterativeOneStack(Node* root) {
    if (root == nullptr) return;

    stack<Node*> s;
    Node* lastVisited = nullptr;
    Node* curr = root;

    while (!s.empty() || curr != nullptr) {
        if (curr != nullptr) {
            s.push(curr);
            curr = curr->left;
        } else {
            Node* peekNode = s.top();

            // If right child exists and hasn't been processed yet
            if (peekNode->right != nullptr && lastVisited != peekNode->right) {
                curr = peekNode->right;
            } else {
                cout << peekNode->data << " ";
                lastVisited = s.top();
                s.pop();
            }
        }
    }
}



// Function to get the Preorder, Inorder and Postorder traversal Of Binary Tree in One traversal
vector<vector<int>> preInPostTraversal(Node* root) {
    // Vectors to store traversals
    vector<int> pre, in, post;

    // If the tree is empty return empty traversals
    if (root == NULL) {
        return {};
    }

    // Stack to maintain nodes
    // and their traversal state
    stack<pair<Node*, int>> st;

    // Start with the root node
    // and state 1 (preorder)
    st.push({root, 1});

    while (!st.empty()) {
        auto it = st.top();
        st.pop();

        // this is part of pre
        if (it.second == 1) {
            // Store the node's data
            // in the preorder traversal
            pre.push_back(it.first->data);
            // Move to state 2
            // (inorder) for this node
            it.second = 2;
            // Push the updated state
            // back onto the stack
            st.push(it); 

            // Push left child onto
            // the stack for processing
            if (it.first->left != NULL) {
                st.push({it.first->left, 1});
            }
        }

        // this is a part of in
        else if (it.second == 2) {
            // Store the node's data
            // in the inorder traversal
            in.push_back(it.first->data);
            // Move to state 3
            // (postorder) for this node
            it.second = 3;
            // Push the updated state
            // back onto the stack
            st.push(it); 

            // Push right child onto
            // the stack for processing
            if (it.first->right != NULL) {
                st.push({it.first->right, 1});
            }
        }

        // this is part of post
        else {
            // Store the node's data
            // in the postorder traversal
            post.push_back(it.first->data);
        }
    }

    // Returning the traversals
    vector<vector<int>> result;
    result.push_back(pre);
    result.push_back(in);
    result.push_back(post);
    return result;
}



// Important
void levelOrderTraversal(Node* root) {
	// Initialisation of queue to maintain the order to print Level order Traversal
	queue<Node*> q;
	q.push(root);
	q.push(NULL);

	//asli traversal start krete h
	while(!q.empty()){
		Node* front = q.front();
		q.pop();

		//(agr ek level Traverse ho chuka hai iska matlab uss Level ke child nodes queue me honge)
		if(front == NULL) {  // this means ek level print/Complete ho gaya 
			cout << endl;
			if(!q.empty()) {
				q.push(NULL);
			}
		}
		else {
			//valid node wala case
			cout << front->data << " ";

			if(front->left != NULL) {
				q.push(front->left);
			}
			if(front->right != NULL) {
				q.push(front->right);
			}
		}
	}
}

class Solution {
    public:
        vector<vector<int>> levelOrder(Node* root) {
            if (!root) return {};
            vector<vector<int>> ans;
            queue<Node*> q;
            q.push(root);
    
            while (!q.empty()) {
                int n = q.size();   // because at a given time, queue me current level ke saare elements hote hai, so q.size = current level size
                vector<int> level; // store current level values
                for (int i = 0; i < n; i++) {
                    Node* node = q.front();
                    q.pop();
                    level.push_back(node->data); // store every node, not just rightmost
                    if (node->left) q.push(node->left);
                    if (node->right) q.push(node->right);
                }
                ans.push_back(level); // add full level to result
            }
            return ans;
        }
    };
    


// MaxDepth using LevelOrder method
int maxDepth(Node* root) {
	// IMP Galti
	if(root==NULL) return 0;

	queue<Node*> q;
	q.push(root);
	q.push(NULL);
	int count = 1;

	//asli traversal start krete h 
	while(!q.empty()) {
		Node* front = q.front();
		q.pop();

		if(front == NULL && !q.empty()){
			count++;
			q.push(NULL);
		}
		else {
			if(front->left != NULL) {
				q.push(front->left);
			}
			if(front->right != NULL) {
				q.push(front->right);
			}
		}
	}
	return count;
};

// MaxDepth using Recursion
int maxHeight(Node* root){
    if(root == nullptr) return 0;
    int leftHeight = maxHeight(root->left);
    int rightHeight = maxHeight(root->right);
    return max(leftHeight, rightHeight) + 1;
}

// Diameter :- Longest path possible between any 2 nodes. (doesn't need to pass through the root node)
// Using Brute Force
int diameterOfBinaryTree(Node* root) {
    if (root == NULL) return 0;

    int leftHeight = maxHeight(root->left);
    int rightHeight = maxHeight(root->right);
    int diameterThroughRoot = leftHeight + rightHeight;

    int leftDiameter = diameterOfBinaryTree(root->left);
    int rightDiameter = diameterOfBinaryTree(root->right);

    return max(diameterThroughRoot, max(leftDiameter, rightDiameter));
}
// Optimized
class Solution {
    public:
        int diameterOfBinaryTree(Node* root) {
            int diameter = 0;
            height(root, diameter);
            return diameter;
        }
    
    private:
        int height(Node* node, int& diameter) {
            if (!node) {
                return 0;
            }
    
            int lh = height(node->left, diameter);
            int rh = height(node->right, diameter);
    
            diameter = max(diameter, lh + rh);
    
            return 1 + max(lh, rh);
        }
};
    

// Function to find the path from the
// root to a given node with value 'x'
bool getPath(Node* root, vector<int>& arr, int x) {
    // Base case: If the current
    // node is null, return false
    if (!root) {
        return false;
    }

    // Add the current node's
    // value to the path vector
    arr.push_back(root->data);

    // If the current node's value is equal
    // to the target value 'x', return true
    if (root->data == x) {
        return true;
    }

    // Recursively search for the target value
    // 'x' in the left and right subtrees
    if (getPath(root->left, arr, x) || getPath(root->right, arr, x)) {
        return true;
    }

    // If the target value 'x' is not found
    // in the current path, backtrack
    arr.pop_back();
    return false;
}
vector<int> solve(Node* A, int x) {

    vector<int> arr;

    // If the root node is null,
    // return the empty path vector
    if (A == NULL) {
        return arr;
    }

    // Call the getPath function to find
    // the path to the node with value 'B'
    getPath(A, arr, x);

    // Return the path vector
    return arr;
}


int main() {

	Node* root = createTree();
	//cout << root->data << endl;
	// cout << "Printing Preorder: ";
	// preOrderTraversal(root);
	// cout << endl;

	cout << "Printing Inorder: ";
	inOrderTraversal(root);
	cout << endl;

	// cout << "Printing PostOrder: ";
	// postOrderTraversal(root);
	// cout << endl;

	// cout << "Level Order : ";
	// levelOrderTraversal(root);
	// cout << endl;

  return 0;
}
