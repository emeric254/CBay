#!/bin/bash
gcc structures.c client.c interfaceClient.c mainClient.c -o client && echo "Compilation réussie"
exit 0
