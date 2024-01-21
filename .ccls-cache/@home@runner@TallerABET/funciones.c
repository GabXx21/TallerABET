#include "funciones.h"
#include "lectura.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

void ingresarProductos(char productos[][COLUMNAS], int cantidad[], float precio[], int *filas){
  for(int i=0; i<*filas; i++){
    do {
        printf("Ingrese el nombre del producto %d: \n", i + 1);
        scanf("%s", productos[i]);
    } while (!isalpha(productos[i][0]));

    do {
        printf("Ingrese la cantidad del producto %d: \n", i + 1);
        scanf("%d", &cantidad[i]);
    } while (cantidad[i] <= 0);

    do {
        printf("Ingrese el precio del producto %d: \n", i + 1);
        scanf("%f", &precio[i]);
    } while (precio[i] <= 0);
  }
}

void eliminarProductos(char productos[][COLUMNAS], int cantidad[], float precio[], int filas){
  char eliminar[50];
  printf("Ingrese el nombre del producto a eliminar: ");
  scanf("%s", eliminar);
  for(int i=0; i<filas; i++){
    if(strcmp(eliminar, productos[i])==0){
      productos[i][0] = '\0';
      precio[i] = '\0';
      cantidad[i] = '\0';
      printf("El producto %s fue eliminado.\n", eliminar);
      break;
    }
  }
}

void editarProductos(const char productos[][COLUMNAS], int cantidad[], float precio[], int filas){
  char editar[50];
  printf("Ingrese el nombre del producto a editar: ");
  scanf("%s", editar);
  for(int i=0; i<filas; i++){
    if(strcmp(editar, productos[i])==0){
      printf("Producto encontrado.\n");
      printf("Ingrese la cantidad del producto %d: \n", i+1);
      scanf("%d", &cantidad[i]);
      printf("Ingrese el precio del producto %d: \n", i+1);
      scanf("%f", &precio[i]);
      printf("Producto editado.\n");
    }
  }
}

void mostrarProductos(const char productos[][COLUMNAS], int cantidad[], float precio[], int filas){
  printf("Producto\tCantidad\tPrecio\n");
  for(int i=0; i<filas; i++){
      printf("%s\t\t%d\t\t\t%.2f\n", productos[i], cantidad[i], precio[i]);
  }
  printf("\n");
}

void calcularVentas(const char productos[][COLUMNAS], int cantidad[], float precio[], int filas){
  int ventas[filas];
  float ventasTotales = 0;
  for(int i=0; i<filas; i++){
    ventas[i] = cantidad[i] * precio[i];
    ventasTotales += ventas[i];
    printf("Del producto '%s' se tiene %d unidades a un precio de %.2f.\n", productos[i], cantidad[i], precio[i]);
  }
  printf("Se espera una ganacia total de: %.2f.\n", ventasTotales);
}
