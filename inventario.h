#define COLUMNAS 15
#define FILAS 100

void ingresarDatos(int *cantidad, char productos[][COLUMNAS], float precio[], int cantidadProductos[]);
void guardarDatos(const int cantidad, char productos[][COLUMNAS], float precio[], int cantidadProductos[]);
void editarDatos();
void aumentarstock();
void eliminarNombre();
void buscarNombre();
void mostrarDatos(char productos[][COLUMNAS], float precio[], int cantidadProductos[]);