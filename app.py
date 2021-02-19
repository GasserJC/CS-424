#This file will be testing both the Process controll block types.
import time
import PCB_V1
import PCB_V2


def V1():
    PCB = []
    PCB.append( PCB1(0) )
    create1(0)
    create1(0)
    create1(2)
    create1(0)
    destroy1(0)

def V2():
    PCB = []
    PCB.append( PCB2(0) )
    create2(0)
    create2(0)
    create2(2)
    create2(0)
    destroy2(0)

def create1( p ):
    PCB[len(PCB)] = PCB1(p)
    p.create(len(PCB))

def destroy1( p ):
   arr = p.destroy()
   for process in arr:
       PCB.remove(process)

def create2( p ):
    PCB[len(PCB)] = PCB2(p)
    p.create(len(PCB))

def destroy2( p ):
    arr = p.destroy()
    for process in arr:
        PCB.remove(process)


