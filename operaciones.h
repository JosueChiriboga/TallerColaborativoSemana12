#define MAX_PRODUCTOS 100 // Numero maximo de los productos
#define MAX_NOMBRE 50 // Longitud maxima del nombre del producto ingresado

// PROTOTIPOS
void agregarProducto(char[][MAX_NOMBRE], int[], float[], int*);
void imprimirProductos(char[][MAX_NOMBRE], int[], float[], int);
void buscarProducto(char[][MAX_NOMBRE], int[], float[], int);
void modificarProducto(char[][MAX_NOMBRE], int[], float[], int);
void eliminarProducto(char[][MAX_NOMBRE], int[], float[], int*);