//To-do
 // Modularizar
 // Reutilizar logíca de cambiar hora los modos "MODIFICAR_FECHA_HORA_ACTUAL" y "MODIFICAR_FECHA_HORA_PROGRAMA_RIEGO"
 //definir 
estado_primario = STAND_BY;
int boton_presionado();//Retorna el último botón presionado
while(1){
    // Verificar si es hora de regar y cambiar al estado de REGAR si es necesario
<<<<<<< HEAD
    si (estado_primario == STAND_BY && estoyEnHoraDeRegar()) {
=======
    if(estado_primario == SLEEP && estoyEnHoraDeRegar()){
>>>>>>> 72e318c159df999796d00c406470f48cb276d923
        estate_primario = REGAR;
		estate_secundario= PREPARADO;
    }
    // Leer el último botón presionado
    boton_presionado = BotonPresionado(); //si no se presionó un botón devuelve null o algun valor caracteristico
    
<<<<<<< HEAD
    
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
=======
    if(estado_primario == SLEEP && boton_presionado != null){
    	estado_primario = MENU;
    }
    if(no presioné ningun boton en 30 seg){
    	estado_primario = SLEEP;
    }

    // MENU PRINCIPAL----------------------------------------------------------------------------------------------
    if(estado_primario == MENU){
            //CAMBIAMOS DE ESTADO_SECUNDARIO DEPENDIENDO DEL BOTÓN PRESIONADO
            if(boton_presionado == UP){
            	if(estado_secundario == CONSULTAR_MODIFICAR_FECHA_HORA_ACTUAL){
			    	estado_secundario = CONSULTAR_MODIFICAR_FECHA_HORA_PROGRAMA;
		    	}
		    	if(estado_secundario == CONSULTAR_MODIFICAR_FECHA_HORA_PROGRAMA){
			     	estado_secundario = CONSULTAR_MODIFICAR_FECHA_HORA_ACTUAL ;
		    	}
		    	if(estado_secundario == CONSULTAR_CAMBIAR_MODO){
			     	estado_secundario = CONSULTAR_MODIFICAR_FECHA_HORA_PROGRAMA;
		    	}
            }
            //CAMBIAMOS DE ESTADO_PRIMARIO SI SE PRESIONÓ ENTER
            if(boton_presionado == ENTER){
		    	if(estado_secundario == CONSULTAR_MODIFICAR_FECHA_HORA_ACTUAL){
			    	estado_primario = MODIFICAR_FECHA_HORA_ACTUAL;
		    	}
		    	if(estado_secundario == CONSULTAR_MODIFICAR_FECHA_HORA_PROGRAMA){
			 		estado_primario = MODIFICAR_FECHA_HORA_PROGRAMA;
		    	}
		    	if(estado_secundario == CONSULTAR_CAMBIAR_MODO){
			 		estado_primario = CAMBIAR_MODO;
		   	 	}
	    }
	    printLCD(estado_primario,estado_secundario);
>>>>>>> 72e318c159df999796d00c406470f48cb276d923

	    
	    Escribir en el lcd leyenda correspondiente según estado actual

<<<<<<< HEAD
    
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
    



=======
    // MODIFICAR FECHA Y HORA INTERNAS----------------------------------------------------------------------------------------------
    // le falta segmentar por dia,mes,año, horas y minutos. Simplificamos el pseudo código para que se entienda mejor
    if(estado_primario == MODIFICAR_FECHA_HORA_ACTUAL){
		if(estado_secundario == MODIFICANDO_FECHA){
			if(boton_presionado == BOTON_UP){
				Incrementar la fecha;
			}else if (boton_presionado == BOTON_DOWN){
		    	Decrementar la fecha;
			}else if(boton_presionado == BOTON_ENTER){
		    	Confirmar la modificación;
		        estado_secundario = MODIFICAR_HORA;
		    }
		}
	}
	if(estado_secundario == MODIFICANDO_HORA){
		if(boton_presionado == BOTON_UP){
		    	Incrementar la hora;
		    }else if(boton_presionado == BOTON_DOWN){
		    	Decrementar la hora;
		    }else if(boton_presionado == BOTON_ENTER){
		    	Confirmar la modificación;
		        estado_secundario = MODIFICAR_FECHA;
		        estado_primario = MENU;
		    }
	}
	printLCD(estado_primario,estado_secundario);

    // MODIFICAR FECHA Y HORA DEL PROGRAMA DE RIEGO----------------------------------------------------------------------------------------------
    // Le falta segmentar por horas y minutos. Simplificamos el pseudo código para que se entienda mejor
    if(estado_primario == MODIFICAR_FECHA_HORA_PROGRAMA_RIEGO){
    	if(estado_primario == MODIFICAR_FECHA_HORA_ACTUAL){
			if(estado_secundario == MODIFICANDO_FECHA){
				if(boton_presionado == BOTON_UP){
					Incrementar día de la semana (lunes,martes,etc);
				}else if(boton_presionado == BOTON_DOWN){
				    Decrementar  día de la semana (lunes,martes,etc);
				}else if(boton_presionado == BOTON_ENTER){
				    Confirmar la modificación;
					estado_secundario = MODIFICAR_HORA;
				}
			}
			
			if(estado_secundario == MODIFICANDO_HORA){
				if(boton_presionado == BOTON_UP){
				    Incrementar la hora;
				}else if(boton_presionado == BOTON_DOWN){
				    Decrementar la hora;
				}else if(boton_presionado == BOTON_ENTER){
				    Confirmar la modificación;
					estado_secundario = MODIFICAR_FECHA;
					estado_primario = MENU;
				}
			}
		printLCD(estado_primario,estado_secundario);
		}
    }

     //CAMBIAR A MODO INTELIGENTE
    if(estado_primario == SELECCIONAR_MODO){
    	if(estado_secundario == RIEGO_INTELIGENTE_OFF){
			estado_secundario == RIEGO_INTELIGENTE_OFF;
    	}
    	else{
    	 	estado_secundario == RIEGO_INTELIGENTE_ON;
    	}
    	printLCD(estado_primario,estado_secundario);
    	//Hago un delay para que se muestre por el lcd que se cambió el modo inteligente por un par de segundos
        delay(2000);
        estado_primario = MENU;
    }

    if(estado_primario == REGAR){
        if(boton_presionado == CANCELAR){
           estado_secundario= FINALIZAR;
		}
        if(estado_secundario == PREPARADO){
            estado_secundario = VÁLVULA1;
            abro válvula 1;
            inicio timer valvula 1;
		}
        if(estado_secundario == VÁLVULA1){
            if(Se cumplió tiempo timer valvula 1){
            	estado_secundario = VÁLVULA2;
				cierro válvula 1;
               	abro valvula 2;
               	inicio timer valvula 2;
	    	}	
        	if(estado_secundario == VÁLVULA2){
            	if(Se cumplió tiempo timer valvula 2){
                	estado_secundario = PREPARADO;
                	estado_primario = MENU;
					cierro válvula 1;
             	  	abro valvula 2;
             	  	inicio timer valvula 2;
	     		}
        	}
        	if(estado_secundario == FINALIZAR){
            	cierro valvula1;
	    		cierro valvula2;
	    		estado_secundario = PREPARADO;
            	estado_primario = MENU;
        	}
        printLCD(estado_primario,estado_secundario);
    	}
	}
>>>>>>> 72e318c159df999796d00c406470f48cb276d923
}
