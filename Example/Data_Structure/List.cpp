//
// Created by jiang-ziyang on 22-8-4.
//

#include "../../Include/Data_Structure_Header.h"

using namespace std;

List<int> &testInsertRemove(List<int> & L) {
    cout << "Please enter the order(insert or remove) and the elem(double)" << endl;
    cout << "like \"insert 3\"(int) or \"remove 3\"(without space)" << endl;
    cout << "enter \"quit\" to end input" << endl;
    string str;
    int elem;
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
        } else if (str == "quit")
            break;
        cout << "The list is " << L << endl << endl;
        cout << "Please enter the order(insert or remove) and the elem(double)" << endl;
    }
    //test its iterator
    for (auto iter = L.begin(); iter != L.end(); ++iter) {
        cout << *iter << endl;
    }
    //test its return value
    if (L)
        cout << "test successfully" << endl;
    else
        cout << "List is empty" << endl;
    return L;
}

int main() {
    List<int> L0;
    auto L1 = testInsertRemove(L0);
    cout << "L1 : " << L1 << endl;
    auto L2 = List<int>(3);
    cout << "L2 : " << L2 << endl;
    auto L3(L0);
    cout << "L3 : " << L3 << endl;
    return 0;
}