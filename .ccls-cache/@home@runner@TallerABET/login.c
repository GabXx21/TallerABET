#include "login.h"
#include <stdio.h>
#include <string.h>

#define USUARIO "user"
#define CONTRASENA "admin"


int realizar_inicio_sesion() {
    int intentos = 0;
    char nombre_usuario[50];  
    char contraseña[50];      
    int respuesta;

    while (intentos < 3) {
        printf("Intento %d\n", intentos + 1);

        printf("Ingrese su nombre de usuario: ");
        fgets(nombre_usuario, sizeof(nombre_usuario), stdin);
        nombre_usuario[strcspn(nombre_usuario, "\n")] = 0;

        printf("Ingrese su contraseña: ");
        fgets(contraseña, sizeof(contraseña), stdin);
        contraseña[strcspn(contraseña, "\n")] = 0;

        respuesta = validar_credenciales(nombre_usuario, contraseña);

        if (respuesta == 1) {
            printf("Inicio de sesión exitoso.\n");
            return 1;  // Éxito, se inicia sesión
        } else {
            printf("Error en el inicio de sesión. Intentos restantes: %d\n",
                   3 - intentos - 1);
            intentos++;
        }
    }

    if (intentos == 3) {
        printf("Ha superado el número de intentos permitidos.\n");
        exit(0);
    }

    return 0;  // Este punto no debería alcanzarse, pero para cumplir con la firma de la función
}

int validar_credenciales(char *nombre_usuario, char *contraseña) {
  if (strcmp(nombre_usuario, USUARIO) != 0 ||
      strcmp(contraseña, CONTRASENA) != 0) {
    printf("Error: El nombre de usuario o la contraseña equivocada.\n");
    return 0;
  } else {
    return 1;
  }
}

int iniciar_sesion(char *nombre_usuario, char *contraseña) {
  return validar_credenciales(nombre_usuario, contraseña);
}