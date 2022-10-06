#include "popuplation_class.h"
int main(){
    srand(time(NULL));
    read_items();
    //show_items();
    Population p = Population(50, count_items);
    Individual best_idv = p.population[0];
    int cur_best = INT_MAX, continuous_unchanged = MAX_CONTINUOUS_UNCHANGED;
    int cur_gen = 0;
    while (cur_gen < MAX_GENERATION && continuous_unchanged > 0){
        p.produce_offspring();
        p.produce_mutation();
        p.selection();
        best_idv = p.population[0];
        if (cur_best == best_idv.fitness) --continuous_unchanged;
        else {
            continuous_unchanged = MAX_CONTINUOUS_UNCHANGED;
            cur_best = best_idv.fitness;
        }
        ++cur_gen;
    }
    cout << cur_gen << endl;
    for (int i = 0; i < 100; ++i){
        
    }
    cout << "BEST IDV: \n";
    best_idv.show_individual();
}