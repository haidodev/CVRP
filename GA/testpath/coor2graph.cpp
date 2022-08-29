#include<iostream>
#include<fstream>
#include<vector>
#include<cmath>
using namespace std;
double distance(int x1_coords, int y1_coords, int x2_coords, int y2_coords){
    double dis = (x1_coords - x2_coords) * (x1_coords - x2_coords) + (y1_coords - y2_coords) * (y1_coords - y2_coords);
    dis = sqrt(dis);
    return round(dis * 100.0) / 100.0;
}
int main(){
    fstream fi("coords");
    fstream fo("../mygraphout");
    int n;
    fi >> n;
    fo << n << "\t" << n * (n - 1) / 2 << endl;

    vector<vector<int>> coords(n, vector<int> (2,0));
    for (int i = 0; i < n; ++i){
        int cur, x_coords, y_coords;
        fi >> cur >> x_coords >> y_coords;
        coords[cur - 1] = {x_coords, y_coords};
    }
    for (int i = 0; i < n; ++i){
        for (int j = i + 1; j < n; ++j){
            fo <<i + 1 << " "<< j + 1 << " " << distance(coords[i][0], coords[i][1], coords[j][0], coords[j][1]) << endl;
        }
    }
}