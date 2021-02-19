#dependencies
import llist
from llist import sllist, sllistnode

class PCB1:
	def __init__(self, parent):
		self.parent = parent
		self.children = sllist([])
	
	def create(self, p):
        	children.append(p)
	
	def destroy(self, p):
		for i in range(0, children.size()):
			node = children.nodeat(i)
			if(node.value == p):
				children.remove(children.nodeat(i))
				return true
		return false


