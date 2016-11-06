#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct edge {
  int i;
  int j;
};


int main(int argc, char* argv[])
{
  vector<int> V;
  vector<edge> E;
  //Usage Test & setting V,E
  try{
    if ((argc < 5)||(*argv[argc-1] != '-')||(argc%2==0)||(atoi(argv[1]) != ((argc-3)/2))) {
      throw;
    }
    for(size_t i = 0; i < atoi(argv[1]); i++){V.push_back(i);}
    for (size_t i = 2; i < (argc-1); i+=2) {
      edge t = {atoi(argv[i]), atoi(argv[i+1])};
      E.push_back(t);
    }
  }catch (int e){
    cerr << "Usage: " << argv[0] << " n i j (i j i j ...) -1" << endl;
    cerr << "n = number of vertices, i j = sequence of pairs (integers between 0 and n)" << endl;
    return 1;
  }
  //






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
