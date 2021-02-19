class PCB2:
	def __init__(self, parent):
		self.parent = parent
		self.first_child = 0
		self.younger_sibling = 0
		self.folder_sibling = 0

	def create(self, p):
		return True

	def destroy(self, p):
		return False
