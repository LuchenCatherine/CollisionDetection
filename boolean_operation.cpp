// Lu Chen, 4/2/2022

#include<iostream>
#include<string>
#include<boost/filesystem.hpp>

using namespace boost::filesystem;

#include<mymesh.h>


void load_meshes(std::string input_path, std::vector<Mymesh>& meshes)
{
    for (directory_entry& entry : directory_iterator(input_path)) 
    {
        Mymesh m;
        m.load_from_off(input_path);
        meshes.push_back(m);
    }
}

std::vector<int> collision_detection()
{

}

void cleanup()
{

}

int main(int argc, char** argv)
{
    std::string input_path = std::string(argv[1]);
    for (directory_entry& entry : directory_iterator(input_path))
    {
        std::cout << entry.path().string() << std::endl;
    }

    std::vector<Mymesh> meshes;
    load_meshes(input_path, meshes);


    collision_detection();

    cleanup();


    
    return 0;
}

