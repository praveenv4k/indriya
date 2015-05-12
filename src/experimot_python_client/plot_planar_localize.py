import matplotlib
import csv

import matplotlib.pyplot as plt
import matplotlib.transforms as tfm
import matplotlib.patches as patches
import matplotlib.animation as animation
import numpy as np

def csv_plot(file_obj):
    reader = csv.reader(file_obj)
    data = []
    
    i=0
    x_val = []
    y_val = []
    theta_val = []
    for row in reader:
        
        if i>0:
            x = np.array(row)
            y = x.astype(np.float)
            data.append(y)
            x_val.append(row[1])
            y_val.append(row[2])
            theta_val.append(row[3])
        i=i+1
        #time.sleep(0.1)
    plt.plot(x_val)
    plt.plot(y_val)
    plt.plot(theta_val)
    plt.show()
    return data

if __name__ == "__main__":
    #data = np.genfromtxt('planar_right_turn.csv',skip_header=1)
    #plt.plot(data,'o-')

    csv_path = "planar_right_turn.csv"
    with open(csv_path, "rb") as f_obj:
        data = csv_plot(f_obj)
        #x = data[:,2]
        #plt.plot(data)
        #plt.show()
