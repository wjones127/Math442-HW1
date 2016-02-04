import os
import commands
from pprint import pprint
import csv
import random

sizes = [2**i for i in range(8,16)]
the_iters = [500]

random.shuffle(sizes)

times_list = []
size_list = []
iters_list = []


for i in range(12):
    for iters in the_iters:
        print("doing iters={}".format(iters))
        for size in sizes:
            print("doing size={}".format(size))
            s = 'python update_locations.py {} {}'.format(size, iters)
            a = commands.getoutput(s)
            times_list.append(a)
            size_list.append(size)
            iters_list.append(iters)


pprint(times_list)
pprint(size_list)
pprint(iters_list)


with open('data.csv', 'wb') as csvfile:
    spamwriter = csv.writer(csvfile, delimiter=',')
    spamwriter.writerow(['time','size','iters'])
    for (a,b,c) in zip(times_list, size_list, iters_list):
        spamwriter.writerow([a,b,c])
