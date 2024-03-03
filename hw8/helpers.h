#ifndef _HELPERS_H_
#define _HELPERS_H_

#include <vector>

#include "Expr.h"

namespace expr {
shared_ptr<expr::Var> var(string name);

shared_ptr<expr::Num> num(double val);
}  // namespace expr

#endif  // _HELPERS_H_
