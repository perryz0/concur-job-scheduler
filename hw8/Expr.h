#ifndef _EXPR_H_
#define _EXPR_H_

#include <iostream>
#include <map>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

using std::map;
using std::shared_ptr;
using std::string;

// Since names like Num and Var are pretty generic, we put them inside of a
// namespace in case other libraries have classes with the same name
namespace expr {

/* An abstract class representing a general math expression
 * It is an abstract class, so you cannot instaniate it.
 * However, you can hold a pointer to it, preferrably through
 * a shared_ptr<Expr> (AKA ExprPtr) */
class Expr {
 public:
  virtual ~Expr() {}
  virtual Expr& operator=(const Expr& rhs) = delete;
  virtual shared_ptr<Expr> clone() const = 0;
  virtual shared_ptr<Expr> setVariables(
      const map<string, double>& values) const = 0;
  virtual string toString() const = 0;
  // Pre: all the Vars in this Expr have been substituted using setVariables
  virtual double evaluate() const = 0;
};

typedef shared_ptr<Expr> ExprPtr;

std::ostream& operator<<(std::ostream& o, const shared_ptr<Expr>& eptr);

class Num : public Expr {
 public:
  Num(double d) : num_(d) {}
  shared_ptr<Expr> clone() const;
  shared_ptr<Expr> setVariables(
      const std::map<std::string, double>& values) const;
  string toString() const;
  double evaluate() const;

 private:
  double num_;
};

/* Class representing a named variable like "x", "foo", etc.
 * */
class Var : public Expr {
 public:
  Var(string name) : name_(name) {}
  shared_ptr<Expr> clone() const;
  shared_ptr<Expr> setVariables(
      const std::map<std::string, double>& values) const;
  string toString() const { return name_; }
  double evaluate() const;

 private:
  string name_;
};

class Sum : public Expr {
 public:
  Sum(shared_ptr<Expr> left, shared_ptr<Expr> right);
  shared_ptr<Expr> clone() const;
  shared_ptr<Expr> setVariables(
      const std::map<std::string, double>& values) const;
  string toString() const {
    return "(" + left_->toString() + " + " + right_->toString() + ")";
  }
  double evaluate() const;

 private:
  shared_ptr<Expr> left_;
  shared_ptr<Expr> right_;
};

shared_ptr<Expr> operator+(shared_ptr<Expr> lhs, shared_ptr<Expr> rhs);

// Done implementation for Prod
class Prod : public Expr {
 public:
  Prod(shared_ptr<Expr> left, shared_ptr<Expr> right);
  shared_ptr<Expr> clone() const;
  shared_ptr<Expr> setVariables(
      const std::map<std::string, double>& values) const;
  string toString() const {
    return "(" + left_->toString() + " * " + right_->toString() + ")";
  }
  double evaluate() const;

 private:
  shared_ptr<Expr> left_;
  shared_ptr<Expr> right_;
};
// Done overload, similar to operator+
shared_ptr<Expr> operator*(shared_ptr<Expr> lhs, shared_ptr<Expr> rhs);

// Done implementation for Pow, directly carried over from Prod class
// For the toString(), output in the format of (left^right); fixed spacing
class Pow : public Expr {
 public:
  Pow(shared_ptr<Expr> left, shared_ptr<Expr> right);
  shared_ptr<Expr> clone() const;
  shared_ptr<Expr> setVariables(
      const std::map<std::string, double>& values) const;
  string toString() const {
    return "(" + left_->toString() + "^" + right_->toString() + ")";
  }
  double evaluate() const;

 private:
  shared_ptr<Expr> left_;
  shared_ptr<Expr> right_;
};

// Done overload, similar to operator*
// e.g. (x ^ 2) is x to the power of 2
// Note, C++ has different operator precedence, so always wrap (L ^ R) in parens
shared_ptr<Expr> operator^(shared_ptr<Expr> lhs, shared_ptr<Expr> rhs);

}  // namespace expr

#endif  // _EXPR_H_
