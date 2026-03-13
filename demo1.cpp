#include <iostream>
#include <vector>

using namespace std;

int main(){
    vector<int> v = {1,2,3,4,5};
    for (int &x : v) {  //要改变v的话，必须加引用
        x = x*2;
        cout << x <<endl;
    }
    for (int i = 0; i < v.size(); ++i) {
        cout << v[i] <<" ";
    }
    cout << endl;
    cout<< v.size() << endl;
    cout<<v.capacity()<<endl;
    cout << "============" << endl;
    v.push_back(1111);
    for (int &x : v) {
        cout << x <<endl;
    }
    //v.resize(3);
    //cout << v.max_size() <<endl;

    cout << "============" << endl;
    for (vector<int>::iterator it = v.begin(); it != v.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;
    return 0;
}
