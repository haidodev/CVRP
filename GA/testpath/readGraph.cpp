#include<iostream>
#include<fstream>
using namespace std;
int main(){
    fstream fi("mygraph_");
    fstream fo("../mygraphout");
    int n;
    fi >> n;
    fo << n << "\t" << n * (n - 1) / 2 << endl;
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < n; ++j){
            int distance;
            fi >> distance;
            if (j > i) fo << i + 1 << "\t" << j + 1 << "\t" << distance << endl;
        }
        
    }
}