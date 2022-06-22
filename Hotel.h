#ifndef HOTEL_H_INCLUDED
#define HOTEL_H_INCLUDED

typedef struct
{
    char nombre[30];
    int edad;
    int dni;
} stCliente;

typedef struct
{
    int numHabitacion;
    char tipoHabitacion[30];
    int precioHabitacion;
    char disponibilidad;

} stHabitacion;

typedef struct
{
    int servicio;
    int pensionComida;
    int estacionamiento;
} stServicios;

typedef struct
{
    char tipoPago[30];
    int cuotas;

} stMetodoPago;

typedef struct
{
    stCliente clienteReserva[10];
    stHabitacion habitacionReserva;
    stServicios serviciosReserva;
    stMetodoPago pagoReserva;
    int cantNoches;
    float precioTotal;
    char estado[30];
    int cantidadPersonas;
} stReserva;

void menu();
void cargarReserva(char archivoReserva[]);
int valorEstacionamiento(char c,stReserva A);
void mostrarArchivo(char archivoReserva[]);
stReserva cargarFamilia(stReserva A,int pos,int x,int y);
int valorDeServicios(char a,char b);
void validacion(char *a,int x,int y);
int cargarTipoDeHabitacion(stReserva reserva, int *tipoHab);
int valorPension(char pension[]);
void cargarArchivoHabitaciones(char archivoHabitacion[]);
void mostrarDisponibles(char archivoHabitaciones[]);
void mostrarDoblesDisponibles(char archivoHabitaciones[]);
void mostrarTriplesDisponibles(char archivoHabitaciones[]);
void mostrarCuadruplesDisponibles(char archivoHabitaciones[]);
void mostrarSuitesDisponibles(char archivoHabitaciones[]);
void mostrarPorTipodeHabitaciones(char archivoHabitaciones[],char tipo[]);
void modificarDisponibilidad(char archivoHabitaciones[],int numHab);
stHabitacion cambioDisponibilidad(stHabitacion A);
int busquedaPosicionHab(char archivoHabitaciones[],int numHab);
int verificacionHabitacionDisponible(char archivoHabitaciones[],int numHab);
int verificarPorTipoHabitacion(int numHab,char tipoHab[]);
float tipoDePago(char tipo[],float total,int cuotas);
float precioTotal(stReserva A,int vHabitacion);
int busquedaPorDNI(char archivo[],int buscado);
void mostrarDeAUno(stReserva A);
int busquedaPorNombre(char archivo[],char buscado[]);
int busquedaPorHabitacion(char archivo[],int buscado);
int busquedaPorTipoHabitacion(char archivo[],char buscado[]);
void borrarRegistro(int bNumHab);
void mostrarOcupadas(char archivoHabitacion[]);
int cantidadRegistros(char archivo[]);
void ordenarArray(stReserva A[], int validos);
void ordenarPorHabitacion(char archivo[]);
int archivo_A_array(char archivo[],stReserva A[]);
void array_A_archivo(char archivo[],stReserva A[],int val);
int verificacionHuesped(char archivo[],int numHab,int huesped);
int busquedaHabitacionposicion(char archivo[],int numHab);
void modificarNombreHuesped(char archivo[],int numHab,int huesped);
void modificarEdadHuesped(char archivo[],int numHab,int huesped);
void modificarDocumento(char archivo[],int numHab,int huesped);
void modificarGymSpa(char archivo[],int numHab);
void modificarPension(char archivo[],int numHab);
void modificarEstacionamiento(char archivo[],int numHab);
stReserva tipodeHab_paramodificar(stReserva A,int control);
void modificarHabitacion(char archivo[],int numHab,int control);
void condicionesDeMuestra(char archivo[], int numHab);
int condicionControl(char archivo[],int numHab,int control);
void modificarNoches(char archivo[],int numHab);


#endif // HOTEL_H_INCLUDED
