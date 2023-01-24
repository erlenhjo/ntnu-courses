# -*- coding: utf-8 -*-
"""
Created on Mon Oct 11 20:45:55 2021

@author: Erlend Hektoen Johansen
"""

import pims
import matplotlib.pyplot as plt
import trackpy as tp
import numpy as np

filenames = ["tracking take 2/A1.avi", "tracking take 2/A2.avi", "tracking take 2/A3.avi",
             "tracking take 2/B1.avi", "tracking take 2/B2.avi", "tracking take 2/B3.avi"]
filenames=["Magx40_7fps_BrightF_22092022-sampleA.avi"]

trackParticles = True
generatePlots = True

particleDiameter = 11
minmass = 100
search_range = 7
minlength = 100

pixelSize = 50*10**(-6)/215  # pixel length in um
fps = 7.5
t = 1/fps

minimumMSD = 1*(pixelSize)**2


def extractParticleDicts(t):
    particleDict = {}
    for particle in t["particle"].unique():
        particleData = t[t["particle"] == particle]
        particleDict[particle] = particleData.to_dict("index")
    return particleDict


def particleMSD(p, pixelSize):
    sum = 0
    num = 0
    for frame in p.keys():
        if(frame-1 in p.keys()):
            sum += (p[frame]["x"]-p[frame-1]["x"])**2 + (p[frame]["y"]-p[frame-1]["y"])**2
            num += 1
    msd = sum/num
    return msd*pixelSize**2


def particleRadius(p, ipxelSize):
    sumR = 0
    num = 0
    for frame in p.keys():
        sumR += p[frame]["size"]
        num += 1
    avgR = sumR/num
    return avgR*pixelSize


def trackParticlesInVideo(frames):
    features = tp.batch(frames, particleDiameter, minmass=minmass)
    t0 = tp.link(features, search_range=search_range)

    t1 = tp.filter_stubs(t0, minlength)

    plt.figure()
    tp.plot_traj(t1)

    d = tp.compute_drift(t1)
    plt.figure()
    d.plot()

    particles = extractParticleDicts(t1)
    msdVals = [particleMSD(p, pixelSize) for p in particles.values()]
    radii = [particleRadius(p, pixelSize) for p in particles.values()]
    return [msdVals, radii]


def filterByMinMSD(msdVals, radiiVals):
    filteredMSD = []
    filteredRadii = []
    for i in range(len(msdVals)):
        if msdVals[i] > minimumMSD:
            filteredMSD.append(msdVals[i])
            filteredRadii.append(radiiVals[i])
    return filteredMSD, filteredRadii


def plotData(msdVals_1, msdVals_2, msdVals_3, radiiOpt_1, radiiOpt_2, radiiOpt_3, sample):
    plt.rc('font', size=20)          # controls default text sizes
    plt.rc('axes', titlesize=28)     # fontsize of the axes title
    plt.rc('axes', labelsize=20)    # fontsize of the x and y labels
    plt.rc('xtick', labelsize=20)    # fontsize of the tick labels
    plt.rc('ytick', labelsize=20)    # fontsize of the tick labels
    plt.rc('legend', fontsize=20)    # legend fontsize
    plt.rc('figure', titlesize=40)  # fontsize of the figure title
    
    
    
    
    
    if sample=="A":
        color="tab:blue"
    if sample=="B":
        color="tab:orange"
    
    D_1 = np.array([msd/(4*t) for msd in msdVals_1])
    D_2 = np.array([msd/(4*t) for msd in msdVals_2])
    D_3 = np.array([msd/(4*t) for msd in msdVals_3])

    print(f"\nSample {sample} - Diffusion constants\\\\ \\hline")
    print(
        "Video number & Mean [µm$^2$/s] & Std. dev. [µm$^2$/s] & Number of particles\\\\ \\hline")
    print(f"1&{np.mean(D_1*10**12):.2f}&{np.sqrt(np.var(D_1*10**12)):.2f}&{len(D_1)}\\\\")
    print(f"2&{np.mean(D_2*10**12):.2f}&{np.sqrt(np.var(D_2*10**12)):.2f}&{len(D_2)}\\\\")
    print(f"3&{np.mean(D_3*10**12):.2f}&{np.sqrt(np.var(D_3*10**12)):.2f}&{len(D_3)}\\\\ \\hline")
    mean = np.mean([np.mean(D_1), np.mean(D_2), np.mean(D_3)])*10**12
    stdd = np.sqrt(np.var(np.concatenate((D_1,D_2,D_3),axis=None)))*10**12
    print(f"Global mean&{mean:.2f}\\\\")
    print(f"Global std. dev.&{stdd:.2f}\\\\")
    print(f"Global particle count&{len(D_1)+len(D_2)+len(D_3)}\\\\")


    bins = np.linspace(0, 1.5, 51)
    
    plt.figure()
    plt.title(f"Sample {sample} - Video 1")
    plt.hist(D_1*10**12, bins=bins, label="Video 1",color=color)
    plt.xlabel("Diffusion constant [µm$^2$/s]")
    plt.ylabel("# of particles")
    plt.savefig(f"Sample {sample} - Diffusion constants - 1",bbox_inches='tight')
    
    plt.figure()
    plt.title(f"Sample {sample} - Video 2")
    plt.hist(D_2*10**12, bins=bins, label="Video 2",color=color)
    plt.xlabel("Diffusion constant [µm$^2$/s]")
    plt.ylabel("# of particles")
    plt.savefig(f"Sample {sample} - Diffusion constants - 2",bbox_inches='tight')
               
    plt.figure()
    plt.title(f"Sample {sample} - Video 3")
    plt.hist(D_3*10**12, bins=bins, label="Video 3",color=color)
    plt.xlabel("Diffusion constant [µm$^2$/s]")
    plt.ylabel("# of particles")
    plt.savefig(f"Sample {sample} - Diffusion constants - 3",bbox_inches='tight')
               
    plt.figure()
    plt.title(f"Sample {sample} - Total")
    plt.hist(np.append(np.append(D_1,D_2),D_3)*10**12, bins=bins, label="Total",color=color)
    plt.xlabel("Diffusion constant [µm$^2$/s]")
    plt.ylabel("# of particles")
    plt.savefig(f"Sample {sample} - Diffusion constants - T",bbox_inches='tight')

    k_b = 1.38064852*10**(-23)
    viscosity = 1*10**(-3)
    T = 292.15

    radiiHyd_1 = k_b*T/(6*3.14*viscosity*D_1)*10**9
    radiiHyd_2 = k_b*T/(6*3.14*viscosity*D_2)*10**9
    radiiHyd_3 = k_b*T/(6*3.14*viscosity*D_3)*10**9

    print(f"\nSample {sample} - Hydrodynamic radii\\\\ \\hline")
    print("Video number & Mean [µm] & Std. dev. [µm] & Number of particles\\\\ \\hline")
    print(f"1&{np.mean(radiiHyd_1)*10**(-3):.2f}&{np.sqrt(np.var(radiiHyd_1))*10**(-3):.2f}&{len(radiiHyd_1)}\\\\")
    print(f"2&{np.mean(radiiHyd_2)*10**(-3):.2f}&{np.sqrt(np.var(radiiHyd_2))*10**(-3):.2f}&{len(radiiHyd_2)}\\\\")
    print(f"3&{np.mean(radiiHyd_3)*10**(-3):.2f}&{np.sqrt(np.var(radiiHyd_3))*10**(-3):.2f}&{len(radiiHyd_3)}\\\\ \\hline")
    mean = np.mean([np.mean(radiiHyd_1), np.mean(
        radiiHyd_2), np.mean(radiiHyd_3)])*10**(-3)
    stdd = np.sqrt(
        np.var(np.concatenate((radiiHyd_1,radiiHyd_2,radiiHyd_3),axis=None)))*10**(-3)
    print(f"Global mean&{mean:.2f}\\\\")
    print(f"Global std. dev.&{stdd:.2f}\\\\")
    print(f"Global particle count&{len(radiiHyd_1)+len(radiiHyd_2)+len(radiiHyd_3)}\\\\")

    bins = np.linspace(0, 2000, 41)*10**(-3)
    
    plt.figure()
    plt.title(f"Sample {sample} - Video 1")
    plt.hist(radiiHyd_1*10**(-3), bins=bins, label="Video 1",color=color)
    plt.xlabel("Radius [µm]")
    plt.ylabel("# of particles")
    plt.savefig(f"Sample {sample} - Hydrodynamic particle radii - 1",bbox_inches='tight')
    
    plt.figure()
    plt.title(f"Sample {sample} - Video 2")
    plt.hist(radiiHyd_2*10**(-3), bins=bins, label="Video 2",color=color)
    plt.xlabel("Radius [µm]")
    plt.ylabel("# of particles")
    plt.savefig(f"Sample {sample} - Hydrodynamic particle radii - 2",bbox_inches='tight')
    
    plt.figure()
    plt.title(f"Sample {sample} - Video 3")
    plt.hist(radiiHyd_3*10**(-3), bins=bins, label="Video 3",color=color)
    plt.xlabel("Radius [µm]")
    plt.ylabel("# of particles")
    plt.savefig(f"Sample {sample} - Hydrodynamic particle radii - 3",bbox_inches='tight')
    
    plt.figure()
    plt.title(f"Sample {sample} - Total")
    plt.hist(np.append(np.append(radiiHyd_1,radiiHyd_2),radiiHyd_3)*10**(-3), bins=bins, label="Total",color=color)
    plt.xlabel("Radius [µm]")
    plt.ylabel("# of particles")
    plt.savefig(f"Sample {sample} - Hydrodynamic particle radii - T",bbox_inches='tight')

    radiiOpt_1=np.array(radiiOpt_1)*10**9
    radiiOpt_2=np.array(radiiOpt_2)*10**9
    radiiOpt_3=np.array(radiiOpt_3)*10**9

    print(f"\nSample {sample} - Optical radii\\\\ \\hline")
    print(
        "Video number & Mean [µm] & Std. dev. [µm] & Number of particles\\\\ \\hline")
    print(
        f"1&{np.mean(radiiOpt_1)*10**(-3):.2f}&{np.sqrt(np.var(radiiOpt_1))*10**(-3):.2f}&{len(radiiOpt_1)}\\\\")
    print(
        f"2&{np.mean(radiiOpt_2)*10**(-3):.2f}&{np.sqrt(np.var(radiiOpt_2))*10**(-3):.2f}&{len(radiiOpt_2)}\\\\")
    print(
        f"3&{np.mean(radiiOpt_3)*10**(-3):.2f}&{np.sqrt(np.var(radiiOpt_3))*10**(-3):.2f}&{len(radiiOpt_3)}\\\\ \\hline")
    mean = np.mean([np.mean(radiiOpt_1), np.mean(
        radiiOpt_2), np.mean(radiiOpt_3)])*10**(-3)
    stdd = np.sqrt(
        np.var(np.concatenate((radiiOpt_1,radiiOpt_2,radiiOpt_3),axis=None)))*10**(-3)
    print(f"Global mean&{mean:.2f}\\\\")
    print(f"Global std. dev.&{stdd:.2f}\\\\")
    print(f"Global particle count&{len(radiiOpt_1)+len(radiiOpt_2)+len(radiiOpt_3)}\\\\")
    
    bins = np.linspace(400, 800, 41)*10**(-3)
    
    plt.figure()
    plt.title(f"Sample {sample} - Video 1")
    plt.hist(radiiOpt_1*10**(-3), bins=bins,color=color)
    plt.xlabel("Radius [µm]")
    plt.ylabel("# of particles")
    plt.savefig(f"Sample {sample} - Optical particle radii - 1",bbox_inches='tight')
    
    plt.figure()
    plt.title(f"Sample {sample} - Video 2")
    plt.hist(radiiOpt_2*10**(-3), bins=bins,color=color)
    plt.xlabel("Radius [µm]")
    plt.ylabel("# of particles")
    plt.savefig(f"Sample {sample} - Optical particle radii - 2",bbox_inches='tight')
    
    plt.figure()
    plt.title(f"Sample {sample} - Video 3")
    plt.hist(radiiOpt_3*10**(-3), bins=bins,color=color)
    plt.xlabel("Radius [µm]")
    plt.ylabel("# of particles")
    plt.savefig(f"Sample {sample} - Optical particle radii - 3",bbox_inches='tight')
    
    plt.figure()
    plt.title(f"Sample {sample} - Total")
    plt.hist(np.append(np.append(radiiOpt_1,radiiOpt_2),radiiOpt_3)*10**(-3), bins=bins,color=color)
    plt.xlabel("Radius [µm]")
    plt.ylabel("# of particles")
    plt.savefig(f"Sample {sample} - Optical particle radii - T",bbox_inches='tight')


def main():
    tp.quiet()
    if trackParticles == True:
        frames = pims.as_gray(pims.open(filenames[0]))
        results = trackParticlesInVideo(frames)
        np.save("msdVals_A1.npy", results[0])
        np.save("radiiVals_A1.npy", results[1])

        frames = pims.as_gray(pims.open(filenames[1]))
        results = trackParticlesInVideo(frames)
        np.save("msdVals_A2.npy", results[0])
        np.save("radiiVals_A2.npy", results[1])

        frames = pims.as_gray(pims.open(filenames[2]))
        results = trackParticlesInVideo(frames)
        np.save("msdVals_A3.npy", results[0])
        np.save("radiiVals_A3.npy", results[1])

        frames = pims.as_gray(pims.open(filenames[3]))
        results = trackParticlesInVideo(frames)
        np.save("msdVals_B1.npy", results[0])
        np.save("radiiVals_B1.npy", results[1])

        frames = pims.as_gray(pims.open(filenames[4]))
        results = trackParticlesInVideo(frames)
        np.save("msdVals_B2.npy", results[0])
        np.save("radiiVals_B2.npy", results[1])

        frames = pims.as_gray(pims.open(filenames[5]))
        results = trackParticlesInVideo(frames)
        np.save("msdVals_B3.npy", results[0])
        np.save("radiiVals_B3.npy", results[1])

    if generatePlots == True:
        msdVals_A1 = np.load("msdVals_A1.npy")
        msdVals_A2 = np.load("msdVals_A2.npy")
        msdVals_A3 = np.load("msdVals_A3.npy")
        msdVals_B1 = np.load("msdVals_B1.npy")
        msdVals_B2 = np.load("msdVals_B2.npy")
        msdVals_B3 = np.load("msdVals_B3.npy")

        radiiVals_A1 = np.load("radiiVals_A1.npy")
        radiiVals_A2 = np.load("radiiVals_A2.npy")
        radiiVals_A3 = np.load("radiiVals_A3.npy")
        radiiVals_B1 = np.load("radiiVals_B1.npy")
        radiiVals_B2 = np.load("radiiVals_B2.npy")
        radiiVals_B3 = np.load("radiiVals_B3.npy")

        filteredMSD_A1, filteredRadii_A1 = filterByMinMSD(
            msdVals_A1, radiiVals_A1)
        filteredMSD_A2, filteredRadii_A2 = filterByMinMSD(
            msdVals_A2, radiiVals_A2)
        filteredMSD_A3, filteredRadii_A3 = filterByMinMSD(
            msdVals_A3, radiiVals_A3)
        filteredMSD_B1, filteredRadii_B1 = filterByMinMSD(
            msdVals_B1, radiiVals_B1)
        filteredMSD_B2, filteredRadii_B2 = filterByMinMSD(
            msdVals_B2, radiiVals_B2)
        filteredMSD_B3, filteredRadii_B3 = filterByMinMSD(
            msdVals_B3, radiiVals_B3)

        plotData(filteredMSD_A1, filteredMSD_A2, filteredMSD_A3,
                 filteredRadii_A1, filteredRadii_A2, filteredRadii_A3, "A")
        plotData(filteredMSD_B1, filteredMSD_B2, filteredMSD_B3,
                 filteredRadii_B1, filteredRadii_B2, filteredRadii_B3, "B")


if __name__ == "__main__":
    main()
