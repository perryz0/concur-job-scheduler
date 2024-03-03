package scheduler

import (
	"io"

	"uw.cse374.go/scheduler/internal/config"
)

// Scheduler schedules and executes a collection
// of one or more jobs.
type Scheduler struct {
	config *config.Config
}

// New returns a new Scheduler with the
// given configuration.
func New(config *config.Config) *Scheduler {
	return &Scheduler{
		config: config,
	}
}

// Run runs all of the configured jobs, writing each
// job's name to the given writer.
func (s *Scheduler) Run(writer io.Writer) error {
	// TODO: Implement me!
	//
	// There are a variety of ways you can implement this function.
	// Some solutions might require different struct types, whereas
	// others do not. There are tradeoffs between each solution,
	// so carefully consider how you'd like to approach this before
	// you start writing any code!
	//
	// Hint: You will need to use the 'go' keyword, which runs the
	//       job in a goroutine (which is a lightweight thread).
	//
	//       For details, see https://go.dev/tour/concurrency
	//
	// Hint: If you need to use any additional data structures, make
	//       sure that you synchronize access so that it's thread-safe
	//       (i.e. use a mutex)!
	//
	//       For details, see https://go.dev/tour/concurrency/9
	//
	// Hint: Some implementations might choose to use a WaitGroup,
	//       but this isn't always necessary.
	//
	//       For details, see https://gobyexample.com/waitgroups
	return nil
}

// Graph writes a DOT-graph containing the configured jobs
// to the given writer.
func (s *Scheduler) Graph(writer io.Writer) error {
	// TODO: Implement me!
	//
	// Hint: You will need to write individual lines of text to
	//       the io.Writer to create the DOT-graph. See the
	//       README.md for details on how to get started.
	//
	//       For details, see https://graphviz.org/doc/info/lang.html
	_, err := io.WriteString(writer, "digraph G {}\n")
	return err
}
