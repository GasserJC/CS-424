#This file will be testing both the Process controll block types.
try:
    import time
    import PCB_V1
    import PCB_V2
    from PCB_V1 import PCB1
    from PCB_V2 import PCB2
except:
    print("")
    print(" do not have llist lib ")
    print(" run the following ")
    print("    $  pip3 install llist     ")
    print("")
    exit()

import time
import PCB_V1
import PCB_V2
from PCB_V1 import PCB1
from PCB_V2 import PCB2

def printPCB(pcb):
    for proc in pcb:
        par = " parent: "
        if(proc.parent != -1):
            par += str(proc.parent)
        print(str(proc.processName) + par)

def v1():
    PCB = []
    PCB.append( PCB1(-1, 0) )
    print("create(0)")
    printPCB(PCB)
    create1(PCB, 0)
    print("create(0)")
    printPCB(PCB)
    create1(PCB, 0)
    print("create(0)")
    printPCB(PCB)
    create1(PCB, 2)
    print("create(2)")
    printPCB(PCB)
    create1(PCB, 0)
    print("create(0)")
    printPCB(PCB)
    destroy1(PCB, 0)
    print("destroy(0)")
    printPCB(PCB)


def v2():
    PCB = []
    PCB.append( PCB2(-1, -1, -1, -1) )
    print("create(0)")
    PCB[0].create(PCB, 0)
    print("create(0)")
    PCB[0].create(PCB, 0)
    print("create(0)")
    PCB[2].create(PCB, 2)
    print("create(2)")
    PCB[0].create(PCB, 0)
    print("create(0)")
    print("--- pre-deletion ---")
    print("NOTE: -1 is equivilent to NA")
    print("")
    for proc in PCB:
        print("process: " + str(proc))
        print("parent: " + str(proc.p))
        print("first child: " + str(proc.fc))
        print("younger sibling: " + str(proc.ys))
        print("older sibling: " + str(proc.os))
    destroy2(PCB, PCB[0])
    print("")
    print("post-deletion")
    for proc in PCB:
        print("process: " + str(proc))
        print("parent: " + str(proc.p))
        print("first child: " + str(proc.fc))
        print("younger sibling: " + str(proc.ys))
        print("older sibling: " + str(proc.os))

def create1( pcb, p ):
    pcb.append( PCB1(p, len(pcb)))
    pcb[p].create( len(pcb) - 1 )


def destroy1( pcb, p ):
    arr = pcb[p].destroy(pcb, p, [])
    arr.remove(p)
    tmp = []
    ix = 0
    for process in pcb:
        if process.processName in arr:
           tmp.append(ix)
        ix += 1
    tmp.reverse()
    for index in tmp:
        pcb.pop(index)

def destroy2(PCB, p):
    p.destroy(PCB, p)
    p.alive = True
    tmp = []
    for i in range(0, len(PCB)):
        if(PCB[i].alive == False):
            tmp.append(i)
    tmp.reverse()
    for proc in tmp:
        PCB.pop(proc)

print("----------------         verison 1           ----------------")
print("")
print("")
v1()


print("")
print("")
print("----------------         version 2           ----------------")
print("")
print("")
v2()

def test_time():
    print("")
    print("")
    print("------------          testing time for dynamic memory allocation version        -----------")
    start1 = time.time()
    for i in range(0, 100000):
        v1_clear()
    end1 = time.time()
    print("version 1 time to execute 100,000 times: " + str(end1 - start1))
    print("")
    print("------------          testing time for dynamic programming version         -----------")
    start2 = time.time()
    for i in range(0, 100000):
        v2_clear()
    end2 = time.time()
    print("version 2 time to execute 100,000 times: " + str(end2 - start2))


def v1_clear():
    PCB = []
    PCB.append( PCB1(0, 0) )
    create1(PCB, 0)
    create1(PCB, 0)
    create1(PCB, 2)
    create1(PCB, 0)
    destroy1(PCB, 0)

def v2_clear():
    PCB = []
    PCB.append( PCB2(-1, -1, -1, -1) )
    PCB[0].create(PCB, 0)
    PCB[0].create(PCB, 0)
    PCB[2].create(PCB, 2)
    PCB[0].create(PCB, 0)
    PCB[0].destroy(PCB, PCB[0])



test_time()
