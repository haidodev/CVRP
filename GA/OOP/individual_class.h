#include "utilities.h"
class Individual{
public:
    vector<int> chromosome;
    double fitness;
    Individual(int gen_length);
    Individual(vector<int> chromosome);
    void mutate();
    double calculate_fitness();
    bool operator<(Individual idv1);

    void show_individual();
    void show_individual_();
};

Individual::Individual(int gen_lenth){
    this -> chromosome = generate_new_individual(gen_lenth);
    this -> fitness = this -> calculate_fitness();
}
Individual::Individual(vector<int> chromosome){
    this -> chromosome = chromosome;
    this -> fitness = this -> calculate_fitness();
}
void Individual::mutate(){
    int gen_len = (this -> chromosome).size();
    int p1 = rand() % gen_len;
    int p2 = rand() % gen_len;
    while (p1 == p2) {
        p2 = rand() % gen_len;
    }

    int v1 = this -> chromosome[p1];
    this -> chromosome[p1] = this -> chromosome[p2];
    this -> chromosome[p2] = v1;
    this -> fitness = this -> calculate_fitness();
}
double Individual::calculate_fitness(){
    int gen_len = (this -> chromosome).size();
    double route_len = 0;
    for (int i = 0; i < gen_len; ++i){
        int src = i % gen_len, dst = (i + 1) % gen_len;
        route_len += graph[this->chromosome[src]][this->chromosome[dst]];
    }
    //return 1.0 / route_len;
    return -route_len;
}
bool Individual::operator<(Individual idv){
    return (this->fitness) > (idv.fitness);
}
void Individual::show_individual(){
    for (int node : this->chromosome){
        cout << node << " ";
    }
    cout << ",Path length: " << -this -> fitness;
    cout << endl;
}
void Individual::show_individual_(){
    for (int node : this->chromosome){
        cout << decod[node] << " ";
    }
    cout << ",Path length: " << -this -> fitness;
    cout << endl;
}