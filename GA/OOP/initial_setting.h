#include <map>
#include <fstream>
#include <string>
#include <vector>
#include <random>
#include <algorithm>
#include <time.h>
#include <iostream>
#include <limits.h>

#define CROSSOVER_RATE 0.5
#define MUTATION_RATE 0.3
#define POPULATION_SIZE 20
#define MAX_GENERATION 10000
#define MAX_CONTINUOUS_UNCHANGED 100

using namespace std;
int count_cities = 0;
double graph[1000][1000];
map<string, int> encod;
map<int, string> decod;