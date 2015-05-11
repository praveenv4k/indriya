import matplotlib
import csv

import matplotlib.pyplot as plt
import matplotlib.transforms as tfm
import matplotlib.patches as patches
import matplotlib.animation as animation
import numpy as np

def csv_reader(file_obj):
    reader = csv.reader(file_obj)
    data = []
    i=0
    for row in reader:
        
        if i>0:
            x = np.array(row)
            y = x.astype(np.float)
            data.append(y)
        i=i+1
        #time.sleep(0.1)
    return data

if __name__ == "__main__":
    #data = np.genfromtxt('planar_right_turn.csv',skip_header=1)
    #plt.plot(data,'o-')

    csv_path = "planar_right_turn.csv"
    with open(csv_path, "rb") as f_obj:
        data = csv_reader(f_obj)
        
        plt.plot(data)
        plt.show()
