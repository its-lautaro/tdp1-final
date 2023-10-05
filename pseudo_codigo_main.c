<<<<<<< HEAD
//To-do
 // Modularizar
 // Reutilizar logíca de cambiar hora los modos "MODIFICAR_FECHA_HORA_ACTUAL" y "MODIFICAR_FECHA_HORA_PROGRAMA_RIEGO"
 //definir 
estado_primario = STAND_BY;
int boton_presionado();//Retorna el último botón presionado
while(1){
    // Verificar si es hora de regar y cambiar al estado de REGAR si es necesario
    if(estado_primario == STAND_BY && estoyEnHoraDeRegar()){
        estate_primario = REGAR;
		estate_secundario= PREPARADO;
    }
    // Leer el último botón presionado
    boton_presionado = BotonPresionado(); //si no se presionó un botón devuelve null o algun valor caracteristico
    
    if(estado_primario == STAND_BY && boton_presionado != null){
    	estado_primario = MENU;
    }
    if(no presioné ningun boton en 30 seg){
    	estado_primario = STAND_BY;
    }
=======
Se avanza al estado primario STAND_BY

Bucle principal del programa

	Escribir en el lcd leyenda correspondiente según estado actual

	Se lee el botón presionado
    
	Si el estado primario es STAND_BY y se presionó algún botón
		Se avanza al estado primario 'MENU'
>>>>>>> 2b38a6ec2614af270d2108f3facfea2e9de29d8c

	Si no se presionó ningún botón en 30 seg
		Se avanza al estado primario 'STAND_BY'

	Si el estado primario es 'MENU' 
		Se presionó el botón UP
	    		Se avanza el estado secundario correspondiente    
		Se presionó el boton Enter
			Se avanza el estado primario correspondiente

	Si el estado primario es 'MODIFICAR_FECHA_HORA_ACTUAL'
		Si el estado secundario es 'MODIFICANDO_FECHA'
			Se presionó el botón 'UP'
			      Incrementar la fecha
			Sino   
				Se presionó el botón 'DOWN'
			      		Decrementar la fecha
			   	Sino
			  		Se presionó el botón 'ENTER'
			     			Se avanza al estado secundario 'MODIFICAR_HORA'
		Si el estado secundario es 'MODIFICANDO_HORA'
			Se presionó el botón 'UP'
				Incrementar la hora
			Sino   
				Se presionó el botón 'DOWN'
			      		Decrementar la hora
			  	Sino
			  		Se presionó el botón 'ENTER'
			  			Se avanza al estado primario 'MENU'
			  			Se avanza al estado secundario 'MODIFICANDO_FECHA'
		       	    
	Si el estado primario es 'MODIFICAR_FECHA_HORA_PROGRAMA_RIEGO'
		Si el estado secundario es 'MODIFICANDO_FECHA'
			Dependiendo de los botones presionados se van seleccionando los días de riego
			Si se finalizó de seleccionar los días de riego
				Se avanza el estado secundario 'MODIFICANDO_HORA'
				     
		Si el estado secundario es 'MODIFICANDO_HORA'
				Se presionó el botón 'UP'
					Incrementar la hora
				Sino
					Se presionó el botón 'DOWN'
						Decrementar la hora
				  	Sino
				  		Se presionó el botón 'ENTER'
				 			Se avanza al estado secundario 'MODIFICAR_FECHA'
							Se avanza al estado primario 'MENU'
			
	Si el estado primario es 'SELECCIONAR_MODO'
		Se presionó el botón 'UP' o 'DOWN'
			Si el estado secundario es 'CAMBIAR_RIEGO_INTELIGENTE_OFF'
				Se avanza al estado secundario 'RIEGO_INTELIGENTE_ON'
	    		Sino
	    	 		Se avanza al estado secundario 'RIEGO_INTELIGENTE_OFF'	
	    	Se presionó el botón 'ENTER'
	    		Se cambia el modo inteligente dependiendo del estado secundario actual		    
	  	Se presionó el botón 'CANCELAR'
	  		Se avanza al estado primario 'MENU'
	    	
   	Si el estado primario es 'REGAR'
		Se presionó el botón 'CANCELAR'
		  	Se avanza al estado secundario 'FINALIZAR'
		Si el estado secundario es 'PREPARADO'
			Se avanza al estado secundario 'VÁLVULA1'
			Abrir válvula 1
			Inicio contador de tiempo valvula 2
		Si el estado secundario es 'VÁLVULA1'
			Si se cumplió el tiempo de riego de la valvula 1
				Se avanza al estado secundario 'VÁLVULA'
				Cerrar válvula 1
				Abrir válvula 2
				Inicio contador de tiempo valvula 2
		Si el estado secundario es 'VÁLVULA2'
			Si se cumplió el tiempo de riego de la valvula 2
				Se avanza al estado secundario 'PREPARADO'
				Se avanza al estado primario 'MENU'
				Cerrar válvula 2
		Si el estado secundario es 'FINALIZAR'
			Cerrar válvula 1
			Cerrar válvula 2
			Se avanza al estado secundario 'PREPARADO'
			Se avanza al estado primario 'MENU'
	Si el estado primario es STAND_BY y es la hora de regar
		Se avanza al estado primario 'REGAR'
		Se avanza al estado secundario 'PREPARADO'
