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

    def destroy(self):
        arr = []
        for i in range(0, self.children.size - 1):
            node = self.children.nodeat(i)
            arr.append(node.value)
            self.children.remove(self.children.nodeat(i))
        return arr

