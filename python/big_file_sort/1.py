import random
file = open('xx.txt', 'w')
x = (f'{i}:{j}:{x}:{y}\n'
     for i in random.choices(range(256), k=20)
     for j in random.choices(range(256), k=10)
     for x in random.choices(range(256), k=50)
     for y in random.choices(range(256), k=10)
     )
file.writelines(x)
