#!/bin/bash
while :
do
	curl -L http://127.0.0.1:12380/my-key -XPUT -d bar
done
