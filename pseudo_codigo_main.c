//To-do
 // Modularizar
 // Reutilizar logíca de cambiar hora los modos "MODIFICAR_FECHA_HORA_ACTUAL" y "MODIFICAR_FECHA_HORA_PROGRAMA_RIEGO"
 //definir 
estado_primario = STAND_BY;
boton_presionado ;
while (1) {
    // Verificar si es hora de regar y cambiar al estado de REGAR si es necesario
    si (estado_primario == STAND_BY && estoyEnHoraDeRegar()) {
        estate_primario = REGAR;
	estate_secundario= PREPARADO;
    }
    
    // Leer el último botón presionado
    boton_presionado = BotonPresionado(); //si no se presionó un botón devuelve null o algun valor caracteristico
    
    
    si(estado_primario == SLEEP && boton_presionado != null){
    	estado_primario = MENU;
    }
    
    si no presioné ningun boton en 30 seg
    	estado_primario = SLEEP
    
    
    // MENU PRINCIPAL----------------------------------------------------------------------------------------------
    Si el estado primario es 'MENU' 
            Si presioné el botón UP
            	    Avanzar estado secundario correspondiente
		    
            Si presioné el boton Enter
		    Avanzar estado primario correspondiente

	    
	    Escribir en el lcd leyenda correspondiente según estado actual

    
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
		      
		        
	
	Escribir en el lcd leyenda correspondiente según estado actual
	    
    


    // MODIFICAR FECHA Y HORA DEL PROGRAMA DE RIEGO----------------------------------------------------------------------------------------------
     // le falta segmentar por horas y minutos. Simplificamos el pseudo código para que se entienda mejor
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
			
			
		Escribir en el lcd leyenda correspondiente según estado actual
		
		
    
    
    


    //CAMBIAR MODO INTELIGENT
    Si el estado primario es 'SELECCIONAR_MODO'
    	Si el estado secundario es 'RIEGO_INTELIGENTE_OFF'
		Avanzo al estado secundario 'RIEGO_INTELIGENTE_OFF'
    	Sino
    	 	Avanzo al estado secundario 'RIEGO_INTELIGENTE_ON'
    	
    	
       Escribir en el lcd leyenda correspondiente según estado actual
       Delay(2000);
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
        
        
         Escribir en el lcd leyenda correspondiente según estado actual
    



}
