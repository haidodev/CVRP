#include "initial_setting.h"

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
void read_graph(){
    ifstream fi("mygraphout");
    fi >> count_cities;
    for (int i = 0; i < count_cities; ++i){
        for (int j = 0; j < count_cities; ++j){
            graph[i][j] = 1000;
            
        }
    }
    int curent_city = 0;
    int edges;
    fi >> edges;

    for (int i = 0; i < edges; ++i){
        string src, dst;
        fi >> src >> dst;
        if (encod.find(src) == encod.end()){
            encod[src] = curent_city;
            decod[curent_city] = src;
            ++curent_city;
        }
        if (encod.find(dst) == encod.end()){
            encod[dst] = curent_city;
            decod[curent_city] = dst;
            ++curent_city;
        }
        int src_idx = encod[src], dst_idx = encod[dst];
        // cout << src << ":" << src_idx << ", " << dst << ":" << dst_idx << endl;
        double distance;
        fi >> distance;
        graph[src_idx][dst_idx] = distance;
        graph[dst_idx][src_idx] = distance;
    }
    // cout << "ENCODE: \n";
    // for (auto elm : encod){
    //     cout << elm.first << " " << elm.second << endl;
    //     }
    // cout << "DECODE: \n";
    // for (auto elm : decod){
    //     cout << elm.first << " " << elm.second << endl;
    // }
}
void show_graph(){
    for (int i = 0; i < count_cities; ++i){
        for (int j = 0; j < count_cities; ++j){
            if (graph[i][j] != INT_MAX)
            cout << graph[i][j] << "\t";
            else cout << "X\t";
            
        }
        cout << endl;
    }
}
double generate_new_rate(){
    return (double) rand() / (RAND_MAX);
}