#include<vector>
#include<algorithm>

using namespace std;
vector<int> generate_new_individual(int gen_length){
    vector<int> new_gene;
    for (int i = 0; i < gen_length; ++i){
        new_gene.push_back(i);
    }
    random_shuffle ( new_gene.begin(), new_gene.end() );
    return new_gene;
}
vector<int> generate_order(vector<int> &arr){
    int arr_sz = arr.size();
    vector<int> order(arr_sz);
    for (int i = 0; i < arr_sz; ++i){
        order[arr[i]] = i;
    }
    return order;
}