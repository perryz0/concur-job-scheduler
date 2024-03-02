scheduler: $(shell find . -type f -name "*.go")
	go build -o scheduler ./cmd/scheduler

.PHONY: install
install:
	go install ./cmd/...

.PHONY: test
test: install
	go test ./...
