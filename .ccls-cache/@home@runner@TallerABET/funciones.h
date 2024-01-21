#define COLUMNAS 15
#define FILAS 100
int menu();

void ingresarProductos(char productos[][COLUMNAS], int cantidad[], float precio[], int *filas);
void eliminarProductos(char productos[][COLUMNAS], int cantidad[], float precio[], int filas);
void editarProductos(const char productos[][COLUMNAS], int cantidad[], float precio[], int filas);
void mostrarProductos(const char productos[][COLUMNAS], int cantidad[], float precio[], int filas);
void calcularVentas(const char productos[][COLUMNAS], int cantidad[], float precio[], int filas);

