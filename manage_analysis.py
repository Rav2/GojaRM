#!/usr/bin/env python
# -*- coding: utf-8 -*-

#import ROOT
import matplotlib.pyplot as plt
from numpy import *
from matplotlib import rcParams, rcdefaults, rc
from matplotlib.colors import LogNorm

import os

import matplotlib.image as mpimg

if __name__ == "__main__":
  
  #root_directory = "/media/pkowalski/TOSHIBA\ EXT/NCBJ/GATE_OUTPUT/Sensitivity/R95_1lay_L020_7mm/"
  root_directory = "./output/"

  os.system("rm ./coincidences.txt")
  
  for i in range(1):
      
      i = i+1
      
      root_file = root_directory + "output" +"_side_large" + ".root"
      
      command = "./analysis 0.2 " + root_file + " >> ./coincidences.txt"
      os.system(command)
      #print command
      
  
  
  
  #energies = linspace(50,280,24)
  ##energies = linspace(0.2,0.28,9)
  ##energies = linspace(50,190,15)
  ##energies = linspace(170,190,3)
  ##print energies
  ##=========================================

  #for energy in energies:
   
    #command = "./analysis " + str(energy/1000.) + " > coincidences/Gamma_L050_simplified_1MBq_100s_short_source/coincidences_100MBq_1s_Gamma_L050_" + str(int(energy)) + "keV"

    #print command
    #os.system(command)
    
    ##filename = "./final/coincidences_SF_1M_100s_Gamma_" + str(int(energy)) + "keV"
    ##filenames.append(filename)
  
