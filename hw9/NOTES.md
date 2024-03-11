## Overview

The implementation of the job scheduler in Golang would be to create a
concurrent reader that takes in jobs from the YAML config files, and then
execute those jobs concurrently while preseving the dependencies betweeen
those jobs. Must also ensure that one job would only be executed after all
its dependencies are completed. After the implementation of the job scheduler,
then worry about generating a DOT graph of the job dependencies.

## Features

- [x] Simple job scheduling
- [x] Job scheduling with dependencies
- [x] DOT Graph generation
- [ ] Added tests
- [ ] Delay configuration
- [ ] Debug log flag

### Simple job scheduling & handling dependencies (first 2 parts)

General workflow:
1. First read YAML config file; each job should be separate entry
2. Iterate thru the job list
3. Check dependencies for each job
      - If yes, wait for all dependencies to finish
4. Execute the current job
5. Make sure the thread safety is preserved with access synchronization
6. Implement job concurrency with goroutines

Additional comments:
Had issues with finish running each goroutine with skeleton implementation,
so I utilized a temp map and a WaitGroup counter to monitor job executions
and the completion of goroutines.

### DOT Graph generation (part 3)

Workflow:
1. Read the README part about generating the DOT graph and the DOT Language
documentation provided on Graphviz
2. Initialize a buffer to store the DOT graph representation for efficient
read and write operations
3. Write header format and footer format
4. Implement the middle section (each of the nodes), by iterating thru each
job in the config
      - Write edges from some job (if any) to dependencies
5. Copy the buffer contents to the writer for the eventual .dot redirection
6. Debug by checking the .dot files with different .yaml's, and once correct,
generate the desired .png files using the provided graph.sh script.

### Added tests (part 4)

NOT FINISHED. Below was my initial workflow but did not have time.

1. More tests in config_test.go

2. Tests in scheduler_test.go
      - Test for correct output after slight dependency addition (i.e. first
      .yaml job list only has "ls" as dependency for "echo" while the second
      has an additional "cd" as dependency for "echo")

### Delay configuration and log flag (parts 5 & 6)

Did not have enough time for these! Will come back to this after finals so
I can wrap this project up :)