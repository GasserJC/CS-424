class PCB2:
    def __init__(self, parent, fc, ys, os):
        self.p = parent
        self.fc = fc
        self.ys = ys
        self.os = os
        self.alive = True

    def create(self, pcb, p):
        #if first child of process p
        if(pcb[p].fc == -1):
            pcb[p].fc = len(pcb)
            pcb.append( PCB2(p, -1, -1, -1) )
        #if the process has children already
        else:
            pcb.append( PCB2(p, -1, -1, -1) )
            child = pcb[p].fc
            while(pcb[child].ys != -1):
                child = pcb[child].ys
            pcb[len(pcb)-1].os = child
            pcb[child].ys = len(pcb)-1

    def destroy(self, pcb, p):
        if(p.fc != -1):
            self.destroy(pcb, pcb[p.fc])
        if(p.ys != -1):
            self.destroy(pcb, pcb[p.ys])
        p.alive = False
        self.alive = False

