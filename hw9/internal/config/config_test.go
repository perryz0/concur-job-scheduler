package config

import (
	"path/filepath"
	"testing"

	"github.com/stretchr/testify/assert"
	"github.com/stretchr/testify/require"
)

// testdataDirectory represents the relative path to the
// test configuration definition directory.
//
// Note: the path is relative to the testdata from _this_ directory.
const testdataDirectory = "../testdata/config"

// TestConfig defines a suite of configuration tests, all with
// their own description.
func TestConfig(t *testing.T) {
	t.Run("no jobs", func(t *testing.T) {
		_, err := ReadConfig(filepath.Join(testdataDirectory, "empty.yaml"))
		require.EqualError(
			t,
			err,
			"scheduler configuration must specify at least one job",
		)
	})

	t.Run("job doesn't specify a name", func(t *testing.T) {
		_, err := ReadConfig(filepath.Join(testdataDirectory, "nameless.yaml"))
		require.EqualError(
			t,
			err,
			"all jobs must specify a name",
		)
	})

	t.Run("duplicate jobs", func(t *testing.T) {
		_, err := ReadConfig(filepath.Join(testdataDirectory, "duplicate.yaml"))
		require.EqualError(
			t,
			err,
			`scheduler configuration contains duplicate job: "echo"`,
		)
	})

	t.Run("single job", func(t *testing.T) {
		config, err := ReadConfig(filepath.Join(testdataDirectory, "single.yaml"))
		require.NoError(t, err)

		assert.NotNil(t, config)
		assert.Len(t, config.Jobs, 1)
		assert.Equal(t, "echo", config.Jobs[0].Name)
	})

	// TODO: Write more tests here!
	//
	// Hint: Check out the additional testdata files, and include a test for each
	//       one. These can be found in the internal/testdata/config directory.
	//
	// Hint: You're encouraged to use a similar testing strategy as the other tests
	//       already written here.
}
