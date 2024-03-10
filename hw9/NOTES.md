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
- [ ] DOT Graph generation
- [ ] Added tests
- [ ] Delay configuration
- [ ] Debug log flag

### Simple job scheduling & handling dependencies (first 2)
1. First read YAML config file; each job should be separate entry
2. Iterate thru the job list
3. Check dependencies for each job
      - If yes, wait for all dependencies to finish
4. Execute the current job
5. Make sure the thread safety is preserved with access synchronization
6. Implement job concurrency with goroutines

### DOT Graph generation

### Added tests
