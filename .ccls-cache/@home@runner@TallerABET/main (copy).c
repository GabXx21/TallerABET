#include "funciones.h"
#include "menu.h"
#include <stdio.h>
#define FILAS 24
#define COLUMNAS 2

int main(void) {
  int opc, productos;
  int datos[FILAS][COLUMNAS];
  do {
    opc = menuprincipal();
    switch (opc) {
    case 1:
      printf("1.- Ingresar producto\n");
      do {
        printf("Ingrese cuantos producto va ingresar: ");
        scanf("%d", &productos);
        if (productos > FILAS) {
          printf("El numero de productos es mayor a los disponibles\n");
          printf("Ingrese otro numero\n");
        } else if (productos < 0) {
          printf("No se acpeta numeros negativos\n");
          printf("Ingrese otro numero\n");
        }
      } while (productos > FILAS || productos < 0);
      IngresarDatos(datos, FILAS, COLUMNAS);
      break;
    case 2:
      printf("2.- Mostrar productos\n");
      break;
    case 3:
      printf("3.- Buscar producto\n");
      break;
    case 4:
      printf("4.- Modificar producto\n");
      break;
    case 5:
      printf("5.- Eliminar producto\n");
      break;
    case 6:
      printf("6.- Salir\n");
      break;
    default:
      printf("Opcion no valida");
      break;
    }
  } while (opc != 6);
  return 0;
}