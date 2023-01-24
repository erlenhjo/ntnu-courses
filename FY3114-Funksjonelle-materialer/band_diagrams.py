# -*- coding: utf-8 -*-
"""
Created on Sat Oct 29 15:37:21 2022

@author: Erlend Johansen
"""

import matplotlib.pyplot as plt
import numpy as np
import matplotlib.transforms as mpl_t




def schottky(phi_m,phi_s,chi_s, bias, N, k_m,k_s):   
    
    phi_s=phi_s+bias
    
    m_v=np.zeros(k_m*N)+phi_m
    s_v=np.zeros(k_s*N)+phi_s

    s_c=np.zeros(k_s*N)+phi_s-chi_s
    m_c=np.zeros(k_m*N)
    
    s_F=np.zeros(k_s*N)+bias
    m_F=np.zeros(k_m*N)
    
    def quadratic_barrier(a,b,N,k_m,k_s):
        
        c=k_s*N//2
        
        x_1=np.zeros(k_m*N)
        x_2=(np.linspace(1,0,c)**2)*a
        x_3=np.zeros(k_s*N-c)
        
        return np.append(x_1,np.append(x_2,x_3,axis=0),axis=0)

    barrier=quadratic_barrier(phi_m-phi_s, phi_m, N, k_m, k_s)

    v=np.append(m_v,s_v,axis=0)
    v=v+barrier
    
    cb=np.append(m_c,s_c,axis=0)
    cb=cb+barrier
    
    
    F=np.append(m_F,s_F,axis=0)     
        


    return F,cb,v

    
def plot_schottky(bias,ax,show_E=False,show_Phi_m=False,show_Phi_s=False,show_Phi_b=False,show_Chi=False,show_bias=False):
    N=10000
    k_m=2
    k_s=3
    
    x=np.linspace(0,1,(k_m+k_s)*N)
    
    phi_m, phi_s, chi = 70,50,45
    
    fermi_level, conduction_band, vacuum_level=schottky(phi_m,phi_s,chi,bias,N,k_m,k_s)
    
    ax.plot(x, vacuum_level,color="k", linestyle="dashdot", label="Vacuum level")
    ax.plot(x[k_m*N-1:],fermi_level[k_m*N-1:],color="k",linestyle="dashed", label="Fermi level")
    ax.plot(x, conduction_band,color="k",linestyle="solid", label="Conduction band")
    ax.axis("off") 
    
    ax.annotate("metal",xy=(0.2,1.0),xycoords="axes fraction",horizontalalignment="center")
    ax.annotate("n-type",xy=(0.7,1.0),xycoords="axes fraction",horizontalalignment="center")
    
    
    if show_E:
        ax.annotate("E/q",xy=(-0.1,0.1),xytext=(-0.1,1.0),xycoords="axes fraction",horizontalalignment="center",rotation=0,arrowprops={"arrowstyle":"<-"},fontsize="large")

    if show_Chi:
        x=0.8
        x_shift=-0.01
        
        y_max=phi_s+bias
        y_min=phi_s-chi+bias
        
        y_avg=(y_max+y_min)/2
        ax.annotate("",xy=(x,y_min),xytext=(x,y_max),xycoords="data",arrowprops={"arrowstyle":"<->"})
        ax.annotate(r"$\chi $",usetex=True,xy=(x+x_shift,y_avg),xycoords="data",horizontalalignment="right",rotation=0,fontsize="large")

        
    if show_Phi_m:
        x=0.1
        x_shift=0.01
        
        y_max=phi_m
        y_min=0
        
        y_avg=(y_max+y_min)/2
        ax.annotate("",xy=(x,y_min),xytext=(x,y_max),xycoords="data",arrowprops={"arrowstyle":"<->"})
        ax.annotate(r"$\Phi_m$",usetex=True,xy=(x+x_shift,y_avg),xycoords="data",horizontalalignment="left",rotation=0,fontsize="large")

    if show_Phi_s:
        x=0.9
        x_shift=0.01
        
        y_max=phi_s+bias
        y_min=bias
        
        y_avg=(y_max+y_min)/2
        ax.annotate("",xy=(x,y_min),xytext=(x,y_max),xycoords="data",arrowprops={"arrowstyle":"<->"})
        ax.annotate(r"$\Phi_s$",usetex=True,xy=(x+x_shift,y_avg),xycoords="data",horizontalalignment="left",rotation=0,fontsize="large")
        
    if show_Phi_b:
        x=0.35
        x_shift=-0.01
        
        y_max=phi_m-chi
        y_min=0
        
        y_avg=(y_max+y_min)/2
        ax.annotate("",xy=(x,y_min),xytext=(x,y_max),xycoords="data",arrowprops={"arrowstyle":"<->"})
        ax.annotate(r"$\Phi_b$",usetex=True,xy=(x+x_shift,y_avg),xycoords="data",horizontalalignment="right",rotation=0,fontsize="large")
    
    if show_bias:
        if bias>0:
            x=0.45
            x_shift=0.01
            align="left"
        else:
            x=0.35
            x_shift=-0.01
            align="right"
        
        y_max=0
        y_min=bias
        
        y_avg=(y_max+y_min)/2
        ax.annotate("",xy=(x,y_min),xytext=(x,y_max),xycoords="data",arrowprops={"arrowstyle":"<->"})
        ax.annotate(r"$V_{bias}$",usetex=True,xy=(x+x_shift,y_avg),xycoords="data",horizontalalignment=align,rotation=0,fontsize="large")
    
    
def plot_mnm(bias,ax,show_E=False,show_Phi_m=False,show_Phi_s=False,show_Phi_b=False,show_Chi=False,show_bias=False):
    N=2000
    k_m=2
    k_s=3
    
    phi_m, phi_s, chi = 70,50,45
    
    x=np.linspace(0,2,2*(k_m+k_s)*N)
    
    fermi_level_left, conduction_band_left, vacuum_level_left=schottky(phi_m,phi_s,chi,bias/2,N,k_m,k_s)
    fermi_level_right, conduction_band_right, vacuum_level_right=schottky(phi_m,phi_s,chi,-bias/2,N,k_m,k_s)
    
    
    fermi_level_right=np.flip(fermi_level_right,axis=0)+bias
    conduction_band_right=np.flip(conduction_band_right,axis=0)+bias
    vacuum_level_right=np.flip(vacuum_level_right,axis=0)+bias
    
    vacuum_level=np.append(vacuum_level_left,vacuum_level_right,axis=0)-bias
    conduction_band=np.append(conduction_band_left,conduction_band_right,axis=0)-bias
    fermi_level=np.append(fermi_level_left,fermi_level_right)-bias
    
    ax.plot(x, vacuum_level,color="k", linestyle="dashdot", label="Vacuum level")
    ax.plot(x[k_m*N-1:(k_m+2*k_s)*N+1],fermi_level[k_m*N-1:(k_m+2*k_s)*N+1],color="k",linestyle="dashed", label="Fermi level")
    ax.plot(x, conduction_band,color="k",linestyle="solid", label="Conduction band")
    ax.axis("off")
    
    ax.annotate("metal",xy=(0.12,1.0),xycoords="axes fraction",horizontalalignment="center")
    ax.annotate("n-type",xy=(0.5,1.0),xycoords="axes fraction",horizontalalignment="center")
    ax.annotate("metal",xy=(0.88,1.0),xycoords="axes fraction",horizontalalignment="center")
    
    if show_E:
        ax.annotate("E/q",xy=(-0.1,0.1),xytext=(-0.1,1.0),xycoords="axes fraction",horizontalalignment="center",rotation=0,arrowprops={"arrowstyle":"<-"},fontsize="large")

    if show_Phi_b:
        x=0.35
        x_shift=-0.01
        
        y_max=phi_m-chi-bias
        y_min=0-bias
        
        y_avg=(y_max+y_min)/2
        ax.annotate("",xy=(x,y_min),xytext=(x,y_max),xycoords="data",arrowprops={"arrowstyle":"<->"})
        ax.annotate(r"$\Phi_b$",usetex=True,xy=(x+x_shift,y_avg),xycoords="data",horizontalalignment="right",rotation=0,fontsize="large")
    
    if show_Phi_b:
        x=2-0.35
        x_shift=0.01
        
        y_max=phi_m-chi
        y_min=0
        
        y_avg=(y_max+y_min)/2
        ax.annotate("",xy=(x,y_min),xytext=(x,y_max),xycoords="data",arrowprops={"arrowstyle":"<->"})
        ax.annotate(r"$\Phi_b$",usetex=True,xy=(x+x_shift,y_avg),xycoords="data",horizontalalignment="left",rotation=0,fontsize="large")
    
    
    if show_bias:
        if bias>0:
            x=1.75
            x_shift=0.01
            align="left"
        elif bias<0:
            x=1.65
            x_shift=-0.01
            align="right"
        
        if bias!=0:
            y_max=0-bias
            y_min=bias-bias
            
            y_avg=(y_max+y_min)/2
            ax.annotate("",xy=(x,y_min),xytext=(x,y_max),xycoords="data",arrowprops={"arrowstyle":"<->"})
            ax.annotate(r"$V_{bias}$",usetex=True,xy=(x+x_shift,y_avg),xycoords="data",horizontalalignment=align,rotation=0,fontsize="large")
        
    
    
    
    
    
def schottky_fig():
    fig, (ax1,ax2,ax3)=plt.subplots(ncols=3,figsize=(9,3),sharey=True)
    
    plot_schottky(0,ax1,show_E=True,show_Chi=True,show_Phi_m=True,show_Phi_b=True,show_Phi_s=True,show_bias=False)
    plot_schottky(-15,ax2,show_E=True,show_Phi_b=True,show_bias=True)
    plot_schottky(15,ax3,show_E=True,show_Phi_b=True,show_bias=True)

    fig.tight_layout(pad=1,h_pad=2,w_pad=2)

    extent1 = mpl_t.Bbox.from_extents([[0,0],[3,3]])
    fig.savefig('schotttky_bands_1.png', bbox_inches=extent1,dpi=400)
    extent2 = mpl_t.Bbox.from_extents([[3,0],[6,3]])
    fig.savefig('schotttky_bands_2.png', bbox_inches=extent2,dpi=400)
    extent3 = mpl_t.Bbox.from_extents([[6,0],[9,3]])
    fig.savefig('schotttky_bands_3.png', bbox_inches=extent3,dpi=400)    
    
    fig.savefig("schotttky_bands.png")
    
    fig.show()
    
def mnm_fig():
    fig, (ax1,ax2,ax3)=plt.subplots(ncols=3,figsize=(9,3), sharey=True)
    
    plot_mnm(0,ax1,show_E=True,show_Phi_b=True,show_bias=True)
    plot_mnm(20,ax2,show_E=True,show_Phi_b=True,show_bias=True)
    plot_mnm(30,ax3,show_E=True,show_Phi_b=True,show_bias=True)
    
    
    
    
    fig.tight_layout(pad=1,h_pad=2,w_pad=2)

    extent1 = mpl_t.Bbox.from_extents([[0,0],[3,3]])
    fig.savefig('mnm_bands_1.png', bbox_inches=extent1,dpi=400)
    extent2 = mpl_t.Bbox.from_extents([[3,0],[6,3]])
    fig.savefig('mnm_bands_2.png', bbox_inches=extent2,dpi=400)
    extent3 = mpl_t.Bbox.from_extents([[6,0],[9,3]])
    fig.savefig('mnm_bands_3.png', bbox_inches=extent3,dpi=400)
    
    fig.savefig("mnm_bands.png")
   
    
if __name__=="__main__":
    
    schottky_fig()
    mnm_fig()
    
    