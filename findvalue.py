import numpy as np
import cv2 as cv
from matplotlib import pyplot as plt
with open('color_out.log','w')as f:
    img = cv.imread('resize.prj/sol1/csim/build/error.bmp')
    assert img is not None, "file could not be read, check with os.path.exists()"
    color = ('b','g','r')
    for i,col in enumerate(color):
        histr = cv.calcHist([img],[i],None,[256],[0,256])
        plt.plot(histr,color = col)
        
        f.write(f'Color space:{col}\n')
    for k in range(0,256):
        if histr[k][0] != 0 :
            f.write(f'{k}:, {histr[k][0]}\n')

    color_to_find = {
        'red':(0,0,255),
        'green':(0,255,0),
        'blue':(255,0,0),
    }
    # print("next color space")
    all_3=[];
    for color_name,color_rgb in color_to_find.items():
        print(color_rgb[0],color_rgb[1],color_rgb[2])
        indices = np.where((img[:,:,0] == color_rgb[0]) & 
                           (img[:,:,1] == color_rgb[1]) & 
                           (img[:,:,2] == color_rgb[2]))
        coordinates = list(zip(indices[0], indices[1])) 
        first_3 = coordinates[:3]
        all_3.append(coordinates[:3])
        f.write(f'{color_name} color coordinates: {first_3}\n')
    # print(unique_coordinates)
    # plt.xlim([0,256])
    # plt.show()

    # resize_img = cv.imread('resize.prj/sol1/csim/build/normalized_abgr_ocv.bmp')
    # for cc in range(len(all_3)):
    #     for x,y in all_3[cc]:
    #         pixel_value =resize_img[x,y]
    #         f.write(f"Pixel at ({x},{y})  {pixel_value}\n")
    #         f.write(f"Pixel at ({x},{y})  {pixel_value}\n")
    #         f.write(f"Pixel at ({x},{y})  {pixel_value}\n")

    # f.write(f"split----------------------------------------------------\n")

    # resize_img = cv.imread('resize.prj/sol1/csim/build/hls_abgr_out.bmp')
    # for cc in range(len(all_3)):
    #     for x,y in all_3[cc]:
    #         pixel_value =resize_img[x,y]
    #         f.write(f"Pixel at ({x},{y})  {pixel_value}\n")
    #         f.write(f"Pixel at ({x},{y})  {pixel_value}\n")
    #         f.write(f"Pixel at ({x},{y})  {pixel_value}\n")

    # f.write(f"split----------------------------------------------------\n")

    # resize_img = cv.imread('resize.prj/sol1/csim/build/resize_ocv.bmp')
    # for cc in range(len(all_3)):
    #     for x,y in all_3[cc]:
    #         pixel_value =resize_img[x,y]
    #         f.write(f"Pixel at ({x},{y})  {pixel_value}\n")
    #         f.write(f"Pixel at ({x},{y})  {pixel_value}\n")
    #         f.write(f"Pixel at ({x},{y})  {pixel_value}\n")
    resize_img = cv.imread('resize.prj/sol1/csim/build/normalized_abgr_ocv.bmp')
    print(resize_img[37,338])
    resize_img = cv.imread('resize.prj/sol1/csim/build/resize_ocv.bmp')
    print(resize_img[37,338])
    resize_img = cv.imread('resize.prj/sol1/csim/build/hls_abgr_out.bmp')
    print(resize_img[37,338])