
#ifndef EVIDENCIA2_H
#define EVIDENCIA2_H

#include <vector>
#include <string>

/**
  Esta estructura representa una edge con un peso
 */
struct Edge {
    /**
     * Constructor
     */
    Edge(int s, int d, int w) : src(s), dest(d), weight(w) {}

    int src; ///< Fuente de la Edge
    int dest; ///< Destino de la Edge
    int weight; ///< Peso de la Edge
};

/** 
 * Estructura para un punto
 */
struct Point {
    /**
     * Constructor
     */
    Point(int _x = 0, int _y = 0) : x(_x), y(_y) {}
    int x; ///< Coordenada x
    int y; ///< Coordenada y
};

/**
 * Disjoint Set data structure
 */
class DisjointSet {
    std::vector<int> parent; ///< Vector de padres
    std::vector<int> rank; ///< Vector de rangos
public:
    /**
     * Constructor
     */
    DisjointSet(int n);

    /**
     *  Encuentra el padre de un elemento
     */
    int Find(int x);

    /**
     * Une dos elementos
     */
    void Unite(int x, int y);
};

/**
 * Algoritmo de kruskal
 */
std::vector<Edge> kruskal_mst(std::vector<Edge>& edges, int V);

/**
 * Calcular distancia entre dos puntos
 */
double distance(const Point& p1, const Point& p2);

/**
 * Encontrar la central mas cercana
 */
Point find_nearest_central(const std::vector<Point>& centrals, const Point& newPoint);

#endif
