#include "Expr.h"

#include <cmath>
#include <memory>

namespace expr {

std::ostream& operator<<(std::ostream& o, const shared_ptr<Expr>& eptr) {
  return o << eptr->toString();
}

string Num::toString() const {
  std::ostringstream s;
  s << num_;
  return s.str();
}

Sum::Sum(shared_ptr<Expr> left, shared_ptr<Expr> right)
    : left_(left), right_(right) {}

shared_ptr<Expr> Sum::clone() const {
  return std::make_shared<Sum>(left_->clone(), right_->clone());
}

shared_ptr<Expr> Num::clone() const { return std::make_shared<Num>(num_); }

shared_ptr<Expr> Var::clone() const { return std::make_shared<Var>(name_); }

shared_ptr<Expr> Num::setVariables(
    const std::map<std::string, double>& values) const {
  // TODO: Implement setVariables
}

shared_ptr<Expr> Sum::setVariables(
    const std::map<std::string, double>& values) const {
  // TODO: Implement setVariables
}

shared_ptr<Expr> Var::setVariables(
    const std::map<std::string, double>& values) const {
  auto result = values.find(name_);
  if (result == values.end()) {
    // TODO: Finish implementing
  } else {
    // TODO: Finish implementing
  }
}

shared_ptr<Expr> operator+(shared_ptr<Expr> lhs, shared_ptr<Expr> rhs) {
  return std::make_shared<Sum>(lhs, rhs);
}

double Var::evaluate() const { return NAN; }
double Num::evaluate() const { return num_; }
double Sum::evaluate() const { return left_->evaluate() + right_->evaluate(); }

// TODO: Implement more functions here

}  // namespace expr
