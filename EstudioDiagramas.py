# -*- coding: utf-8 -*-
"""
Created on Thu Mar 21 19:20:45 2019

@author: Guillermo
"""

import SantanderGraf as gr

def main():
    n=4 #Columna a estudiar
    j=3 #Tipo de gasto (relativo a la columna)
    mes=6 #mes, en nº
    clase='DE' #clase que filtra. En string
    
     
    gr.grafico(n,j,mes,clase)
            

if __name__=='__main__':
    main()