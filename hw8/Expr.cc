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

// Base case #1
shared_ptr<Expr> Num::setVariables(
    const std::map<std::string, double>& values) const {
  // Copy is returned, while wrapped with share_ptr
  return clone();   // Line 25
}

// Recursive case for Sum
shared_ptr<Expr> Sum::setVariables(
    const std::map<std::string, double>& values) const {

  // setVariables() calls on left and right expr's
  ExprPtr left = left_->setVariables(values);
  ExprPtr right = right_->setVariables(values);
  // Summed expression of the left and right
  return std::make_shared<Sum>(left, right);
}

// Base case #2
shared_ptr<Expr> Var::setVariables(
    const std::map<std::string, double>& values) const {
  auto result = values.find(name_);
  if (result == values.end()) {
    // Not found in map, return copy of itself
    return clone();   // Line 27
  } else {
    // Found in map, return value associated with var key in the pair
    return std::make_shared<Num>(result->second);
  }
}

shared_ptr<Expr> operator+(shared_ptr<Expr> lhs, shared_ptr<Expr> rhs) {
  return std::make_shared<Sum>(lhs, rhs);
}

double Var::evaluate() const { return NAN; }
double Num::evaluate() const { return num_; }
double Sum::evaluate() const { return left_->evaluate() + right_->evaluate(); }


// ***PARTS 2 AND 3***


// IMPLEMENTATIONS FOR PROD (PART 2)
Prod::Prod(shared_ptr<Expr> left, shared_ptr<Expr> right)
    : left_(left), right_(right) {}   // slight modifications from Sum

shared_ptr<Expr> Prod::clone() const {
  return std::make_shared<Prod>(left_->clone(), right_->clone());
}   // slight modifications from Sum

// Recursive case for Prod (identical algo to Sum)
shared_ptr<Expr> Prod::setVariables(
    const std::map<std::string, double>& values) const {

  // setVariables() calls on left and right expr's
  ExprPtr left = left_->setVariables(values);
  ExprPtr right = right_->setVariables(values);
  // Prod expression of the left and right
  return std::make_shared<Prod>(left, right);
}

// Identical algo with operator+ above (line 60)
shared_ptr<Expr> operator*(shared_ptr<Expr> lhs, shared_ptr<Expr> rhs) {
  return std::make_shared<Prod>(lhs, rhs);
}

// Identical algo with Sum::evaluate(), just changed arithmetic operator
double Prod::evaluate() const { return left_->evaluate()*right_->evaluate(); }


// IMPLEMENTATIONS FOR POW (PART 3)
Pow::Pow(shared_ptr<Expr> left, shared_ptr<Expr> right)
    : left_(left), right_(right) {}   // slight modifications from Prod

shared_ptr<Expr> Pow::clone() const {
  return std::make_shared<Pow>(left_->clone(), right_->clone());
}   // slight modifications from Prod

// Recursive case for Pow (identical algo to Prod)
shared_ptr<Expr> Pow::setVariables(
    const std::map<std::string, double>& values) const {

  // setVariables() calls on left and right expr's
  ExprPtr left = left_->setVariables(values);
  ExprPtr right = right_->setVariables(values);
  // Prod expression of the left and right
  return std::make_shared<Pow>(left, right);
}

// Identical algo with operator* above (line 92)
shared_ptr<Expr> operator^(shared_ptr<Expr> lhs, shared_ptr<Expr> rhs) {
  return std::make_shared<Pow>(lhs, rhs);
}

// Identical algo with Prod::evaluate(), uses the pow() function from <cmath>
double Pow::evaluate() const {
  return pow(left_->evaluate(), right_->evaluate());
}

}  // namespace expr
