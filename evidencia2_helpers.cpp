
#include "evidencia2.h"
#include <cmath>
#include <algorithm>
#include <vector>
#include <climits>

DisjointSet::DisjointSet(int n) {
    parent.resize(n);
    rank.resize(n, 0);
    for (int i = 0; i < n; i++) parent[i] = i;
}

int DisjointSet::Find(int x) {
    if (parent[x] != x)
        parent[x] = Find(parent[x]);
    return parent[x];
}

void DisjointSet::Unite(int x, int y) {
    int px = Find(x), py = Find(y);
    if (rank[px] < rank[py])
        parent[px] = py;
    else if (rank[px] > rank[py])
        parent[py] = px;
    else {
        parent[py] = px;
        rank[px]++;
    }
}

std::vector<Edge> kruskal_mst(std::vector<Edge>& edges, int V) {
	//Sorteamos las edges por peso
    std::sort(edges.begin(), edges.end(),
              [](Edge& a, Edge& b) { return a.weight < b.weight; });

    std::vector<Edge> result;
    DisjointSet ds(V);

    for (Edge& e : edges) {
        int set1 = ds.Find(e.src);
        int set2 = ds.Find(e.dest);

        if (set1 != set2) {
            result.push_back(e);
            ds.Unite(set1, set2);
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

// Función auxiliar para el TSP
int tsp(std::vector<std::vector<int>>& graph, std::vector<std::vector<int>>& dp, int visited, int pos, int n) {
    if (visited == (1 << n) - 1) {
        return graph[pos][0];
    }
    if (dp[visited][pos] != -1) {
        return dp[visited][pos];
    }
    int result = INT_MAX;
    for (int city = 0; city < n; city++) {
        if ((visited & (1 << city)) == 0) {
            int newCost = graph[pos][city] + tsp(graph, dp, visited | (1 << city), city, n);
            result = std::min(result, newCost);
        }
    }
    return dp[visited][pos] = result;
}

bool bfs(std::vector<std::vector<int>>& rGraph, int s, int t, std::vector<int>& parent) {
    int V = rGraph.size();
	std::vector<bool> visited(V, false);
	std::vector<int> queue;
    queue.push_back(s);
    visited[s] = true;
    parent[s] = -1;

    while (!queue.empty()) {
        int u = queue.front();
        queue.erase(queue.begin());
        for (int v = 0; v < V; v++) {
            if (!visited[v] && rGraph[u][v] > 0) {
                if (v == t) {
                    parent[v] = u;
                    return true;
                }
                queue.push_back(v);
                parent[v] = u;
                visited[v] = true;
            }
        }
    }
    return false;
}
