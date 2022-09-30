#include<vector>
#include<math.h>
#include<algorithm>
#include<inital_setting.h>
using namespace std;
double evaluate_weight(vector<int> gene){
    int gen_length = gene.size();
    double cur_weight = 0;
    for (int i = 0; i < gen_length; ++i){
        cur_weight += weight[i] * gene[i];
    }
    return cur_weight;
}
bool feasible_group(vector<int> gene){
    return evaluate_weight(gene) < max_weight;
}
vector<int> generate_new_individual(int gen_length){
    vector<int> new_gene(gen_length);
    bool feasible = false;
    do {
        int new_gene_val = rand() % (int)pow(2, gen_length);
        int cur_node = gen_length - 1;
        while (new_gene_val > 0){
            new_gene[cur_node] = new_gene_val % 2;
            new_gene_val /= 2;
        }
    } while (!feasible_group(new_gene));
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

void read_items(){
    ifstream fi("items");
    fi >> count_items;
    for (int i = 0; i < count_items; ++i){
        fi >> weight[i];
    }
    for (int i = 0; i < count_items; ++i){
        fi >> value[i];
    }
    fi >> max_weight;
}
void show_items(){
    for (int i = 0; i < count_items; ++i){
        cout << "Item " << i << ", weight: " << weight[i] << ", value: " << value[i] << endl;  
    }
}