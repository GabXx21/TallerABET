#include <stdio.h>
#include "menu.h"
#include "lectura.h"

int menuprincipal (){
  printf("1.-Ingresar Cliente\n");
  printf("2.-Modificar Cliente\n");
  printf("3.-Consultar Cliente\n");
  printf("4.-Ver listado de clientes\n");
  printf("5.-Ingresar productos\n");
  printf("6.-Modificar producto.\n");
  printf("7.-Aumentar Stock\n");
  printf("8.-Eliminar producto.\n");
  printf("9.-Consultar producto.\n");
  printf("10.-Ver productos.\n");
  printf("11.-Facturar.\n");
  printf("12.-Ver facturas.\n");
  printf("13.-Buscar factura.\n");
  printf("0.-Salir\n");
  return leerEnteroEntre("Escoga una opcion\n", 0, 13);

}

