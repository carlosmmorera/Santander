# -*- coding: utf-8 -*-
"""
Created on Mon Mar  4 19:30:05 2019

@author: Guillermo
"""
#import pyspark
import matplotlib.pyplot as plt
import numpy as np
from sympy import *

def main():
    parejasdic=dict()
    gastototal=dict()
    datosgraf=[]
    with open("1553016165_sociodemo.csv") as file1:
        with open("1553016181_transaccional.csv") as file2:
            file1.readline()
            file2.readline()
            for line in file1:
                line=line.split(';')
                if line[0] not in parejasdic:
                    parejasdic[line[0]]={line[4]}
            for line in file2:
                line=line.split(';')
                if line[0] not in gastototal:
                    gastototal[line[0]]=float(line[2])+float(line[3])+float(line[4])
                else:
                    gastototal[line[0]]=gastototal[line[0]]+float(line[2])+float(line[3])+float(line[4])
            for i in parejasdic:
                datosgraf.append((str(list(parejasdic[i])[0]),gastototal[i]))
            dic=dict()
            for i in datosgraf:
                if i[0] not in dic:
                    dic[i[0]]=i[1]
                else:
                    dic[i[0]]=dic[i[0]]+i[1]
            listafinal=list(dic.items())
            grafx=[]
            grafy=[]
            for i in listafinal:
                grafx.append(i[0])
                grafy.append(i[1])
            #print(sorted(listafinal))
            print(sorted(grafy))
            plt.bar(grafx,grafy)
def dic_modelo():
     a=dict()
     with open("1553016181_transaccional.csv") as file:
         file.readline()
         for line in file:
             line=line.split(';')
             if line[0] not in a:
                 a[line[0]]=float(line[2])+float(line[3])+float(line[4])
             else:
                 a[line[0]]=a[line[0]]+float(line[2])+float(line[3])+float(line[4]) 
         return a
    
         """
         number=len(a)
         total=0
         total_2018_clientes=0
         b=Symbol('b')
         for i in a:
             total=total+a[i]
         media=total/number
         total_2018=total*1.046
         for i in a:
             total_2018_clientes=total_2018_clientes*(1+alpha(a[i]/media,b)/100)
         solve(total_2018-total_2018_clientes,a)
         """
def alpha(x,a):
    return -1/(x+1/a)+a
def reiterar(total_2018,est_inicial,a,media):
    b=0
    paso=0.1
    est=est_inicial
    total_2018_clientes=0
    for i in a:
        total_2018_clientes=total_2018_clientes+a[i]*(1+alpha(a[i]/media,est)/100)
    variable=(total_2018-total_2018_clientes)/total_2018
    variable2=variable
    while b==0:
        if variable2>0.00001:
            est=est+paso
            total_2018_clientes=0
            for i in a:
                total_2018_clientes=total_2018_clientes+a[i]*(1+alpha(a[i]/media,est)/100)
            variable2=(total_2018-total_2018_clientes)/total_2018
            if variable2*variable<0:
                paso=paso/10
                variable=variable2
        elif variable2<-0.00001:
            est=est-paso
            total_2018_clientes=0
            for i in a:
                total_2018_clientes=total_2018_clientes+a[i]*(1+alpha(a[i]/media,est)/100)
            variable2=(total_2018-total_2018_clientes)/total_2018
            if variable2*variable<0:
                paso=paso/10
                variable=variable2
        else:
            b=1
    return est
        
    
            

if __name__=='__main__':
    main()

