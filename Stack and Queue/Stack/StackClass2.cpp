#include <iostream>
#include <stack>

using namespace std;

// implement 2stack using 1 array
// method 1 is to divide the array in 2 parts and then implement (but in this case memory is not efficiently used)
// method 2 is to start filling from startng and ending of the array
class Stack{
public:
    int *arr;
    int size;
    int top1;  // at -1 (starting of the array)
    int top2;  // at size (end of the array)
    Stack(int size){
        this->size = size;
        this->arr = new int[size];

        this->top1 = -1;
        this->top2 = size;
    }

    void push1(int data){
        if (abs(top2 - top1) == 1){
            cout << "Stack OverFlow!" << endl;
            return;
        }
        else{
            top1++;
            arr[top1] = data;
        }
    }

    void push2(int data){
        if (abs(top2 - top1) == 1){
            cout << "Stack OverFlow!" << endl;
            return;
        }
        else{
            top2--;
            arr[top2] = data;
        }
    }

    void pop1(){
        if (top1 == -1){
            cout << "Stack underFlow!" << endl;
            return;
        }else{
            arr[top1] = 0;
            top1--;
        }
    }

    void pop2(){
        if (top2 == size){
            cout << "Stack Underflow!" << endl;
            return;
        }else{
            arr[top2] = 0;
            top2++;
        }
    }

    void print(){
        cout << endl;
        cout << "Top 1 : " << top1 << endl;
        cout << "Top 2 : " << top2 << endl;
        for(int i=0; i<size; i++){
            cout << arr[i] << " ";
        }
        cout << endl;
    }

    int getTop1(){
        return arr[top1];
    }
    int getTop2()
    {
        return arr[top1];
    }
};

// check for redundant bracket, faltu ke brackets jinki need nahi hai like ((a)+(b))
bool checkRedundantBracket(string s)
{
    stack<char> st;
    int n = s.size();
    for (int i = 0; i < n; i++)
    {
        char ch = s[i];
        if (ch == '(' || ch == '+' || ch == '-' || ch == '*' || ch == '/')
            st.push(ch);
        else if (ch == ')')
        {
            int operatorCount = 0;
            while (st.size() != 0 && st.top() != '(')
            {
                char temp = st.top();
                if (temp == '+' || temp == '-' || temp == '*' || temp == '/')
                    operatorCount++;
                st.pop();
            }
            st.pop();
            if (operatorCount == 0)
                return 1;
        }
    }
    return 0;
}


int main(){

    // Stack st(5);
    // st.push1(1);
    // st.push1(2);
    // st.push1(3);
    // st.push2(4);
    // st.print();
    // cout << st.getTop1() << endl;
    // string str = "((a+b)*(a+b))";
    // cout << checkRedundantBracket(str) << endl;
    return 0;
}