# -*- coding: utf-8 -*-
"""
@author: Octavio

"""

from threading import Thread
from multiprocessing import Process
import time

def cuenta_positivamente():
    cuenta = 0
    for i in range(100000000):
        cuenta = cuenta + i

def cuenta_negativamente():
    cuenta = 0
    for i in range(100000000):
        cuenta = cuenta - i

if __name__ == "__main__":
    
    inicio = time.time()

    cuenta_positivamente()
    cuenta_negativamente()
    
    fin = time.time()

    print("Tiempo serial:", fin - inicio)
    
    inicio = time.time()

    positivo = Thread(target=cuenta_positivamente)
    negativo = Thread(target=cuenta_negativamente)
    
    positivo.start()
    negativo.start()

    positivo.join()
    positivo.join()

    fin = time.time()
    
    print("Tiempo hilos:", fin - inicio)
    
    inicio = time.time()

    positivo = Process(target=cuenta_positivamente)
    negativo = Process(target=cuenta_negativamente)
   
    positivo.start()
    negativo.start()

    positivo.join()
    positivo.join()

    fin = time.time()
    

    print("Tiempo procesos:", fin - inicio)
