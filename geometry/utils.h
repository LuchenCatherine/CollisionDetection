// Lu Chen, 04/07/2022

#pragma once

#include <iostream>
#include <vector>
#include <string>
#include "mymesh.h"

#include<boost/filesystem.hpp>
using namespace boost::filesystem;

void load_organ_meshes(std::string input_path, std::vector<Mymesh>& meshes);
void load_tissue_meshes(std::string input_path, std::vector<Mymesh>& meshes);
void build_indexes(std::vector<Mymesh>& meshes, std::vector<Tree*>& aabbtrees);
void extract_faces_array(std::vector<Mymesh>& meshes, std::vector<std::vector<Triangle>> faces);
void print(std::vector<int> array);
void cleanup(std::vector<Tree*>& organ_aabbtrees, std::vector<Tree*> tissue_aabbtrees);
