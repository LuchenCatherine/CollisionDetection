#ifndef ALGO_H_
#define ALGO_H_

#include "mymesh.h"
#include "RTree.h"
#include<iostream>
#include<vector>
#include<chrono>

typedef RTree<int, double, 3, double> rtree_3;
typedef int ValueType;

bool MySearchCallback(ValueType id);

void rtree_aabb(std::vector<Mymesh> meshes, std::vector<Tree*>& aabbtrees, std::vector<std::string>& parts, Mymesh tissue, Tree* tissue_tree, int size, int AS);

void openmp_aabb(std::vector<Tree*>& aabbtrees, std::vector<std::string>& parts, Tree* tissue_tree, int size, int AS);

void only_aabb(std::vector<Tree*>& aabbtrees, std::vector<std::string>& parts, Tree* tissue_tree, int size, int AS);

void brute_force(std::vector<std::vector<Triangle>>& faces_mesh, std::vector<std::string>& parts, std::vector<Triangle> tissue_faces, int size, int AS);

#endif