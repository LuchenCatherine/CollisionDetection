#include "algo.h"
bool MySearchCallback(ValueType id)
{
//   std::cout << "Hit data rect " << id << "\n";
  return true; // keep going
}

void rtree_aabb(std::vector<Mymesh> meshes, std::vector<Tree*>& aabbtrees, std::vector<std::string>& parts, Mymesh tissue, Tree* tissue_tree, int size, int AS)
{

    rtree_3 rtree;
    CGAL::Bbox_3 bb;

    for (int i = 0; i < AS; ++i)
    {
        double min[3], max[3];
        bb = PMP::bbox(meshes[i % size].get_raw_mesh());
        min[0] = bb.xmin();
        min[1] = bb.ymin();
        min[2] = bb.zmin();
        max[0] = bb.xmax();
        max[1] = bb.ymax();
        max[2] = bb.zmax();

        rtree.Insert(min, max, i);
    }

    bb = PMP::bbox(tissue.get_raw_mesh());
    double search_min[3] = {bb.xmin(), bb.ymin(), bb.zmin()};
    double search_max[3] = {bb.xmax(), bb.ymax(), bb.zmax()};
    
    std::vector<int> hits;
    hits = rtree.Search2(search_min, search_max, MySearchCallback);

    std::vector<std::string> collision_parts;
    std::cout << "two levels starts" << std::endl;
    clock_t start = clock();


    for (int i: hits)
    {
        clock_t tmp_start = clock();
        Tree* tree = aabbtrees[i % size];
        if (tree->do_intersect(*tissue_tree))
        {
            // std::cout << "kidney_part_" << parts[i] << " collides with tissue, running time is "<< 1.0* (clock() - tmp_start)/CLOCKS_PER_SEC << '\n';
            collision_parts.push_back(parts[i % size]);

        }
        else
        {
            // std::cout << "kidney_part_" << parts[i] << " does not collide with tissue, running time is "<< 1.0* (clock() - tmp_start)/CLOCKS_PER_SEC << '\n';
        }
    }

    clock_t end = clock();
    std::cout << "two levels ends" << std::endl;
    std::cout << "two levels running time is " << 1.0* (end - start)/CLOCKS_PER_SEC << " seconds" << std::endl;
    
    // std::cout << "collision part index: ";
    // for (std::string part: collision_parts)
    // {
    //     std::cout << part << " ";
    // }
    std::cout << std::endl;

}


void openmp_aabb(std::vector<Tree*>& aabbtrees, std::vector<std::string>& parts, Tree* tissue_tree, int size, int AS)
{

    std::vector<std::string> collision_parts_parallel;
    std::cout << "parallel starts \n";
    // clock_t parallel_start = clock();
    auto start = std::chrono::high_resolution_clock::now();

    #pragma omp parallel
    {
        std::vector<std::string> collision_parts_private;
        #pragma omp for nowait  
        for (int i = 0; i < AS; ++i)
        {
            clock_t tmp_start = clock();
            Tree* tree = aabbtrees[i % size];
            if (tree->do_intersect(*tissue_tree))
            {
                // std::cout << "kidney_part_" << parts[i] << " collides with tissue, running time is "<< 1.0* (clock() - tmp_start)/CLOCKS_PER_SEC << '\n';
                collision_parts_private.push_back(parts[i % size]); 
            }
            else
            {
                // std::cout << "kidney_part_" << parts[i] << " does not collide with tissue, running time is "<< 1.0* (clock() - tmp_start)/CLOCKS_PER_SEC << '\n';
            }

        }

        #pragma omp critical
        collision_parts_parallel.insert(collision_parts_parallel.end(), collision_parts_private.begin(), collision_parts_private.end());

    }

    // clock_t parallel_end = clock();
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start; 

    std::cout << "parallel ends" << std::endl;
    // std::cout << "parallel total running time is " << 1.0*(parallel_end - parallel_start) / CLOCKS_PER_SEC << std::endl;
    std::cout << "parallel total running time is " << duration.count() << std::endl;
    // std::cout << "collision part index: ";
    // for (std::string part: collision_parts_parallel)
    // {
    //     std::cout << part << " ";
    // }
    std::cout << std::endl;


}


void only_aabb(std::vector<Tree*>& aabbtrees, std::vector<std::string>& parts, Tree* tissue_tree, int size, int AS)
{
    std::vector<std::string> collision_parts;
    std::cout << "non parallel starts" << std::endl;
    // clock_t start = clock();
    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < AS; ++i)
    {
        clock_t tmp_start = clock();
        Tree* tree = aabbtrees[i % size];
        if (tree->do_intersect(*tissue_tree))
        {
            // std::cout << "kidney_part_" << parts[i] << " collides with tissue, running time is "<< 1.0* (clock() - tmp_start)/CLOCKS_PER_SEC << '\n';
            collision_parts.push_back(parts[i%size]);

        }
        else
        {
            // std::cout << "kidney_part_" << parts[i] << " does not collide with tissue, running time is "<< 1.0* (clock() - tmp_start)/CLOCKS_PER_SEC << '\n';
        }
    }

    // clock_t end = clock();
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start; 
    std::cout << "non parallel ends" << std::endl;
    // std::cout << "non parallel running time is " << 1.0* (end - start)/CLOCKS_PER_SEC << " seconds" << std::endl;
    std::cout << "non parallel running time is " << duration.count() << " seconds" << std::endl;
    
    // std::cout << "collision part index: ";
    // for (std::string part: collision_parts)
    // {
    //     std::cout << part << " ";
    // }
    std::cout << std::endl;
}

void brute_force(std::vector<std::vector<Triangle>>& faces_mesh, std::vector<std::string>& parts, std::vector<Triangle> tissue_faces, int size, int AS)
{
        // brute-force method, e.g., test every pair of triangles intersect or not
    std::vector<std::string> collision_parts_bf;
    std::cout << "brute force starts" << std::endl;
    clock_t start_itst_bf = clock();

    for (int i = 0; i < AS; ++i)
    {
        if (intersection_brute_force(faces_mesh[i%size], tissue_faces))
        {
            collision_parts_bf.push_back(parts[i%size]);
        }
    }
    clock_t end_itst_bf = clock();

    std::cout << "brute force ends " << std::endl;
    std::cout << "brute force running time is " << 1.0*(end_itst_bf - start_itst_bf)/CLOCKS_PER_SEC << " seconds" << std::endl;

    std::cout << "collision part index: ";
    for (std::string part: collision_parts_bf)
    {
        std::cout << part << " ";
    }
    std::cout << std::endl;
}



struct Rect
{
  Rect()  {}

  Rect(int a_minX, int a_minY, int a_maxX, int a_maxY)
  {
    min[0] = a_minX;
    min[1] = a_minY;

    max[0] = a_maxX;
    max[1] = a_maxY;
  }


  int min[2];
  int max[2];
};

struct Rect rects[] =
{
  Rect(0, 0, 2, 2), // xmin, ymin, xmax, ymax (for 2 dimensional RTree)
  Rect(5, 5, 7, 7),
  Rect(8, 5, 9, 6),
  Rect(7, 1, 9, 2),
};

int nrects = sizeof(rects) / sizeof(rects[0]);

Rect search_rect(6, 4, 10, 6); // search will find above rects that this one overlaps

