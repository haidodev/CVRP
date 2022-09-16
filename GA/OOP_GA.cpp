#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <time.h>
#include <fstream>
#include <string>
#include <map>
#include <limits.h>
using namespace std;

#define CROSSOVER_RATE 0.5
#define MUTATION_RATE 0.1
#define POPULATION_SIZE 100
#define MAX_GENERATION 1000

int count_cities = 0;
double graph[1000][1000];
map<string, int> encod;
map<int, string> decod;

vector<int> generate_new_individual(int gen_length){
    vector<int> new_gene;
    for (int i = 0; i < gen_length; ++i){
        new_gene.push_back(i);
    }
    random_shuffle ( new_gene.begin(), new_gene.end() );
    return new_gene;
}
class Individual{
public:
    vector<int> chromosome;
    double fitness;
    Individual(int gen_length);
    Individual(vector<int> chromosome);
    void mutate();
    double calculate_fitness();
    bool operator<(Individual idv1);
    bool operator>(Individual idv1);

    void show_individual();
    void show_individual_();
};
Individual::Individual(int gen_lenth){
    this -> chromosome = generate_new_individual(gen_lenth);
    this -> fitness = calculate_fitness();
}
Individual::Individual(vector<int> chromosome){
    this -> chromosome = chromosome;
    this -> fitness = calculate_fitness();
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
}
double Individual::calculate_fitness(){
    int gen_len = (this -> chromosome).size();
    double route_len = 0;
    for (int i = 0; i < gen_len; ++i){
        int src = i % gen_len, dst = (i + 1) % gen_len;
        route_len += graph[src][dst];
    }
    return 1.0 / route_len;
}
bool Individual::operator<(Individual idv){
    return this -> fitness < idv.fitness;
}
bool Individual::operator>(Individual idv){
    return this -> fitness > idv.fitness;
}
void Individual::show_individual(){
    for (int node : this->chromosome){
        cout << node << " ";
    }
    cout << endl;
}
void Individual::show_individual_(){
    for (int node : this->chromosome){
        cout << decod[node] << " ";
    }
    cout << endl;
}
class Population{
public:
    vector<Individual> population;
    Population(int population_sz, int gen_length);
    void selection();
    void produce_offspring();
    void produce_mutation();
    Individual crossover(Individual p1, Individual p2);
    void show_population();
    void show_population_();
};
Population::Population(int population_sz, int gen_length){
    while (population_sz--){
        this->population.push_back(Individual(gen_length));
    }
}
Individual Population::crossover(Individual parent1, Individual parent2){
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
void Population::produce_offspring(){
    int parent_range = this->population.size();
    for (int i = 0; i < parent_range; ++i){
        for (int j = i + 1; j < parent_range; ++j){
            double curent_rate = ((double) rand() / (RAND_MAX));
            if (curent_rate <= CROSSOVER_RATE){
                this->population.push_back(this->crossover(this->population[i], this->population[j]));
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
    sort(begin(this->population), end(this -> population));
    while (this->population.size() > POPULATION_SIZE) this->population.pop_back();
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
void read_graph(){
    ifstream fi("in");
    fi >> count_cities;
    for (int i = 0; i < count_cities; ++i){
        for (int j = 0; j < count_cities; ++j){
            graph[i][j] = INT_MAX;
            
        }
    }
    int edges;
    fi >> edges;

    for (int i = 0; i < edges; ++i){
        string src, dst;
        fi >> src >> dst;
        if (encod.find(src) == encod.end()){
            encod[src] = count_cities;
            decod[count_cities] = src;
            ++count_cities;
        }
        if (encod.find(dst) == encod.end()){
            encod[dst] = count_cities;
            decod[count_cities] = dst;
            ++count_cities;
        }
        int src_idx = encod[src], dst_idx = encod[dst];
        // cout << src << ":" << src_idx << ", " << dst << ":" << dst_idx << endl;
        double distance;
        fi >> distance;
        graph[src_idx][dst_idx] = distance;
        graph[dst_idx][src_idx] = distance;
    }
}
int main(){
    srand(time(NULL));
    read_graph();
    Population p = Population(10, count_cities);
    Individual best_idv = p.population[0];
    // for (int i = 0; i < 100; ++i){
    //     p.produce_offspring();
    //     p.produce_mutation();
    //     p.selection();
    //     best_idv = p.population[0];
    // }
    best_idv.show_individual_();
    for (int i = 0; i < count_cities; ++i){
        for (int j = 0; j < count_cities; ++j){
            cout << graph[i][j] << "\t";
            
        }
        cout << endl;
    }

}