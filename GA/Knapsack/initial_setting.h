#include <vector>
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <time.h>
#include <fstream>
#include <string>
#include <limits.h>
#include<math.h>
using namespace std;

#define CROSSOVER_RATE 0.5
#define MUTATION_RATE 0.3
#define POPULATION_SIZE 20
#define MAX_GENERATION 10000
#define MAX_CONTINUOUS_UNCHANGED 100
#define MAX_ITEM 1000

int count_items;
double weight[MAX_ITEM], value[MAX_ITEM];
string item_name[MAX_ITEM];
double max_weight;