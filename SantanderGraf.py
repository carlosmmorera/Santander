# -*- coding: utf-8 -*-
"""
Created on Wed Mar 20 20:50:34 2019

@author: Guillermo
"""

import matplotlib.pyplot as plt
#import numpy as np
#import pandas as pd
#import pyspark as sp

def grafico(n,j,mes,clase):
        parejasdic=dict()
        gasto=dict()
        datosgraf=[]
        # n es la columna a estudiar
        # j es tipo de gasto j=2 trans j=3 recibo j=4 tarjeta
        # mes es el mes a estudiar
        # clase es el tipo de cliente a estudiar. ¿Traduccón de clases?
        with open("1553016165_sociodemo.csv") as file1:
            with open("1553016181_transaccional.csv") as file2:
                file1.readline()
                file2.readline()
                #A cada cliente le asocio su clase
                for line in file1:
                    line=line.split(';')
                    if line[0] not in parejasdic:
                        parejasdic[line[0]]=line[n]
                #A cada cliente le asocio su gasto en ese mes y concepto
                for line in file2:
                    line=line.split(';')
                    if int(line[1])==mes:
                        if line[0] not in gasto:
                            gasto[line[0]]=float(line[j])
                        else:
                            gasto[line[0]]=gasto[line[0]]+float(line[j])
                #Comprobamos que solo añadimos los de la clase que queremos
                elementos=list(parejasdic.items())
                for i in elementos:
                    if  i[1]==clase:
                        datosgraf.append(gasto[i[0]])
                #Calculo la media para graficar
                contador=0
                x=0
                x2=0
                for i in datosgraf:
                    contador=contador+1
                    x=x+i
                    x2=x2+i**2
                media=x/contador
                media2=x2/contador
                sigma=(media2-media**2)**(1/2)
                
                #Traducción del concepto
                if j==2:
                    concepto='Transferencia'
                elif j==3:
                    concepto='Recibo'
                elif j==4:
                    concepto='Tarjeta'
                #Grafico 1
                altura=[0,0,0,0,0]
                for i in datosgraf:
                    if i<=media-2*sigma:
                        altura[0]=altura[0]+1
                    if i<=media-sigma and i>media-2*sigma:
                        altura[1]=altura[1]+1    
                    if i<=media+sigma and i>media-sigma:
                        altura[2]=altura[2]+1    
                    if i<=media+2*sigma and i>media+sigma:
                        altura[3]=altura[3]+1 
                    elif i>media+2*sigma:
                        altura[4]=altura[4]+1 
            
                    
                grafx=["M-2s",'M-s','M','M+s','M+2s']
                plt.figure(1)
                plt.title('Distribución. Mes '+str(mes)+
                          ' Concepto: '+concepto+
                          ' Categoría '+str(n)+'-"'+str(clase)+'"')
                plt.ylabel('Nº de clientes')
                plt.ylabel('Nº de clientes')
                plt.bar(grafx,altura)
                #Grafico 2
                altura1=[0,0,0,0,0]
                for i in datosgraf:
                    if i<=media-0.1*media:
                        altura1[0]=altura1[0]+1
                    if i<=media-0.05*media and i>media-0.1*media:
                        altura1[1]=altura1[1]+1    
                    if i<=media+0.05*media and i>media-0.05*media:
                        altura1[2]=altura1[2]+1    
                    if i<=media+0.05*media and i>media+0.1*media:
                        altura1[3]=altura1[3]+1 
                    elif i>media+0.1*media:
                        altura1[4]=altura1[4]+1 
                grafx1=["M-0.1M",'M-0.05M','M','M+0.05M','M+0.1M']
                plt.figure(2)
                plt.title('Distribución. Mes '+str(mes)+
                          ' Concepto: '+concepto+
                          ' Categoría '+str(n)+'-"'+str(clase)+'"')
                plt.ylabel('Nº de clientes')
                plt.bar(grafx1,altura1)
                
def main():
    pass


if __name__=='__main__':
    main()
