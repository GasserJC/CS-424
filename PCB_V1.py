#dependencies
import llist
from llist import sllist, sllistnode

class PCB1:
    def __init__(self, parent, name):
        self.parent = parent
        self.children = sllist([])
        self.processName = name

    def create(self, p):
        self.children.append(p)
        print(self.children)

    def destroy(self, pcb, p, arr):
        name = int(pcb[p].processName)
        arr.append(name)
        for proc in pcb[p].children:
            pcb[p].destroy(pcb, proc, arr)
        for proc in pcb[p].children:
            pcb[p].children.pop()
        return arr