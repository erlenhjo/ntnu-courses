# -*- coding: utf-8 -*-
"""
Created on Fri Oct  7 21:34:32 2022

@author: Erlend Johansen
"""
import os
import numpy as np
import cv2
import matplotlib.pyplot as plt

folderName="fft_images"

fileNames=os.listdir(folderName)

fig1,axes1=plt.subplots(ncols=3,nrows=3, figsize=(9,9))
axarr1=axes1.flatten()
fig2,axes2=plt.subplots(ncols=3,nrows=3, figsize=(9,9))
axarr2=axes2.flatten()

for i,file in enumerate(fileNames):
    image=cv2.imread(os.path.join(folderName,file),flags=cv2.IMREAD_GRAYSCALE)
    axarr1[i].imshow(image)
    
    fft_image=np.fft.fft2(image)
    a=np.shape(image)[0]
    b=np.shape(image)[1]
    c=3
    fft_image=np.fft.fftshift(fft_image[(a//2-a//c):(a//2+a//c),(b//2-b//c):(b//2+b//c)])
    
    axarr2[i].imshow(abs(fft_image))
    
    axarr1[i].axis("off")
    axarr2[i].axis("off")
    
plt.tight_layout()
plt.show()