#!/usr/bin/env python3
import subprocess
import copy

import graphviz

MAXIMUM_DEPTH = 4

class State:
    def __init__(self, parent, identifier, transitions, stateHash):
        self.parent = parent
        self.identifier = identifier
        self.transitions = transitions
        self.stateHash = stateHash

runtime = subprocess.Popen("./a.out", encoding="utf8", stdout=subprocess.PIPE, stdin=subprocess.PIPE)

sh = int(runtime.stdout.readline())
readyQueue = runtime.stdout.readline().strip(", \n").split(",")
root = State(None, 0, [], sh)

graph = graphviz.Digraph(comment="Execution Schedules")
graph.node(str(root.identifier), label="hash: " + str(root.stateHash))

stateCount = 1

searchQueue = []
for transition in readyQueue:
    searchQueue.append(State(root.identifier, stateCount, [transition.strip()], None))
    stateCount += 1

searchStack = []

while searchQueue:
    current = searchQueue.pop()

    if current.transitions[:len(searchStack)] == searchStack:
        toApply = current.transitions[len(searchStack):]

        for transition in toApply:
            print(transition, file=runtime.stdin)
            runtime.stdin.flush()
            searchStack.append(transition)
            
            current.stateHash = int(runtime.stdout.readline())
            readyQueue = runtime.stdout.readline().strip(", \n").split(",")
        
    else:
        searchStack = []

        # restart process
        runtime.kill()
        runtime = subprocess.Popen("./a.out", encoding="utf8", stdout=subprocess.PIPE, stdin=subprocess.PIPE)

        runtime.stdout.readline()
        runtime.stdout.readline()

        # re-apply everything...
        for transition in current.transitions:
            print(transition, file=runtime.stdin)
            runtime.stdin.flush()

            # move cursor
            current.stateHash = int(runtime.stdout.readline())
            readyQueue = runtime.stdout.readline().strip(", \n").split(",")
            
            searchStack.append(transition)

    
    graph.node(str(current.identifier), label="hash: " + str(current.stateHash))
    graph.edge(str(current.parent), str(current.identifier), label=current.transitions[-1])

    for transition in readyQueue:
        t = copy.deepcopy(searchStack)
        t.append(transition.strip())
        if len(t) <= MAXIMUM_DEPTH:
            s = State(current.identifier, stateCount, t, None)
            stateCount += 1
            searchQueue.append(s)

graph.render("graph", format="jpeg")