#include "initial.h"
class Individual {
public:
    int fitness1, fitness2;
    int ranking1, ranking2;
    vector<int> chromosome;
    Individual(int length);
    Individual(vector<int> chromosome);
    void mutuate();
    int calculate_fitness(int gen_length, int distance[MAX_N][MAX_N]);
    bool operator<(Individual idv1);
    void show_idv();
};
Individual::Individual(int lenth){
    this -> chromosome = random_permutation(lenth);
    this -> fitness1 = this -> calculate_fitness(co_cities1, distance1);
    this -> fitness2 = this -> calculate_fitness(co_cities2, distance2);
}
Individual::Individual(vector<int> chromosome){
    this -> chromosome  = chromosome;
    this -> fitness1 = this -> calculate_fitness(co_cities1, distance1);
    this -> fitness2 = this -> calculate_fitness(co_cities2, distance2);
}
void Individual::mutuate(){
    int gen_length = this -> chromosome.size();
    vector<int> rand_idx = random_n_elements(2, gen_length);
    swap(this -> chromosome[rand_idx[0]], this -> chromosome[rand_idx[1]]);

}
int Individual::calculate_fitness(int gen_length, int distance[MAX_N][MAX_N]){
    int prev = -1, cur_fitness = 0, start_point = -1;
    for (int i = 0; i < this -> chromosome.size(); ++i){
        if (this -> chromosome[i] < gen_length){
            if (prev != -1) cur_fitness += distance[prev][i];
            else start_point = this -> chromosome[i];
            prev = this -> chromosome[i];
        }
    }
    return cur_fitness + distance[prev][start_point];
}
bool Individual::operator<(Individual idv1){
    return true;
}
void Individual::show_idv(){
    for (int node : this -> chromosome) cout << node << " ";
    cout << "\t F1: " << this -> fitness1;
    cout << "\t rank1: " << this -> ranking1;

    cout << "\t F2: " << this -> fitness2;
    cout << "\t rank2: " << this -> ranking2;

    cout << endl;
}