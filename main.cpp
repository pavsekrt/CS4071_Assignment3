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
      throw(0);
    }
    for(size_t i = 0; i < atoi(argv[1]); i++){V.push_back(i);}
    for (size_t i = 2; i < (argc-1); i+=2) {
      int x = atoi(argv[i]);
      int y = atoi(argv[i+1]);
      if (x > atoi(argv[1]) || x < 0 || y > atoi(argv[1]) || y < 0){
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
  //END Usage Test & setting V,E





  return 0;
}
