//
// Created by jiang-ziyang on 22-8-4.
//

#include "../../Include/Data_Structure_Header.h"

using namespace std;

int main() {
    size_t size;
    cout << "Please enter the size of stack" << endl;
    cin >> size;
    Stack<double> S(size);
    double elem;
    string str;
    cout << "Please enter the order(push or pop) and the elem(double)" << endl;
    cout << "like \"push 3.1415\" or \"pop\"(without space)" << endl;
    for (;;) {
        cin >> str;
        if (str == "push") {
            cin >> elem;
            S.push(elem);
            cout << "stack push element " << elem << " successfully" << endl;
        } else if (str == "pop") {
            cout << "stack pop element " << S.pop() << " successfully" << endl;
        }
        cout << "The stack's size is " << S.size() << " and its element number is " << S.elemNum() << endl << endl;
        cout << "Please enter the order(push or pop) and the elem(double)" << endl;
    }
}