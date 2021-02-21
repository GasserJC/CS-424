#This file will be testing both the Process controll block types.
import time
import PCB_V1
import PCB_V2
from PCB_V1 import PCB1
from PCB_V2 import PCB2


def v1():
    PCB = []
    PCB.append( PCB1(0, 0) )
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

def v2():
    PCB = []
    PCB.append( PCB2(-1, -1, -1, -1) )
    PCB[0].create(PCB, 0)
    PCB[0].create(PCB, 0)
    PCB[2].create(PCB, 2)
    PCB[0].create(PCB, 0)
    print("pre-deletion")
    for proc in PCB:
        print(proc)
        print(proc.p)
        print(proc.fc)
        print(proc.ys)
        print(proc.os)
        time.sleep(5)
    PCB[0].destroy(PCB, 0)
    print("post-deletion")
    for proc in PCB:
        print(proc)
        print(proc.p)
        print(proc.fc)
        print(proc.ys)
        print(proc.os)
        time.sleep(5)

def create1( pcb, p ):
    pcb.append( PCB1(p, len(pcb)))
    pcb[p].create( len(pcb) - 1 )


def destroy1( pcb, p ):
    arr = pcb[p].destroy(p)
    tmp = []
    print(arr)
    ix = 0
    for process in pcb:
        if process.processName in arr:
           tmp.append(ix)
        ix += 1
    tmp.reverse()
    for index in tmp:
        pcb.pop(index)

print("----------------         verison 1           ----------------")
v1()

print("----------------         version 2           ----------------")
v2()