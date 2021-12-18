// standard includes
#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>
#include <string>
#include <limits.h>
#include <queue>


// includes for defining the Voronoi diagram adaptor
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Voronoi_diagram_2.h>
#include <CGAL/Delaunay_triangulation_adaptation_traits_2.h>
#include <CGAL/Delaunay_triangulation_adaptation_policies_2.h>
#include <CGAL/draw_voronoi_diagram_2.h>
#include <CGAL/draw_triangulation_2.h>

using namespace std;

// typedefs for defining the adaptor
typedef CGAL::Exact_predicates_inexact_constructions_kernel                     K;
typedef CGAL::Delaunay_triangulation_2<K>                                       DT;
typedef CGAL::Delaunay_triangulation_adaptation_traits_2<DT>                    AT;
typedef CGAL::Delaunay_triangulation_caching_degeneracy_removal_policy_2<DT>    AP;
typedef CGAL::Voronoi_diagram_2<DT,AT,AP>                                       VD;

// typedef for the result type of the point location
typedef AT::Site_2                      Site_2;
typedef K::Point_2                      Point_2;

typedef VD::Locate_result             Locate_result;
typedef VD::Vertex_handle             Vertex_handle;
typedef VD::Face_handle               Face_handle;
typedef VD::Halfedge_handle           Halfedge_handle;
typedef VD::Ccb_halfedge_circulator   Ccb_halfedge_circulator;

// ABC vector used for assigning letters to numbered nodes
vector<char> ABC = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};

// Implementation of the Floyd-Warshall algorithm
// For each pair of nodes in a graph, we find the weight of the path with the smallest cost between them.
// Complexity: O(n^3).
void floydWarshall(vector<vector<int>> auxMatrix, int n){
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(auxMatrix[i][j]==-1){
                auxMatrix[i][j]=INT_MAX;
            }
        }
    }
    
    for(int k=0; k<n; k++){
        for(int i=0; i<n; i++){
            for(int j=0; j<n; j++){
                if(auxMatrix[i][k] != INT_MAX && auxMatrix[k][j] != INT_MAX){
                    auxMatrix[i][j] = min(auxMatrix[i][j], auxMatrix[i][k]+auxMatrix[k][j]);
                }
            }
        }
    }
    
    for(int j=0; j<n; j++){
        for(int k=0; k<n; k++){
            if(j!=k && j<k){
                if(auxMatrix[j][k]==INT_MAX){
                    cout << "(" << ::ABC[j%26] << ((j/26)>0? to_string(j/26):"") <<","<< ::ABC[k%26] << ((k/26)>0? to_string(k/26):"") << "): " <<  "INF" << endl;
                }else{
                    cout << "(" << ::ABC[j%26] << ((j/26)>0? to_string(j/26):"") <<","<< ::ABC[k%26] << ((k/26)>0? to_string(k/26):"") << "): " << auxMatrix[j][k] << endl;
                }
            }
        }
    }
}

// Implementation of the Repetitive Nearest Neighbor algorithm
// To solve the Traveling Salesman Problem (pseudo-optimally) we use a greedy algorithm to find the nearest neighbor for the given current node (start node is arbitrarily chosen). This process is repeated 'n' times (so that all nodes may at some point be the start node) and the shortest path is chosen.
// Complexity: O(n^3).
void repetitiveNearestNeighbor(vector<vector<int>> &auxMatrix, int n){
    vector<vector<string>> nodes(n);
    int path = INT_MAX;
    int vectorPos;
    
    for(int x=0; x<n; x++){
        bool visited[n];
        for(int i=0; i<n; i++){
            visited[i] = false;
        }

        visited[x] = true;
        int aux = 0;
        int row = x;
        nodes[x].push_back(::ABC[row%26] + ((row/26)>0? to_string(row/26):""));
        int pathLength = 0;
        for(int i=0; i<n; i++){
            int auxNeighborDistance = INT_MAX;
            for(int j=0; j<n; j++){
                if(j != row && !visited[j] && (auxNeighborDistance > auxMatrix[row][j])){
                    auxNeighborDistance = auxMatrix[row][j];
                    aux = j;
                }
            }
            pathLength += auxMatrix[row][aux];
            row = aux;
            visited[row] = true;
            nodes[x].push_back(::ABC[row%26] + ((row/26)>0? to_string(row/26):""));
        }
        nodes[x].pop_back();
        nodes[x].push_back(nodes[x].front());
        
        pathLength += auxMatrix[row][x];
        
        if(path > pathLength){
            path = pathLength;
            vectorPos = x;
        }
    }
    
    for(int v=0; v<n+1; v++){
        cout << nodes[vectorPos][v] << " ";
    }
    cout << endl;
}


// Implementation of a Breadth First Search
// Used to find if there is an augmenting path within the graph to reach the final node 't'.
// Complexity: O(V^2), where 'V' is the number of nodes.
bool bfs(vector<vector<int>> &residual, int s, int t, int parent[]){
    queue<int> q;
    q.push(s);
    bool visited[residual.size()];
    for(int i=0; i<residual.size(); i++){
        visited[i] = false;
    }
    visited[s] = true;
    parent[s] = -1;
    
    while(!q.empty()){
        int x = q.front();
        q.pop();
        for(int i = 0; i<residual.size(); i++){
            if((visited[i]==false) && (residual[x][i]>0)){
                if(i==t){
                    parent[i] = x;
                    return true;
                }
                visited[i] = true;
                q.push(i);
                parent[i] = x;
            }
        }
    }

    return false;
}
 
// Edmonds-Karp implementation of the Ford-Fulkerson algorithm
// Used to find the maximum possible flow in a graph, where the starting node 's' is 0 and the final node 't' is n-1.
// Complexity: O(V^3 * E), where 'V' is the number of nodes and 'E' the number of edges.
int edmondsKarp(vector<vector<int>> &matrix, int s, int t){
    int flow = 0;
    int parent[matrix[0].size()];

    vector<vector<int>> residual;
    for(int i=0; i<matrix[0].size(); i++){
        vector<int> aux;
        for(int j=0; j<matrix[0].size(); j++){
            aux.push_back(matrix[i][j]);
        }
        residual.push_back(aux);
    }
    
    while(bfs(residual, s, t, parent)){
        int flowPath = INT_MAX;
        for(int i=t; i!=s; i=parent[i]){
            int j = parent[i];
            if(flowPath > residual[j][i]){
                flowPath = residual[j][i];
            }
        }
        
        for(int i=t; i!=s; i=parent[i]){
            int j = parent[i];
            residual[j][i] -= flowPath;
            residual[i][j] += flowPath;
        }
        flow = flow + flowPath;
    }
 
    return flow;
}

// CGAL method to print a given point
// Complexity: O(1).
void print_endpoint(Halfedge_handle e, bool is_src) {
  cout << "\t";
  if ( is_src ) {
    if ( e->has_source() )  cout << "(" << e->source()->point().x() << "," << e->source()->point().y() << ")" << endl;
    else  cout << "point at infinity" << endl;
  } else {
    if ( e->has_target() )  cout << "(" << e->target()->point().x() << "," << e->target()->point().y() << ")" << endl;
      
    else  cout << "point at infinity" << endl;
  }
}

int main(){
    ifstream ifs("input.txt");
    assert( ifs );
    
    int n;
    string line;
    vector<vector<int>> matrix; // Distance (km) matrix
    vector<int> values;
    vector<int> values2;
    string pair;
    
    vector<Point_2> points;
    int cont = 1;
    while(ifs){
        ifs >> line;
        if(cont == 1){
            n = stoi(line);
        }else if(cont >= 2 && cont <= n*n+1){
            values.push_back(stoi(line));
        }else if(cont >= n*n+2 && cont <= (2*n*n)+1){
            values2.push_back(stoi(line));
        }else if(cont >= (2*n*n)+2){
            // Get coordinates (points) that represent the stations
            pair = line;
            int pos = pair.find(",");
            int pos2 = pair.find(")");
            int a = stoi(pair.substr(1,pos-1));
            int b = stoi(pair.substr(pos+1,pos2-pos-1));
            points.push_back(Point_2(a,b));
        }
        cont++;
    }
    ifs.close();

    // Get the distance (km) matrix that represents the neighborhoods graph
    int counter = 0;
    for (int i = 0; i < n; i++) {
        vector<int> auxMatrix;
        for (int j = 0; j < n; j++) {
            auxMatrix.push_back(values[counter]);
            counter++;
        }
        matrix.push_back(auxMatrix);
    }
	
    // Get the matrix that represents the flow graph
    int counter2 = 0;
    vector<vector<int>> matrix2;
    for (int i = 0; i < n; i++) {
        vector<int> auxMatrix2;
        for (int j = 0; j < n; j++) {
            auxMatrix2.push_back(values2[counter2]);
            counter2++;
        }
        matrix2.push_back(auxMatrix2);
    }
    cout << endl;
        
    // Get a coordinate (point) that represents a newly linked site to a station
    Point_2 p;
    cin >> pair;
    int pos = pair.find(",");
    int pos2 = pair.find(")");
    int a = stoi(pair.substr(1,pos-1));
    int b = stoi(pair.substr(pos+1,pos2-pos-1));
    p = Point_2(a,b);

    // Section 1
    floydWarshall(matrix, n);
    cout << endl;
    
    // Section 2
    repetitiveNearestNeighbor(matrix, n);
    cout << endl;
    
    // Section 3
    cout << edmondsKarp(matrix2, 0, n-1) << "\n" << endl;
    
    // Section 4
    // CGAL was used to calculate the Voronoi diagram of the station points, draw it and ubicate a new site within a region of the Voronoi diagram.
    // Complexity: O(n*log(n)), where 'n' is the number of stations.
    VD vd;
    Site_2 t;
    vd.insert(points.begin(), points.end());
    assert( vd.is_valid() );
    
    cout << "Query point (" << p.x() << "," << p.y()
              << ") lies on a Voronoi " << flush;
    Locate_result lr = vd.locate(p);
    if ( Vertex_handle* v = boost::get<Vertex_handle>(&lr) ) {
      cout << "vertex." << endl;
      cout << "The Voronoi vertex is:" << endl;
      cout << "\t" << "(" << (*v)->point().x() << "," << (*v)->point().y() << ")" << endl;
    } else if ( Halfedge_handle* e = boost::get<Halfedge_handle>(&lr) ) {
      cout << "edge." << endl;
      cout << "The source and target vertices "
                << "of the Voronoi edge are:" << endl;
      print_endpoint(*e, true);
      print_endpoint(*e, false);
    } else if ( Face_handle* f = boost::get<Face_handle>(&lr) ) {
      cout << "face." << endl;
      cout << "The vertices of the Voronoi face are"
                << " (in counterclockwise order):" << endl;
      Ccb_halfedge_circulator ec_start = (*f)->ccb();
      Ccb_halfedge_circulator ec = ec_start;
      do {
          print_endpoint(ec, false);
      } while ( ++ec != ec_start );
    }
    cout << endl;
    
    CGAL::draw(vd);
    
    return 0;
}
