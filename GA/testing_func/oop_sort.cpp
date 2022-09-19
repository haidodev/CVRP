#include<iostream>
#include<random>
#include<vector>
#include<algorithm>
using namespace std;
class MyClass {
public:
    int x, y, z;
    MyClass(int x, int y, int z);
    bool operator<(MyClass obj);
    void show();
};
MyClass::MyClass(int x, int y, int z){
    this -> x = x;
    this -> y = y;
    this -> z = z;

}
bool MyClass::operator<(MyClass obj){
    return this -> y < obj.y;
}
void MyClass::show(){
    cout << this-> x << "\t"<<this->y<<"\t" << this->z << endl;
}
int my_rand(int x){
    return rand() % x;
}
int main(){
    vector<MyClass> arr;
    for (int i = 0; i < 10; ++i){
        arr.push_back(MyClass(my_rand(30), my_rand(30), my_rand(30)));
    }
    for (auto elm : arr) elm.show();
    cout << "\n------\n";
    sort(begin(arr), end(arr));
    for (auto elm : arr) elm.show();
    
}