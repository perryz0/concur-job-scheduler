#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <iostream>
using std::ostream;

namespace vector374 {

// A Vector represents a vector in 3-space.
class Vector {
 public:
  // constructors:

  // Default: construct the vector (0,0,0)
  Vector();

  // Construct the vector (x,y,z)
  Vector(const float x, const float y, const float z);

  // Copy constructor
  Vector(const Vector &v);

  // Destructor
  ~Vector();

  // Assignment
  Vector &operator=(const Vector &rhs);

  // Additional functions that are not members of Vector but
  // need to be friends so they can access instance variables:

  // dot-product: if a is (a,b,c) and b is (x,y,z),
  // return ax+by+cz
  friend double operator*(const Vector &a, const Vector &b);

  // scalar multiplication: if v is (a,b,c), return (ak,bk,ck)
  friend Vector operator*(const double k, const Vector &v);
  friend Vector operator*(const Vector &v, const double k);

  // Stream output: define << for Vectors
  friend ostream & operator<<(ostream &out, const Vector &v);

 private:
  // A Vector is represented by a heap-allocated array of three
  // floats giving the x, y, and z magnitudes in v[0], v[1],
  // and v[2] respectively.
  float *v_;

  // private helper function used by constructors: initialize
  // vector state to given x, y, z values.
  void init(const float x, const float y, const float z);
};

}  // namespace vector374

#endif  //  _VECTOR_H_
