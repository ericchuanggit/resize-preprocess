import numpy as np
import cv2 as cv
from matplotlib import pyplot as plt
img = cv.imread('resize.prj/sol1/csim/build/error.png')
assert img is not None, "file could not be read, check with os.path.exists()"
color = ('b','g','r')
for i,col in enumerate(color):
 histr = cv.calcHist([img],[i],None,[256],[0,256])
 plt.plot(histr,color = col)
#  for k in range(0,256):
#   if histr[k][0] != 0 :
#     print(k,':', histr[k][0])
#  print("next color space")
 plt.xlim([0,256])
plt.show()