#!/bin/bash
docker build -t linux .
docker run --rm -it -v $PWD:/app -w /app linux
