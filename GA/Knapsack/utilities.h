#include "initial_setting.h"
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
    return evaluate_weight(gene) <= max_weight;
}
vector<int> generate_new_individual(int gen_length){
    vector<int> new_gene(gen_length);
    bool feasible = false;
    do {
        for (int &node : new_gene){
            node = rand() % 2;
        }
    } while (!feasible_group(new_gene));
    return new_gene;
}
void read_items(){
    ifstream fi("items");
    fi >> count_items >> max_weight;
    for (int i = 0; i < count_items; ++i){
        fi >> item_name[i];
        fi >> weight[i];
        fi >> value[i];
    }
}
void show_item(int i){
    cout << "Item " << item_name[i] << ", weight: " << weight[i] << ", value: " << value[i] << endl;
}
void show_items(){
    for (int i = 0; i < count_items; ++i){
          show_item(i);
    }
}
double generate_new_rate(){
    return (double) rand() / (RAND_MAX);
}