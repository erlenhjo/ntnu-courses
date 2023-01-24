# -*- coding: utf-8 -*-
"""
Created on Mon Oct 11 20:45:55 2021

@author: Erlend Hektoen Johansen
"""

import pims
import matplotlib.pyplot as plt
import trackpy as tp
import numpy as np

filenames=["tracking take 2/A1.avi","tracking take 2/A2.avi","tracking take 2/A3.avi",
           "tracking take 2/B1.avi","tracking take 2/B2.avi","tracking take 2/B3.avi"]

filenames=["Magx40_7fps_BrightF_22092022-sampleA.avi"]

trackParticles=True
generatePlots=True

particleDiameter=7  #7 
invert=False
minmass=100         #100
search_range=7            
minlength=50

pixelSize=50*10**(-6)/215     #pixel length in um
fps=7.5
t=1/fps

minimumMSD=1*(pixelSize)**2

def extractParticleDicts(t):
    particleDict={}
    for particle in t["particle"].unique():  
        particleData=t[t["particle"]==particle]
        particleDict[particle]=particleData.to_dict("index")
    return particleDict
        
def particleMSD(p,pixelSize):
    sum=0
    num=0
    for frame in p.keys():           
        if(frame-1 in p.keys()):
            sum+=(p[frame]["x"]-p[frame-1]["x"])**2+(p[frame]["y"]-p[frame-1]["y"])**2
            num+=1   
    if num==0:
        return 0     #will be filtered out
    
    msd=sum/num  
    return msd*pixelSize**2

def particleRadius(p,pixelSize):
    sumR=0
    num=0
    for frame in p.keys():           
        sumR+=p[frame]["size"]
        num+=1
    avgR=sumR/num  
    return avgR*pixelSize
    
def trackParticlesInVideo(frames):
    features=tp.batch(frames,particleDiameter,invert=invert, minmass=minmass)
    t0=tp.link(features,search_range=search_range) 
    
    t1 = tp.filter_stubs(t0, minlength)
    
    plt.figure()
    tp.plot_traj(t1);
    
    d = tp.compute_drift(t1)
    plt.figure()
    d.plot()
    
    particles=extractParticleDicts(t1)
    msdVals=[particleMSD(p,pixelSize) for p in particles.values()]
    radii=[particleRadius(p,pixelSize) for p in particles.values()]
    return [msdVals,radii]

def filterByMinMSD(msdVals,radiiVals):
    filteredMSD=[]
    filteredRadii=[]
    for i in range(len(msdVals)):
        if msdVals[i]>minimumMSD:
            filteredMSD.append(msdVals[i])
            filteredRadii.append(radiiVals[i])
    return filteredMSD,filteredRadii        
    
def plotData(msdVals_A,msdVals_B,radiiEst_A,radiiEst_B):
    D_A=np.array([msd/(4*t) for msd in msdVals_A])
    D_B=np.array([msd/(4*t) for msd in msdVals_B])
    
    meanD_A, stddD_A= np.mean(D_A), np.sqrt(np.var(D_A))
    meanD_B, stddD_B = np.mean(D_B), np.sqrt(np.var(D_B))
    
    plt.figure()
    plt.title("Diffusion constants")
    plt.hist(D_A, bins=40, density=True)
    plt.hist(D_B, bins=40, alpha=0.5, density=True)
    
    k_b=1.38064852*10**(-23)
    viscosity=10**(-3)
    T=293.15
    
    radiiHyd_A=k_b*T/(6*3.14*viscosity*D_A)
    radiiHyd_B=k_b*T/(6*3.14*viscosity*D_B)
    
    meanRHyd_A, stddRHyd_A = np.mean(radiiHyd_A), np.sqrt(np.var(radiiHyd_A))
    meanRHyd_B, stddRHyd_B = np.mean(radiiHyd_B), np.sqrt(np.var(radiiHyd_B))

    print(meanRHyd_A)
    print(meanRHyd_B)    

    plt.figure()
    plt.title("Hydrodynamic particle radii")
    plt.hist(radiiHyd_A, bins=40,density=True)
    plt.hist(radiiHyd_B, bins=40,alpha=0.5,density=True)
    
    plt.figure()
    plt.title("Estimated particle radii")
    plt.hist(radiiEst_A, bins=40,density=True)
    plt.hist(radiiEst_B, bins=40,alpha=0.5,density=True)
    
def main():
    #tp.quiet()
    msdVals_A=[]
    msdVals_B=[]
    radiiVals_A=[]
    radiiVals_B=[]
    
    if trackParticles==True:
        for filename in filenames[:3]:
            frames=pims.as_gray(pims.open(filename))
            results=trackParticlesInVideo(frames)
            msdVals_A.extend(results[0])
            radiiVals_A.extend(results[1])
            
        for filename in filenames[3:]:
            frames=pims.as_gray(pims.open(filename))
            results=trackParticlesInVideo(frames)
            msdVals_B.extend(results[0])
            radiiVals_B.extend(results[1])
            
        np.save("msdVals_A.npy",msdVals_A)
        np.save("msdVals_B.npy",msdVals_B)
        np.save("radiiVals_A.npy",radiiVals_A)
        np.save("radiiVals_B.npy",radiiVals_B)
        
    if generatePlots==True:
        msdVals_A=np.load("msdVals_A.npy")
        msdVals_B=np.load("msdVals_B.npy")
        radiiVals_A=np.load("radiiVals_A.npy")
        radiiVals_B=np.load("radiiVals_B.npy")
        
        filteredMSD_A,filteredRadii_A=filterByMinMSD(msdVals_A,radiiVals_A)
        filteredMSD_B,filteredRadii_B=filterByMinMSD(msdVals_B,radiiVals_B)
        
        plotData(filteredMSD_A,filteredMSD_B,filteredRadii_A,filteredRadii_B)
    
if __name__=="__main__":
    main()
    
    