#!/bin/bash

while true; do
	echo "Starting script..."
	./myexe1 | sudo ./myexe2
	sleep 3  # Pauses for 3 seconds	
	echo "3 seconds have passed."
done
