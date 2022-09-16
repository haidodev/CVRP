with open('INPUT.INP', 'r') as filein:
    parent1_str = filein.readline()
    parent2_str = filein.readline()
    parent1 = [int(node) for node in parent1_str.split(',')]
    parent2 = [int(node) for node in parent2_str.split(',')]

from random import randrange
def crossover(parent1, parent2):
    gen_len = len(parent1)
    visited = set()
    start, end = randrange(0, gen_len), randrange(0, gen_len)
    if (start > end):
        tmp = start
        start = end
        end = tmp
    child = [0] * gen_len
    for i in range(start, end + 1):
        child[i] = parent2[i]
        visited.add(parent2[i])
    curIdx = (end + 1) % gen_len
    for i in range(end + 1, gen_len):
        while parent1[curIdx] in visited:
            curIdx = (curIdx + 1) % gen_len
        child[i] = parent1[curIdx]
        visited.add(parent1[curIdx])
    for i in range(start):
        while parent1[curIdx] in visited:
            curIdx = (curIdx + 1) % gen_len
        child[i] = parent1[curIdx]
        visited.add(parent1[curIdx])
    return child
print(parent1)
print(parent2)
print(crossover(parent1, parent2))
