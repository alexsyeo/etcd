#!/bin/bash

count=1
while :
do
	curl -L http://172.20.10.3:12380/my-key -XPUT -d "$count"
	curl -L http://172.20.10.3:12380/my-key
	echo "request $count"
	let count=count+1
done
