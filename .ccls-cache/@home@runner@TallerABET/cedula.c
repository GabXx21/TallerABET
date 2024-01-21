#include "cedula.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>


bool validarCedulaEcuatoriana(const char cedula[]) {
  int coeficientes[9] = {2, 1, 2, 1, 2, 1, 2, 1, 2};
  int total = 0;

  // Verificar que la cédula tenga 10 dígitos
  if (strlen(cedula) != 10) {
    return false;
  }

  // Verificar que todos los caracteres sean dígitos
  for (int i = 0; i < 10; i++) {
    if (!isdigit(cedula[i])) {
      return false;
    }
  }

  // Calcular el total de la multiplicación de cada dígito por su coeficiente correspondiente
  for (int i = 0; i < 9; i++) {
    // conversión de un carácter numérico en formato de cadena a un entero
    int digito = cedula[i] - '0';
    int producto = digito * coeficientes[i];
    total += (producto > 9) ? producto - 9 : producto;
  }

  // Verificar que el último dígito sea igual a 10 menos el residuo de la división del total entre 10
  int ultimoDigito = cedula[9] - '0';
  int residuo = total % 10;
  int digitoVerificador = (residuo == 0) ? 0 : 10 - residuo;

  return ultimoDigito == digitoVerificador;
}

bool existeCliente(const char cedula[]) {
  FILE *archivo = fopen("clientes.txt", "r");
  if (archivo == NULL) {
    printf("El archivo no pudo abrirse\n");
    return false;
  }

  char cedulaActual[MAX_CEDULA_LENGTH];
  char nombre[MAX_NOMBRE_LENGTH];
  char apellido[MAX_APELLIDO_LENGTH];

  while (fscanf(archivo, "%s %s %s", cedulaActual, nombre, apellido) != EOF){

    if (strcmp(cedula, cedulaActual) == 0) {
      fclose(archivo);
      return true;
    }
  }

  fclose(archivo);
  return false;
}

bool esLetra(const char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isalpha(str[i])) {
            return false;
        }
    }
    return true;
}

void ingresarCliente() {
    char cedula[MAX_CEDULA_LENGTH];
    char nombre[MAX_NOMBRE_LENGTH];
    char apellido[MAX_APELLIDO_LENGTH];

    while (1) {
        printf("Ingrese la cedula del cliente: ");
        scanf("%s", cedula);

        if (validarCedulaEcuatoriana(cedula)) {
            if (!existeCliente(cedula)) {
                break;  // Salir del bucle si la cédula es válida y no existe un cliente con esa cédula
            } else {
                printf("Ya existe un cliente con esa cedula.\n");
            }
        } else {
            printf("Cédula inválida. Debe tener 10 dígitos y ser válida según el algoritmo ecuatoriano.\n");
        }
    }

    do {
        printf("Ingrese el nombre del cliente: ");
        scanf("%s", nombre);
        if (!esLetra(nombre)) {
            printf("El nombre solo debe contener letras.\n");
        }
    } while (!esLetra(nombre));

    do {
        printf("Ingrese el apellido del cliente: ");
        scanf("%s", apellido);
        if (!esLetra(apellido)) {
            printf("El apellido solo debe contener letras.\n");
        }
    } while (!esLetra(apellido));

    FILE *archivo = fopen("clientes.txt", "a");
    fprintf(archivo, "%s %s %s\n", cedula, nombre, apellido);
    fclose(archivo);

    printf("Cliente ingresado exitosamente.\n");
}


void modificarCliente() {
    char cedula[MAX_CEDULA_LENGTH];
    char nombre[MAX_NOMBRE_LENGTH];
    char apellido[MAX_APELLIDO_LENGTH];
    char confirmacion[5];

    printf("Ingrese la cedula del cliente a modificar: ");
    scanf("%s", cedula);

    if (!existeCliente(cedula)) {
        printf("No se encontró un cliente con esa cedula.\n");
        return;
    }

    do {
        printf("Ingrese el nuevo nombre del cliente: ");
        scanf("%s", nombre);
        if (!esLetra(nombre)) {
            printf("El nombre solo debe contener letras.\n");
        }
    } while (!esLetra(nombre));

    do {
        printf("Ingrese el nuevo apellido del cliente: ");
        scanf("%s", apellido);
        if (!esLetra(apellido)) {
            printf("El apellido solo debe contener letras.\n");
        }
    } while (!esLetra(apellido));

    printf("Está seguro de que desea modificar el cliente? (s/n): ");
    scanf("%s", confirmacion);

    if (strcmp(confirmacion, "s") != 0) {
        printf("Modificación cancelada.\n");
        return;
    }

    FILE *archivo = fopen("clientes.txt", "r");
    FILE *temporal = fopen("temp.txt", "w");

    char cedulaActual[MAX_CEDULA_LENGTH];
    char nombreActual[MAX_NOMBRE_LENGTH];
    char apellidoActual[MAX_APELLIDO_LENGTH];

    while (fscanf(archivo, "%s %s %s", cedulaActual, nombreActual, apellidoActual) != EOF) {
        if (strcmp(cedula, cedulaActual) == 0) {
            fprintf(temporal, "%s %s %s\n", cedula, nombre, apellido);
        } else {
            fprintf(temporal, "%s %s %s\n", cedulaActual, nombreActual, apellidoActual);
        }
    }

    fclose(archivo);
    fclose(temporal);

    remove("clientes.txt");
    rename("temp.txt", "clientes.txt");

    printf("Cliente modificado exitosamente.\n");
}


void consultarCliente() {
    char cedula[MAX_CEDULA_LENGTH];
    printf("Ingrese la cedula del cliente a consultar: ");
    scanf("%s", cedula);

    if (!existeCliente(cedula)) {
        printf("No se encontró un cliente con esa cedula.\n");
        return;
    }

    FILE *archivo = fopen("clientes.txt", "r");
    char cedulaActual[MAX_CEDULA_LENGTH];
    char nombre[MAX_NOMBRE_LENGTH];
    char apellido[MAX_APELLIDO_LENGTH];

    while (fscanf(archivo, "%s %s %s", cedulaActual, nombre, apellido) != EOF) {
        if (strcmp(cedula, cedulaActual) == 0) {
            printf("Cedula: %s\n", cedulaActual);
            printf("Nombre: %s\n", nombre);
            printf("Apellido: %s\n", apellido);
            break;
        }
    }

    fclose(archivo);
}

void verListadoClientes() {
    FILE *archivo = fopen("clientes.txt", "r");
    char cedula[MAX_CEDULA_LENGTH];
    char nombre[MAX_NOMBRE_LENGTH];
    char apellido[MAX_APELLIDO_LENGTH];

    printf("Listado de clientes:\n");
    printf("------------------\n");

    while (fscanf(archivo, "%s %s %s", cedula, nombre, apellido) != EOF) {
        printf("Cedula: %s\n", cedula);
        printf("Nombre: %s\n", nombre);
        printf("Apellido: %s\n", apellido);
        printf("--------------------\n");
    }

    fclose(archivo);
}