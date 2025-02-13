/////////////////////////////////////////////////////////////////////////////////
//
//
//                                  Utilities  
//
//
/////////////////////////////////////////////////////////////////////////////////
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/convex_hull_2.h>
#include <CGAL/Polygon_2.h>
#include <CGAL/intersections.h>
#include <algorithm>
#include <vector>
#include <numeric>
#include <string>
#include <chrono>
#include <ctime>
#include <cmath>
#include <fstream>
#include <sstream>

// New includes
#include <CGAL/Simple_cartesian.h>
#include <CGAL/Search_traits_2.h>
#include <CGAL/Orthogonal_k_neighbor_search.h>
#include <CGAL/Fuzzy_iso_box.h>

// Some typedefs for readability

typedef CGAL::Epick                                           K;
typedef K::Point_2                                            Point;
typedef CGAL::Segment_2<K>                                    Segment;
typedef CGAL::Object                                          Object;   
typedef CGAL::Polygon_2<K>                                    Polygon;
typedef CGAL::Triangle_2<K>                                   Triangle;
typedef Polygon::Vertex_iterator                              VertexIterator;
typedef Polygon::Vertex_circulator                            VertexCirculator;
typedef Polygon::Edge_const_circulator                        EdgeCirculator;
typedef Polygon::Edge_const_iterator                          EdgeIterator;
typedef std::vector<Point>                                    PointVector;
typedef std::vector<Segment>                                  SegmentVector;
typedef PointVector::iterator                                 pPointVector;
typedef SegmentVector::iterator                               pSegmentVector;
typedef std::string                                           String;    

// New typedefs
typedef std::vector<VertexCirculator>                         VertexCirculatorVector;
typedef VertexCirculatorVector::iterator                      pVertexCirculatorVector;

typedef CGAL::Search_traits_2<K> SearchTraits;
typedef CGAL::Orthogonal_k_neighbor_search<SearchTraits> Neighbor_search;
typedef Neighbor_search::Tree Tree;
typedef CGAL::Fuzzy_iso_box<SearchTraits> Box;



//______________________________Input/Output functions___________________________________


// Parses the file filename and returns a PointVector with the input points

PointVector parse_file(String filename);

// Output file function. Writes the results into the output file. 

void print_output(Polygon polygon_initial, 
                  Polygon polygon, 
                  PointVector points, 
                  std::string filename,
                  std::string algorithm_initial,
                  std::string algorithm,
                  std::string optimization, 
                  std::chrono::duration<double> duration);
//________________________________Printing functions______________________________________


// Prints a Point

void print_point(Point);

// Prints a Segment

void print_segment(Segment);

// Prints a Polygon

void print_polygon(Polygon);

// Prints a PointVector

void print_point_vector(PointVector points);

// Prints a SegmentVector

void print_segment_vector(SegmentVector segments);

//______________________________________________________________________

int position_of_point_in_polygon(Polygon polygon, Point point);

int position_of_segment_in_polygon(Polygon polygon, Segment segment);

// Compare Function for sorting point vectors.
bool comparePoints(Point a, Point b);


// Returns true if Metropolis criterion holds, false otherwise.
bool metropolis(double difference, double temperature);


// Computates the energy of the given polygon based on the convex hull area
// and uses the correct formula depending on the state of "minimalization" flag (true/false).
double compute_energy(Polygon polygon, double ch_area, bool minimalization);