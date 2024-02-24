#include <memory>  // For shared_ptr and make_unique

#include "Expr.h"
#include "helpers.h"  // for var() and num()

using namespace std;
using namespace expr;

int main() {
  // ExprPtr is another name for shared_ptr<Expr>
  ExprPtr exp1;
  // var() and num() are helper functions that generate pointers to Var and Num
  exp1 = var("x") + num(374);
  cout << "(x + 374)  (expected)" << endl;
  cout << exp1 << endl;

  // Same idea as Map<Key, Value> in Java
  map<string, double> values = {{"x", 42}, {"y", 43}};

  cout << "(42 + 374) = 416  (expected)" << endl;
  cout << exp1->setVariables(values) << " = ";
  cout << exp1->setVariables(values)->evaluate() << endl;

  cout << "(x + 374)  (expected)" << endl;
  ExprPtr exp2 = exp1->clone();
  cout << exp2 << endl;

  // TODO: Uncomment the rest of the code as you progress

  // cout << "((x + 374) * (x + 374))  (expected)" << endl;
  // ExprPtr exp4 = exp1 * exp1;
  // cout << exp4 << endl;

  // cout << "((x + 374) + ((x + 374)^2))  (expected)" << endl;
  // ExprPtr exp3 = exp2 + (exp2 ^ num(2));
  // cout << exp3 << endl;

  // cout << "((42 + 374) + ((42 + 374)^2)) = 173472  (expected)" << endl;
  // cout << exp3->setVariables(values) << " = ";
  // cout << exp3->setVariables(values)->evaluate() << endl;
}
