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
    // void show_individual_();
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
    int position = rand() % gen_len;
    this->chromosome[position] = 1 - this->chromosome[position];
}
double Individual::calculate_fitness(){
    int gen_len = (this -> chromosome).size();
    double total_value = 0;
    for (int i = 0; i < gen_len; ++i){
        total_value += value[i] * this->chromosome[i];
    }
    //return 1.0 / route_len;
    return total_value;
}
bool Individual::operator<(Individual idv){
    return (this->fitness) > (idv.fitness);
}
void Individual::show_individual(){
    int gene_length = this->chromosome.size();
    for (int i = 0; i < gene_length; ++i){
        int node = this->chromosome[i];
        if (node) show_item(i);
    }
    cout << ",Max Value: " << this -> fitness;
    cout << endl;
}