#include <iostream>
#include <queue>
using namespace std;

class Node{
    public:
        int data;
        Node *left;
        Node *right;
        // Direct Initialization (Member Initializer List)
        Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

Node* createTree(){
    int data;
    // data enter karo
    cin >> data;

    // agr data = -1 hai toh aage ki call nahi jaayegi
    if(data == -1){
        return NULL;
    }

    // agr data != -1 hai toh node ka memory assign karo
    Node* root = new Node(data);

    // uske baad node ke left and right ko call kar do
    root->left = createTree();
    root->right = createTree();
    
    return root;
}


void levelOrderTraversal(Node* root) {
    if (root == NULL) {
        return; // Handle empty tree case
    }
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



int searchInOrder(int arr[], int s, int ele){
    for (int i = 0; i < s; i++){
        if(arr[i] == ele){
            return i;
        }
    }
    return -1;
}



Node* constructTreeFromPreAndInorderTraversal(int inOrder[], int preOrder[], int size, int &preOrderIndex, int inOrderStart, int inOrderEnd){
    // Base case
    if(preOrderIndex >= size || inOrderStart > inOrderEnd) return nullptr;

    // 1 case mai solve karunga
    // PreOrder ka jo 1st Index hai uske liye Node create karr do
    int element = preOrder[preOrderIndex];
    preOrderIndex++;

    Node *root = new Node(element);

    // Now is node ke Left and right me kya lagana hai ye dekhna hai (voh milega Inorder ke andr)
    // Search the Node in Inorder
    int position = searchInOrder(inOrder, size, element);
    // Now position mill gayi so ab uss index ke left side ke saare elements ab left node me lagenge and same for right
    // Baaki recursion Samhaal lega
    root->left = constructTreeFromPreAndInorderTraversal(inOrder, preOrder, size, preOrderIndex, inOrderStart, position - 1);
    root->right = constructTreeFromPreAndInorderTraversal(inOrder, preOrder, size, preOrderIndex, position + 1, inOrderEnd);

    return root;
}


Node* constructTreeFromPostAndInorderTraversal(int inorder[], int postOrder[], int size, int &postIndex, int inorderStart, int inorderEnd){
     // Base case
    if(postIndex < 0|| inorderStart > inorderEnd) return nullptr;

    // 1 case mai solve karunga
    int element = postOrder[postIndex];
    postIndex--;
    Node *root = new Node(element);
    // search karo in inorder
    int position = searchInOrder(inorder, size, element);


    // baaki recursion samhaal lega
    // right ki call pehle lagegi (LRN) N ke baad R process hota hai
    root->right = constructTreeFromPostAndInorderTraversal(inorder, postOrder, size, postIndex, position+1, inorderEnd);
    root->left = constructTreeFromPostAndInorderTraversal(inorder, postOrder, size, postIndex, inorderStart, position-1);

    return root;
}



int main(){
    // From inOrder and preOrder
    // int inOrder[] = {10, 8, 6, 2, 4, 12};
    // int preOrder[] = {2, 8, 10, 6, 4, 12};
    // int size = 6;
    // int preOrderIndex = 0;
    // int inOrderStart = 0;
    // int inOrderEnd = 5;
    // Node* rootAns = constructTreeFromPreAndInorderTraversal(inOrder, preOrder, size, preOrderIndex, inOrderStart, inOrderEnd);
    // levelOrderTraversal(rootAns);


    // From postOrder and inOrder
    int inorder[] = {8, 14, 6, 2, 10, 4};
    int postOrder[] = {8, 6, 14, 4, 10, 2};
    int size = 6;
    int postIndex = size - 1;
    int inorderStart = 0;
    int inorderEnd = size - 1;
    Node* rootAns = constructTreeFromPostAndInorderTraversal(inorder, postOrder, size, postIndex, inorderStart, inorderEnd);
    levelOrderTraversal(rootAns);

}
