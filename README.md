Videojuego_Tanque
=================

Videojuego Simple usando el microcontrolador AT89C52 y una pantalla LCD 16x2

Descripcion:

El videojuego consiste en disparar a un enemigo que está en movimiento parpadeando. 

El disparo se realizara mediante un push button conectado al puerto 0.1.  

El envió de datos y comandos se realizara por el puerto 2 del microcontrolador.  
Otro push button estará conectado en el puerto 3.2 INT 0 para el manejo de 
interrupciones externas, este tendrá como fin manejar una pausa momentánea. 

Rs, Rw y En estarán controlados mediante los pines de los puertos 3.1,3.2 y 3.6 respectivamente.
