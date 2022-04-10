// Lu Chen, 4/2/2022

#include<iostream>
#include<string>

#include "omp.h"

#include "mymesh.h"
#include "utils.h"
#include "algo.h"


int main(int argc, char** argv)
{
    //init
    std::vector<Mymesh> organ_meshes;
    std::vector<Tree*> organ_aabbtrees;
    std::vector<Mymesh> tissue_meshes;
    std::vector<Tree*> tissue_aabbtrees;
    std::vector<std::vector<Triangle>> organ_faces;
    std::vector<std::vector<Triangle>> tissue_faces;

    // std::string input_organ_path = std::string(argv[1]);
    // std::string input_tissue_path = std::string(argv[2]);
    
    std::string input_organ_path = std::string("/home/catherine/Research/CollisionDetection/collision_detection_kidney/models/kidney_AS/");
    std::string input_tissue_path = std::string("/home/catherine/Research/CollisionDetection/collision_detection_kidney/models/tissue/");

    auto start = std::chrono::high_resolution_clock::now();
    load_organ_meshes(input_organ_path, organ_meshes);
    build_indexes(organ_meshes, organ_aabbtrees);

    load_tissue_meshes(input_tissue_path, tissue_meshes);
    build_indexes(tissue_meshes, tissue_aabbtrees);

    extract_faces_array(organ_meshes, organ_faces);
    extract_faces_array(tissue_meshes, tissue_faces);


    auto t1 = std::chrono::high_resolution_clock::now();
    
    std::vector<int> result = collision_detection(organ_aabbtrees, tissue_aabbtrees);
    auto t2 = std::chrono::high_resolution_clock::now();
    print(result);
    std::chrono::duration<double> duration1 = t1 - start;
    std::chrono::duration<double> duration2 = t2 - t1;

    double t3 = omp_get_wtime();
    std::cout << "loading time is " << duration1.count() << " seconds" << std::endl;  
    std::cout << "parallel running time is " << duration2.count() << " seconds" << std::endl;  
    
    cleanup(organ_aabbtrees, tissue_aabbtrees);

    return 0;
}

