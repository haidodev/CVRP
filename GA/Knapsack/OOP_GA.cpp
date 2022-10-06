#include "popuplation_class.h"
using namespace std;

int main(){
    srand(time(NULL));
    read_items();
    //show_graph();
    Population p = Population(50, count_items);
    Individual best_idv = p.population[0];
    int cur_best = INT_MAX, continuous_unchanged = 20;
    int cur_gen = 0;
    while (cur_gen < MAX_GENERATION && continuous_unchanged > 0){
        p.produce_offspring();
        p.produce_mutation();
        p.selection();
        best_idv = p.population[0];
        if (cur_best == best_idv.fitness) --continuous_unchanged;
        else {
            continuous_unchanged = 20;
            cur_best = best_idv.fitness;
        }
        ++cur_gen;
    }
    cout << cur_gen << endl;
    for (int i = 0; i < 100; ++i){
        
    }
    cout << "BEST IDV: ";
    best_idv.show_individual();
}