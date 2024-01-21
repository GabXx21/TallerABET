#define COLUMNAS 15
#define FILAS 100

void realizarCalculos(char cedula[], int totalProductos, char productos[][COLUMNAS], float precio[], int cantidadProductos[]);
void imprimirFactura(const char cedula[], const char productos[][COLUMNAS],const int totalProductos, const float total);
void mostrarFacturas();
void buscarFactura();