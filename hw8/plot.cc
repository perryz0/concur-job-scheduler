#include <fstream>
#include <iostream>
#include <vector>

#include "Expr.h"
#include "helpers.h"

using namespace std;
using namespace expr;

// For each x in xs, substitute it in for x in the equation fx and evaluate
vector<double> plot(const shared_ptr<Expr>& fx, vector<double> xs);

// Over write file with filename as a CSV file where each row has an x,y
void write_file(string filename, ExprPtr equation,
                const map<string, double>& values, const vector<double>& xs);

int main(int argc, char** argv) {
  // A list of evenly spaced x points from -5 to 5
  vector<double> xs;
  for (double d = -5; d <= 5; d += 0.1) {
    xs.push_back(d);
  }

  // Plots a line using y = mx + b
  ExprPtr line = var("m") * var("x") + var("b");
  cout << "Equation: " << line << endl;

  // Set slope to 0.5 and y intercept to 3
  map<string, double> values = {{"m", 0.5}, {"b", 3}};
  write_file("line.csv", line, values, xs);

  // ***PART 4***
  // Done plotting a curve using y = mx^2 + b where m = 0.5, b = 3
  //      Written into a file called "curve.csv"
  //      Reuses the same `xs` variable as above
  //      *Also reuses the same values map bc variables have same values
  ExprPtr curve = var("m") * (var("x")^num(2)) + var("b");
  cout << "Equation: " << curve << endl;
  write_file("curve.csv", curve, values, xs);
}

void write_file(string filename, ExprPtr equation,
                const map<string, double>& values, const vector<double>& xs) {
  // Overwrite file
  ofstream file(filename);

  ExprPtr subst = equation->setVariables(values);
  auto ys = plot(subst, xs);

  auto x_it = xs.begin();
  auto y_it = ys.begin();
  while (x_it != xs.end()) {
    file << *x_it << "," << *y_it << endl;
    x_it++;
    y_it++;
  }
  // Automatically closes file when destructor is called
}

vector<double> plot(const shared_ptr<Expr>& fx, vector<double> xs) {
  vector<double> ys;
  for (double x : xs) {
    auto subst = fx->setVariables({{"x", x}});
    ys.push_back(subst->evaluate());
  }
  return ys;
}
