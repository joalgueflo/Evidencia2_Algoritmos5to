
#include "evidencia2.h"
#include "evidencia2_helpers.cpp"
#include <iostream>
#include <vector>
#include <climits>
using namespace std;

void problema_resuelto_1(int N, vector<vector<int>>& matrix) {
    vector<Edge> edges;
    for(int i = 0; i < N; i++) {
        for(int j = i + 1; j < N; j++) {
            if(matrix[i][j] != 0) {
                edges.push_back(Edge(i, j, matrix[i][j]));
            }
        }
    }
    
    vector<Edge> mst = kruskal_mst(edges, N);
    
    cout << "1." << endl;
    for(Edge& e : mst) {
        char src = 'A' + e.src;
        char dest = 'A' + e.dest;
        cout << "(" << src << ", " << dest << ")" << endl;
    }
}

void problema_resuelto_2(int N, vector<vector<int>>& matrix) {
    vector<vector<int>> dp(1 << N, vector<int>(N, -1));
    int cost = tsp(matrix, dp, 1, 0, N);
    cout << "2.\nRuta más corta: " << cost << endl;
}

void problema_resuelto_3(int N, vector<vector<int>>& capacity) {
    vector<vector<int>> rGraph = capacity;
    vector<int> parent(N);
    int max_flow = 0;
    
    while (bfs(rGraph, 0, N - 1, parent)) {
        int path_flow = INT_MAX;
        for (int v = N - 1; v != 0; v = parent[v]) {
            int u = parent[v];
            path_flow = min(path_flow, rGraph[u][v]);
        }
        for (int v = N - 1; v != 0; v = parent[v]) {
            int u = parent[v];
            rGraph[u][v] -= path_flow;
            rGraph[v][u] += path_flow;
        }
        max_flow += path_flow;
    }
    cout << "3.\nFlujo máximo: " << max_flow << endl;
}

void problema_resuelto_4(int N, vector<Point>& centrals, Point newPoint) {
    Point nearest = findNearestCentral(centrals, newPoint);
    cout << "4.\n";
    cout << "(" << nearest.x << ", " << nearest.y << ")" << endl;
}

int main() {
    // Input manual
    int N;
    cout << "Ingrese el número de colonias: ";
    cin >> N;
    
    // Primera matriz (distancias)
    cout << "Ingrese la matriz de distancias " << N << "x" << N << ":\n";
    vector<vector<int>> distanceMatrix(N, vector<int>(N));
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            cin >> distanceMatrix[i][j];
        }
    }
    
    // Segunda matriz (capacidades)
    cout << "Ingrese la matriz de capacidades " << N << "x" << N << ":\n";
    vector<vector<int>> capacityMatrix(N, vector<int>(N));
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            cin >> capacityMatrix[i][j];
        }
    }
    
    // Coordenadas de centrales
    vector<Point> centrals;
    cout << "Ingrese las " << N << " coordenadas de centrales (x,y):\n";
    for(int i = 0; i < N; i++) {
        int x, y;
        cout << "Central " << i+1 << ": ";
        char dummy;
        cin >> dummy >> x >> dummy >> y >> dummy; // Lee formato (x,y)
        centrals.push_back(Point(x, y));
    }
    
    // Punto nuevo
    int x, y;
    cout << "Ingrese el punto nuevo (x,y): ";
    char dummy;
    cin >> dummy >> x >> dummy >> y >> dummy;
    Point newPoint(x, y);
    
    // Llamada a las funciones
    problema_resuelto_1(N, distanceMatrix);
    problema_resuelto_2(N, distanceMatrix);
    problema_resuelto_3(N, capacityMatrix);
    problema_resuelto_4(N, centrals, newPoint);
    
    return 0;
}

