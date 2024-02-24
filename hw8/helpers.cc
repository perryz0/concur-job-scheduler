#include "helpers.h"

#include "Expr.h"

using namespace expr;

shared_ptr<Num> expr::num(double val) { return std::make_shared<Num>(val); }

shared_ptr<Var> expr::var(string name) { return std::make_shared<Var>(name); }
