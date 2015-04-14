__author__ = 'Praveenkumar VASUDEVAN'

import matplotlib.pyplot as plt
import matplotlib.transforms as tfm
import matplotlib.patches as patches
import matplotlib.animation as animation
import math
import numpy
from mpl_toolkits.axes_grid1 import AxesGrid

def make_rectangle(x,y,heading):
    rect = plt.Rectangle((x-0.1,y-0.2),0.2,0.4,0)
    # move the center to the bottom left
    rect.xy = (x-0.1,y-0.2)
    rect._angle = heading
    rect.xy = (x+0.1,y+0.2)
    return rect

def make_rectangle_patch(ax,x,y,heading):
    ts = ax.transData
    coords = ts.transform([x, y])
    tr = tfm.Affine2D().rotate_deg_around(coords[0], coords[1], heading)
    t= ts + tr

    rect = patches.Rectangle((x-0.1,y-0.2),0.2,0.4,transform=t)
    rect = patches.Rectangle((x-0.2,y-0.2),0.4,0.4,transform=t)
    return rect

#plt.axes()
F = plt.figure(1,(10,10))


ax = plt.gca()
ax.cla() # clear things for fresh plot
# change default range so that new circles will work
ax.set_xlim((-0.5,5.5))
ax.set_ylim((-3,3))

ax.set_title('Localization on XZ Plane')
ax.set_xlabel('Z Axis (m)')
ax.set_ylabel('X Axis (m)')

fig = plt.gcf()

#circle1=patches.Ellipse((2,0),0.5,0.8,340,color='g')
#%fig.gca().add_patch(circle1)

angle = 330
wedge1= patches.Wedge((3,0),0.5,angle-15,angle+15)
#fig.gca().add_patch(wedge1)

# Camera
points = [[0, 0.3], [0, -0.3], [-0.3, 0]]
polygon = plt.Polygon(points)
fig.gca().add_artist(polygon)
# Camera origin
camera_origin=plt.Circle((0,0),0.05,color='r')
fig.gca().add_artist(camera_origin)
# Camera Text annotation
ax.text(-0.4, -0.5, 'KINECT', fontsize=18)

# arrow = plt.Arrow(2,2,0.5,0)
# fig.gca().add_artist(arrow)
#
# fig.gca().add_patch(make_rectangle_patch(ax,1,1,45))
# circle2=plt.Circle((1,1),0.05,color='g')
# fig.gca().add_artist(circle2)



plt.draw()
plt.grid()
#plt.axis('scaled')

deg =0

def init():
    wedge1.center = (3, 0)
    ax.add_patch(wedge1)
    return wedge1,

def animate(i):
    x,y   = wedge1.center
    theta1 = wedge1.theta1
    theta2 = wedge1.theta2
    wedge1.set_center((x,y))
    wedge1.set_theta1(i - 15)
    wedge1.set_theta2(i + 15)
    #deg = i + 1
    print "Hello : (%d,%d);(%d,%d)" % (x,y,theta1,theta2)
    return wedge1,

an1 = animation.FuncAnimation(fig,animate,init_func=init,interval=500)
plt.show()


