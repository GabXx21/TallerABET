#include "factura.h"
#include "cedula.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAX_CEDULA_LENGTH 11
#define MAX_NOMBRE_LENGTH 50
#define MAX_APELLIDO_LENGTH 50
#define MAX_PRODUCTOS 100

void actualizarInventario(char producto[], int cantidad) {
  FILE *archivo = fopen("inventario.txt", "r");
  FILE *temporal = fopen("temporal.txt", "w");

  char nombreProducto[50];
  int cantidadExistente;
  float precio;

  while (fscanf(archivo, "%s %d %f", nombreProducto, &cantidadExistente, &precio) == 3) {
    if (strcmp(nombreProducto, producto) == 0) {
      cantidadExistente -= cantidad;
      if (cantidadExistente < 0) {
        cantidadExistente = 0;
      }
    }
    fprintf(temporal, "%s %d %.2f\n", nombreProducto, cantidadExistente, precio);
  }

  fclose(archivo);
  fclose(temporal);

  remove("inventario.txt");
  rename("temporal.txt", "inventario.txt");
}

void realizarCalculos(char cedula[], int totalProductos, char productos[][COLUMNAS], float precio[], int cantidadProductos[]) {
  FILE *factura = fopen("factura.txt", "a+");
  FILE *clientes = fopen("clientes.txt", "r");
  char productosSeleccionados[MAX_PRODUCTOS][50];
  int cantidadProductosSeleccionados = 0;
  char nombre[MAX_NOMBRE_LENGTH];
  char apellido[MAX_APELLIDO_LENGTH];
  char producto[50];
  int cantidad;
  float precioVenta;
  float total = 0;
  int numeroFactura;

  char cedula_factura[20];
  printf("Ingrese la cedula del cliente: ");
  scanf("%s", cedula);

  if (!validarCedulaEcuatoriana(cedula)) {
    printf("Cédula inválida. Intente nuevamente y asegúrese de ingresar una cédula ecuatoriana.\n");
    return;
  }

  if (!existeCliente(cedula)) {
    printf("El cliente no existe. Por favor, registre al cliente antes de facturar.\n");
    ingresarCliente();
  }

  printf("Ingrese los productos a facturar. Ingrese 'fin' para finalizar.\n");

  char nombreProducto[50];
  int cantidad_venta[MAX_PRODUCTOS];

  for (;;) {
    printf("Ingrese el nombre del producto: ");
    scanf("%s", nombreProducto);
    if (strcmp(nombreProducto, "fin") == 0) {
      break;  // Salir del bucle
    }

    int indiceProducto = -1;
    for (int i = 0; i < cantidadProductosSeleccionados; i++) {
      if (strcmp(productosSeleccionados[i], nombreProducto) == 0) {
        printf("Este producto ya fue agregado a la factura. Introduzca uno diferente.\n");
        indiceProducto = i;
        break;
      }
    }

    if (indiceProducto != -1) {
      continue;  // Volver a solicitar otro producto
    }

    FILE *archivo = fopen("inventario.txt", "r");
    while (fscanf(archivo, "%s %d %f", producto, &cantidad, &precioVenta) == 3) {
      if (strcmp(producto, nombreProducto) == 0) {
        do {
          printf("Ingrese la cantidad de '%s' a facturar: ", nombreProducto);
          scanf("%d", &cantidad_venta[cantidadProductosSeleccionados]);
          if (cantidad_venta[cantidadProductosSeleccionados] > cantidad) {
            printf("No hay suficiente stock para facturar esa cantidad\n");
          } else {
            strcpy(productosSeleccionados[cantidadProductosSeleccionados], nombreProducto);
            total += cantidad_venta[cantidadProductosSeleccionados] * precioVenta;
            cantidad -= cantidad_venta[cantidadProductosSeleccionados];  // Reducir la cantidad en el inventario
            actualizarInventario(nombreProducto, cantidad_venta[cantidadProductosSeleccionados]); // Actualizar el inventario
            cantidadProductosSeleccionados++;
            break;
          }
        } while (cantidad_venta[cantidadProductosSeleccionados] > cantidad);
        break;
      }
    }
    fclose(archivo);

    if (indiceProducto == -1) {
      printf("Producto no encontrado en el inventario.\n");
    }
  }

  // Restablecer el puntero del archivo al inicio
  fseek(factura, 0, SEEK_SET);

  // Leer la primer línea del archivo
  char primeraLinea[100];
  fgets(primeraLinea, sizeof(primeraLinea), factura);

  // Saltar las líneas necesarias
  int lineasASaltar = 3; // Cambia este valor según tus necesidades
  for (int i = 0; i < lineasASaltar; i++) {
    fgets(primeraLinea, sizeof(primeraLinea), factura);
  }
  fscanf(factura, "Número de factura: %d", &numeroFactura);
  numeroFactura++;
  fprintf(factura, "\nNúmero de factura: %d\n", numeroFactura);
  while (fscanf(clientes, "%s %s %s", cedula_factura, nombre, apellido) != EOF) {
    if (strcmp(cedula_factura, cedula) == 0) {
      fprintf(factura, "Cliente: %s %s %s\n", cedula_factura, nombre, apellido);
      break;
    }
  }

  FILE *archivo = fopen("inventario.txt", "r");
  // Procesar los productos seleccionados
  for (int i = 0; i < cantidadProductosSeleccionados; i++) {
    while(fscanf(archivo, "%s %d %f", producto, &cantidad, &precioVenta) != EOF){
      if (strcmp(producto, productosSeleccionados[i]) == 0){
        fprintf(factura, "Producto: %s %d %.2f\n", productosSeleccionados[i], cantidad_venta[i], precioVenta); // Escribir en la factura
        break;
      }
    }
  }

  // Obtener la fecha y hora actual
  time_t t = time(NULL);
  struct tm *tm = localtime(&t);
  char fecha[64];
  strftime(fecha, sizeof(fecha), "%c", tm);

  // Escribir la fecha y hora en el archivo de factura
  fprintf(factura, "Fecha y hora: %s\n", fecha);
  fprintf(factura, "Total: %.2f\n", total);

  fclose(archivo);
  fclose(factura);
  fclose(clientes);
}

void imprimirFactura(const char cedula[], const char productos[][COLUMNAS], const int totalProductos, const float total) {
  FILE *archivo = fopen("inventario.txt", "r");
  FILE *clientes = fopen("clientes.txt", "r");
  char cedula_aux[MAX_CEDULA_LENGTH];
  char nombre[MAX_NOMBRE_LENGTH];
  char apellido[MAX_APELLIDO_LENGTH];
  char productos_aux[50];  
  int cantidadProductos;
  float precio;
  if (archivo == NULL || clientes == NULL) {
    printf("Error al abrir los archivos.\n");
    return;
  }
  int encontrado = 0; 
  while (fscanf(clientes, "%s %s %s ", cedula_aux, nombre, apellido) != EOF) {
    if (strcmp(cedula, cedula_aux) == 0) {  
      encontrado = 1;  
      printf("********** Factura **********\n");
      printf("Cédula del cliente: %s\n", cedula);
      printf("Nombre del cliente: %s %s\n", nombre, apellido);
      printf("Producto\tCantidad\tPrecio\n");
      break;  
    }
  }
  if (!encontrado) {  
    printf("Cliente no encontrado.\n");
  } else {
    for (int i = 0; i < totalProductos; i++) {
      fseek(archivo, 0, SEEK_SET);  
      int prod_encontrado = 0;  
      while (fscanf(archivo, "%s %d %f", productos_aux, &cantidadProductos, &precio) == 3) {
          if (strcmp(productos_aux, productos[i]) == 0) {  
              prod_encontrado = 1;
              printf("%s\t\t%d\t\t\t%.2f\n", productos_aux, cantidadProductos, precio);
              break;  
          }
      }
      if (!prod_encontrado) {
        printf("Producto no encontrado en el inventario: %s\n", productos[i]);
      }
    }
  }
  printf("Total a pagar: $%.2f\n", total);
  printf("*****************************\n");
  fclose(archivo);
  fclose(clientes);
}

void mostrarFacturas(){
  double tiempoEjecucionAnterior = 0.0;
  FILE *archivo = fopen("factura.txt", "r");
  char linea[100];
  if (archivo == NULL){
    printf("No se pudo abrir el archivo.\n");
    return;
  }
  printf("Facturas:\n");
  while (fgets(linea, sizeof(linea), archivo) != NULL){
    printf("%s", linea);
  }
}

void buscarFactura() {
  double tiempoEjecucionAnterior = 0.0;
  int numeroFactura;
  printf("Ingrese el número de factura que desea buscar: ");
  scanf("%d", &numeroFactura);

  FILE *factura = fopen("factura.txt", "r");
  if (factura == NULL) {
    printf("Error al abrir el archivo de facturas.\n");
    return;
  }

  char linea[100];
  int facturaEncontrada = 0;

  while (fgets(linea, sizeof(linea), factura)) {
    int num;
    if (sscanf(linea, "Número de factura: %d", &num) == 1 && num == numeroFactura) {
      facturaEncontrada = 1;
      printf("Factura encontrada:\n");
      printf("\n%s", linea);  // Imprimir la línea que contiene el número de factura
      // Imprimir el resto de los datos de la factura
      while (fgets(linea, sizeof(linea), factura) && linea[0] != '\n') {
        printf("%s", linea);
      }
      printf("\n");
      break;  // Salir del bucle una vez que se encuentra la factura
    }
  }

  if (!facturaEncontrada) {
    printf("La factura con el número %d no fue encontrada.\n", numeroFactura);
  }

  printf("Tiempo de ejecución de la función anterior: %.2f segundos\n", tiempoEjecucionAnterior);

  fclose(factura);
}
