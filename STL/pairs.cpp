#include <bits/stdc++.h>
using namespace std;

int main(){

    pair<int, string> p; //Declaration
    //pair<int, pair<int, int>> p = {1, {2, 3}}; // Nested pairs

    // You can take Inputs
    cin >> p.first;
    cin >> p.second;
    cout << p.first << endl;
    cout << p.second << endl;

    //Intialisation
    pair<int, string> p1 = {1, "Ravi"};
    //p = make_pair(2, "Ravi"); //This is not of much use
    p1 = {2, "Ravi"};

    // pair<int, string> p1 = p; // Copying of P to P1 (Pas By Value hota hai)
    pair<int, string> &p2 = p; // Copying of P to P1 (Pas By Refrence)
    p2.first = 3;

    cout << p.first << " " << p.second << endl;


    pair<int, int> p_arr[] = {{1, 100}, {2, 99}, {3, 98}}; // array of pairs

    cout << p_arr[1].second << endl;

    for (int i = 0; i < 3;i++){
        cout << p_arr[i].first << " " << p_arr[i].second << endl;
    }
}