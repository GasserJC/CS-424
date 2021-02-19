#dependencies
import llist
from llist import sllist, sllistnode

class PCB1:
    def __init__(self, parent):
        self.parent = parent
        self.children = sllist([])

    def create(self, p):
        self.children.append(p)

    def destroy(self):
        arr = []
        for i in range(0, self.children.size()):
            node = self.children.nodeat(i)
            arr.append(node.value)
            self.children.remove(self.children.nodeat(i))
        return arr

