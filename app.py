#This file will be testing both the Process controll block types.
import time
import PCB_V1
import PCB_V2
from PCB_V1 import PCB1
from PCB_V2 import PCB2

procN = 0

def v1():
    PCB = []
    PCB.append( PCB1(0, procN) )
    create1(PCB, 0)
    print(PCB)
    create1(PCB, 0)
    print(PCB)
    create1(PCB, 2)
    print(PCB)
    create1(PCB, 0)
    print(PCB)
    destroy1(PCB, 0)
    print(PCB)

def create1( pcb, p ):
    global procN
    procN += 1
    pcb.append( PCB1(p, procN))
    pcb[p].create( procN )


def destroy1( pcb, p ):
    arr = pcb[p].destroy()
    tmp = []
    print(arr)
    ix = 0
    for process in pcb:
        if process.processName in arr:
           tmp.append(ix)
        ix += 1
    tmp.reverse()
    for index in tmp:
        pcb[index] = -1

v1()