#!/usr/bin/env python3
import subprocess
import copy

MAXIMUM_DEPTH = 8

runtime = subprocess.Popen("./a.out", encoding="utf8", stdout=subprocess.PIPE, stdin=subprocess.PIPE)

readyQueue = runtime.stdout.readline().strip(", \n").split(",")

searchQueue = [[transition.strip()] for transition in readyQueue]
searchStack = []

while searchQueue:
    print(searchQueue)
    print(searchStack)

    current = searchQueue.pop()
    if current[:len(searchStack)] == searchStack:
        toApply = current[len(searchStack):]
        print(toApply)

        for transition in toApply:
            print(runtime.communicate(input=transition, timeout=None))
            searchStack.append(transition)

        runtime.stdout.readline()
        readyQueue = runtime.stdout.readline().strip(", \n").split(",")
        
        for transition in readyQueue:
            searchQueue.append(copy.deepcopy(searchStack).append(transition.strip()))
    else:
        searchStack = []
        runtime.kill()
        # restart process