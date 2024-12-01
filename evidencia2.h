/* evidencia2.h
 * Alonso Huerta, Jose Guerrero, Hector Arroyo
 */

#ifndef EVIDENCIA2_H
#define EVIDENCIA2_H

#include <vector>
#include <string>

//Esta estructura representa una edge con un peso
struct Edge {
    int src, dest, weight;
    Edge(int s, int d, int w) : src(s), dest(d), weight(w) {}
};

//Estructura para un punto
struct Point {
    int x, y;
    Point(int _x = 0, int _y = 0) : x(_x), y(_y) {}
};

//Disjoint Set data structure
class DisjointSet {
    std::vector<int> parent, rank;
public:
    DisjointSet(int n);
    int find(int x);
    void unite(int x, int y);
};

std::vector<Edge> kruskalMST(std::vector<Edge>& edges, int V);
double distance(const Point& p1, const Point& p2);
Point findNearestCentral(const std::vector<Point>& centrals, const Point& newPoint);

#endif

