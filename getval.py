import numpy as np
import cv2 as cv

img = cv.imread('resize.prj/sol1/csim/build/error.png', cv.IMREAD_COLOR)
# img = cv.imread('resize.prj/sol1/csim/build/resize_ocv.png', cv.IMREAD_COLOR)
# print(img.format)

print('B')
print(img[63,190])
print(img[64,65])
print(img[68,31])

print('G')
print(img[40,112])
print(img[41,114])
print(img[43,691])


print('R')
print(img[37,112])
print(img[37,338])
print(img[43,92])
