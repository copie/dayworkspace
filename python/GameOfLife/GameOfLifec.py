import random
from copy import deepcopy
import time
maxl = 50
mymap = []
mymaptmp = []

dir = [[1, 1], [1, 0], [1, -1], [0, 1], [0, -1], [-1, 1], [-1, 0], [-1, -1]]

for _ in range(0, maxl):
    tmp = []
    tt = []
    for _ in range(0, maxl):
        tmp.append(random.choice([0, 1]))
        tt.append(0)
    mymap.append(tmp)
    mymaptmp.append(tt)
# print(mymap)
    mymapzero = deepcopy(mymaptmp)
while True:
    mymaptmp = deepcopy(mymapzero)
    for i in range(0, maxl):
        for j in range(0, maxl):
            for k in range(0, 8):
                if(i + dir[k][0] < 0 or j + dir[k][1] >= maxl or i + dir[k][0] >= maxl or j + dir[k][1] < 0):
                    continue
                else:
                    if mymap[i + dir[k][0]][j + dir[k][1]] == 1:
                        mymaptmp[i][j] += 1
    for i in range(0, maxl):
        for j in range(0, maxl):
            if mymaptmp[i][j] == 3:
                mymap[i][j] = 1
            elif mymaptmp[i][j] == 2:
                pass
            else:
                mymap[i][j] = 0
    print("\033c", end='')
    # time.sleep(0.5)
    for i in range(0, maxl):
        for j in range(0, maxl):
            if mymap[i][j] == 0:
                print('.', end='')
            else:
                print("*", end='')
        print("\n", end='')
