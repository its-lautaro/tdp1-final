Se avanza al estado primario STAND_BY

Bucle principal del programa

	Escribir en el lcd leyenda correspondiente según estado actual

	Se lee el botón presionado
    
	Si el estado primario es STAND_BY y se presionó algún botón
		Se avanza al estado primario 'MENU'

	Si no se presionó ningún botón en 30 seg
		Se avanza al estado primario 'STAND_BY'

	Si el estado primario es 'MENU' 
		Se presionó el botón UP
	    		Avanzar estado secundario correspondiente    
		Se presionó el boton Enter
			Avanzar estado primario correspondiente

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
			Se presionó 'UP'
				Incrementar día de la semana (lunes,martes,etc)
			Sino
				Se presionó el botón 'DOWN'
			      		Decrementar  día de la semana (lunes,martes,etc)
			      	Sino
			      		Se presionó el botón 'ENTER'
			   			estado_secundario = MODIFICAR_HORA
				     
		Si el estado secundario es 'MODIFICANDO_HORA)'
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
