class PCB2:
    def __init__(self, parent, fc, ys, os):
        self.parent = parent
        self.first_child = fc
        self.younger_sibling = ys
        self.folder_sibling = os

    def create(self, p):
        return False

    def destroy(self, p):
        return False
