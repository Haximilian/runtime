#!/usr/bin/env python3
import subprocess
import copy
import json

import graphviz

MAXIMUM_DEPTH = 3
EXECUTABLE = "./a.out"

class State(dict):
    def __init__(self, identifier, transitions, readyQueue, stateHash):
        super().__init__()
        self.__dict__ = self
        self.identifier = identifier
        self.transitions = transitions
        self.readyQueue = readyQueue
        self.stateHash = stateHash
        self.children = []

class Runtime:
    def __init__(self):
        self.count = 0
        self.stack = None
        self.runtime = None

    def initialize_runtime(self):
        self.stack = []
        self.runtime = subprocess.Popen(EXECUTABLE, encoding="utf8", stdout=subprocess.PIPE, stdin=subprocess.PIPE)

        stateHash = int(self.runtime.stdout.readline())
        readyQueue = self.runtime.stdout.readline().strip(", \n").split(",")

        return (stateHash, readyQueue)

    def visit(self, transitions):
        # initial state
        if self.runtime is None:
            stateHash, readyQueue = self.initialize_runtime()

        if transitions[:len(self.stack)] == self.stack:
            apply = transitions[len(self.stack):]
        else:
            self.runtime.kill()

            stateHash, readyQueue = self.initialize_runtime()

            apply = transitions

        for t in apply:
            print(t, file=self.runtime.stdin)
            self.runtime.stdin.flush()

            self.stack.append(t)
            
            stateHash = int(self.runtime.stdout.readline())
            readyQueue = self.runtime.stdout.readline().strip(", \n").split(",")

        self.count += 1
        return State(self.count, transitions, readyQueue, stateHash)

def build_tree(root, runtime):
    if len(root.transitions) == MAXIMUM_DEPTH:
        return

    if root.readyQueue == []:
        return

    for t in root.readyQueue:
        child_transitions = copy.deepcopy(root.transitions)
        child_transitions.append(t.strip())
        child = runtime.visit(child_transitions)
        build_tree(child, runtime)
        root.children.append(child)

def create_graph(root: State, graph):
    graph.node(str(root.identifier), label="hash: " + str(root.stateHash))

    for child in root.children:
        create_graph(child, graph)
        graph.edge(str(root.identifier), str(child.identifier), label=child.transitions[-1])


runtime = Runtime()

root = runtime.visit([])

build_tree(root, runtime)

graph = graphviz.Digraph(comment="Execution Schedules")

create_graph(root, graph)

graph.render("graph", format="jpeg")

with open("./schedule.json", mode="w") as f:
    json.dump(root.__dict__, f)