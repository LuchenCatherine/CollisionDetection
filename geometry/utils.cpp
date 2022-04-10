
#include <utils.h>


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


void load_tissue_meshes(std::string input_path, std::vector<Mymesh>& meshes)
{
    for (directory_entry& entry : directory_iterator(input_path))
    {
        Mymesh m;
        std::string path = entry.path().string();
        // std::cout << path << std::endl;
        m.load_from_off(path);
        m.triangulate_mesh();
        meshes.push_back(m);
    }
}


void build_indexes(std::vector<Mymesh>& meshes, std::vector<Tree*>& aabbtrees)
{
    for (int i = 0; i < meshes.size(); ++i)
    {
        Tree* tree = meshes[i].create_aabb_tree();
        aabbtrees.push_back(tree);
    }

}


void extract_faces_array(std::vector<Mymesh>& meshes, std::vector<std::vector<Triangle>> faces)
{

    for (int i = 0; i < meshes.size(); ++i)
    {
        std::vector<Triangle> face = meshes[i].extract_faces();
        faces.push_back(face);
    }

}


void print(std::vector<int> array)
{
    for (int i: array) printf("%d ", i);
    printf("\n");
}

void cleanup(std::vector<Tree*>& organ_aabbtrees, std::vector<Tree*> tissue_aabbtrees)
{

    for (int i = 0; i < organ_aabbtrees.size(); i++) delete organ_aabbtrees[i];
    for (int i = 0; i < tissue_aabbtrees.size(); i++) delete tissue_aabbtrees[i];
}