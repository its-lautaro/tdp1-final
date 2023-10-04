
Se avanza al estado primario STAND_BY
Bucle del programa

	Escribir en el lcd leyenda correspondiente según estado actual

	Si el estado primario es STAND_BY y es la hora de regar
		Avanzo al estado primario 'REGAR'
		Avanzo al estado secundario 'PREPARADO'

	Se lee el botón presionado
    
	Si el estado primario es STAND_BY y se preionó algún botón
		Avanzo al estado primario 'MENU'


	Si no se presionó ningún botón en 30 seg
		Avanzo al estado primario 'STAND_BY'

	Si el estado primario es 'MENU' 
		Si presioné el botón UP
	    	    Avanzar estado secundario correspondiente
		    
		Si presioné el boton Enter
		    Avanzar estado primario correspondiente


	Si el estado primario es 'MODIFICAR_FECHA_HORA_ACTUAL'

		Si el estado secundario es 'MODIFICANDO_FECHA'
			Si presioné el botón 'UP'
			      Incrementar la fecha
			Sino   
				Si presioné el botón 'DOWN'
			      		Decrementar la fecha
			   	Sino
			  		Si presioné el botón 'ENTER'
			     			Avanzo al estado secundario 'MODIFICAR_HORA'

		        
		Si el estado secundario es 'MODIFICANDO_HORA'
			Si presioné el botón 'UP'
			      Incrementar la hora
			Sino   
				Si presioné el botón 'DOWN'
			      		Decrementar la hora
			  	Sino
			  		Si presioné el botón 'ENTER'
			  			Avanzo al estado primario 'MENU'
			  			Avanzo al estado secundario 'MODIFICANDO_FECHA'
		       	    

	Si el estado primario es 'MODIFICAR_FECHA_HORA_PROGRAMA_RIEGO'
		Si el estado secundario es 'MODIFICANDO_FECHA'
			Si presioné el botón 'UP'
				Incrementar día de la semana (lunes,martes,etc)
			Sino
				Si presioné el botón 'DOWN'
			      		Decrementar  día de la semana (lunes,martes,etc)
			      	Sino
			      		Si presioné el botón 'ENTER'
			   			estado_secundario = MODIFICAR_HORA
				     
			
			
		Si el estado secundario es 'MODIFICANDO_HORA)'
				Si presioné el botón 'UP'
					Incrementar la hora
				Sino
					Si presioné el botón 'DOWN'
						Decrementar la hora
				  	Sino
				  		Si presioné el botón 'ENTER'
				 			Avanzo al estado secundario 'MODIFICAR_FECHA'
							Avanzo al estado primario 'MENU'
			
			
	Si el estado primario es 'SELECCIONAR_MODO'
    
		Si se presionó el botón 'UP' o 'DOWN'
			Si el estado secundario es 'CAMBIAR_RIEGO_INTELIGENTE_OFF'
				Avanzo al estado secundario 'RIEGO_INTELIGENTE_ON'
	    		Sino
	    	 		Avanzo al estado secundario 'RIEGO_INTELIGENTE_OFF'	
	    		
	    	Si presioné el botón 'ENTER'
	    		Se cambia el modo inteligente dependiendo del estado secundario actual
	    				    
	  	Si se presionó el botón 'CANCELAR'
	  		Avanzo al estado primario 'MENU'
	    	
    	
   	Si el estado primario es 'REGAR'
		Si se presionó el botón 'CANCELAR'
		  	Avanzo al estado secundario 'FINALIZAR'
		
		Si el estado secundario es 'PREPARADO'
			Avanzo al estado secundario 'VÁLVULA1'
			Abrir válvula 1
			Inicio contador de tiempo valvula 2

		Si el estado secundario es 'VÁLVULA1'
			Si se cumplió el tiempo de riego de la valvula 1
				Avanzo al estado secundario 'VÁLVULA'
				Cerrar válvula 1
				Abrir válvula 2
				Inicio contador de tiempo valvula 2

		Si el estado secundario es 'VÁLVULA2'
			Si se cumplió el tiempo de riego de la valvula 2
				Avanzo al estado secundario 'PREPARADO'
				Avanzo al estado primario 'MENU'
				Cerrar válvula 2
		      
		Si el estado secundario es 'FINALIZAR'
			Cerrar válvula 1
			Cerrar válvula 2
			Avanzo al estado secundario 'PREPARADO'
			Avanzo al estado primario 'MENU'
		
        
         
