#include "population.h"

int main(){
    read_input();
    vector<int> arr = random_permutation(10);
    for (int elm :arr) cout << elm << " ";
    sort(arr.begin(), arr.end());
    cout << endl;
    for (int elm :arr) cout << elm << " ";
    sort(arr.begin(), arr.end(), [](int x1, int x2){return x1 > x2;});


    // Population cur_pop = Population(9);
    // cur_pop.show_pop();
    // cur_pop.update_ranking();
    // cur_pop.show_pop();
}