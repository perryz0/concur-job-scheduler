package config

import (
	"errors"
	"fmt"
	"io/ioutil"

	"gopkg.in/yaml.v3"
)

// Config represents the scheduler configuration,
// which is defined as JSON or YAML.
type Config struct {
	Jobs []Job `json:"jobs" yaml:"jobs"`
}

// Validate ensures the scheduler configuration is
// well-formed and returns an error otherwise.
func (c *Config) Validate() error {
	if c == nil || len(c.Jobs) == 0 {
		return errors.New("scheduler configuration must specify at least one job")
	}
	names := make(map[string]struct{})
	for _, job := range c.Jobs {
		if err := job.Validate(); err != nil {
			return err
		}
		if _, ok := names[job.Name]; ok {
			return fmt.Errorf("scheduler configuration contains duplicate job: %q", job.Name)
		}
		names[job.Name] = struct{}{}
	}
	// TODO: Optional; this item is not referenced in the assignment spec.
	//
	// Do we need to validate anything else? What happens if there's
	// a cycle in the graph?
	//
	// You will _not_ be evaluated on whether or not your solution
	// prevents cycles, but it's worthwhile to think about out how
	// to validate against this.
	return nil
}

// Job represents a single job, or unit of work.
//
// If a job has any dependencies, those jobs must
// complete before this job can be executed.
type Job struct {
	Name      string   `json:"name" yaml:"name"`
	DependsOn []string `json:"dependsOn" yaml:"dependsOn"`

	// TODO: Add the ability to configure an optional delay.
	//
	// The delay should be represnted as seconds (i.e. a simple
	// [unsigned] integer). If configured, the job should wait that
	// many seconds before it writes its name and completes. To be
	// clear, the optional delay should be used in the scheduler.
}

// Validate ensures the job is well-formed and returns
// an error otherwise.
func (j *Job) Validate() error {
	if j == nil || len(j.Name) == 0 {
		return errors.New("all jobs must specify a name")
	}
	return nil
}

// UnmarshalYAML implements the yaml.Unmarshaler interface so
// that we can customize how the jobs are represented in YAML.
//
// This makes it more convenient to specify a job without
// dependencies.
func (j *Job) UnmarshalYAML(node *yaml.Node) error {
	var name string
	if err := node.Decode(&name); err == nil {
		// The simpler format was used (i.e. only the name was specified).
		//
		// For example,
		//
		// - ls
		//
		// Set just the name.
		j.Name = name
		return nil
	}

	type rawJob Job
	if err := node.Decode((*rawJob)(j)); err != nil {
		return err
	}

	return nil
}

// ReadConfig reads the given filename and unmarshals it
// into a scheduler configuration.
func ReadConfig(filename string) (*Config, error) {
	data, err := ioutil.ReadFile(filename)
	if err != nil {
		return nil, err
	}
	var config Config
	if err = yaml.Unmarshal(data, &config); err != nil {
		return nil, err
	}
	if err := config.Validate(); err != nil {
		return nil, err
	}
	return &config, nil
}
