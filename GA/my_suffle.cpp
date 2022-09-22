#include<vector>
#include<iostream>
#include<random>
using namespace std;
void my_random_shuffle(vector<int> &arr){
    int arr_sz = arr.size();
    for (int i = 0; i < arr.size(); ++i){
        int rand_idx = rand() % arr_sz;
        swap(arr[i], arr[rand_idx]);
    }
}
vector<int> generate_order(vector<int> &arr){
    int arr_sz = arr.size();
    vector<int> order(arr_sz);
    for (int i = 0; i < arr_sz; ++i){
        order[arr[i]] = i;
    }
    return order;
}
void print_vector(vector<int> arr){
    for (int elm : arr){
        cout << elm << ' ';
    }
    cout << endl;
}
vector<int> crossover_2(vector<int> parent1, vector<int> parent2){
    int gen_length = parent1.size();
    vector<int> child(gen_length, 0);
    vector<bool> visited(gen_length, false);
    vector<int> order = generate_order(parent1);
    int take_from = 0;
    for (int i = 0; i < gen_length; ++i){
        if (visited[i]) continue;
        visited[i] = true;
        int idx = i;
        cout << parent1[idx] << " ";
        while (parent2[idx] != parent1[i]){
            if (take_from) child[idx] = parent2[idx];
            else child[idx] = parent1[idx];
            idx = order[parent2[idx]];
            visited[idx] = true;
            cout << parent1[idx] << " ";
        }
        if (take_from) child[idx] = parent2[idx];
        else child[idx] = parent1[idx];
        cout << endl;
        take_from = 1 - take_from;
    }
    cout << " --- \n";
    print_vector(parent1);
    print_vector(parent2);
    print_vector(child);
    cout << " --- \n";
    return child;
}
int main(){
    srand(time(NULL));
    vector<int> arr1(6);
    for (int i = 0; i < arr1.size(); ++i){
        arr1[i] = i;
    }
    vector<int> arr2(6);
    for (int i = 0; i < arr2.size(); ++i){
        arr2[i] = i;
    }
    my_random_shuffle(arr1);
    my_random_shuffle(arr2);
    crossover_2(arr1, arr2);
}