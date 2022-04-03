#include "./geometry/mymesh.h"
#include <iostream>
#include <ctime>

typedef CGAL::Side_of_triangle_mesh<Surface_mesh, Kernel> Point_inside;

using namespace std;

int main() 
{

    string kidney_off_path = "/home/catherine/Research/CollisionDetection/models/kidney/counterpart2/kidney_part_5.off";
    string tissue_off_path = "/home/catherine/Research/CollisionDetection/models/kidney/counterpart2/tissue.off";

    string part[] = {"2", "4", "5", "7", "8", "9", "10", "11", "13"};
    Mymesh kidney_mesh;
    Mymesh tissue_mesh;

    kidney_mesh.load_from_off(kidney_off_path);
    tissue_mesh.load_from_off(tissue_off_path);

    kidney_mesh.triangulate_mesh();
    tissue_mesh.triangulate_mesh();

    Tree* tree = kidney_mesh.create_aabb_tree();
    bool intersected = false;

    clock_t start = clock();
    int count = 10;
    int n = 0;
    for (int i = 0; i < count; ++i)
    {
        for (Triangle triangle_face:tissue_mesh.extract_faces()) {

            // 
            if (tree->do_intersect(triangle_face)) {
                intersected = true;
                // cout << "the organ is intersected with tissue" << endl;
                break;
            }

        }
        if (i % 100 == 0)
            std::cout << i << std::endl;
    }
    
    clock_t end = clock();

    cout << "the running time is " << 1.0* (end - start)/count/CLOCKS_PER_SEC << " seconds" << endl;

    if (!intersected)
        cout << "the organ is not intersected with tissue" << endl;   
    else
        cout << "the organ is intersected with tissue" << endl; 

    int nb_inside = 0;
    Point query = Point(0.0, 0.0, 0.0);
    Point_inside inside_tester(*tree);
    for (int i = 0; i < count; i++)
    {
        if (inside_tester(query) == CGAL::ON_BOUNDED_SIDE)
            nb_inside++;
    }

    delete tree;
    // float vol = PMP::volume(kidney_mesh.get_raw_mesh());
    clock_t end2 = clock();
    cout <<  "the running time of point inside test is " << 1.0* (end2 - end)/CLOCKS_PER_SEC << " seconds" << endl;
    return 0;

}

