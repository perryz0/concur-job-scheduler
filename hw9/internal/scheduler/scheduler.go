package scheduler

import (
	"fmt"
	"io"
	"sync"

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
	// Create a map to store signal channels for each job
	jobSignals := make(map[string]chan struct{})

	// Create a new WaitGroup for each invocation
	var wg sync.WaitGroup

	// Embedded helper function to execute a job
	var executeJob = func(jobName string) {
		// Get the job details from the configuration
		jobIndex := findJobIndex(s.config, jobName)
		if jobIndex == -1 {
			// Job not found in configuration, return
			return
		}

		job := s.config.Jobs[jobIndex]

		// Wait for all dependencies to complete
		for _, depName := range job.DependsOn {
			<-jobSignals[depName]
		}

		// Execute the job
		fmt.Fprintf(writer, "%s\n", jobName)

		// Signal job completion
		close(jobSignals[jobName])
		wg.Done() // Decrement the WaitGroup counter when the goroutine completes
	}

	// Execute each job concurrently
	for _, job := range s.config.Jobs {
		// Increment the WaitGroup counter
		wg.Add(1)

		// Create a signal channel for the job
		jobSignals[job.Name] = make(chan struct{})

		// Launch a goroutine to execute the job
		go func(jobName string) {
			executeJob(jobName)
		}(job.Name)
	}

	// Wait for all goroutines to complete
	wg.Wait()

	return nil
}

// Helper function that returns the index of a job with the given name in the configuration.
// If the job is not found, it returns -1.
func findJobIndex(cfg *config.Config, jobName string) int {
	for i, job := range cfg.Jobs {
		if job.Name == jobName {
			return i
		}
	}
	return -1
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
