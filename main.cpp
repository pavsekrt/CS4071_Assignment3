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

class AdjacencyMatrix{
  public:
    int **adj;
    int n;
    AdjacencyMatrix(int n){
      this->n = n;
      adj = new int* [n];
      for (int i = 0; i < n; i++){
        adj[i] = new int [n];
        for(int j = 0; j < n; j++){
            adj[i][j] = 0;
        }
      }
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
        // adj[j][i] += 1;
      }
    }
    void print(){
      int i,j;
      for(i = 0;i < n;i++){
        for(j = 0; j < n; j++){
          cout<<adj[i][j]<<"  ";
        }
        cout<<endl;
      }
    }

};

class BFS{
  public:
    int n;
    list<int> *adj;

    BFS(int n){
      this->n = n;
      adj = new list<int>[n];
    }

    void addEdges(const vector<edge> E){
      for (size_t i = 0; i < E.size(); i++) {
        addEdge(E.at(i).i, E.at(i).j);
      }
    }

    void addEdge(int i, int j){
      adj[i].push_back(j); // Add i to j’s list.
      // adj[j].push_back(i); // Add j to i’s list.
    }

    void print(int s){
      bool *visited = new bool[n];
      for(size_t i = 0; i < n; i++){
        visited[i] = false;
      }
      queue<int> q;
      visited[s] = true;// current node as visited
      q.push(s);//and enqueue it
      list<int>::iterator i;//used to get all adjacent vertices
      cout << "breadth-first search from " << s << endl;
      while(!q.empty()){
        s = q.front();// Dequeue from queue & print
        cout << s << " ";
        q.pop();
        // adjacent has not been visited, mark  visited and enqueue
        for(i = adj[s].begin(); i != adj[s].end(); ++i){
          if(!visited[*i]){
            visited[*i] = true;
            q.push(*i);
          }
        }
      }
      cout << endl;
    }
};

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
  AdjacencyMatrix a = AdjacencyMatrix(numOfVertices);
  a.addEdges(E);
  // a.print();
  BFS b = BFS(numOfVertices);
  b.addEdges(E);
  b.print(0);
  b.print(1);
  b.print(2);
  b.print(3);
  b.print(4);



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
