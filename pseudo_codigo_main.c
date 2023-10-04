//To-do
 // Modularizar
 // Reutilizar logíca de cambiar hora los modos "MODIFICAR_FECHA_HORA_ACTUAL" y "MODIFICAR_FECHA_HORA_PROGRAMA_RIEGO"
 //definir 
estado_primario = STAND_BY;
boton_presionado ;
while (1) {
    // Verificar si es hora de regar y cambiar al estado de REGAR si es necesario
    //esto debería de ir ultimo? 
    if (estado_primario == SLEEP && estoyEnHoraDeRegar()) {
        estate_primario = REGAR;
	estate_secundario= PREPARADO;
    }
    
    // Leer el último botón presionado
    boton_presionado = BotonPresionado(); //si no se presionó un botón devuelve null o algun valor caracteristico
    
    
    if(estado_primario == SLEEP && boton_presionado != null){
    	estado_primario = MENU;
    }
    
    if(no presioné ningun boton en 30 seg){
    	estado_primario = SLEEP
    }
    
    // MENU PRINCIPAL----------------------------------------------------------------------------------------------
    if (estado_primario == MENU) {
            //CAMBIAMOS DE ESTADO_SECUNDARIO DEPENDIENDO DEL BOTÓN PRESIONADO
            if(boton_presionado == UP){
            	if (estado_secundario == CONSULTAR_MODIFICAR_FECHA_HORA_ACTUAL) {
			    estado_secundario = CONSULTAR_MODIFICAR_FECHA_HORA_PROGRAMA;
		    }
		    if (estado_secundario == CONSULTAR_MODIFICAR_FECHA_HORA_PROGRAMA) {
			     estado_secundario = CONSULTAR_MODIFICAR_FECHA_HORA_ACTUAL ;
		    }
		    if (estado_secundario == CONSULTAR_CAMBIAR_MODO) {
			     estado_secundario = CONSULTAR_MODIFICAR_FECHA_HORA_PROGRAMA;
		    }
            }
            
            //CAMBIAMOS DE ESTADO_PRIMARIO SI SE PRESIONÓ ENTER
            if(boton_presionado == ENTER){
		    if (estado_secundario == CONSULTAR_MODIFICAR_FECHA_HORA_ACTUAL) {
			    estado_primario = MODIFICAR_FECHA_HORA_ACTUAL;
		    }
		    if (estado_secundario == CONSULTAR_MODIFICAR_FECHA_HORA_PROGRAMA) {
			    estado_primario = MODIFICAR_FECHA_HORA_PROGRAMA;
		    }
		    if (estado_secundario == CONSULTAR_CAMBIAR_MODO) {
			    estado_primario = CAMBIAR_MODO;
		    }
	    }
	    
	    
	    printLCD(estado_primario,estado_secundario);

    }

    // MODIFICAR FECHA Y HORA INTERNAS----------------------------------------------------------------------------------------------
    // le falta segmentar por dia,mes,año, horas y minutos. Simplificamos el pseudo código para que se entienda mejor
    if (estado_primario == MODIFICAR_FECHA_HORA_ACTUAL) {

	if(estado_secundario == MODIFICANDO_FECHA){
		if (boton_presionado == BOTON_UP) {
		      // Incrementar la fecha
		    } else if (boton_presionado == BOTON_DOWN) {
		      // Decrementar la fecha
		    } else if (boton_presionado == BOTON_ENTER) {
		      // Confirmar la modificación
	
		        estado_secundario = MODIFICAR_HORA
		     }
		}
	}
	
	
	if(estado_secundario == MODIFICANDO_HORA){
		if (boton_presionado == BOTON_UP) {
		      // Incrementar la hora
		    } else if (boton_presionado == BOTON_DOWN) {
		      // Decrementar la hora
		    } else if (boton_presionado == BOTON_ENTER) {
		      // Confirmar la modificación
	
		        estado_secundario = MODIFICAR_FECHA
		        estado_primario = MENU
		     }
		}
	}
	
	printLCD(estado_primario,estado_secundario);
	    
    }


    // MODIFICAR FECHA Y HORA DEL PROGRAMA DE RIEGO----------------------------------------------------------------------------------------------
     // le falta segmentar por horas y minutos. Simplificamos el pseudo código para que se entienda mejor
    if (estado_primario == MODIFICAR_FECHA_HORA_PROGRAMA_RIEGO) {
    		if (estado_primario == MODIFICAR_FECHA_HORA_ACTUAL) {

			if(estado_secundario == MODIFICANDO_FECHA){
				if (boton_presionado == BOTON_UP) {
				      // Incrementar día de la semana (lunes,martes,etc)
				    } else if (boton_presionado == BOTON_DOWN) {
				      // Decrementar  día de la semana (lunes,martes,etc)
				    } else if (boton_presionado == BOTON_ENTER) {
				      // Confirmar la modificación
			
					estado_secundario = MODIFICAR_HORA
				     }
				}
			
			
			
			if(estado_secundario == MODIFICANDO_HORA){
				if (boton_presionado == BOTON_UP) {
				      // Incrementar la hora
				    } else if (boton_presionado == BOTON_DOWN) {
				      // Decrementar la hora
				    } else if (boton_presionado == BOTON_ENTER) {
				      // Confirmar la modificación
			
					estado_secundario = MODIFICAR_FECHA
					estado_primario = MENU
				     }
			}
		
		printLCD(estado_primario,estado_secundario);
		
		}
    }
    
    


     //CAMBIAR MODO INTELIGENT
    if (estado_primario == SELECCIONAR_MODO) {
    	if(estado_secundario == RIEGO_INTELIGENTE_OFF){
		estado_secundario == RIEGO_INTELIGENTE_OFF;
    	}
    	else
    	{
    	 	estado_secundario == RIEGO_INTELIGENTE_ON;
    	}
    	
    	printLCD(estado_primario,estado_secundario);
    	//hago un delay para que se muestre por el lcd que se cambió el modo inteligente por un par de segundos
        delay(2000);
        estado_primario = MENU
    	
    }

    if (estado_primario == REGAR) {
        if(boton_presionado == CANCELAR){
           estado_secundario= FINALIZAR;
	}
        if(estado_secundario == PREPARADO){
            estado_secundario = VÁLVULA1;
            //abro válvula 1
            //inicio timer valvula 1
	}
        if(estado_secundario == VÁLVULA1){
            if(//Se cumplió tiempo timer valvula 1){
                estado_secundario = VÁLVULA2;
		//cierro válvula 1
               //abro valvula 2
               //inicio timer valvula 2
	     }	
        if(estado_secundario == VÁLVULA2){
            if(Se cumplió tiempo timer valvula 2){
                estado_secundario = PREPARADO;
                estado_primario = MENU
		//cierro válvula 1
               //abro valvula 2
               //inicio timer valvula 2
	     }
        }
        if(estado_secundario == FINALIZAR){
            //cierro valvula1
	    //cierro valvula2
	    estado_secundario = PREPARADO;
            estado_primario = MENU
        }
        
        printLCD(estado_primario,estado_secundario);
    }
}


}
