// Lu Chen, 4/2/2022

#include<iostream>
#include<string>
#include<boost/filesystem.hpp>
#include "algo.h"
using namespace boost::filesystem;

#include<mymesh.h>


void load_organ_meshes(std::string input_path, std::vector<Mymesh>& meshes)
{
    for (directory_entry& entry : directory_iterator(input_path)) 
    {
        Mymesh m;
        std::string path = entry.path().string();
        // std::cout << path << std::endl;
        m.load_from_off(path);
        meshes.push_back(m);
    }
}


void load_tissue_mesh(std::string input_path, Mymesh& mesh)
{
    mesh.load_from_off(input_path);
    mesh.triangulate_mesh();
}


void build_organ_indexes(std::vector<Mymesh>& meshes, std::vector<Tree*>& aabbtrees)
{
    for (int i = 0; i < meshes.size(); ++i)
    {
        Tree* tree = meshes[i].create_aabb_tree();
        aabbtrees.push_back(tree);
    }

}



void build_tissue_index(Mymesh& tissue_mesh, Tree*& tissue_aabbtree)
{
    tissue_aabbtree = tissue_mesh.create_aabb_tree();

}


std::vector<int> collision_detection(std::vector<Tree*>& organ_aabbtrees, Tree* tissue_aabbtree)
{
    std::vector<int> collision_parts_parallel;
    auto t1 = std::chrono::high_resolution_clock::now();
    #pragma omp parallel
    {
        std::vector<int> collision_parts_private;
        #pragma omp for nowait  
        for (int i = 0; i < organ_aabbtrees.size(); ++i)
        {
            Tree* tree = organ_aabbtrees[i];
            if (tree->do_intersect(*tissue_aabbtree))
            {
                // std::cout << "kidney_part_" << parts[i] << " collides with tissue, running time is "<< 1.0* (clock() - tmp_start)/CLOCKS_PER_SEC << '\n';
                collision_parts_private.push_back(i); 
            }

        }

        #pragma omp critical
        collision_parts_parallel.insert(collision_parts_parallel.end(), collision_parts_private.begin(), collision_parts_private.end());
    }
    auto t2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration2 = t2 - t1;
    std::cout << "parallel running time is " << duration2.count() << " seconds" << std::endl;  
    // std::vector<int> collision_parts;
    // std::cout << "non parallel starts" << std::endl;
    // // clock_t start = clock();
    // auto start = std::chrono::high_resolution_clock::now();

    // for (int i = 0; i < organ_aabbtrees.size(); ++i)
    // {
    //     Tree* tree = organ_aabbtrees[i];
    //     if (tree->do_intersect(*tissue_aabbtree))
    //     {
    //         // std::cout << "kidney_part_" << parts[i] << " collides with tissue, running time is "<< 1.0* (clock() - tmp_start)/CLOCKS_PER_SEC << '\n';
    //         collision_parts.push_back(i);

    //     }
    //     else
    //     {
    //         // std::cout << "kidney_part_" << parts[i] << " does not collide with tissue, running time is "<< 1.0* (clock() - tmp_start)/CLOCKS_PER_SEC << '\n';
    //     }
    // }

    return collision_parts_parallel;

}

void cleanup(std::vector<Tree*>& organ_aabbtrees, Tree* tissue_aabbtree)
{

    for (int i = 0; i < organ_aabbtrees.size(); i++) delete organ_aabbtrees[i];
    delete tissue_aabbtree;
}


void print(std::vector<int> array)
{
    for (int i: array) printf("%d ", i);
    printf("\n");
}


int main(int argc, char** argv)
{
    //init
    std::vector<Mymesh> organ_meshes;
    std::vector<Tree*> organ_aabbtrees;
    Mymesh tissue_mesh;
    Tree* tissue_aabbtree;

    // std::string input_organ_path = std::string(argv[1]);
    // std::string input_tissue_path = std::string(argv[2]);
    
    std::string input_organ_path = std::string("/home/catherine/Research/CollisionDetection/collision_detection_kidney/models/kidney_AS/");
    std::string input_tissue_path = std::string("/home/catherine/Research/CollisionDetection/collision_detection_kidney/models/tissue/tissue2.off");
    std::vector<std::string> parts = {"2", "4", "5", "7", "8", "9", "10", "11", "13", "15", "17"};

    auto start = std::chrono::high_resolution_clock::now();
    load_organ_meshes(input_organ_path, organ_meshes);
    build_organ_indexes(organ_meshes, organ_aabbtrees);

    load_tissue_mesh(input_tissue_path, tissue_mesh);
    build_tissue_index(tissue_mesh, tissue_aabbtree);
    
    auto t1 = std::chrono::high_resolution_clock::now();
    
    std::vector<int> result = collision_detection(organ_aabbtrees, tissue_aabbtree);
    auto t2 = std::chrono::high_resolution_clock::now();
    print(result);
    std::chrono::duration<double> duration1 = t1 - start;
    std::chrono::duration<double> duration2 = t2 - t1;

    std::cout << "loading time is " << duration1.count() << " seconds" << std::endl;  
    std::cout << "parallel running time is " << duration2.count() << " seconds" << std::endl;  
    
    cleanup(organ_aabbtrees, tissue_aabbtree);

    return 0;
}

