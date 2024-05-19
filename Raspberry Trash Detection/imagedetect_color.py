import sys
sys.path.append(r'C:\Users\User\AppData\Local\Packages\PythonSoftwareFoundation.Python.3.12_qbz5n2kfra8p0\LocalCache\local-packages\Python312\Scripts')
sys.path.append(r'c:\users\user\appdata\local\packages\pythonsoftwarefoundation.python.3.12_qbz5n2kfra8p0\localcache\local-packages\python312\site-packages')

import numpy as np
import cv2

def color_detect():
    flag = 0
    img = cv2.imread('trash.jpg')
    img = cv2.resize(img, (820,616))   
    #cv2.imshow('Original Image', img)
    #print(img.shape) > (2464, 3280, 3)
    cv2.waitKey(0)
    hsv_img = cv2.cvtColor(img, cv2.COLOR_BGR2HSV)
    img_rot = cv2.rotate(hsv_img, cv2.ROTATE_90_CLOCKWISE)
    cropped_image = img_rot[300:3280, 0:2464]

    # lower and range of white in HSV
    sensitivity = 70
    lower_white = np.array([0,0,255-sensitivity])
    upper_white = np.array([255,sensitivity,255])

    mask = cv2.inRange(cropped_image, lower_white, upper_white)
    color_image = cv2.bitwise_and(cropped_image, cropped_image, mask=mask)
    print(cv2.countNonZero(mask))
    if (cv2.countNonZero(mask) > 25000):
        flag = 1
    #cv2.imshow('Coloured Image', color_image)
    return flag

# Display the color of the image
#
#cv2.waitKey(0)
#3cv2.destroyAllWindows()




