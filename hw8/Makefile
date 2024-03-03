CXX = g++
COPTS = -g -Wall -std=c++14

all: main

main: main.o Expr.o helpers.o
	$(CXX) $(COPTS) -o $@ $^

helpers.o: helpers.cc helpers.h
	$(CXX) $(COPTS) -o $@ -c $<

main.o: main.cc Expr.h
	$(CXX) $(COPTS) -o $@ -c $<

Expr.o: Expr.cc Expr.h
	$(CXX) $(COPTS) -o $@ -c $<

plot.o: plot.cc Expr.h helpers.h
	$(CXX) $(COPTS) -o $@ -c $<

plot_csv: plot.o Expr.o helpers.o
	$(CXX) $(COPTS) -o $@ $^

plot: plot_csv
	if ! pip show matplotlib > /dev/null 2>&1; then \
		pip install matplotlib; \
	fi
	./plot_csv
	./plot_png.py

clean:
	rm -f *.o main *.csv plot_csv
