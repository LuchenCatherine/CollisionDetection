#include "mymesh.h"
#include "omp.h"
#include <iostream>
#include <ctime>
#include "algo.h"
#include "RTree.h"
#include "./tinygltf/tiny_gltf.h"
// typedef CGAL::Side_of_triangle_mesh<Surface_mesh, Kernel> Point_inside;


int main()
{
    std::string kidney = "/home/catherine/Research/CollisionDetection/AABBTest/models/kidney/";
    std::string tissue_off_path = "/home/catherine/Research/CollisionDetection/AABBTest/models/tissue/tissue.off";
    std::vector<std::string> parts = {"2", "4", "5", "7", "8", "9", "10", "11", "13"};
    // std::vector<std::string> parts = {"5"};

    std::vector<Mymesh> meshes;
    std::vector<Tree*> aabbtrees;

    // load meshes of kidney
    for (std::string part: parts)
    {
        Mymesh m;
        std::string path = kidney + "kidney_part_" + part + ".off";
        m.load_from_off(path);
        meshes.push_back(m);
    }

    //load tissue mesh
    Mymesh tissue;
    tissue.load_from_off(tissue_off_path);

    // triangulate meshes
    for (auto m = meshes.begin(); m != meshes.end(); ++m)
    {
        m->triangulate_mesh();
    }
    tissue.triangulate_mesh();

    // build aabb tree for every mesh
    for (int i = 0; i < meshes.size(); ++i)
    {
        Tree* tree = meshes[i].create_aabb_tree();
        aabbtrees.push_back(tree);
    }
    
    std::vector<Triangle> tissue_faces = tissue.extract_faces();
    Tree* tissue_tree = tissue.create_aabb_tree();
    
    std::vector<std::vector<Triangle>> faces_mesh;
    for (int i = 0; i < meshes.size(); ++i)
    {
        std::vector<Triangle> faces = meshes[i].extract_faces();
        faces_mesh.push_back(faces);
    }


    int size, AS;
    size = aabbtrees.size(); 
    AS = 1000000;
    
    
    
    rtree_aabb(meshes, aabbtrees, parts, tissue, tissue_tree, size, AS);
    only_aabb(aabbtrees, parts, tissue_tree, size, AS);
    openmp_aabb(aabbtrees, parts, tissue_tree, size, AS);
    // brute_force(faces_mesh, parts, tissue_faces, size, AS);



    // volume computation
    // Point_inside inside_tester(*tree);
    // clock_t start_volume = clock();
    // double x_min, x_max, y_min, y_max, z_min, z_max;
    // x_min = 0.06136225;
    // x_max = 0.08136225;
    // y_min = 0.29237636;
    // y_max = 0.30237636;
    // z_min = -0.04712087;
    // z_max = -0.04412087;

    // Tree* aabbtree_part_2 = aabbtrees[0];
    // Tree* aabbtree_part_5 = aabbtrees[2];
    // Tree* aabbtree_part_9 = aabbtrees[5];
    // Point_inside inside_tester_2(*aabbtree_part_2);
    // Point_inside inside_tester_5(*aabbtree_part_5);
    // Point_inside inside_tester_9(*aabbtree_part_9);

    // int nb_voxels_2 = monte_carlo_volume(x_min, x_max, y_min, y_max, z_min, z_max, 10, inside_tester_2);
    // clock_t end_volume_2 = clock();
    // std::cout << "intersection volume between kidney_part_2 and tissue is " << nb_voxels_2 << std::endl;
    // std::cout << "the running time is " << 1.0* (end_volume_2 - start_volume)/CLOCKS_PER_SEC << " seconds" << std::endl;

    // int nb_voxels_5 = monte_carlo_volume(x_min, x_max, y_min, y_max, z_min, z_max, 10, inside_tester_5);
    // clock_t end_volume_5 = clock();
    // std::cout << "intersection volume between kidney_part_5 and tissue is " << nb_voxels_5 << std::endl;
    // std::cout << "the running time is " << 1.0* (end_volume_5 - end_volume_2)/CLOCKS_PER_SEC << " seconds" << std::endl;

    // int nb_voxels_9 = monte_carlo_volume(x_min, x_max, y_min, y_max, z_min, z_max, 10, inside_tester_9);
    // clock_t end_volume_9 = clock();
    // std::cout << "intersection volume between kidney_part_9 and tissue is " << nb_voxels_9 << std::endl;
    // std::cout << "the running time is " << 1.0* (end_volume_9 - end_volume_5)/CLOCKS_PER_SEC << " seconds" << std::endl;
    
    // // use boolean operation to compute volume of intersection
    // float tmp_volume;
    // std::string output_folder = "/home/catherine/Research/CollisionDetection/AABBTest/models/output/";
    // for (int i = 0; i < meshes.size(); ++i)
    // {
    //     clock_t start_bool_op = clock();
    //     tmp_volume = meshes[i].compute_intersection_volume(tissue, output_folder + "kidney_part_" + parts[i] + ".off");
    //     std::cout << "boolean operation: intersection volume between kidney_part_" << parts[i] << " and tissue is " << tmp_volume;
    //     std::cout << ", running time is: " << 1.0* (clock() - start_bool_op)/CLOCKS_PER_SEC << std::endl;        
    // }
    

    // delete aabb tree for every mesh
    for (int i = 0; i < aabbtrees.size(); ++i)
    {
        delete aabbtrees[i];
    }
    delete tissue_tree;
    
}