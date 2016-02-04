import os
import commands
from pprint import pprint
import csv

sizes = [2**i for i in range(8,14)]
the_iters = range(1000, 5000, 1000)

times_list = []
size_list = []
iters_list = []
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
