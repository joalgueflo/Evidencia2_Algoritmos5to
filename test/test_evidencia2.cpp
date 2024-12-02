
#include "test_wrapper.h"
#include "../evidencia2.h"

test(KruskalMST, BasicTest) {
    std::vector<Edge> edges = { Edge(0, 1, 10), Edge(0, 2, 6), Edge(0, 3, 5), Edge(1, 3, 15), Edge(2, 3, 4) };
    int V = 4;

    std::vector<Edge> mst = kruskal_mst(edges, V);

    ASSERT_EQ(mst.size(), V - 1);
    EXPECT_EQ(mst[0].weight, 4);
    EXPECT_EQ(mst[1].weight, 5);
}

test(DistanceFunction, PythagoreanTriple) {
    Point p1(0, 0), p2(3, 4);
    EXPECT_DOUBLE_EQ(distance(p1, p2), 5.0);
}

test(FindNearestCentral, SimpleTest) {
    std::vector<Point> centrals = { Point(0, 0), Point(10, 10), Point(5, 5) };
    Point newPoint(2, 2);

    Point nearest = find_nearest_central(centrals, newPoint);
    EXPECT_EQ(nearest.x, 0);
    EXPECT_EQ(nearest.y, 0);
}
