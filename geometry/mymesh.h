#ifndef MYMESH_H_
#define MYMESH_H_

#include<CGAL/Simple_cartesian.h>

#include<CGAL/Surface_mesh.h>
#include<CGAL/polygon_mesh_processing.h>
#include<CGAL/AABB_face_graph_triangle_primitive.h>
#include <CGAL/Side_of_triangle_mesh.h>
#include<fstream>
#include<iostream>
#include<vector>

typedef CGAL::Simple_cartesian<double> Kernel;
typedef Kernel::Point_3 Point;
typedef Kernel::Triangle_3 Triangle;

typedef CGAL::Surface_mesh<Point> Surface_mesh;

typedef CGAL::AABB_face_graph_triangle_primitive<Surface_mesh> Primitive;
typedef CGAL::AABB_traits<Kernel, Primitive> Traits;
typedef CGAL::AABB_tree<Traits> Tree;
typedef Surface_mesh::Face_range Face_range;
typedef Surface_mesh::Halfedge_index halfedge_descriptor;
typedef CGAL::Side_of_triangle_mesh<Surface_mesh, Kernel> Point_inside;

namespace PMP = CGAL::Polygon_mesh_processing;
using std::vector;

class Mymesh{

    public:

        Mymesh(){};
        ~Mymesh(){};

        bool load_from_off(std::string file_path);
        bool triangulate_mesh();
        bool is_closed_mesh();
        bool point_inside(Point& query);

        Tree* create_aabb_tree();
        vector<Triangle> extract_faces();
        float compute_intersection_volume(Mymesh& other_mesh, std::string output_file_path);
        Surface_mesh& get_raw_mesh();
        
        
    private:
        Surface_mesh mesh;
        Tree* aabbTree;

};


// Tree* get_AABB_tree(Surface_mesh mesh);

int monte_carlo_volume(double x_min, double x_max, double y_min, double y_max, double z_min, double z_max, int nb_partition, Point_inside& inside_tester);
bool intersection_brute_force(std::vector<Triangle> faces1, std::vector<Triangle> faces2);
bool save_as_off(std::string file_path, Surface_mesh& mesh);



#endif