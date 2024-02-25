#include <iostream>
#include <cstdlib>

#include "Vector.h"

using std::cout;
using std::endl;
using vector374::Vector;

// Create several vectors and test their operations
int main() {
  // test constructors and stream output
  Vector v1;
  cout << "default Vector, should be (0,0,0): " << v1 << endl;
  Vector v2(1, 2, 3);
  cout << "Vector with initial values, should be (1,2,3): " << v2 << endl;
  Vector v3(v2);
  cout << "Vector from copy constructor, should be (1,2,3): " << v3 << endl;

  // test assignment (including chaining)
  Vector v4(3.1, -2.5, 2.7);
  v1 = v3 = v4;
  cout << "Vector assignment, should have three copies of (3.1,-2.5,2.7):\n";
  cout << "  " << v1 << "  " << v3 << "  " << v4 << endl;

  // dot product
  cout << "Dot product: (a,b,c) * (x,y,z) = (ax+by+cz)" << endl;
  cout << "  " << v2 << " * " << v2 << " = " << v2*v2 << endl;

  // scalar product
  cout << "Scalar product: (a,b,c) * k = (ak,bk,ck)" << endl;
  cout << "  "       << v1 << " * 2 = " << v1*2 << endl;
  cout << "Should be (3.1,-2.5,2.7): " << v1 << endl;
  cout << "  2 * " << v1 <<       " = " << 2*v1 << endl;

  return EXIT_SUCCESS;
}
