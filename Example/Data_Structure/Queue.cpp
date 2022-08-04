//
// Created by jiang-ziyang on 22-8-4.
//


#include "../../Include/Data_Structure_Header.h"

using namespace std;

int main(){
    size_t size;
    cout << "Please enter the size of stack" << endl;
    cin >> size;
    Queue<double> S(size);
    double elem;
    string str;
    cout << "Please enter the order(enroll or eject) and the elem(double)" << endl;
    cout << "like \"enroll 3.1415\" or \"eject\"(without space)" << endl;
    for (;;) {
        cin >> str;
        if (str == "enroll") {
            cin >> elem;
            S.enroll(elem);
            cout << "stack push element " << elem << " successfully" << endl;
        } else if (str == "eject") {
            cout << "stack pop element " << S.eject() << " successfully" << endl;
        }
        cout << "The Queue is:" << S << endl << endl;
        cout << "Please enter the order(push or pop) and the elem(double)" << endl;
    }
}