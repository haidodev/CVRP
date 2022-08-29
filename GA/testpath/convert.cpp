#include<iostream>
#include<fstream>
using namespace std;
int main(){
    fstream fi("path");
    int n;
    fi >> n;
    for (int i = 0; i < n; ++i){
        int n ;
        fi >> n;
        cout << n - 1 << ", ";
        
    }
}