#include <bits/stdc++.h> 
#define inf 1000000      
using namespace std;     
const int V = 1005;
const int E = 10005;
int n,m,nbPopulation = 26;
map<vector<int>,int> memo_value; // Memoization map to store the value of each path
int graph[V][V];
vector<int> bstSol;
vector<vector<int>> par,child;
int idx; //index of every city, useful for the encoding function
map<string,int> encod;
map<int,string> decod;


void init()
{
    idx = 0;
    for(int i=0; i<n; ++i)
    {
        for(int j=0; j<n; ++j)
        {
            graph[i][j] = inf; // initially we haven't any edge
        }
    }
}

void addBiEdge(int u,int v,int c)
{
    graph[u][v] = c;
    graph[v][u] = c;
}

void encoding()
{
    ifstream cin("mygraphout");
    cin>>n>>m;
    init();
    for(int i=0; i<m; ++i)
    {
        string city1 , city2;
        int distance;
        cin>>city1>>city2>>distance;
        if(!encod.count(city1)) // if a city doesn't have an index yet
        {
            encod[city1] = idx;
            decod[idx++] = city1;
        }
        if(!encod.count(city2))
        {
            encod[city2] = idx;
            decod[idx++] = city2;
        }
        addBiEdge(encod[city1],encod[city2],distance); // we use the index of each node to add a bidrectional edge to our graph representation
    }
}


vector<int> gen() // Complexity O(n)
{
    vector<int> myvector;
    for(int i=0; i<n; ++i) myvector.push_back(i);
    random_shuffle ( myvector.begin(), myvector.end() ); // Random shuffling to generate population
    return myvector;
}



vector<int> makeOrd(vector<int> v){
    int n = v.size();
    vector<int> ord(n);
    for (int i =0; i < n; ++i){
        ord[v[i]] = i;
    }
    return ord;
}

vector<int> cloneVector(vector<int> v){
    vector<int> clone(v.size());
    for (int i = 0; i < v.size(); ++i) clone[i] = v[i];
    return clone;
}
vector<int> crossover(vector<int> &p1, vector<int> &p2){
    int n = p1.size();
    vector<int> o1, p1clone;
    o1 = makeOrd(p1);
    p1clone = cloneVector(p1);
    int left = rand() % n, right = rand() % n;
    for (int i = left; i <= right; ++i){
        int tmp1 = o1[p2[i]];
        swap(p1clone[tmp1], p1clone[i]);
    }
    return p1clone;
}
int evaluation(vector<int> v) //Complexity O(n)
{
    int ret = 0 ;
    for (int i=0; i<n-1 ;i++)
    {
        ret +=graph[v[i]][v[i+1]]; // counting the sum of weights of edges represented by the nodes in the array v
    }
    ret += graph[v[n-1]][v[0]];
    return ret ;
}

vector<int> mutation(vector<int> &vv)
{
    vector<int> v = vv;
    int ind1 = rand()%n; // first index
    int ind2(ind1); // second index
    while(ind2 == ind1)
    {
        ind2 = rand()%n;
    }
    // ind1 is always less than ind2
    if(ind1>ind2) swap(ind1,ind2);
    reverse(v.begin()+ind1,v.begin()+ind2+1);
    return v;
}

int optimalSolution(int n) // brute force solution computes all the possible paths and return the best
{                       // Complexity O(n!) ==> Only works for small graphs ( n < 11 )
    vector<int> g;
    g.clear(); g.resize(n);
    for(int i=0;i<n;++i) g[i] = i;
    int ret(4*inf);
    while(next_permutation(g.begin() , g.end()))
    {
        ret = min(ret,evaluation(g));
    }
    return ret;
}

void population_generate() // Complexity O(n * nbPopulation)
{
    nbPopulation += 4 - nbPopulation%4; // nbPopulation will be always a multiple of 4
    par.clear(); par.resize(nbPopulation);
    for(int i=0;i<nbPopulation;++i)
    {
        par[i] = gen();
    }
}

bool cmp(const vector<int> &v1 , const vector<int> &v2) // Comparator that will be useful to sort the population according to their value
{
    return (memo_value[v1]<memo_value[v2]);
}

void population_evaluate() // Complexity O( nbPopulation * log²(nbPopulation))
{                          // Complexity without memoization O(nbPopulation * n * log(nbPopulation))
    for(int i=0;i<nbPopulation ; ++i)
    {
        memo_value[par[i]] = evaluation(par[i]);
    }
    sort(par.begin(),par.end(),cmp);
    bstSol = par[0];
    for(int i=0 ; i<nbPopulation/2; ++i)
    {
        par.pop_back(); // eliminate last ranked populations after the sort operation
    }
}


void population_crossover()
{
    int nn = (int)par.size();
    for(int i=0;i<nn-1;i+=2) // for each consecutive couple in the population we do their crossover
    {
        par.push_back(crossover(par[i],par[i+1]));
    }
}

void population_mutation()
{
    for(int i=0;i<nbPopulation/4;++i) // We do the mutation only for the best solutions to have a effcient genotype
    {
       par.push_back(mutation(par[i]));
    }
}

void decoding(vector<int> v)
{
    for(int i=0;i<(int)v.size() ; ++i)
    {
        cout<<decod[v[i]]<<" ";
        if(i < v.size()) cout<<"--> ";
    }
    cout<<decod[v[0]];
}




int main()
{
    encoding();
    population_generate();
    population_evaluate();
    int cur_best_solution = evaluation(par[0]); // current best solution of the population taken
    int last_best_solution(-1);
    int nb_iteration = 1;
    int infinite_iterations = (int)1e6; // limit of number of iterations to avoid infinit loop
    int consecutive_not_update = 100;
    while((consecutive_not_update) && (infinite_iterations--))
    {
        if (last_best_solution == cur_best_solution) --consecutive_not_update;
        else consecutive_not_update = 100;
        last_best_solution = cur_best_solution;
        population_crossover();
        population_mutation();
        population_evaluate();
        cur_best_solution = evaluation(par[0]); // par[0] is the best solution in the population because
        nb_iteration++;                         //  of the sort operation in population_evaluate function
    }
    cout<<"Number of iterations = "<<nb_iteration<<endl;
    cout<<"Genetic algorithm solution weight: "<<evaluation(bstSol)<<endl;
    cout<<"Genetic algorithm's outputed path : ";
    decoding(bstSol);
    cout << endl << evaluation({0, 24, 23, 22, 25, 21, 20, 16, 17, 19, 18, 15, 10, 11, 12, 14, 13, 9, 8, 7, 6, 4, 5, 3, 2, 1}) << endl;
    //cout<<endl<<"Optimal solution weight: "<<optimalSolution(n)<<endl;
    return 0;
}