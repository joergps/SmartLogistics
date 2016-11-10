#!/bin/python
# Source: http://www.pyimagesearch.com/2014/09/15/python-compare-two-images/
print "Started '07_DetectItemByCamera.py'..."

import numpy as np
import cv2

def mse(imageA, imageB):
	# the 'Mean Squared Error' between the two images is the
	# sum of the squared difference between the two images;
	# NOTE: the two images must have the same dimension
	err = np.sum((imageA.astype("float") - imageB.astype("float")) ** 2)
	err /= float(imageA.shape[0] * imageA.shape[1])
	
	# return the MSE, the lower the error, the more "similar"
	# the two images are
	return err

# Load empty picture
imageEmpty = cv2.imread('empty.jpg')
imageGrayEmpty = cv2.cvtColor(imageEmpty, cv2.COLOR_BGR2GRAY)

# Load full picture
imageFull = cv2.imread('full.jpg')
imageGrayFull = cv2.cvtColor(imageFull, cv2.COLOR_BGR2GRAY)

# Compare empty <-> full
m1 = mse(imageEmpty, imageFull)
print "Empty <-> full: " + str(m1)

# Compare gray empty <-> full
m2 = mse(imageGrayEmpty, imageGrayFull)
print "Gray: Empty <-> full: " + str(m2)

# Compare empty <-> empty
m3 = mse(imageEmpty, imageEmpty)
print "Empty <-> empty: " + str(m3)



print "Ended."
