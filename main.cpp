#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
  //Usage Test
  if ((argc < 5)||(*argv[argc-1] != '-')||(argc%2==0)) {
    cerr << "Usage: " << argv[0] << " n i j (i j i j ...) -1" << endl;
    cerr << "n = number of vertices, i j = sequence of pairs (integers between 0 and n)" << endl;
    return 1;
  }
  //

  
  for (size_t i = 1; i < argc-1; i++) {
    cout << argv[argc-1] << endl;
  }

  return 0;
}
