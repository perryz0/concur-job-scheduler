#!/bin/bash
#
# Generate a DOT graph for every one of the .dot
# files in the given arguments.

if [ $# -eq 0 ]; then
  echo "Usage: graph [filename ...]" 1>&2
  exit 1
fi

for file in "$@"; do
  if [ ! -f "$file" ]; then
    echo "$file is not a file!"
    exit 1
  fi

  if [ $file != *.dot ]; then
    echo "$file must have a .dot extension!"
    exit 1
  fi

  # The output files will have the same name, excluding
  # the .dot extension.
  BASENAME="$(basename $file .dot)"

  # Generate a .png for the DOT graph.
  dot -Tpng -o "$BASENAME.png" "$BASENAME.dot"
done
