#include "evidencia2.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
using namespace std;


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
