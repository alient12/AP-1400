import matplotlib.pyplot as plt
from PIL import Image
import numpy as np
import imageio
import os

img = Image.open('../resources/image.jpg')

dpi = 100
fig_size = (3024/dpi, 1632/dpi)
fig = plt.figure(figsize=fig_size, dpi=dpi, facecolor='red')


############## background image ##############
ax = fig.add_axes([0.05, 0.05, 0.9, 0.9], frame_on=True)
ax.tick_params(axis="both", labelcolor='none', top=False, bottom=False, left=False, right=False)
for axis in ['top','bottom','left','right']:
    ax.spines[axis].set_linewidth(2)

img_bg = img.copy()
img_bg = img_bg.resize((2869, 1569), Image.ANTIALIAS)
implot = ax.imshow(img_bg, aspect='equal')
##############################################

################ DAEMON text #################
textstr = "           DAEMON           "
props = dict(facecolor='white', pad=30)
ax.text(0.015, 0.029, textstr, transform=ax.transAxes, fontsize=48, va='bottom', ha='left', bbox=props, weight='bold')
##############################################

############## graysclae image ###############
ax_gray = fig.add_axes([0.55, 0.55, 0.45, 0.45], frame_on=True)
ax_gray.tick_params(axis="both", labelcolor='none', top=False, bottom=False, left=False, right=False)
img_gray = img.copy()
img_gray = img_gray.resize((int(fig_size[0] * dpi), int(fig_size[1] * dpi)), Image.ANTIALIAS)
img_gray = np.array(img_gray)
img_gray[:,:,0] = img_gray[:,:,1] = img_gray[:,:,2] = np.dot(img_gray[:,:,:3], [0.369, 0.369, 0.005])
implot = ax_gray.imshow(img_gray, aspect='equal')
##############################################

################ sinus plot ##################
ax_sine = fig.add_axes([0.013, 0.25, 0.975, 0.1], frame_on=False)
ax_sine.tick_params(axis="both", labelcolor='none', top=False, bottom=False, left=False, right=False)

phis = np.linspace(0, np.pi*2, 20)
x = np.linspace(0, np.pi*40, 4000)
##############################################


################# makeing gif ################
filenames = []
for i, phi in enumerate(phis):
    # plot the line chart
    y = np.sin(x - phi)
    ax_sine.clear()
    ax_sine.plot(x, y, 'k', lw=10)
    
    # create file name and append it to a list
    filename = f'{i}.png'
    filenames.append(filename)
    
    # save frame
    fig.savefig(filename)
# build gif
with imageio.get_writer('daemon.gif', mode='I') as writer:
    for filename in filenames:
        image = imageio.imread(filename)
        writer.append_data(image)
        
# Remove files
for filename in set(filenames):
    os.remove(filename)
##############################################