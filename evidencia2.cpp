#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>
using namespace std;

//Esta estructura representa una edge con un peso
struct Edge {
    int src, dest, weight;
    Edge(int s, int d, int w) : src(s), dest(d), weight(w) {}
};

//Disjoint Set data structure
class DisjointSet {
    vector<int> parent, rank;
public:
    DisjointSet(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for(int i = 0; i < n; i++) parent[i] = i;
    }
    
    int find(int x) {
        if(parent[x] != x)
            parent[x] = find(parent[x]);
        return parent[x];
    }
    
    void unite(int x, int y) {
        int px = find(x), py = find(y);
        if(rank[px] < rank[py])
            parent[px] = py;
        else if(rank[px] > rank[py])
            parent[py] = px;
        else {
            parent[py] = px;
            rank[px]++;
        }
    }
};

vector<Edge> kruskalMST(vector<Edge>& edges, int V) {
    //Sorteamos las edges por peso
    sort(edges.begin(), edges.end(), 
        [](Edge& a, Edge& b) { return a.weight < b.weight; });
    
    vector<Edge> result;
    DisjointSet ds(V);
    
    for(Edge& e : edges) {
        int set1 = ds.find(e.src);
        int set2 = ds.find(e.dest);
        
        if(set1 != set2) {
            result.push_back(e);
            ds.unite(set1, set2);
        }
    }
    return result;
}


//Estructura para un punto
struct Point {
    int x, y;
    Point(int _x = 0, int _y = 0) : x(_x), y(_y) {}
};

//calcular distancia entre dos puntos
double distance(const Point& p1, const Point& p2) {
    return sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2));
}

// Función para encontrar la central más cercana
Point findNearestCentral(const vector<Point>& centrals, const Point& newPoint) {
    Point nearest = centrals[0];
    double minDist = distance(centrals[0], newPoint);
    
    for(size_t i = 1; i < centrals.size(); i++) {
        double dist = distance(centrals[i], newPoint);
        if(dist < minDist) {
            minDist = dist;
            nearest = centrals[i];
        }
    }
    return nearest;
}


void problemaResuelto1(ifstream& file){
    const int V = 4;
    vector<vector<int>> matrixEj1(V, vector<int>(V));
    
    //Solo lee las primeras 4 líneas (primera matriz)
    string line;
    for(int i = 0; i < V && getline(file, line); i++) {
        istringstream iss(line);
        for(int j = 0; j < V; j++) {
            iss >> matrixEj1[i][j];
        }
    }
    
    //Convertimos matrixEj1 a una lista de edges
    vector<Edge> edges;
    for(int i = 0; i < V; i++) {
        for(int j = i + 1; j < V; j++) {
            if(matrixEj1[i][j] != 0) {
                edges.push_back(Edge(i, j, matrixEj1[i][j]));
            }
        }
    }
    
    //LLamamos a la función kruskalMST
    vector<Edge> mst = kruskalMST(edges, V);
    
    //Printeamos el primer resultado como lo piden en el ejercicio
    cout << "1." << endl;
    for(Edge& e : mst) {
        char src = 'A' + e.src;
        char dest = 'A' + e.dest;
        cout << "(" << src << ", " << dest << ")" << endl;
    }
}


void problemaResuelto4(ifstream& file) {
    vector<Point> centrals;
    string line;
    
    //Skipeamos la primera matriz
    for(int i = 0; i < 4; i++) {
        getline(file, line);
    }
    
    //Skipeamos la linea vacia
    getline(file, line);
    
    //Skipeamos la primera matriz
    for(int i = 0; i < 4; i++) {
        getline(file, line);
    }
    
    //Skipeamos la linea vacia
    getline(file, line);
    
    //Leemos las coordenas de las centrales
    for(int i = 0; i < 4; i++) {
        getline(file, line);
        if(!line.empty()) {
            int x, y;
            sscanf(line.c_str(), "(%d,%d)", &x, &y);
            centrals.push_back(Point(x, y));
        }
    }
    
    // Skipeamos line
    getline(file, line);
    
    // Leemos el punto nuevo
    getline(file, line);
    int x, y;
    sscanf(line.c_str(), "(%d,%d)", &x, &y);
    Point newPoint(x, y);
    
    //Encontramos central más cercana
    Point nearest = findNearestCentral(centrals, newPoint);
    
    cout << "4.\n";
    cout << "(" << nearest.x << ", " << nearest.y << ")" << endl;
}

int main() {
    ifstream file("input.txt");
    if (!file.is_open()) {
        cout << "Error al abrir el archivo" << endl;
        return 1;
    }
    
    problemaResuelto1(file);
    file.close();
    
    file.open("input.txt");
    problemaResuelto4(file);
    file.close();
    
    return 0;
}