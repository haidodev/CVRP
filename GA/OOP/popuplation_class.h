#include "individual_class.h"

class Population{
public:
    vector<Individual> population;
    Population(int population_sz, int gen_length);
    void selection();
    void produce_offspring();
    void produce_mutation();
    Individual crossover_1(Individual p1, Individual p2);
    Individual crossover_2(Individual p1, Individual p2);
    void show_population();
    void show_population_();
};

Population::Population(int population_sz, int gen_length){
    while (population_sz--){
        this->population.push_back(Individual(gen_length));
    }
}
Individual Population::crossover_1(Individual parent1, Individual parent2){
    int gen_length = parent1.chromosome.size();
    int pos1 = rand() % gen_length, pos2 = rand() % gen_length;
    if (pos1 > pos2) swap(pos1, pos2);
    vector<int> child(gen_length, 0);
    vector<bool> visited(gen_length, false);
    for (int i = pos1; i <= pos2; ++i){
        child[i] = parent2.chromosome[i];
        visited[parent2.chromosome[i]] = true;
    }
    int curIdx = (pos2 + 1) % gen_length;
    for (int i = pos2 + 1; i < gen_length; ++i){
        while (visited[parent1.chromosome[curIdx]]){
            curIdx = (curIdx + 1) % gen_length;
        }
        child[i] = parent1.chromosome[curIdx];
        visited[parent1.chromosome[curIdx]] = true;
            
    }
    for (int i = 0; i < pos1; ++i){
        while (visited[parent1.chromosome[curIdx]]){
            curIdx = (curIdx + 1) % gen_length;
        }
        child[i] = parent1.chromosome[curIdx];
        visited[parent1.chromosome[curIdx]] = true;
            
    }
    return Individual(child);
}
Individual Population::crossover_2(Individual parent1, Individual parent2){
    int gen_length = parent1.chromosome.size();
    vector<int> child(gen_length, 0);
    vector<bool> visited(gen_length, false);
    vector<int> order = generate_order(parent1.chromosome);
    int take_from = 0;
    for (int i = 0; i < gen_length; ++i){
        if (visited[i]) continue;
        visited[i] = true;
        int idx = i;
        while (parent2.chromosome[idx] != parent1.chromosome[i]){
            visited[idx] = true;
            if (take_from) child[idx] = parent2.chromosome[idx];
            else child[idx] = parent1.chromosome[idx];
            idx = order[parent2.chromosome[idx]];
            visited[idx] = true;
        }
        if (take_from) child[idx] = parent2.chromosome[idx];
        else child[idx] = parent1.chromosome[idx];
        take_from = 1 - take_from;
    }
    return Individual(child);
}
void Population::produce_offspring(){
    int parent_range = this->population.size();
    for (int i = 0; i < parent_range; ++i){
        for (int j = i + 1; j < parent_range; ++j){
            double curent_rate = ((double) rand() / (RAND_MAX));
            if (curent_rate <= CROSSOVER_RATE){
                Individual new_child = this->crossover_2(this->population[i], this->population[j]);
                this->population.push_back(new_child);
            }
        }
    }
    
}
void Population::produce_mutation(){
    int population_sz = this->population.size();
    for (int i = 0; i < population_sz; ++i){
        this->population[i].mutate();
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
void Population::show_population_(){
    for (Individual id : this->population){
        id.show_individual_();
    }
}
