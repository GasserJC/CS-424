#This file will be testing both the Process controll block types.
import time
import PCB_V1
import PCB_V2
from PCB_V1 import PCB1
from PCB_V2 import PCB2


def V1():
    PCB = []
    PCB.append( PCB1(0, 0) )
    create1(PCB, 0)
    print(PCB)
    time.sleep(4)
    create1(PCB, 0)
    print(PCB)
    time.sleep(4)
    create1(PCB, 2)
    print(PCB)
    time.sleep(4)
    create1(PCB, 0)
    print(PCB)
    destroy1(PCB, 0)
    print(PCB)

def V2():
    PCB = []
    PCB.append( PCB2(0) )
    create2(0)
    create2(0)
    create2(2)
    create2(0)
    destroy2(0)

def create1( pcb, p ):
    pcb.append(PCB1(p, (len(pcb)-1))
    pcb[p].create(len(pcb) - 1)

def destroy1( pcb, p ):
   arr = pcb[p].destroy()
   for process in pcb:
       if process in arr:
           del process

def create2( p ):
    PCB[len(PCB)] = PCB2(p)
    p.create(len(PCB))

def destroy2( p ):
    arr = p.destroy()
    for process in arr:
        PCB.remove(process)


V1()
