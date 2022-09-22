#include <vector>
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