//
// Created by jiang-ziyang on 22-8-7.
//

#include "../../Data_Structure/Hash_Table.h"
#include "../../Include/Supported_Tools.h"

#define HASH_TABLE_SIZE 200

using namespace std;
using type = int;

int main() {
    HashTableOpeningAddress<type> H(HASH_TABLE_SIZE);
    cout << "Please enter the order(insert or remove or search) and the elem(" << typeid(type).name() << ")" << endl;
    cout << "like \"insert 32\"(" << typeid(type).name() << ") or \"remove 32\"(without space)" << endl;
    string str;
    type elem;
    size_t index;
    for (;;) {
        cin >> str;
        if (str == "insert") {
            cin >> elem;
            H.insert(elem);
            cout << "hash table insert element " << elem << " successfully" << endl;
        } else if (str == "remove") {
            cin >> elem;
            try {
                H.remove(elem);
                cout << "hash table remove element " << elem << " successfully" << endl;
            } catch (runtime_error e) {
                cout << "We didn't find the elem " << elem << endl;
            }
        } else if (str == "search") {
            cin >> elem;
            if ((index = H.search(elem)) != NIL) {
                cout << "elem " << elem << " exists, and it locate at index " << index << endl;
            } else
                cout << "elem " << elem << " doesn't exist" << endl;
        }
        cout << "The hash table is " << H << endl;
        cout << "Please enter the order(insert or remove) and the elem(double)" << endl;
    }
}