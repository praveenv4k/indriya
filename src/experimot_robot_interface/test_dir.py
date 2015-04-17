import os
import sys
import time
import argparse

from naoqi import ALProxy

from os.path import dirname
from os.path import abspath

currdir = dirname(__file__)
parent = abspath(os.path.join(currdir,os.pardir))

i = 0

bin = os.environ["DEV_SDK_ROOT"]

print bin

parent = currdir
while i<4:
    #parent = abspath(os.path.join(parent,os.pardir))
    if not "scripts" in parent:
        i=i+1
        continue
    else:
        break
    i=i+1



print currdir
print parent

for dirname, dirnames, filenames in os.walk(parent):
    # print path to all subdirectories first.
    for subdirname in dirnames:
        print os.path.join(dirname, subdirname)


sys.path.append(currdir)
sys.path.append(parent)