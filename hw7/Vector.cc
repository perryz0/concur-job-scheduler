#include "Vector.h"

#include <utility>
using std::swap;

namespace vector374 {

// *HELPER FUNCTIONS
// Helps initialize vector state to given x y z values
void Vector::init(const float x, const float y, const float z) {
    v_ = new float[3];
    v_[0] = x;
    v_[1] = y;
    v_[2] = z;
}

// *CONSTRUCTORS/DESTRUCTORS
// Default constructor that initializes to (0,0,0)
Vector::Vector() {
    init(0, 0, 0);
}

// Vector constructor with specified x y z directions and magnitudes
Vector::Vector(const float x, const float y, const float z) {
    init(x, y, z);
}

// Copy constructor that makes a copy of a vector
Vector::Vector(const Vector &v) {
    init(v.v_[0], v.v_[1], v.v_[2]);
}

// Destructor to handle post-dealloc issues (unnecessary in this case)
Vector::~Vector() {}

// *OPERATORS
// = operator for vector assignment (u=v)
Vector &Vector::operator=(const Vector &rhs) {
    Vector temp(rhs);
    swap(temp.v_, v_);
    return *this;
}

// * operator to compute dot product of two Vectors
double operator*(const Vector &a, const Vector &b) {
    return a.v_[0] * b.v_[0] + a.v_[1] * b.v_[1] + a.v_[2] * b.v_[2];
}

// Overloaded * operator for scalar multiplication on a Vector
Vector operator*(const double k, const Vector &v) {
    return Vector(k * v.v_[0], k * v.v_[1], k * v.v_[2]);
}

// Reused overload of same scalar multiplication on a Vector, for cases of
// reversed multiplication order (i.e. k*v = v*k)
Vector operator*(const Vector &v, const double k) {
    return k * v;
}

// << operator to write Vector as stream output
ostream &operator<<(ostream &out, const Vector &v) {
    out << "(" << v.v_[0] << "," << v.v_[1] << "," << v.v_[2] << ")";
    return out;
}

}   // namespace vector374
