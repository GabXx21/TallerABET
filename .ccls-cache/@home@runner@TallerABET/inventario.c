#include "inventario.h"
#include "factura.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

bool esCaracter(const char *str) {
  for (int i = 0; str[i] != '\0'; i++) {
    if (!isalpha(str[i])) {
      return false;
    }
  }
  return true;
}

void ingresarDatos(int *cantidad, char productos[][COLUMNAS], float precio[],
                   int cantidadProductos[]) {
  int capacidad = FILAS; // Capacidad inicial
  char temp[COLUMNAS];
  int repetido;
  FILE *archivo;

  do {
    printf("Ingrese el numero de productos\n");
    int num;
    scanf("%d", &num);
    *cantidad = num;
    if (*cantidad > capacidad) {
      printf("No se pueden ingresar mas de %d productos\n", capacidad);
      printf("Ingrese otro numero\n");
    } else if (*cantidad < 0) {
      printf("No se pueden ingresar numeros negativos\n");
      printf("Ingrese otro numero\n");
    }
  } while (*cantidad > capacidad || *cantidad < 0);

  for (int i = 0; i < *cantidad; i++) {
    do {
      repetido = 0;
      printf("Ingrese el nombre del producto %d: \n", i + 1);
      scanf("%s", temp);
      if (!esCaracter(temp)) {
        printf("El nombre del producto solo debe contener letras.\n");
      } else {
        archivo = fopen("inventario.txt", "r");
        if (archivo != NULL) {
          char line[256];
          while (fgets(line, sizeof(line), archivo)) {
            if (strstr(line, temp) != NULL) {
              printf("El producto ya está almacenado.\n");
              repetido = 1;
              break;
            }
          }
          fclose(archivo);
        }
      }
    } while (!esCaracter(temp) || repetido);
    strcpy(productos[i], temp);
    do {
      printf("Ingrese la cantidad del producto %d: \n", i + 1);
      scanf("%d", &cantidadProductos[i]);
    } while (cantidadProductos[i] <= 0);
    do {
      printf("Ingrese el precio del producto %d: \n", i + 1);
      scanf("%f", &precio[i]);
    } while (precio[i] <= 0);
    capacidad--; // Reduce la capacidad
    printf("Se puede almacenar %d productos más.\n",
           capacidad); // Muestra cuántos productos más se pueden almacenar
    printf("-------------------------------------\n");
  }
}

void guardarDatos(const int cantidad, char productos[][COLUMNAS],
                  float precio[], int cantidadProductos[]) {
  FILE *archivo;
  if ((archivo = fopen("inventario.txt", "a+")) != NULL) {
    for (int i = 0; i < cantidad; i++) {
      fprintf(archivo, "\n");
      fputs(productos[i], archivo);
      fputs(" ", archivo);
      fprintf(archivo, "%d", cantidadProductos[i]);
      fputs(" ", archivo);
      fprintf(archivo, "%.2f", precio[i]);
      fputs("\n", archivo);
    }
  } else
    printf("El archivo no pudo abrirse");

  fclose(archivo);
}

void editarDatos() {
  FILE *archivo;
  FILE *nuevoArchivo;
  char productos[50];
  int cantidadProductos;
  float precio;
  char nuevoProducto[50];
  char confirmacion;
  int scanCheck;

  archivo = fopen("inventario.txt", "r+");
  if (archivo == NULL) {
    printf("El archivo no pudo abrirse.\n");
    return;
  }

  printf("Productos actuales en el inventario:\n");
  while (fscanf(archivo, "%49s %d %f", productos, &cantidadProductos,
                &precio) == 3) {
    printf("%s\n", productos);
  }
  rewind(archivo);

  printf("Ingrese el nombre del producto que desea editar: \n");
  scanCheck = scanf("%49s", nuevoProducto);
  if (scanCheck != 1) {
    printf("Entrada inválida.\n");
    fclose(archivo);
    return;
  }

  nuevoArchivo = fopen("nuevo_inventario.txt", "w+");
  if (nuevoArchivo == NULL) {
    printf("No se pudo crear el nuevo archivo.\n");
    fclose(archivo);
    return;
  }

  while (fscanf(archivo, "%49s %d %f", productos, &cantidadProductos,
                &precio) == 3) {
    if (strcmp(productos, nuevoProducto) == 0) {
      printf("¿Está seguro de que desea editar este producto? (s/n): \n");
      scanf(" %c", &confirmacion);
      if (confirmacion != 's' && confirmacion != 'S') {
        printf("Edición cancelada.\n");
        fclose(archivo);
        fclose(nuevoArchivo);
        remove("nuevo_inventario.txt");
        return;
      }

      printf("Ingrese el nuevo nombre del producto: \n");
      scanCheck = scanf("%49s", productos);
      if (scanCheck != 1) {
        printf("Entrada inválida.\n");
        fclose(archivo);
        fclose(nuevoArchivo);
        remove("nuevo_inventario.txt");
        return;
      }

      printf("Ingrese la nueva cantidad del producto: \n");
      scanCheck = scanf("%d", &cantidadProductos);
      if (scanCheck != 1) {
        printf("Entrada inválida.\n");
        fclose(archivo);
        fclose(nuevoArchivo);
        remove("nuevo_inventario.txt");
        return;
      }

      printf("Ingrese el nuevo precio del producto: \n");
      scanCheck = scanf("%f", &precio);
      if (scanCheck != 1) {
        printf("Entrada inválida.\n");
        fclose(archivo);
        fclose(nuevoArchivo);
        remove("nuevo_inventario.txt");
        return;
      }
    }
    fprintf(nuevoArchivo, "\n%s %d %.2f\n", productos, cantidadProductos,
            precio);
  }

  fclose(archivo);
  fclose(nuevoArchivo);
  remove("inventario.txt");
  rename("nuevo_inventario.txt", "inventario.txt");
  printf("El producto ha sido editado exitosamente.\n");
}

void aumentarstock() {
  FILE *archivo;
  FILE *nuevoArchivo;
  char productos[50];
  int cantidadProductos;
  float precio;
  char nuevoProducto[50];
  char confirmacion;
  int scanCheck;

  archivo = fopen("inventario.txt", "r+");
  if (archivo == NULL) {
    printf("El archivo no pudo abrirse.\n");
    return;
  }

  printf("Productos actuales en el inventario:\n");
  while (fscanf(archivo, "%49s %d %f", productos, &cantidadProductos,
                &precio) == 3) {
    printf("%s\n", productos);
  }
  rewind(archivo);

  printf("Ingrese el nombre del producto que desea editar: \n");
  scanCheck = scanf("%49s", nuevoProducto);
  if (scanCheck != 1) {
    printf("Entrada inválida.\n");
    fclose(archivo);
    return;
  }

  nuevoArchivo = fopen("nuevo_inventario.txt", "w+");
  if (nuevoArchivo == NULL) {
    printf("No se pudo crear el nuevo archivo.\n");
    fclose(archivo);
    return;
  }

  while (fscanf(archivo, "%49s %d %f", productos, &cantidadProductos,
                &precio) == 3) {
    if (strcmp(productos, nuevoProducto) == 0) {
      printf("¿Está seguro de que desea editar la cantidad de este producto? (s/n): \n");
      scanf(" %c", &confirmacion);
      if (confirmacion != 's' && confirmacion != 'S') {
        printf("Edición cancelada.\n");
        fclose(archivo);
        fclose(nuevoArchivo);
        remove("nuevo_inventario.txt");
        return;
      }

      printf("Ingrese la nueva cantidad del producto: \n");
      scanCheck = scanf("%d", &cantidadProductos);
      if (scanCheck != 1) {
        printf("Entrada inválida.\n");
        fclose(archivo);
        fclose(nuevoArchivo);
        remove("nuevo_inventario.txt");
        return;
      }
    }
    fprintf(nuevoArchivo, "\n%s %d %.2f\n", productos, cantidadProductos,
            precio);
  }

  fclose(archivo);
  fclose(nuevoArchivo);
  remove("inventario.txt");
  rename("nuevo_inventario.txt", "inventario.txt");
  printf("La cantidad del producto ha sido editada exitosamente.\n");
}

void eliminarNombre() {
  FILE *archivo = fopen("inventario.txt", "r");
  if (archivo == NULL) {
    printf("No se pudo abrir el archivo inventario.txt\n");
    return;
  }

  printf("Productos en el inventario:\n");
  char nombre[50];
  int cantidadProductos;
  float precio;
  while (fscanf(archivo, "%s %d %f", nombre, &cantidadProductos, &precio) !=
         EOF) {
    printf("%s\n", nombre);
  }

  rewind(archivo); // Regresa al inicio del archivo para la siguiente operación

  char nombreBuscado[50];
  printf("Ingrese el nombre que desea eliminar: ");
  scanf("%s", nombreBuscado);

  char confirmacion[5];
  printf("¿Está seguro de que desea eliminar el producto %s? (s/n): ",
         nombreBuscado);
  scanf("%s", confirmacion);
  if (strcmp(confirmacion, "s") != 0) {
    printf("Eliminación cancelada.\n");
    return;
  }

  FILE *temporal = fopen("temp.txt", "w");
  int encontrado = 0;

  while (fscanf(archivo, "%s %d %f", nombre, &cantidadProductos, &precio) !=
         EOF) {
    if (strcmp(nombre, nombreBuscado) != 0) {
      fprintf(temporal, "\n%s %d %.2f\n", nombre, cantidadProductos, precio);
    } else {
      encontrado = 1;
    }
  }

  fclose(archivo);
  fclose(temporal);

  remove("inventario.txt");
  rename("temp.txt", "inventario.txt");

  if (encontrado) {
    printf("Nombre eliminado exitosamente.\n");
  } else {
    printf("Nombre no encontrado.\n");
  }
}

void buscarNombre() {
  FILE *archivo = fopen("inventario.txt", "r");
  char nombreBuscado[50];
  char nombre[50];
  int encontrado = 0;
  int cantidadProductos;
  float precio;
  char opcion;

  do {
    printf("Ingrese el nombre que desea buscar: ");
    scanf("%49s", nombreBuscado);

    rewind(archivo);
    while (fscanf(archivo, "%49s %d %f", nombre, &cantidadProductos, &precio) !=
           EOF) {
      if (strcmp(nombre, nombreBuscado) == 0) {
        printf("------------------------\n");
        printf("Producto encontrado: %s\n", nombre);
        printf("Cantidad: %d\n", cantidadProductos);
        printf("Precio: %.2f\n", precio);
        printf("------------------------\n");
        encontrado = 1;
        break;
      }
    }

    if (!encontrado) {
      printf("Nombre no encontrado. ¿Desea seguir intentando? (s/n): ");
      scanf(" %c", &opcion);
      if (opcion != 's' && opcion != 'S') {
        break;
      }
    }
  } while (!encontrado);

  fclose(archivo);
}

void mostrarDatos(char productos[][COLUMNAS], float precio[],
                  int cantidadProductos[]) {
  FILE *archivo;
  if ((archivo = fopen("inventario.txt", "r")) != NULL) {
    char productos[50];
    int cantidadProducto;
    float precioProducto;
    rewind(archivo);
    while (fscanf(archivo, "%s %d %f", productos, &cantidadProducto,
                  &precioProducto) != EOF) {
      printf("------------------------\n");
      printf("Producto: %s\n", productos);
      printf("Cantidad: %d\n", cantidadProducto);
      printf("Precio: %.2f\n", precioProducto);
      printf("------------------------\n");
    }
    fclose(archivo);
  } else {
    printf("El archivo no pudo abrirse");
  }
}