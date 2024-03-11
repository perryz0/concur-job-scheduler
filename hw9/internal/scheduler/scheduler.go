package scheduler

import (
	"bytes"
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
	// Create a temp map to monitor completion of each job exec
	jobSignals := make(map[string]chan struct{})

	// Create WaitGroup to wait for multiple launched goroutines to finish
	var wg sync.WaitGroup

	// Loop that iterates and executes each job concurrently
	for _, job := range s.config.Jobs {
		// Increment the WaitGroup counter
		wg.Add(1)

		// Create a signal channel for the job
		jobSignals[job.Name] = make(chan struct{})

		// Launch a goroutine to execute the job
		go func(jobName string) {
			// Get the job details from the config
			jobIndex := findJobIndex(s.config, jobName)

			// Job not found case
			if jobIndex == -1 {
				return
			}

			// Retrieve current job config
			job := s.config.Jobs[jobIndex]

			// Process all dependencies first
			for _, depName := range job.DependsOn {
				<-jobSignals[depName]
			}

			// Now execute the job
			fmt.Fprintf(writer, "%s\n", jobName)

			// Signal job completion & decrement the wg counter
			close(jobSignals[jobName])
			defer wg.Done()
		}(job.Name)
	}

	// Wait for all goroutines to complete (until wg counter = 0)
	wg.Wait()

	return nil
}

// Helper function that returns the index of a job within the configuration.
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
	// Generate the graph representation using sequence of memory bytes
	dotGraph := &bytes.Buffer{}

	// Header format of the graph
	_, err := io.WriteString(dotGraph, "digraph G {\n")
	if err != nil {
		return err
	}

	// Iterate thru each job in the config
	for _, job := range s.config.Jobs {
		// If job has dependencies, write edges from this job to its dependencies
		for _, depName := range job.DependsOn {

			// Added regex double quotes to prevent special chars from causing issues in graph
			_, err := fmt.Fprintf(dotGraph, "  \"%s\" -> \"%s\"\n", job.Name, depName)
			if err != nil {
				return err
			}
		}
	}

	// Footer format of the graph
	_, err = io.WriteString(dotGraph, "}\n")
	if err != nil {
		return err
	}

	// Copies contents of the buffer to the writer from io reader to writer
	_, err = io.Copy(writer, dotGraph)
	return err
}
