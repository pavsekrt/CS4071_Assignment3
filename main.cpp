#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
  if ((argc < 5)||(*argv[argc-1] != -1)) {
    cerr << "Usage: " << argv[0] << " n i j (i j i j ...) -1" << endl;
    cerr << "n = number of vertices, i j = sequence of pairs (integers between 0 and n)" << endl;
    return 1;
  }

  return 0;
}
