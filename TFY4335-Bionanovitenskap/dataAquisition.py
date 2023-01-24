# -*- coding: utf-8 -*-
"""
Created on Wed Oct 13 19:28:55 2021

@author: Erlend Johansen
"""

def particleDicts(t):
    particleDict={}
    for particle in t["particle"].unique():  
        particleData=t[t["particle"]==particle]
        particleDict[particle]=particleData.to_dict("index")
        
    return particleDict
        
        
        
def MSD(d,pixelSize):
    sum=0
    num=0
    for frame in d.keys():
        if frame-1 in d.keys():            
            sum+=(d[frame]["x"]-d[frame-1]["x"])**2+(d[frame]["y"]-d[frame-1]["y"])**2
            num+=1
    if(num==0):
        msd=0
    else:
        msd=sum/num  
    return msd*pixelSize**2