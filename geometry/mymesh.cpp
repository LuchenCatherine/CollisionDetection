#include "mymesh.h"

bool Mymesh::load_from_off(std::string file_path) {
    
    std::ifstream input(file_path);

    if (!input ||!(input >> this->mesh) || this->mesh.is_empty()){
        std::cerr << "Not a valid mesh" << std::endl;
        return false;
    }

    return true;

}


bool Mymesh::triangulate_mesh() {

    PMP::triangulate_faces(this->mesh);

    //confirm all faces are triangles

    for (boost::graph_traits<Surface_mesh>::face_descriptor fit : faces(mesh)) {
        
        if (next(next(halfedge(fit, mesh), mesh), mesh) 
                != prev(halfedge(fit, mesh), mesh)){
            std::cerr << "Error: non-triangular face left in mesh." << std::endl;

            return false;
        }
    }

    return true;

}


bool Mymesh::is_closed_mesh() {
    std::cout << "still exist" << std::endl;
    return true;
}

bool Mymesh::point_inside(Point& query)
{
    Point_inside inside_tester(*aabbTree);
    return inside_tester(query) == CGAL::ON_BOUNDED_SIDE;
}

Tree* Mymesh::create_aabb_tree() {

        // std::unique_ptr<Tree> tree = std::make_unique<Tree> (faces(mesh).first, faces(mesh).second, mesh);
        Tree* tree = new Tree(faces(mesh).first, faces(mesh).second, mesh);
        tree->accelerate_distance_queries();

        return tree;

}

float Mymesh::compute_intersection_volume(Mymesh& other_mesh, std::string output_file_path)
{
    Surface_mesh intersect_mesh;
    bool result = PMP::corefine_and_compute_intersection(mesh, other_mesh.get_raw_mesh(), intersect_mesh);
    if (!result) return 0.0f;

    save_as_off(output_file_path, intersect_mesh);
    return PMP::volume(intersect_mesh);

}


Surface_mesh& Mymesh::get_raw_mesh()
{
    return mesh;
}


vector<Triangle> Mymesh::extract_faces() {

    vector<Triangle> triangles;

    for (auto f: mesh.faces()) {
        halfedge_descriptor hd = halfedge(f, mesh);
        Point p1 = mesh.point(source(hd, mesh));
        Point p2 = mesh.point(target(hd, mesh));
        Point p3 = mesh.point(target(next(hd, mesh), mesh));
        triangles.push_back(Triangle(p1, p2, p3));
    }

    return triangles;
    
}



// Tree* get_AABB_tree(Surface_mesh mesh) {

//     Tree* tree = new Tree(faces(mesh).first, faces(mesh).second, mesh);
//     return tree;
// }

int monte_carlo_volume(double x_min, double x_max, double y_min, double y_max, double z_min, double z_max, int nb_partition, Point_inside& inside_tester)
{
    double d_x, d_y, d_z;
    d_x = (x_max - x_min)/10;
    d_y = (y_max - y_min)/10;
    d_z = (z_max - z_min)/10;

    double d_v = d_x * d_y * d_z;
    double x, y, z;
    int nb_inside = 0;

    clock_t start_volume = clock();
    for (int i = 0; i < nb_partition; ++i)
    {
        for (int j = 0; j < nb_partition; ++j)
        {
            for (int k = 0; k < nb_partition; ++k)
            {
                x = x_min + 0.5 * d_x * (2*i + 1);
                y = y_min + 0.5 * d_y * (2*j + 1);
                z = z_min + 0.5 * d_z * (2*k + 1); 
                Point p(x, y, z);

                if (inside_tester(p) == CGAL::ON_BOUNDED_SIDE)
                    nb_inside++;

            }

        }
    }

    return nb_inside;
}

bool intersection_brute_force(std::vector<Triangle> faces1, std::vector<Triangle> faces2)
{

    for (auto it1=faces1.begin(); it1 != faces1.end(); ++it1)
    {
        for (auto it2=faces2.begin(); it2 != faces2.end(); ++it2)
        {
            if (CGAL::do_intersect(*it1, *it2))
                return true;
            
        }
    }

    return false;
}


bool save_as_off(std::string file_path, Surface_mesh& mesh)
{
    std::ofstream output(file_path);
    output << mesh;
    
    if (!output || !(output << mesh))
    {
        std::cerr << "Not a valid output" << std::endl;
        return false;
    }

    return true;

}