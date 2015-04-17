import os
import sys
import time
import argparse

from naoqi import ALProxy

from os.path import dirname
from os.path import abspath

currdir = dirname(__file__)
parent = abspath(os.path.join(currdir,os.pardir))

print currdir
print parent

for dirname, dirnames, filenames in os.walk(parent):
    # print path to all subdirectories first.
    for subdirname in dirnames:
        print os.path.join(dirname, subdirname)


sys.path.append(currdir)
sys.path.append(parent)