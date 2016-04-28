#include <stdio.h>
#include  <stdlib.h>
#include  <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <time.h>
#include <netinet/in.h>    

#include <netdb.h>    	/* netbd.h es necesitada por la estructura hostent */
//#define PORT 7300     	/* El Puerto Abierto del nodo remoto */   
#define MAXDATASIZE 100  /* El número máximo de datos en bytes */

int fd, tipo_conex;

 void conexion(int argc, char *argv[]);
	/*  void conexion(int argc, char *argv[])
	 *  Realiza la conexion con el servidor, 
	 *  recibe por parametros los datos introducidos por el usuario 
	 *  (numero de parametos y por el otro argumento ip puerto y tipo de protocolo)
	 */

 void enviar(void *cadena, long int tamano);
	/*  void enviar(void *cadena)
	 *  Funcion de envio de mensajes al servidor
	 *  recibe por parametro el dato a enviar
	 */
 void* recibir(); 
	/*  void* recibir()
	 *  Funcion de recibir de mensajes al servidor
	 *  retorna el mensaje recibido del servidor, de tipo void *
	 */
 int create(void* mensaje, long int size);
	/*  int create(void *mensaje);
	 *  Permite crear segmentos en el servidor
	 *  recibe por parametro el dato a almacenar 
	 *  retorna 1 si el mensaje fue creado con exito o -1 si hubo errores
	 */
 void* get(int *indice);
	/*  void* get(int *indice)
	 *  Permite obtener la informacion de un segmento del servidor
	 *  recibe por parametro el numero de segmento a consultar 
	 *  retorna el mensaje del segmento consultado, de tipo void *
	 */
 int update(void *mensaje, int *indice,long int tamano);
	/*  update(void *mensaje, int *indice)
	 *  Permite actualizar segmentos del servidor
	 *  recibe por parametro la informacion a sustituir y el numero de segmento a reemplazar 
	 *  retorna 1 si el mensaje fue actualizado con exito o -1 si hubo errores
	 */
 int delete(int *indice);
	/*  delete(int *indice);
	 *  Permite eliminar segmentos del servidor
	 *  recibe por parametro el numero del segmento a eliminar 
	 *  retorna 1 si el mensaje fue eliminado con exito o -1 si hubo errores
	 */

 int length_mem();
	/*  length_mem();
	 *  Permite consultar el numero segmentos creados en el servidor
	 *  retorna el numero de segmentos creados, -1 si no contiene segmentos
	 */

 void desconectar();
	/*  void desconectar();
	 *  
	 */

 //void menu(int fd);
	/*  menu(int fd)
	 *  Funcion que permite desplegar una serie de opciones en el cliente
	 *  
	 */		
		




