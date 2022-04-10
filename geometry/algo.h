#ifndef ALGO_H_
#define ALGO_H_

#include "mymesh.h"
#include "RTree.h"
#include<iostream>
#include<vector>
#include<chrono>

typedef RTree<int, double, 3, double> rtree_3;
typedef int ValueType;

std::vector<int> collision_detection(std::vector<Tree*>& organ_aabbtrees, std::vector<Tree*>& tissue_aabbtrees);

std::vector<int> collision_detection_2(std::vector<Tree*>& organ_aabbtrees, std::vector<Tree*>& tissue_aabbtrees);

std::vector<int> collision_detection_3(std::vector<std::vector<Triangle>>& organ_faces, std::vector<std::vector<Triangle>>& tissue_faces);

bool MySearchCallback(ValueType id);

void rtree_aabb(std::vector<Mymesh> meshes, std::vector<Tree*>& aabbtrees, std::vector<std::string>& parts, Mymesh tissue, Tree* tissue_tree, int size, int AS);

void openmp_aabb(std::vector<Tree*>& aabbtrees, std::vector<std::string>& parts, Tree* tissue_tree, int size, int AS);

void only_aabb(std::vector<Tree*>& aabbtrees, std::vector<std::string>& parts, Tree* tissue_tree, int size, int AS);

void brute_force(std::vector<std::vector<Triangle>>& faces_mesh, std::vector<std::string>& parts, std::vector<Triangle> tissue_faces, int size, int AS);

#endif