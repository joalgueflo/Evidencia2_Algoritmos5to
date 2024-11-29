#include "evidencia2.h"
#include <cmath>
#include <algorithm>

DisjointSet::DisjointSet(int n) {
    parent.resize(n);
    rank.resize(n, 0);
    for (int i = 0; i < n; i++) parent[i] = i;
}

int DisjointSet::find(int x) {
    if (parent[x] != x)
        parent[x] = find(parent[x]);
    return parent[x];
}

void DisjointSet::unite(int x, int y) {
    int px = find(x), py = find(y);
    if (rank[px] < rank[py])
        parent[px] = py;
    else if (rank[px] > rank[py])
        parent[py] = px;
    else {
        parent[py] = px;
        rank[px]++;
    }
}

std::vector<Edge> kruskalMST(std::vector<Edge>& edges, int V) {
	//Sorteamos las edges por peso
    std::sort(edges.begin(), edges.end(),
              [](Edge& a, Edge& b) { return a.weight < b.weight; });

    std::vector<Edge> result;
    DisjointSet ds(V);

    for (Edge& e : edges) {
        int set1 = ds.find(e.src);
        int set2 = ds.find(e.dest);

        if (set1 != set2) {
            result.push_back(e);
            ds.unite(set1, set2);
        }
    }
    return result;
}

//calcular distancia entre dos puntos
double distance(const Point& p1, const Point& p2) {
    return std::sqrt(std::pow(p2.x - p1.x, 2) + std::pow(p2.y - p1.y, 2));
}

// Función para encontrar la central más cercana
Point findNearestCentral(const std::vector<Point>& centrals, const Point& newPoint) {
    Point nearest = centrals[0];
    double minDist = distance(centrals[0], newPoint);

    for (size_t i = 1; i < centrals.size(); i++) {
        double dist = distance(centrals[i], newPoint);
        if (dist < minDist) {
            minDist = dist;
            nearest = centrals[i];
        }
    }
    return nearest;
}
