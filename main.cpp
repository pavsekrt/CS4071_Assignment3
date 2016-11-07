#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <string>

using namespace std;

struct edge {
  int i;
  int j;
};
void printMatrix(int** g, int n){
  int i,j;
  for(i = 0;i < n;i++){
    for(j = 0; j < n; j++){
      cout<<g[i][j]<<"  ";
    }
    cout<<endl;
  }
}

class Graph{
  private:
    int **adj;
    int n;
  public:
    Graph(int n){
      this->n = n;
      adj = new int* [n];
      for (int i = 0; i < n; i++){//nxn matrix of 0's
        adj[i] = new int [n];
        for(int j = 0; j < n; j++){
            adj[i][j] = 0;
        }
      }
    }
    Graph(const vector<edge> E, int n){
      this->n = n;
      adj = new int* [n];
      for (int i = 0; i < n; i++){//nxn matrix of 0's
        adj[i] = new int [n];
        for(int j = 0; j < n; j++){
            adj[i][j] = 0;
        }
      }
      addEdges(E);
    }
    void addEdges(const vector<edge> E){
      for (size_t i = 0; i < E.size(); i++) {
        addEdge(E.at(i).i, E.at(i).j);
      }
    }
    void addEdge(int i, int j){
      if( i > n || j > n || i < 0 || j < 0){
        cout<<"Invalid edge!\n";
      }else{
        adj[i][j] += 1;
        adj[j][i] += 1;
      }
    }
    void print(){
      printMatrix(adj, n);
    }
    int** getGraph(){
      return adj;
    }
    int getN(){
      return n;
    }
};

int BFS(int** g, int start, int end, int numOfVertices) {
  queue<int> verts;
  queue<int> dist;
  vector<bool> visited(numOfVertices);
  visited.at(start) = true;
  verts.push(start);
  dist.push(0);

  int curVert;
  int distance;
  while (!verts.empty()) {
    vector<int> neighbors;
    curVert = verts.front();
    distance = dist.front();
    // cout << curVert << " - " << distance << endl;
    // return distance
    if (curVert == end) {
      return distance;
    }
    verts.pop();
    dist.pop();
    // get the neighbors of current vertex
    for (int i = 0; i < numOfVertices; i++) {
      if (g[i][curVert] == true) {
        // add the vertex
        neighbors.push_back(i);
      }
    }
    // add neighbors & distance to queues
    for (int i = 0; i < neighbors.size(); i++) {
      if (!visited.at(neighbors[i])) {
        visited.at(neighbors[i]) = true;
        verts.push(neighbors[i]);
        dist.push(distance + 1);
      }
    }
  }
  return -1;
}

int** distanceMatrix(int** g, int numOfVertices) {
  int **matrix;

  // BFS computes the distances for all elements
  matrix = new int* [numOfVertices];
  for (int i = 0; i < numOfVertices; i++) {
    matrix[i] = new int [numOfVertices];
    for (int j = 0; j < numOfVertices; j++) {
      matrix[i][j] = BFS(g, i, j, numOfVertices);
    }
  }

  return matrix;
}

int diameter(int** g, int numOfVertices) {
  // get distance matrix
  int** matrix = distanceMatrix(g, numOfVertices);
  // graph connected?
  for (int i = 0; i < numOfVertices; i++) {
    for (int j = 0; j < numOfVertices; j++) {
      if (matrix[i][j] == -1) {
        return -1;
      }
    }
  }
  // find max distance in distance matrix
  int max = 0;
  for (int i = 0; i < numOfVertices; i++) {
    for (int j = 0; j < numOfVertices; j++) {
      if (matrix[i][j] > max) {
        max = matrix[i][j];
      }
    }
  }
  return max;
}










int main(int argc, char* argv[])
{
  int numOfVertices;
  vector<int> V;
  vector<edge> E;
  //Usage Test & setting V,E
  try{
    numOfVertices = atoi(argv[1]);
    if ((argc < 5)||(*argv[argc-1] != '-')||(argc%2==0)||(numOfVertices != ((argc-3)/2))) {
      throw(0);
    }
    for(size_t i = 0; i < numOfVertices; i++){V.push_back(i);}// V
    for (size_t i = 2; i < (argc-1); i+=2) { // E
      int x = atoi(argv[i]);
      int y = atoi(argv[i+1]);
      if (x > numOfVertices || x < 0 || y > numOfVertices || y < 0){
        throw(0);
      }
      edge t = {x, y};
      E.push_back(t);
    }
  }catch (int e){
    cerr << endl << "Usage: " << argv[0] << " n i j (i j i j ...) -1" << endl;
    cerr << "n = number of vertices, i j = sequence of pairs (integers between 0 and n)" << endl << endl;
    return 1;
  }
  //END
  Graph a = Graph(E, numOfVertices);
  a.print();
  cout << endl;
  int **dMatrix = distanceMatrix(a.getGraph() , numOfVertices);
  printMatrix(dMatrix, numOfVertices);
  cout << endl;
  cout << diameter(a.getGraph(), numOfVertices) << endl;
  // cout << "V: " << endl;
  // for (size_t i = 0; i < V.size(); i++) {
  //   cout << V.at(i) << ", ";
  // }
  // cout << endl << "E: " << endl;
  // for (size_t i = 0; i < E.size(); i++) {
  //   cout << "i = " << E.at(i).i << ", j = " << E.at(i).j << endl;
  // }





  return 0;
}
