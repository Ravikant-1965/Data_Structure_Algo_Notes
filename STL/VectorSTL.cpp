#include <bits/stdc++.h>
using namespace std;


void print2(vector<int> v) {
	cout << "Printing vector method 2" << endl;
	for(auto it:v){
		cout<<it<<" ";
	}
	cout << endl;
}


void print_v(vector<int> &v){  // pass by refrence
	cout << "Size of the Vector is : " << v.size() << endl; //O(1) TC
	for (int i = 0; i < v.size(); i++){
		cout << v[i] << " ";
	}
	cout << endl;
}


int main(){

	// vector<int> vr(10, 3); // Of size 10 with all 3's, values by default 0
	// vr.push_back(7); // 11th elemnt will be 7
	// vector<int> v = {1, 2, 3, 4}; // Declaration

	// vr.emplace_back(23); // faster than push_back

	// vector<pair<int, int>> vec;
	// vec.push_back({1, 2});  // in case of this you have to put curly brackets
	// vec.emplace_back(1, 2); // emplace back automatically handles it

	// int size;
	// cout << "Enter size of the array : ";
	// cin >> size;

	// for (int i = 0; i < size;i++){
	// 	int x;
	// 	cout << "Enter the value";
	// 	cin >> x;
	// 	v.push_back(x);
	// }
	// print_v(v);

	// v.pop_back(); // pops last element

	// vector<int> v1 = v; // Copying of array (changes in v2 won't affect v) TC : O(n)

	// // array of Vectors
	// vector<int> va[5]; // this creates an array of 5 0 size Vectors


	vector<int> v5 = {1,2,3,4,5,6};
	for (int i = 0; i < v5.size(); i++){
		cout << v5[i] << " ";
	}
	cout << endl;
	// In array there are Indexes through which you can access the data
	// but in other DS like map there is no concept of Indexig, instead there is concept of Iterators
	// Declare Iterator
	// vector<int>::iterator it;
	vector<int>::iterator it = v5.begin();   // you can avoid this declaration using auto keyWord
	cout << (*it) << endl;
	for(it = v5.begin(); it != v5.end(); ++it){
		cout << (*it) << " ";
	}
	cout << endl;

	// Range based Loops
	for(int it : v5){
		cout << it << " ";
	}
	cout << endl;
	// auto keyword automatically Dynamically takes the Data Type of the variable
	// this auto keyWord helps you to avoid declare the iterator....It automatically takes the iterator data Type
	for(auto it : v5){
		cout << it << " ";
	}
	cout << endl;
	
}

// int main() {

  // dont tell size of vector.
  // just keep inserting, vector will manage the allocations.
  // vector<int> v; // array hi hai.

  // vector<int> v;
  // v.push_back(10);
  // v.push_back(20);
  // v.push_back(30);
  // v.push_back(40);
  // print2(v);

  // vector<char> v;
  // v.push_back('a');
  // v.push_back('b');
  // v.push_back('c');
  // v.push_back('d');

  // cout << "Front element: " << v[0] << endl;
  // cout << "Front element: " << v.front() << endl;
  // cout << "End Element: " << v[v.size() - 1] << endl;
  // cout << "End Element: " << v.back() << endl;


  // // how to copy vector
  // vector<int> arr5 = {1,2,3,4,5};
  // vector<int>arr6(arr5);
  // print(arr6);

  // to clear the vector
  // v.clear();
  // v.push_back(50);
  // print2(v);
//}