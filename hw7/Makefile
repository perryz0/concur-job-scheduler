CXX = g++
OBJS = Vector.o hw7.o
EXE  = hw7
HEADERS = Vector.h
CPPFLAGS = -Wall -g -std=c++11

# default target
$(EXE): $(OBJS)
	echo "Linking executable"
	$(CXX) $(CPPFLAGS) -o $(EXE) $(OBJS)

# source files
%.o: %.cc $(HEADERS)
	echo "Compiling $@"
	$(CXX) $(CPPFLAGS) -c $<

# phony target - remove generated files and backups
clean:
	rm -rf $(EXE) *.o *~ *.dSYM
