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

    def destroy(self, p, arr):
        arr.append(p.processName)
        for proc in p.children:
            p.destroy(proc, arr)
        for proc in p.children:
            p.children.pop()
        return arr
        '''
        arr = [p]
        for i in range(0, self.children.size):
            node = self.children.nodeat(i)
            arr.append(node.value)
        for process in self.children:
            self.children.pop()
        return arr
        '''