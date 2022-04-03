#include "./geometry/mymesh.h"
#include <iostream>
#include <ctime>

int main()
{
    Point a(0.06136225, 0.29237636, -0.04712087);
    Point b(0.08136225, 0.29237636, -0.04712087);
    Point c(0.08136225, 0.30237636, -0.04712087);

    Triangle triangle_query(a,b,c);
    std::string kidney_off_path = "/home/catherine/Research/CollisionDetection/models/kidney/counterpart2/kidney_part_2.off";

    Mymesh mesh;
    mesh.load_from_off(kidney_off_path);
    mesh.triangulate_mesh();
    Tree* tree = mesh.create_aabb_tree();
    clock_t start = clock();
    tree->do_intersect(triangle_query);
    clock_t end = clock();

    std::cout << end - start << std::endl;

}