#include "individual.h"
class Population {
public: 
    vector<Individual> population;
    Population(int gen_length);
    void update_ranking();
    void show_pop();
};
Population::Population(int gen_length){
    for (int i = 0; i < POP_SIZE; ++i) this -> population.push_back(Individual(gen_length));
}
void Population::update_ranking(){
    //Update ranking 1
    // sort(this -> population.begin(), this -> population.end(), [] (Individual const& idv1, Individual const& idv2){return idv1.fitness1 < idv2.fitness1;});
    // for (int i = 0 ; i < POP_SIZE; ++i) this -> population[i].ranking1 = i;
    // sort(this -> population.begin(), this -> population.end(), [] (Individual const& idv1, Individual const& idv2){return idv1.fitness2 < idv2.fitness2;});
    // for (int i = 0 ; i < POP_SIZE; ++i) this -> population[i].ranking2 = i;
}
void Population::show_pop(){
    for (int i = 0; i < POP_SIZE; ++i) this -> population[i].show_idv();
}