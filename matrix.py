import time

def OnMult(lines):

    pha, phb, phc = [], [], []

    for i in range(lines):
        for j in range(lines):
            pha.append(1)

    for i in range(lines):
        for j in range(lines):
            phb.append(i + 1)


    for i in range(lines):
        for j in range(lines):
            phc.append(1)

    time1 = time.time()

    for i in range(lines):
        for j in range(lines):
            temp = 0
            for k in range(lines):
                temp += pha[i*lines + k] * phb[k*lines + j]
            phc[i*lines + j] = temp

    time2 = time.time()

    print("Time: %3.3f seconds" % (time2 - time1))
    
    print("Result matrix: ")
    for j in range(min(10, lines)):
        print(phc[j], end=" ")
    print()




def OnMultLine( lines):
    pha, phb, phc = [], [], []

    for i in range(lines):
        for j in range(lines):
            pha.append(1)

    for i in range(lines):
        for j in range(lines):
            phb.append(i + 1)


    for i in range(lines):
        for j in range(lines):
            phc.append(1)
    
    Time1 = time.time()


    for i in range(lines):
        for j in range(lines):
            phc[i * lines + j] = pha[i * lines + j] * phb[j * lines + j]

    Time2 = time.time()
    
 
    print("Time: %3.5f seconds\n" % (Time2 - Time1))
    
    for j in range(min(10, lines)):
        print(phc[j], end=" ")
    



def OnMultBlock(lines, bkSize):
    
    pass

def main():
    op = 1
    while op != 0:
        print("\n1. Multiplication")
        print("2. Line Multiplication")
        print("3. Block Multiplication")
        op = int(input("Selection?: "))
        if op == 0:
            break
        lin = int(input("Dimensions: lins=cols ? "))
        
        if op == 1:
            OnMult(lin)
        elif op == 2:
            OnMultLine(lin)
        elif op == 3:
            blockSize = int(input("Block Size? "))
            OnMultBlock(lin, blockSize)

if __name__ == "__main__":
    main()

