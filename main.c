#include "inventario.h"
#include "factura.h"
#include "cedula.h"
#include "login.h"
#include "menu.h"

#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define FILAS 100
#define COLUMNAS 15

#define MAX_CEDULA_LENGTH 11
#define MAX_NOMBRE_LENGTH 50
#define MAX_APELLIDO_LENGTH 50
#define MAX_PRODUCTOS 100

int main(void) {
  FILE *archivo;
  int opc, filas;
  int cantidad[FILAS];
  float precio[FILAS];
  char producto[FILAS][COLUMNAS];
  char nombre_usuario[100];
  char contraseña[100];
  int intentos = 0;
  int respuesta;
  char productos[FILAS][COLUMNAS];
  char cedula[MAX_CEDULA_LENGTH];
  int cantidadProductos[FILAS];
  char nombre[MAX_NOMBRE_LENGTH];  
  char apellido[MAX_APELLIDO_LENGTH]; 
  int totalProductos = 0;
  float total;
  int opcion;
  int tamaño;

  int resultado = realizar_inicio_sesion();

    do {
      opc = menuprincipal();
      switch (opc) {
        case 1:
          ingresarCliente();
          break;
        case 2:
          modificarCliente();
          break;
        case 3:
          consultarCliente();
          break;
        case 4:
          verListadoClientes();
          break;
        case 5:
          ingresarDatos(&tamaño, productos, precio, cantidadProductos);
          guardarDatos(tamaño, productos, precio, cantidadProductos);
          break;
        case 6:
          editarDatos();
          break;
        case 7:
          aumentarstock();
          break;
        case 8:
          eliminarNombre();
          break;
        case 9:
          buscarNombre();
          break;
        case 10:
          mostrarDatos(productos, precio, cantidadProductos);
          break;
        case 11:
          realizarCalculos(cedula, totalProductos, productos, precio, cantidadProductos);
          break;
        case 12:
          mostrarFacturas();
          break;
        case 13:
          buscarFactura();
          break;
        case 0:
          printf("Saliendo del programa...\n");
          break;
        default:
          printf("Opción inválida. Por favor, ingrese una opción válida.\n");
          break;
      }
    } while (opc != 0);
  return 0;
}