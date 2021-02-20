class PCB2:
    def __init__(self, parent, fc, ys, os):
        self.parent = parent
        self.first_child = fc
        self.younger_sibling = ys
        self.folder_sibling = os

    def create(self, pcb, p):
        if(pcb[p].first_child == -1):
            pcb[p].first_child = len(pcb)
            pcb.append( PCB2(p, -1, -1, -1) )
        else:
            pcb.append( PCB2(p, -1, -1, -1) )


    def destroy(self, p):
        return False
