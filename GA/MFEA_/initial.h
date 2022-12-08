#include<iostream>
#include<vector>
#include<fstream>
#include<algorithm>

using namespace std;

#define FILE "mfea.txt"
#define POP_SIZE 10
#define MAX_GENERATION 300
#define rmp 0.5 
#define MAX_N 20

int co_cities1, co_cities2;
int N;
int distance1[MAX_N][MAX_N], distance2[MAX_N][MAX_N];

void read_input(){
    ifstream fi(FILE);
    fi >> co_cities1 >> co_cities2;
    for (int i = 0; i < co_cities1; ++i){
        for (int j = 0; j < co_cities1; ++j){
            fi >> distance1[i][j];
        }
    }
    for (int i = 0; i < co_cities2; ++i){
        for (int j = 0; j < co_cities2; ++j){
            fi >> distance2[i][j];
        }
    }
}

vector<int> random_permutation(int n){
    vector<int> arr(n);
    for (int i = 0; i < n; ++i) arr[i] = i;
    for (int i = 0; i < n; ++i) swap(arr[i], arr[rand() % n]);
    return arr;
}
vector<int> random_n_elements(int n, int range){
    vector<int> arr = random_permutation(range), res(n);
    for (int i = 0; i < n; ++i){
        res[i] = arr[i];
    }
    return res;
}
vector<int> gen_order(vector<int> arr){
    vector<int> order(arr.size());
    for (int i = 0; i < arr.size(); ++i){
        order[arr[i]] = i;
    }
    return order;
}