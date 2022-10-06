#include "individual_class.h"
class Population{
public:
    vector<Individual> population;
    Population(int population_sz, int gen_length);
    void selection();
    void produce_offspring();
    void produce_mutation();
    Individual crossover(Individual p1, Individual p2);
    void show_population();
    // void show_population_();
};
Population::Population(int population_sz, int gen_length){
    while (population_sz--){
        this->population.push_back(Individual(gen_length));
    }
}
Individual Population::crossover(Individual parent1, Individual parent2){
    int gene_length = parent1.chromosome.size();
    int pos1 = rand() % gene_length, pos2 = rand() % gene_length;
    if (pos1 > pos2) swap(pos1, pos2);
    vector<int> child(gene_length, 0);
    vector<bool> visited(gene_length, false);
    for (int i = 0; i < gene_length; ++i){
        if (i >= pos1 && i <= pos2) child[i] = parent2.chromosome[i];
        else child[i] = parent1.chromosome[i];
    }
    return Individual(child);
}
void Population::produce_offspring(){
    int parent_range = this->population.size();
    for (int i = 0; i < parent_range; ++i){
        for (int j = i + 1; j < parent_range; ++j){
            
            if (generate_new_rate() <= CROSSOVER_RATE){
                Individual new_child = this->crossover(this->population[i], this->population[j]);
                if (feasible_group(new_child.chromosome)) this->population.push_back(new_child);
            }
        }
    }
    
}
void Population::produce_mutation(){
    int population_sz = this->population.size();
    for (int i = 0; i < population_sz; ++i){
        if (generate_new_rate() <= MUTATION_RATE) this->population[i].mutate();
    }
    
}
// Change the way to 
void Population::selection(){
    vector<Individual> new_population;
    for (Individual id : this->population) new_population.push_back(id);
    sort(begin(new_population), end(new_population));
    while (new_population.size() > POPULATION_SIZE) new_population.pop_back();
    this->population = new_population;
}
void Population::show_population(){
    for (Individual id : this->population){
        id.show_individual();
    }
}
// void Population::show_population_(){
//     for (Individual id : this->population){
//         id.show_individual_();
//     }
// }