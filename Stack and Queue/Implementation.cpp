#include <iostream>
#include <stack>
#include <queue>

using namespace std;

// Implementation of Queue using array

# define N 5
int myQueue[N];
int front = -1;
int rear = -1;

void enqueue(int n){
    if(rear == N-1){
        cout << "Overflow condition" << endl;
        return;
    }
    else if(front == -1 && rear == -1){
        front = rear = 0;
        myQueue[rear] = n;
        return;
    }
    else{
        rear++;
        myQueue[rear] = n;
        return;
    }
}


void dequeue(){
    if(front == -1 && rear == -1){
        cout << "Stack UnderFlow Condition";
        return;
    }
    else if(front == rear){
        front = rear = -1;
        return;
    }
    front++;
}

void peek(){
    if(front == -1 && rear == -1){
        cout << "The queue is empy";
        return;
    }
    cout << "The Front element is : " << myQueue[front];
}

void display(){
    if(front == -1 && rear == -1){
        cout << "The queue is empy";
        return;
    }
    for(int i = front; i<=rear; i++){
        cout << myQueue[i] << endl;
    }
}


// Implementaion of Queue using Linked List
// Since enqueue and dequeue should take O(1) so we have to maintain 2 pointers
// head for deletion and tail for insertion

struct QueueL{
    int data;
    struct QueueL *next;

    QueueL(int data){
        this->data = data;
        this->next = nullptr;
    }
};

struct QueueL *frontL = nullptr;
struct QueueL *rearL = nullptr;

void enqueueL(int data){
    struct QueueL *newnode = new QueueL(data);

    if(frontL == nullptr && rearL == nullptr){
        frontL = rearL = newnode;
    }
    else{
        rearL->next = newnode;
        rearL = newnode;
    }
}

void displayL(){
    if(frontL == nullptr && rearL == nullptr){
        cout << "List is empty" << endl;
        return;
    }
    struct QueueL *temp;
    temp = frontL;
    while(temp != nullptr){
        cout << temp->data << " ";
        temp = temp->next;
    }
}

void dequeueL(){
    if(frontL == nullptr && rearL == nullptr){
        cout << "Queue is empty" << endl;
        return;
    }
    struct QueueL *temp;
    temp = frontL;
    frontL = frontL->next;
    delete temp;
}

void peekL(){
    if(frontL == nullptr && rearL == nullptr){
        cout << "The list is empty" << endl;
        return;
    }
    cout << frontL->data;
}


int main(){
    enqueueL(5);
    enqueueL(2);
    enqueueL(1);
    enqueueL(2);
    enqueueL(3);
    displayL();
    dequeueL();
    displayL();
}
