/*============================================================================
 * Autor:
 * Licencia:
 * Fecha:
 *===========================================================================*/

// Inclusiones

#include "app.h"        // <= Biblioteca sAPI
#include "reles.h"         // <= Su propia cabecera
// FUNCION PRINCIPAL, PUNTO DE ENTRADA AL PROGRAMA LUEGO DE ENCENDIDO O RESET.
int main( void )
{
   // ---------- CONFIGURACIONES ------------------------------

   // Inicializar y configurar la plataforma
   boardConfig();
   initReles();
   
   // ---------- REPETIR POR SIEMPRE --------------------------
   while( TRUE ) {
      encenderRele(1);
      delay( 500 );
      apagarRele(1);
      
      delay(1000);
      
      encenderRele(2);
      delay( 500 );
      apagarRele(2);
      
      delay(2000);
   }
   // NO DEBE LLEGAR NUNCA AQUI, debido a que a este programa se ejecuta
   // directamenteno sobre un microcontroladore y no es llamado por ningun
   // Sistema Operativo, como en el caso de un programa para PC.
   return 0;
}
