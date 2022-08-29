#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
vector<int> gen(int n) // Complexity O(n)
{
    vector<int> myvector;
    for(int i=0; i<n; ++i) myvector.push_back(i);
    random_shuffle ( myvector.begin(), myvector.end()); // Random shuffling to generate population
    return myvector;
}
vector<int> makeOrd(vector<int> v){
    int n = v.size();
    vector<int> ord(n);
    for (int i =0; i < n; ++i){
        ord[v[i]] = i;
    }
    return ord;
}
void crossover_(vector<int> &p1, vector<int> &p2){
    vector<int> o1, o2;
    o1 = makeOrd(p1);
    o2 = makeOrd(p2);
    int left = 3, right = 7;
    for (int i = left; i <= right; ++i){
        int tmp1 = o1[p2[i]], tmp2 = o2[p1[i]];
        swap(p1[tmp1], p1[i]);
        swap(p2[tmp2], p2[i]);
    }
}
vector<int> cloneVector(vector<int> v){
    vector<int> clone(v.size());
    for (int i = 0; i < v.size(); ++i) clone[i] = v[i];
    return clone;
}
vector<int> crossover(vector<int> &p1, vector<int> &p2){
    vector<int> o1, o2, p1clone;
    o1 = makeOrd(p1);
    p1clone = cloneVector(p1);
    int left = 3, right = 7;
    for (int i = left; i <= right; ++i){
        int tmp1 = o1[p2[i]];
        swap(p1clone[tmp1], p1clone[i]);
    }
    return p1clone;
}
void printArray(vector<int> v){
    for (int elm : v){
        cout << elm << " ";
    }
    cout << endl;
}
int main(){
    vector<int> p1, p2;
    p1 = gen(10);
    p2 = gen(10);
    printArray(p1);
    printArray(p2);
    printArray(crossover(p1, p2));
    printArray(p1);
    printArray(p2);
}