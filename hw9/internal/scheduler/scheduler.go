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
	// Map to keep track of completed jobs
	completed := make(map[string]bool)
	// Mutex for synchronization
	var mutex sync.Mutex

	// Helper function to execute a job
	var executeJob func(jobName string)

	executeJob = func(jobName string) {
		// Check if the job is already completed
		mutex.Lock()
		_, ok := completed[jobName]
		mutex.Unlock()

		if ok {
			// Job already completed, return
			return
		}

		// Get the job details from the configuration
		jobIndex := findJobIndex(s.config.Jobs, jobName)
		if jobIndex == -1 {
			// Job not found in configuration, return
			return
		}

		job := s.config.Jobs[jobIndex]

		// Execute dependencies first
		for _, depName := range job.DependsOn {
			executeJob(depName)
		}

		// Execute the job
		mutex.Lock()
		fmt.Fprintf(writer, "%s\n", jobName)
		completed[jobName] = true
		mutex.Unlock()
	}

	// Execute each job concurrently
	for _, job := range s.config.Jobs {
		go executeJob(job.Name)
	}

	return nil
}

// Helper function that returns the index of job with the given name in the slice of jobs.
// If the job is not found, it returns -1.
func findJobIndex(jobs []config.Job, jobName string) int {
	for i, job := range jobs {
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
