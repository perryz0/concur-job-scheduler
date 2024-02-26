#include "Vector.h"

namespace vector374 {

Vector::Vector() {
    init(0, 0, 0);
}

Vector::Vector(const float x, const float y, const float z) {
    init(x, y, z);
}

Vector::Vector(const Vector &v) {
    init(v.v_[0], v.v_[1], v.v_[2]);
}

Vector::~Vector() {
    delete[] v_;
}

Vector& Vector::operator=(const Vector &rhs) {
    if (this != &rhs) {
        delete[] v_;
        init(rhs.v_[0], rhs.v_[1], rhs.v_[2]);
    }
    return *this;
}

double operator*(const Vector &a, const Vector &b) {
    return a.v_[0] * b.v_[0] + a.v_[1] * b.v_[1] + a.v_[2] * b.v_[2];
}

Vector operator*(const double k, const Vector &v) {
    return Vector(k * v.v_[0], k * v.v_[1], k * v.v_[2]);
}

Vector operator*(const Vector &v, const double k) {
    return k * v;
}

ostream& operator<<(ostream &out, const Vector &v) {
    out << "(" << v.v_[0] << "," << v.v_[1] << "," << v.v_[2] << ")";
    return out;
}

void Vector::init(const float x, const float y, const float z) {
    v_ = new float[3];
    v_[0] = x;
    v_[1] = y;
    v_[2] = z;
}

}   // namespace vector374
