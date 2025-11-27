from multiprocessing import Process
from threading import Thread
import time


def suma(a, b):
    print("Suma: ", a + b)
    time.sleep(5)

def resta(a, b):
    print("Resta: ", a - b)
    time.sleep(10)
    

if __name__ == "__main__":

    a = 25
    b = 30
    
    inicio = time.time()

    suma(a, b)
    resta(a, b)
    
    fin = time.time()
    
    print("Tiempo serial:", fin - inicio)

    inicio = time.time()
    hilo_suma = Thread(target=suma, args=(a, b))
    hilo_resta = Thread(target=resta, args=(a, b))
    
    hilo_suma.start()
    hilo_resta.start()

    hilo_suma.join()
    hilo_resta.join()
    
    fin = time.time()
    
    print("Tiempo hilos:", fin - inicio)
    
    inicio = time.time()
    proceso_suma = Process(target=suma, args=(a, b))
    proceso_resta = Process(target=resta, args=(a, b))
    
    proceso_suma.start()
    proceso_resta.start()

    proceso_suma.join()
    proceso_resta.join()
    
    fin = time.time()
    
    print("Tiempo procesos:", fin - inicio)
