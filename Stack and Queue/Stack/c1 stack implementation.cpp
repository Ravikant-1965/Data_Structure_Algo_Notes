#include <iostream>
#include <stack>
using namespace std;

// Implementation of stack using array
// In stack the values are accesible only by the Top variable (we have to move the top variable only)

// static
# define N 5
int stack[N];
int top = -1;

void push(){
	if(top == N-1){
		cout << "Stack Overflow";
		return;
	}

	int n;
	cout << "Enter the data to be entered : ";
	cin >> n;

	top++;
	stack[top] = n;
	return;
}

void pop(){
	if(top == -1){
		cout << "Stack Underflow";
		return;
	}
	top--;
	return;
}

void peek(){
	if(top == -1){
		cout << "stack is empty";
		return;
	}

	int data = stack[top];
	cout << "The Top element is : " << data;
}

void display(){
	if(top == -1){
		cout << "stack is empty";
		return;
	}

	for (int i = top; i>=0; i--){
		cout << stack[top];
	}
}

// Dynamic
class Stack {
	public:
		int* arr;
		int size;
		int top;

		Stack(int size) {
			arr = new int[size];
			this->size = size;
			this->top = -1;
		}

		void push(int data) {
			if(top == size-1) {
				cout << "Stack overflow" << endl;
				return;
			}
			else {
				top++;
				arr[top] = data;
			}
		}

		void pop() {
			if(top == -1) {
			cout << "Stack underflow" << endl;
			return;
			}
			else {
				top--;
			}
		}

		bool isEmpty() {
			if(top == -1) {
				return true;
			}
			else {
				return false;
			}
		}

		int getTop() {
			if(top == -1) {
				cout << "Stack is empty" << endl;
				return -1;
			}
			else {
				return arr[top];
			}   
		}

		int getSize() {
			return top+1;
		}

		void print() {
			cout << "Top:  " << top << endl;
			cout << "Top element: " << getTop() << endl; 
			cout << "Stack: ";
			for(int i=0; i<getSize(); i++) {
				cout << arr[i] << " ";
			}  cout << endl << endl;
		}
};





// Implementation of stack using Linked List
struct stackL_node {
    int data;
    struct stackL_node *next;

	stackL_node(int data){
		this->data = data;
		this->next = nullptr;
	}
};

struct stackL_node *Top = NULL;

void push_L() {
    int value;
    cout << "Enter the data to be entered: ";
    cin >> value;

    struct stackL_node *newNode = new stackL_node(value);
    newNode->data = value;
    newNode->next = Top;
    Top = newNode;
    cout << "Pushed " << value << " onto the stack.\n";
}

void pop_L() {
    if (Top == NULL) {
        cout << "Stack underflow\n";
        return;
    }
    struct stackL_node *temp = Top;
    Top = Top->next;
    cout << "Popped " << temp->data << " from the stack.\n";
    delete temp;
}

void peek_L() {
    if (Top == NULL) {
        cout << "Stack underflow condition\n";
        return;
    }
    cout << "Top is: " << Top->data << endl;
}

void display_L() {
    if (Top == NULL) {
        cout << "Stack is empty\n";
        return;
    }
    cout << "Stack elements:\n";
    struct stackL_node *temp = Top;
    while (temp != NULL) {
        cout << temp->data << endl;
        temp = temp->next;
    }
}





int main(){

	//creation 
	Stack st(8);

	// push
	st.push(10);
	st.print();

	st.push(20);
	st.print();

	cout<< endl << "Top elemet: " << st.getTop() << endl;
	cout << endl << "Size of stack: " << st.getSize() << endl;

	st.pop();
	st.pop();
	if(st.isEmpty()) 
	{
		cout << "Empty" << endl;
	}
	else {
		cout << "Not empty" << endl;
	}

	//   st.push(30);
	//   st.print();

	//     st.push(10);
	//   st.print();

	//   st.push(20);
	//   st.print();



	//   st.push(30);
	//   st.print();
	//     st.push(10);
	//   st.print();

	//   st.push(20);
	//   st.print();

	//   st.push(30);
	//   st.print();

	//   st.pop();
	//   st.print();
	//   st.pop();
	//   st.print();
	//   st.pop();
	//   st.print();

	return 0;
}

// #include <iostream>
// #include<stack>
// using namespace std;

// int main(){
// 	string str = "hellojee";
// 	stack<char> st;
// 	for(int i=0; i<str.length(); i++) {
// 		char ch = str[i];
// 		st.push(ch);
// 	}
// 	cout << endl;

// 	while( !st.empty() ) {
// 		cout << st.top()  ;
// 		st.pop();
// 	}cout << endl;

// 	return 0;
// }






// #include <iostream>
// #include<stack>
// using namespace std;

// int main(){

// 	//creation
// 	stack<int> st;

// 	//insertion
// 	st.push(10);
// 	st.push(20);
// 	st.push(30);

// 	//size check
// 	cout << "Size of stack is: " << st.size() << endl;

// 	//remove 
// 	st.pop(); 

// 	//check empty
// 	if(st.empty()) {
// 		cout << "Stack is empty" << endl;
// 	}
// 	else {
// 		cout << "stack is non empty" << endl;
// 	}


// 	//top element
// 	cout << st.top() << endl;


// 	return 0;
// }