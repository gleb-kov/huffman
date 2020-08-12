import sys

argc = len(sys.argv)

if argc != 3:
    print("run with arg: <filename> <sizeof test>")
    exit()

fname = sys.argv[1]
num = int(sys.argv[2])

kib = 1000
gib = kib * 1000 * 1000

if num < kib or num > gib:
    print("Unusual test size. File would be generated no matter what.")

with open(fname, 'w') as fout:
    for i in range(0, num):
        fout.write('a')
