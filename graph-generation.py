#!/usr/bin/env python3
import subprocess
import copy

import graphviz

MAXIMUM_DEPTH = 4
EXECUTABLE = "./a.out"

class State:
    def __init__(self, parent, identifier, transitions, stateHash):
        self.parent = parent
        self.identifier = identifier
        self.transitions = transitions
        self.stateHash = stateHash

class Runtime:
    def __init__(self):
        pass

    def apply(self, toApply, r, stack):
        stateHash = None
        readyQueue = None

        for t in toApply:
            print(t, file=r.stdin)
            r.stdin.flush()

            stack.append(t)
            
            stateHash = int(r.stdout.readline())
            readyQueue = r.stdout.readline().strip(", \n").split(",")
        
        return (stateHash, readyQueue)

r = Runtime()

runtime = subprocess.Popen(EXECUTABLE, encoding="utf8", stdout=subprocess.PIPE, stdin=subprocess.PIPE)

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

        current.stateHash, readyQueue = r.apply(toApply, runtime, searchStack)
    else:
        searchStack = []

        # restart process
        runtime.kill()
        runtime = subprocess.Popen("./a.out", encoding="utf8", stdout=subprocess.PIPE, stdin=subprocess.PIPE)

        runtime.stdout.readline()
        runtime.stdout.readline()

        current.stateHash, readyQueue = r.apply(current.transitions, runtime, searchStack)
    
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