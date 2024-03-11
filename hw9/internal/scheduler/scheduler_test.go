package scheduler

import (
	"path/filepath"
	"testing"

	"github.com/stretchr/testify/require"
)

const testdataDirectory = "../testdata/config"

func TestScheduler(t *testing.T) {
	t.Run("Scheduler Run() with basic config", func(t *testing.T) {
		// Load the configuration from a test file
		config, err := ReadConfig(filepath.Join(testdataDirectory, "basic-deps.yaml"))
		require.NoError(t, err, "config error")
	})

}
