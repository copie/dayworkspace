string = input()

if len(string) == 1:
    print(''.join(map(str, range(1, int(string) + 1))))
if len(string) == 2:
    print('S' * int(string[0]) + ''.join(map(str, range(1, int(string[1]) + 1))))
if len(string) == 3:
    print('B' * int(string[0]) + 'S' * int(string[1]) + ''.join(map(str, range(1, int(string[2]) + 1))))