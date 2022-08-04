//
// Created by jiang-ziyang on 22-8-4.
//

#include "../../Include/Data_Structure_Header.h"

using namespace std;

int main() {
    List<int> L;
    cout << "Please enter the order(insert or remove) and the elem(double)" << endl;
    cout << "like \"insert 3\"(int) or \"remove 3\"(without space)" << endl;
    string str;
    double elem;
    for (;;) {
        cin >> str;
        if (str == "insert") {
            cin >> elem;
            L.insert(elem);
            cout << "list insert element " << elem << " successfully" << endl;
        } else if (str == "remove") {
            cin >> elem;
            try {
                L.remove(elem);
                cout << "list remove element " << elem << " successfully" << endl;
            } catch (runtime_error e) {
                cout << "We didn't find the elem " << elem << endl;
            }
        }
        cout << "The list is " << L << endl << endl;
        cout << "Please enter the order(insert or remove) and the elem(double)" << endl;
    }
}