#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "Hotel.h"

const int doble = 250;
const int triple = 375;
const int cuadruple = 500;
const int suite = 800;

void cargarReserva(char archivoReserva[])///El usuario carga una reserva.
{
    stReserva reserva;
    fflush(stdin);
    FILE *archi = fopen(archivoReserva,"ab");
    if(archi!=NULL)
    {
        gotoxy(8,6);
        printf("Cantidad de Noches: ");
        scanf("%d",&reserva.cantNoches);

        gotoxy(8,8);
        printf("Tipo de Habitacion (Doble / Triple / Cuadruple / Suite): ");
        fflush(stdin);
        gets(reserva.habitacionReserva.tipoHabitacion);

        while(strcmpi(reserva.habitacionReserva.tipoHabitacion,"Doble")!=0 && strcmpi(reserva.habitacionReserva.tipoHabitacion,"Triple")!=0 && strcmpi(reserva.habitacionReserva.tipoHabitacion,"Cuadruple")!=0 && strcmpi(reserva.habitacionReserva.tipoHabitacion,"Suite")!=0 )
        {
            gotoxy(8,9);
            printf("El tipo no existe. Ingrese nuevamente: ");
            fflush(stdin);
            gets(reserva.habitacionReserva.tipoHabitacion);
        }

        int tipoHab;
        reserva.habitacionReserva.precioHabitacion = cargarTipoDeHabitacion(reserva,&tipoHab);

        gotoxy(8,10);
        int cantPersonas;
        printf("Cantidad de Personas: ");
        scanf("%d",&reserva.cantidadPersonas);

        while(reserva.cantidadPersonas>tipoHab)
        {
            gotoxy(8,10);
            printf("El maximo de personas para la habitacion es %d. Ingrese nuevamente: ",tipoHab);
            scanf("%d",&reserva.cantidadPersonas);
        }

        gotoxy(8,12);
        char pension[30];
        printf("Tipo de Pension (Media / Completa): ");
        fflush(stdin);
        scanf("%s",&pension);
        while(strcmpi(pension,"Media")!=0 && strcmpi(pension,"Completa")!=0 )
        {
            gotoxy(8,12);
            printf("No existe. Ingrese nuevamente (Media / Completa): ");
            fflush(stdin);
            scanf("%s",&pension);
        }

        reserva.serviciosReserva.pensionComida = valorPension(pension);

        char a,b,c;
        gotoxy(8,14);
        printf("Tipos de Servicios: ");

        gotoxy(10,15);
        printf("- GYM (s/n) : ");
        fflush(stdin);
        scanf("%c",&a);
        validacion(&a,10,16);

        gotoxy(10,17);
        printf("- SPA (s/n) : ");
        fflush(stdin);
        scanf("%c",&b);
        validacion(&b,10,18);

        gotoxy(10,19);
        printf("- Estacionamiento(s/n) : ");
        fflush(stdin);
        scanf("%c",&c);
        validacion(&c,10,20);


        reserva.serviciosReserva.estacionamiento = valorEstacionamiento(c,reserva);
        reserva.serviciosReserva.servicio = valorDeServicios(a,b);

        system("cls");
        gotoxy(50,2);
        printf("HOTEL YAPEYU");
        gotoxy(48,4);
        printf("RESERVA - CLIENTE");

        int x=8, y=7, num=1;
        for(int k=0; k<reserva.cantidadPersonas; k++)
        {
            printf("\nPersona %d de %d:",num,reserva.cantidadPersonas);
            reserva=cargarFamilia(reserva,k,x,y);
            y+=8;
            num++;
        }

        system("cls");
        gotoxy(50,2);
        printf("HOTEL YAPEYU");
        gotoxy(40,4);
        printf("RESERVA - HABITACIONES DISPONIBLES\n\n");

        printf("Habitaciones %s disponibles: \n",reserva.habitacionReserva.tipoHabitacion);
        mostrarPorTipodeHabitaciones("Habitaciones.bin",reserva.habitacionReserva.tipoHabitacion);

        printf("\n\nElija numero de habitacion a hospedar: ");
        scanf("%d",&reserva.habitacionReserva.numHabitacion);
        int veriDispo=1,veriTipo=1;

        do
        {
            veriDispo= verificacionHabitacionDisponible("Habitaciones.bin",reserva.habitacionReserva.numHabitacion);
            veriTipo = verificarPorTipoHabitacion(reserva.habitacionReserva.numHabitacion,reserva.habitacionReserva.tipoHabitacion);
            if(veriDispo!=1 || veriTipo!=1)
            {
                gotoxy(0,19);
                printf("Habitacion no disponible o no se encuentra dentro del tipo de habitacion '%s'... Elija nuevamente: ",reserva.habitacionReserva.tipoHabitacion);
                scanf("%d",&reserva.habitacionReserva.numHabitacion);
            }
        }
        while(veriDispo!=1 || veriTipo!=1);

        float total = precioTotal(reserva,reserva.habitacionReserva.precioHabitacion);

        system("cls");
        gotoxy(50,2);
        printf("HOTEL YAPEYU");
        gotoxy(43,4);
        printf("RESERVA - RESUMEN DE PAGO ");
        gotoxy(10,6);
        printf("Cantidad de Noches: %d",reserva.cantNoches);
        gotoxy(10,8);
        printf("Valor de Habitacion por noche ($ %d)", reserva.habitacionReserva.precioHabitacion);
        gotoxy(50,8);
        printf("$ %d",reserva.habitacionReserva.precioHabitacion*reserva.cantNoches);
        gotoxy(10,10);
        printf("Valor de Servicios ");
        gotoxy(50,10);
        printf("$ %d",reserva.serviciosReserva.servicio);
        gotoxy(10,12);
        if(reserva.serviciosReserva.pensionComida==50)
        {
            printf("Valor de Pension (Media = $50)");
        }
        else
        {
            printf("Valor de Pension (Completa = $100)");
        }
        gotoxy(50,12);
        printf("$ %d",reserva.serviciosReserva.pensionComida*reserva.cantNoches);
        gotoxy(10,14);
        printf("Valor Estacionamiento por noche($ 25)");
        gotoxy(50,14);
        printf("$ %d",reserva.serviciosReserva.estacionamiento);
        gotoxy(10,16);
        printf("PRECIO TOTAL");
        gotoxy(10,16);
        printf("----------------------------------------------------");
        gotoxy(50,18);
        printf("$ %.2f",total);
        gotoxy(10,22);
        printf("Elija metodo de pago (Efectivo / Debito / Credito): ");
        fflush(stdin);
        gets(reserva.pagoReserva.tipoPago);

        float precioFinal;

        while(strcmpi(reserva.pagoReserva.tipoPago,"Efectivo")!=0 && strcmpi(reserva.pagoReserva.tipoPago,"Debito")!=0 && strcmpi(reserva.pagoReserva.tipoPago,"Credito")!=0)
        {
            gotoxy(10,21);
            printf("Metodo de Pago Inexistente! Por favor, ingrese nuevamente: ");
            fflush(stdin);
            gets(reserva.pagoReserva.tipoPago);
        }

        if(strcmpi(reserva.pagoReserva.tipoPago,"Credito")==0)
        {
            gotoxy(10,23);
            printf("Opciones de cuotas: ");
            gotoxy(10,25);
            printf("- 3  cuotas de $ %.2f  (15%% de recargo)",(total*1.15)/3);
            gotoxy(10,26);
            printf("- 6  cuotas de $ %.2f  (20%% de recargo)",(total*1.20)/6);
            gotoxy(10,27);
            printf("- 9  cuotas de $ %.2f  (25%% de recargo)",(total*1.25)/9);
            gotoxy(10,28);
            printf("- 12 cuotas de $ %.2f  (30%% de recargo)",(total*1.30)/12);
            gotoxy(10,30);
            printf("Seleccione cantidad de cuotas: ");
            scanf("%d",&reserva.pagoReserva.cuotas);
            while(reserva.pagoReserva.cuotas!=3 && reserva.pagoReserva.cuotas!=6 && reserva.pagoReserva.cuotas!=9 && reserva.pagoReserva.cuotas!=12)
            {
                gotoxy(10,31);
                printf("Error! Intente nuevamente: ");
                scanf("%d",&reserva.pagoReserva.cuotas);
            }
            gotoxy(10,33);
        }
        else
        {
            gotoxy(10,23);
        }

        precioFinal = tipoDePago(reserva.pagoReserva.tipoPago,total,reserva.pagoReserva.cuotas);

        printf("El Precio Final Total es: $%.2f",precioFinal);

        reserva.precioTotal = precioFinal;

        modificarDisponibilidad("Habitaciones.bin",reserva.habitacionReserva.numHabitacion);

        fwrite(&reserva,sizeof(stReserva),1,archi);
        fclose(archi);
    }
}

int valorEstacionamiento(char c,stReserva A)///Calcula el valor del estacionamiento y lo retorna.
{
    int v;
    if(c == 's'||c =='S')
    {
        v = 25 * A.cantNoches;
    }
    else
    {
        v=0;
    }
    return v;
}

void mostrarArchivo(char archivoReserva[])///Muestra las reservas cargadas al archivo.
{
    stReserva A;
    int num=1;
    int i;
    FILE * archi = fopen(archivoReserva,"rb");
    if(archi!=NULL)
    {
        while(fread(&A,sizeof(stReserva),1,archi)>0)
        {
            mostrarDeAUno(A);
            printf("\n");
        }

        fclose(archi);
    }
    else
    {
        printf("\n\nEl archivo no existe...");
    }
}

stReserva cargarFamilia(stReserva A,int pos,int x,int y)///Carga la informacion de los huespedes de la reserva
{
    gotoxy(x,y);
    printf("- Nombre y Apellido: ");
    fflush(stdin);
    gets(A.clienteReserva[pos].nombre);

    gotoxy(x,y+2);
    printf("- Edad: ");
    scanf("%d",&A.clienteReserva[pos].edad);

    gotoxy(x,y+4);
    printf("- Documento: ");
    scanf("%d",&A.clienteReserva[pos].dni);
    return A;
}

int valorDeServicios(char a,char b)///Retorna el valor de los servicios contratados (SPA y GYM), en base a los dias y a cuantos servicios va a usar.
{
    int valor;

    if((a=='s' || a=='S') && (b=='s' || b=='S'))
    {
        valor= 100;
    }
    else if ((a=='s'|| a=='S') && (b=='n' || b=='N'))
    {
        valor = 50;
    }
    else if((a=='n'|| a=='N') && (b=='s' || b=='S'))
    {
        valor = 70;
    }
    else if((a=='n'|| a=='N') && (b=='n' || b=='N'))
    {
        valor=0;
    }

    return valor;
}

void validacion(char *a,int x,int y)///Valida que el char ingresado sea 's' o 'n'.
{
    while(*a!='s'&& *a!='S' && *a!='n'&& *a!='N')
    {
        gotoxy(x,y);
        printf("- No existe. Ingrese nuevamente (s/n): ");
        fflush(stdin);
        scanf("%c",a);
    }
}

int cargarTipoDeHabitacion(stReserva reserva, int *tipoHab)///Carga el tipo de habitacion que selecciona el usuario.
{
    if(strcmpi(reserva.habitacionReserva.tipoHabitacion,"Doble")==0)
    {
        *tipoHab = 2;
        reserva.habitacionReserva.precioHabitacion = doble;
    }
    if(strcmpi(reserva.habitacionReserva.tipoHabitacion,"Triple")==0)
    {
        *tipoHab = 3;
        reserva.habitacionReserva.precioHabitacion = triple;
    }
    if(strcmpi(reserva.habitacionReserva.tipoHabitacion,"Cuadruple")==0)
    {
        *tipoHab = 4;
        reserva.habitacionReserva.precioHabitacion = cuadruple;
    }
    if(strcmpi(reserva.habitacionReserva.tipoHabitacion,"Suite")==0)
    {
        *tipoHab = 6;
        reserva.habitacionReserva.precioHabitacion = suite;
    }

    return reserva.habitacionReserva.precioHabitacion;
}

int valorPension(char pension[])///Compara y retorna el valor de la pension de la comida, que despues se calcula por dia.
{
    int valor;
    if(strcmpi(pension,"Media")==0)
    {
        valor = 50;
    }
    if(strcmpi(pension,"Completa")==0)
    {
        valor = 100;
    }
    return valor;
}

void cargarArchivoHabitaciones(char archivoHabitacion[]) ///Carga el Archivo "Habitaciones.bin";
{
    stHabitacion room;
    int num;
    FILE *archi=fopen(archivoHabitacion,"wb");
    if(archi!=NULL)
    {
        for(num = 1; num <=55; num++)
        {
            if(num<=43 && num%2==1)
            {
                room.numHabitacion=num;
                strcpy(room.tipoHabitacion,"Doble");
                room.precioHabitacion= 250;
                room.disponibilidad='s';

            }
            else if(num<=44 && num%2==0)
            {
                room.numHabitacion=num;
                strcpy(room.tipoHabitacion,"Triple");
                room.precioHabitacion= 375;
                room.disponibilidad='s';

            }
            else if(num>=45 && num<=49)
            {
                room.numHabitacion=num;
                strcpy(room.tipoHabitacion,"Cuadruple");
                room.precioHabitacion= 500;
                room.disponibilidad='s';
            }
            else if(num>=50 && num<=55)
            {
                room.numHabitacion=num;
                strcpy(room.tipoHabitacion,"Suite");
                room.precioHabitacion= 800;
                room.disponibilidad='s';
            }
            fwrite(&room,sizeof(stHabitacion),1,archi);
        }
        fclose(archi);
    }
}

void mostrarDisponibles(char archivoHabitaciones[])///Llama a las funciones que muestran las habitaciones disponibles de cada tipo.
{
    printf("\nHabitaciones Dobles: \n");
    mostrarDoblesDisponibles(archivoHabitaciones);
    printf("\n\nHabitaciones Triples: \n");
    mostrarTriplesDisponibles(archivoHabitaciones);
    printf("\n\nHabitaciones Cuadruples: \n");
    mostrarCuadruplesDisponibles(archivoHabitaciones);
    printf("\n\nHabitaciones Suites: \n");
    mostrarSuitesDisponibles(archivoHabitaciones);
}

void mostrarDoblesDisponibles(char archivoHabitaciones[])///Muestra las habitaciones dobles. Las disponibles en verde y las ocupadas en rojo.
{
    stHabitacion room;
    int i=0;
    FILE *archi = fopen(archivoHabitaciones,"rb");
    if(archi!=NULL)
    {
        while(fread(&room,sizeof(stHabitacion),1,archi)>0)
        {
            if((room.numHabitacion<=43 && room.numHabitacion%2==1))
            {
                if(i>2)
                {
                    printf("\n");
                    i=0;
                }
                if(room.numHabitacion<10 && (room.disponibilidad=='s'||room.disponibilidad=='S'))
                {
                    printf ("\033[1;32m");
                    printf("\t\[ 0%d ]", room.numHabitacion);


                }
                else if (room.numHabitacion<10 && (room.disponibilidad=='n'||room.disponibilidad=='N'))
                {
                    printf ("\033[1;31m"); // rojo
                    printf("\t\[ 0%d ]", room.numHabitacion);

                }
                else if (room.numHabitacion >= 10 && (room.disponibilidad=='s'||room.disponibilidad=='S'))
                {
                    printf ("\033[1;32m");
                    printf("\t\[ %d ]", room.numHabitacion);

                }
                else if (room.numHabitacion >= 10 && (room.disponibilidad=='n'||room.disponibilidad=='N'))
                {
                    printf ("\033[1;31m"); // rojo
                    printf("\t\[ %d ]", room.numHabitacion);
                }
                printf ("\033[0m");
                i++;
            }

        }
        fclose(archi);
    }
    else
    {
        printf("El archivo no existe...");
    }
}

void mostrarTriplesDisponibles(char archivoHabitaciones[])///Muestra las habitaciones triples. Las disponibles en verde y las ocupadas en rojo.
{
    stHabitacion room;
    FILE *archi = fopen(archivoHabitaciones,"rb");
    int i=0;
    if(archi!=NULL)
    {
        while(fread(&room,sizeof(stHabitacion),1,archi)>0)
        {
            if((room.numHabitacion<=44 && room.numHabitacion%2==0))
            {
                if(i>2)
                {
                    printf("\n");
                    i=0;
                }
                if(room.numHabitacion<10 && (room.disponibilidad=='s'||room.disponibilidad=='S'))
                {
                    printf ("\033[1;32m");//verde
                    printf("\t\[ 0%d ]", room.numHabitacion);

                }
                else if (room.numHabitacion<10 && (room.disponibilidad=='n'||room.disponibilidad=='N'))
                {
                    printf ("\033[1;31m"); // rojo
                    printf("\t\[ 0%d ]", room.numHabitacion);
                }
                else if (room.numHabitacion >= 10 && (room.disponibilidad=='s'||room.disponibilidad=='S'))
                {
                    printf ("\033[1;32m");
                    printf("\t\[ %d ]", room.numHabitacion);

                }
                else if (room.numHabitacion >= 10 && (room.disponibilidad=='n'||room.disponibilidad=='N'))
                {
                    printf ("\033[1;31m"); // rojo
                    printf("\t\[ %d ]", room.numHabitacion);
                }
                printf ("\033[0m");
                i++;
            }
        }
    }
    fclose(archi);
}

void mostrarCuadruplesDisponibles(char archivoHabitaciones[])///Muestra las habitaciones cuadruples. Las disponibles en verde y las ocupadas en rojo.
{
    stHabitacion room;
    FILE *archi = fopen(archivoHabitaciones,"rb");
    if(archi!=NULL)
    {
        while(fread(&room,sizeof(stHabitacion),1,archi)>0)
        {
            if((room.numHabitacion>=45 && room.numHabitacion<=49))
            {
                if ((room.disponibilidad=='s'||room.disponibilidad=='S'))
                {
                    printf ("\033[1;32m");
                    printf("\t\[ %d ]", room.numHabitacion);

                }
                else if ((room.disponibilidad=='n'||room.disponibilidad=='N'))
                {
                    printf ("\033[1;31m"); // rojo
                    printf("\t\[ %d ]", room.numHabitacion);
                }
                printf ("\033[0m");
            }
        }
        fclose(archi);
    }
}

void mostrarSuitesDisponibles(char archivoHabitaciones[])///Muestra las habitaciones suites. Las disponibles en verde y las ocupadas en rojo.
{
    stHabitacion room;
    FILE *archi = fopen(archivoHabitaciones,"rb");
    if(archi!=NULL)
    {
        while(fread(&room,sizeof(stHabitacion),1,archi)>0)
        {
            if((room.numHabitacion>=50 && room.numHabitacion<=55))
            {
                if ((room.disponibilidad=='s'||room.disponibilidad=='S'))
                {
                    printf ("\033[1;32m");
                    printf("\t\[ %d ]", room.numHabitacion);

                }
                else if ((room.disponibilidad=='n'||room.disponibilidad=='N'))
                {
                    printf ("\033[1;31m"); // rojo
                    printf("\t\[ %d ]", room.numHabitacion);
                }
                printf ("\033[0m");
            }
        }
    }
    fclose(archi);
}

void mostrarPorTipodeHabitaciones(char archivoHabitaciones[],char tipo[])///Muestra (en la carga de una reserva) todas las habitaciones del tipo seleccionado, en verdes las disponibles y las ocupadas en rojo.
{
    stHabitacion room;
    FILE *archi = fopen(archivoHabitaciones,"rb");
    int i=0;
    if(archi!=NULL)
    {
        while(fread(&room,sizeof(stHabitacion),1,archi)>0)
        {
            if((room.disponibilidad=='s'||room.disponibilidad=='S') && strcmpi(room.tipoHabitacion,tipo)==0)
            {
                if(i>2)
                {
                    printf("\n");
                    i=0;
                }
                printf ("\033[1;32m");// Verde
                if(room.numHabitacion<10)
                    printf("[ 0%d ]", room.numHabitacion);
                else
                    printf("[ %d ]", room.numHabitacion);
                    i++;
            }
            else if ((room.disponibilidad=='n'||room.disponibilidad=='N') && strcmpi(room.tipoHabitacion,tipo)==0) /// rojos no disponibles
            {
                if(i>2)
                {
                    printf("\n");
                    i=0;
                }
                printf ("\033[1;31m"); // Rojo
                if(room.numHabitacion<10)
                    printf("[ 0%d ]", room.numHabitacion);
                else
                    printf("[ %d ]", room.numHabitacion);
                    i++;
            }
        }

        printf ("\033[0m");
        fclose(archi);
    }
}

void modificarDisponibilidad(char archivoHabitaciones[],int numHab)///Cambia la disponibilidad de una habitacion determinada.
{
    stHabitacion A;
    int pos = busquedaPosicionHab(archivoHabitaciones,numHab);
    FILE *archi = fopen(archivoHabitaciones,"r+b");
    if(archi!=NULL)
    {
        fseek(archi,sizeof(stHabitacion)*(pos-1),SEEK_SET);
        fread(&A,sizeof(stHabitacion),1,archi);

        A = cambioDisponibilidad(A);

        fseek(archi,sizeof(stHabitacion)*(pos-1),SEEK_SET);
        fwrite(&A,sizeof(stHabitacion),1,archi);

        fclose(archi);
    }
}

stHabitacion cambioDisponibilidad(stHabitacion A)///Funcion que cambia la disponibilidad de una habitacion. Si estaba disponible, la ocupa y si esta ocupada, la desocupa.
{
    if(A.disponibilidad=='s'||A.disponibilidad=='S')
        A.disponibilidad='n';
    else if(A.disponibilidad=='n'||A.disponibilidad=='N')
        A.disponibilidad='s';
    return A;
}

int busquedaPosicionHab(char archivoHabitaciones[],int numHab) ///Busqueda posicion habitacion dentro del archivo "Habitaciones.bin"
{
    int pos,i=1;
    FILE *archi=fopen(archivoHabitaciones,"rb");
    stHabitacion A;
    if(archi!=NULL)
    {
        while(fread(&A,sizeof(stHabitacion),1,archi)>0)
        {
            if(A.numHabitacion==numHab)
            {
                pos=i;
            }
            i++;
        }
        fclose(archi);
    }
    else
    {
        printf("\nEl archivo no existe....");
    }
    return pos;
}

int verificacionHabitacionDisponible(char archivoHabitaciones[],int numHab)///Verifica si una habitacion determinada esta ocupada o no.
{
    stHabitacion room;
    int estado=0;
    FILE *archi = fopen(archivoHabitaciones,"rb");
    if(archi!=NULL)
    {
        int pos = busquedaPosicionHab(archivoHabitaciones,numHab);
        fseek(archi,sizeof(stHabitacion)*(pos-1),SEEK_SET);
        fread(&room,sizeof(stHabitacion),1,archi);
        if(room.disponibilidad=='s'||room.disponibilidad=='S')
        {
            estado = 1;
        }
        fclose(archi);
    }
    return estado;
}

int verificarPorTipoHabitacion(int numHab,char tipoHab[])///Verifica que el numero de habitacion (en la carga de reserva) corresponda al tipo de habitacion seleccionado.
{
    int estado = 0;
    if((numHab<=43 && numHab%2==1)&& strcmpi(tipoHab,"Doble")==0)
    {
        estado=1;
    }
    else if((numHab<=44 && numHab%2==0)&& strcmpi(tipoHab,"Triple")==0)
    {
        estado=1;
    }
    else if((numHab>=45 && numHab<=49)&& strcmpi(tipoHab,"Cuadruple")==0)
    {
        estado=1;
    }
    else if((numHab>=50 && numHab<=55)&& strcmpi(tipoHab,"Suite")==0)
    {
        estado=1;
    }

    return estado;
}

float tipoDePago(char tipo[],float total,int cuotas)///Calcula los distintos recargos para las cuotas (si seleccionan pagar con credito).
{
    float precio,precioCuota;
    if(strcmpi(tipo,"Credito")==0)
    {
        if(cuotas==3)
        {
            precioCuota=(total*1.15)/3;
            precio=precioCuota*3;
        }
        else if(cuotas==6)
        {
            precioCuota=(total*1.20)/6;
            precio=precioCuota*6;
        }
        else if(cuotas==9)
        {
            precioCuota=(total*1.25)/9;
            precio=precioCuota*9;
        }
        else if(cuotas==12)
        {
            precioCuota=(total*1.30)/12;
            precio=precioCuota*12;
        }
    }
    else
    {
        precio = total;
    }
    return precio;
}

float precioTotal(stReserva A,int vHabitacion)///Suma todos los valores para calcular el precio total de la reserva.
{
    float total;

    total = A.serviciosReserva.servicio + (float)A.cantNoches*vHabitacion + A.serviciosReserva.pensionComida*A.cantNoches + A.serviciosReserva.estacionamiento;

    return total;
}

int busquedaPorDNI(char archivo[],int buscado)///Busca un DNI dentro de "Reserva.bin" y muestra la reserva asociada al mismo.
{
    int flag =0;
    stReserva A;
    FILE *archi = fopen(archivo,"rb");
    if(archi!=NULL)
    {
        while(fread(&A,sizeof(stReserva),1,archi)>0)
        {
            for(int i=0; i<A.cantidadPersonas; i++)
            {
                if(A.clienteReserva[i].dni==buscado)
                {
                    mostrarDeAUno(A);
                    printf("\n");
                    flag = 1;
                }
            }
        }
        fclose(archi);
    }
    return flag;
}

void mostrarDeAUno(stReserva A)///Muestra la informacion de una reserva.
{
    printf("\n---------------- Numero de Habitacion: %d ----------------",A.habitacionReserva.numHabitacion);

    for(int i=0; i<A.cantidadPersonas; i++)
    {
        printf("\nHuesped %d: ",i+1);
        printf("\n- Nombre y Apellido     : %s",A.clienteReserva[i].nombre);
        printf("\n- Documento             : %d",A.clienteReserva[i].dni);
        printf("\n- Edad                  : %d",A.clienteReserva[i].edad);
    }
    printf("\n             ----");
    printf("\n- Cantidad de Noches    : %d",A.cantNoches);
    if(A.serviciosReserva.pensionComida==50)
        printf("\n- Pension de Comida     : Media");
    else
        printf("\n- Pension de Comida     : Completa");

    if(A.serviciosReserva.servicio==100)
    {
        printf("\n- Servicios             : Gym y Spa");
    }
    else if(A.serviciosReserva.servicio==70)
    {
        printf("\n- Servicios             : Spa");
    }
    else if(A.serviciosReserva.servicio==50)
    {
        printf("\n- Servicios             : Gym");
    }
    else
    {
        printf("\n- Servicios             : No");
    }
    printf("\n- Tipo de Habitacion    : %s",A.habitacionReserva.tipoHabitacion);
    printf("\n- Cantidad de Personas  : %d",A.cantidadPersonas);
    printf("\n- Tipo de Pago          : %s",A.pagoReserva.tipoPago);
    if(strcmpi(A.pagoReserva.tipoPago,"Credito")==0)
    {
        printf("\n- Pago en %d Cuotas", A.pagoReserva.cuotas);
    }
    if(A.serviciosReserva.estacionamiento !=0)
    {
        printf("\n- Estacionamiento       : Si");
    }
    else
    {
        printf("\n- Estacionamieto        : No");
    }
    printf("\n- Precio Final          : %.2f",A.precioTotal);
}

int busquedaPorNombre(char archivo[],char buscado[])///Busca un nombre determinado dentro de archivo "Reserva.bin" y muestra la reserva asociada.
{
    stReserva A;
    int flag = 0;
    FILE *archi = fopen(archivo,"rb");
    if(archi!=NULL)
    {
        while(fread(&A,sizeof(stReserva),1,archi)>0)
        {
            for(int i=0; i<A.cantidadPersonas; i++)
            {
                if(strcmpi(A.clienteReserva[i].nombre,buscado)==0)
                {
                    mostrarDeAUno(A);
                    printf("\n");
                    flag = 1;
                }
            }
        }
        fclose(archi);
    }
    return flag;
}

int busquedaPorHabitacion(char archivo[],int buscado) ///Muestra la habitacion buscada
{
    int flag;
    stReserva A;
    FILE*archi=fopen(archivo,"rb");
    if(archi!=NULL)
    {
        while(fread(&A,sizeof(stReserva),1,archi)>0)
        {
            if(A.habitacionReserva.numHabitacion == buscado)
            {
                mostrarDeAUno(A);
                printf("\n");
                flag = 1;
            }
        }
        fclose(archi);
    }
    return flag;
}

int busquedaPorTipoHabitacion(char archivo[],char buscado[])///Muestra todas las reservas de un determinado tipo de habitacion.
{
    int flag=0;
    stReserva A;
    FILE *archi =fopen(archivo,"rb");
    if(archi!=NULL)
    {
        while(fread(&A,sizeof(stReserva),1,archi)>0)
        {
            if(strcmpi(A.habitacionReserva.tipoHabitacion,buscado)==0)
            {
                mostrarDeAUno(A);
                printf("\n");
                flag = 1;
            }
        }
        fclose(archi);
    }
    return flag;
}

void borrarRegistro(int bNumHab)///Borra un registro de "Reservas.bin" (cancela una reserva).
{
    FILE *archi = fopen("Reservas.bin","rb");
    if(archi==NULL)
        exit(1);
    stReserva A;

    FILE *nuevo = fopen("Reservas.tmp","ab");
    if(archi==NULL)
        exit(1);

    int existe=0;
    fread(&A,sizeof(stReserva),1,archi);
    while(!feof(archi))
    {
        if(bNumHab==A.habitacionReserva.numHabitacion)
        {
            printf("La reserva eliminada es de la habitacion: %d",A.habitacionReserva.numHabitacion);
            existe = 1;
        }
        else
        {
            fwrite(&A,sizeof(stReserva),1,nuevo);
        }
        fread(&A,sizeof(stReserva),1,archi);
    }

    if(existe==0)
    {
        printf("La habitacion no esta cargada...");
    }
    fclose(archi);
    fclose(nuevo);
    remove("Reservas.bin");
    rename("Reservas.tmp","Reservas.bin");
    modificarDisponibilidad("Habitaciones.bin",bNumHab);
}

void mostrarOcupadas(char archivoHabitacion[])///Muestra todas las habitaciones ocupadas.
{
    stHabitacion room;
    FILE *archi =fopen(archivoHabitacion,"rb");
    if(archi!=NULL)
    {
        while(fread(&room,sizeof(stHabitacion),1,archi)>0)
        {
            if(room.disponibilidad=='N'||room.disponibilidad=='n')
            {
                printf("[ %d ]",room.numHabitacion);
            }
        }
        fclose(archi);
    }
}

int cantidadRegistros(char archivo[])///Ordenamiento de seleccion para ordenar las habitaciones por numero.
{
    int cant;
    FILE *archi = fopen(archivo,"rb");
    if(archi!=NULL)
    {
        fseek(archi,0,SEEK_END);
        cant = ftell(archi)/sizeof(stReserva);
        fclose(archi);
    }
    return cant;
}

void ordenarArray(stReserva A[], int validos)///Pasa un arreglo a un archivo.
{
    int menor, i=0;
    stReserva aux;
    while (i < validos)
    {
        menor = i;
        for (int j=i+1; j < validos; j++)
        {
            if (A[menor].habitacionReserva.numHabitacion > A[j].habitacionReserva.numHabitacion)
            {

                menor = j;
            }
        }
        aux = A[i];
        A[i] = A[menor];
        A[menor] = aux;
        i++;
    }
}

void array_A_archivo(char archivo[],stReserva A[],int val)///Pasa un archivo a un arreglo.
{
    FILE *archi = fopen(archivo,"wb");
    stReserva aux;
    if(archi!=NULL)
    {
        for(int i=0; i<val; i++)
        {
            aux = A[i];
            fwrite(&aux,sizeof(stReserva),1,archi);
        }
        fclose(archi);
    }
}

int archivo_A_array(char archivo[],stReserva A[])///Ordena las habitaciones por el tipo.
{
    FILE *archi = fopen(archivo,"rb");
    stReserva aux;
    int i=0;
    if(archi!=NULL)
    {
        while(fread(&aux,sizeof(stReserva),1,archi)>0)
        {
            A[i]=aux;
            i++;
        }
        fclose(archi);
    }
    return i;
}

void ordenarPorHabitacion(char archivo[])///Busca a una persona determinada dentro de archivo "Reserva.bin".
{
    stReserva A[100];
    int val = archivo_A_array(archivo,A);
    ordenarArray(A,val);
    array_A_archivo(archivo,A,val);
}

int verificacionHuesped(char archivo[],int numHab,int huesped)///Modifica a una persona en una reseva determinada.
{
    int pos = busquedaHabitacionposicion(archivo,numHab);
    FILE *archi = fopen(archivo,"rb");
    int flag = 0;
    stReserva A;
    if(archi!=NULL)
    {
        fseek(archi,sizeof(stReserva)*(pos-1),0);
        fread(&A,sizeof(stReserva),1,archi);
        if(huesped<=0 || huesped>A.cantidadPersonas)
            flag = 1;
        else
            flag=0;
        fclose(archi);
    }
    return flag;
}

void modificarNombreHuesped(char archivo[],int numHab,int huesped)///Posicion de la Habitacion en el archivo "Reserva.bin".
{
    int i = (huesped - 1);
    int pos = busquedaHabitacionposicion(archivo,numHab);
    FILE *archi = fopen(archivo,"r+b");
    stReserva A;
    if(archi!=NULL)
    {
        fseek(archi,sizeof(stReserva)*(pos-1),SEEK_SET);
        fread(&A,sizeof(stReserva),1,archi);

        gotoxy(68,8);
        printf("Ingrese nuevo Nombre y Apellido: ");
        fflush(stdin);
        gets(A.clienteReserva[i].nombre);

        fseek(archi,sizeof(stReserva)*(pos-1),SEEK_SET);
        fwrite(&A,sizeof(stReserva),1,archi);
    }
    fclose(archi);
}

int busquedaHabitacionposicion(char archivo[],int numHab) //Posicion de la Habitacion en el archivo Reserva
{
    stReserva A;
    int pos,i=1,flag=0;
    FILE *archi = fopen(archivo,"rb");
    if(archi!=NULL)
    {
        while((fread(&A,sizeof(stReserva),1,archi)>0) && flag ==0)
        {
            if(A.habitacionReserva.numHabitacion==numHab)
            {
                pos  = i;
                flag = 1;
            }
            i++;
        }
        fclose(archi);
    }
    return pos;
}

void modificarEdadHuesped(char archivo[],int numHab,int huesped)///Modifica la edad de una persona en una reserva determinada.
{
    int i = (huesped - 1);
    int pos = busquedaHabitacionposicion(archivo,numHab);
    FILE *archi = fopen(archivo,"r+b");
    stReserva A;
    if(archi!=NULL)
    {
        fseek(archi,sizeof(stReserva)*(pos-1),SEEK_SET);
        fread(&A,sizeof(stReserva),1,archi);

        gotoxy(68,8);
        printf("Ingrese nueva Edad: ");
        scanf("%d",&A.clienteReserva[i].edad);

        fseek(archi,sizeof(stReserva)*(pos-1),SEEK_SET);
        fwrite(&A,sizeof(stReserva),1,archi);
    }
    fclose(archi);
}

void modificarDocumento(char archivo[],int numHab,int huesped)///Modifica el documento de una persona dentro de una reserva determinada.
{
    int i = (huesped - 1);
    int pos = busquedaHabitacionposicion(archivo,numHab);
    FILE *archi = fopen(archivo,"r+b");
    stReserva A;
    if(archi!=NULL)
    {
        fseek(archi,sizeof(stReserva)*(pos-1),SEEK_SET);
        fread(&A,sizeof(stReserva),1,archi);

        gotoxy(68,8);
        printf("Ingrese nuevo DNI: ");
        scanf("%d",&A.clienteReserva[i].dni);

        fseek(archi,sizeof(stReserva)*(pos-1),SEEK_SET);
        fwrite(&A,sizeof(stReserva),1,archi);
    }
    fclose(archi);
}

void modificarGymSpa(char archivo[],int numHab)///Modifica los servicios (agrega o cancela los servicios de SPA/GYM).
{
    int pos = busquedaHabitacionposicion(archivo,numHab);
    FILE *archi = fopen(archivo,"r+b");
    float total;
    stReserva A;
    char a,b;
    if(archi!=NULL)
    {
        fseek(archi,sizeof(stReserva)*(pos-1),0);
        fread(&A,sizeof(stReserva),1,archi);

        gotoxy(68,8);
        printf("- Desea el servicio del Gym (s/n): ");
        fflush(stdin);
        scanf("%c",&a);
        validacion(&a,68,9);
        gotoxy(68,10);
        printf("- Desea el servicio del Spa (s/n): ");
        fflush(stdin);
        scanf("%c",&b);
        validacion(&b,68,11);

        A.serviciosReserva.servicio=valorDeServicios(a,b);
        float total = precioTotal(A,A.habitacionReserva.precioHabitacion);
        A.precioTotal = tipoDePago(A.pagoReserva.tipoPago,total,A.pagoReserva.cuotas);

        fseek(archi,sizeof(stReserva)*(pos-1),0);
        fwrite(&A,sizeof(stReserva),1,archi);

        fclose(archi);
    }
}

void modificarPension(char archivo[],int numHab)///Modifica la pension de la comida.
{
    int pos = busquedaHabitacionposicion(archivo,numHab);
    float total;
    stReserva A;
    char pension[30];

    FILE *archi = fopen(archivo,"r+b");
    if(archi!=NULL)
    {
        fseek(archi,sizeof(stReserva)*(pos-1),0);
        fread(&A,sizeof(stReserva),1,archi);
        gotoxy(68,8);
        printf("Elija Tipo de Pension (Media / Completa): ");
        fflush(stdin);
        scanf("%s",&pension);
        while(strcmpi(pension,"Media")!=0 && strcmpi(pension,"Completa")!=0 )
        {
            gotoxy(68,9);
            printf("No existe. Ingrese nuevamente (Media / Completa): ");
            fflush(stdin);
            scanf("%s",&pension);
        }

        A.serviciosReserva.pensionComida = valorPension(pension);
        float total = precioTotal(A,A.habitacionReserva.precioHabitacion);
        A.precioTotal = tipoDePago(A.pagoReserva.tipoPago,total,A.pagoReserva.cuotas);

        fseek(archi,sizeof(stReserva)*(pos-1),0);
        fwrite(&A,sizeof(stReserva),1,archi);
        fclose(archi);
    }

}

void modificarEstacionamiento(char archivo[],int numHab)///Modifica el estacionamiento.
{
    int pos = busquedaHabitacionposicion(archivo,numHab);
    FILE *archi = fopen(archivo,"r+b");
    float total;
    stReserva A;
    char a;
    if(archi!=NULL)
    {
        fseek(archi,sizeof(stReserva)*(pos-1),0);
        fread(&A,sizeof(stReserva),1,archi);
        gotoxy(68,8);
        printf("Desea el Estacionamiento? (s/n): ");
        fflush(stdin);
        scanf("%c",&a);
        validacion(&a,68,9);

        A.serviciosReserva.estacionamiento = valorEstacionamiento(a,A);
        float total = precioTotal(A,A.habitacionReserva.precioHabitacion);
        A.precioTotal = tipoDePago(A.pagoReserva.tipoPago,total,A.pagoReserva.cuotas);

        fseek(archi,sizeof(stReserva)*(pos-1),0);
        fwrite(&A,sizeof(stReserva),1,archi);
        fclose(archi);
    }
}

void modificarHabitacion(char archivo[],int numHab,int control) ///Modifica el tipo y/o numero de la habitacion de una reserva determinada.
{
    int pos = busquedaHabitacionposicion(archivo,numHab);
    stReserva A;
    FILE *archi=fopen(archivo,"r+b");
    if(archi!=NULL)
    {
        fseek(archi,sizeof(stReserva)*(pos-1),0);
        fread(&A,sizeof(stReserva),1,archi);
        int aux;

        A = tipodeHab_paramodificar(A,control);
        A.habitacionReserva.numHabitacion=control;
        A.habitacionReserva.precioHabitacion = cargarTipoDeHabitacion(A,&aux);
        modificarDisponibilidad("Habitaciones.bin",control);
        modificarDisponibilidad("Habitaciones.bin",numHab);
        float total = precioTotal(A,A.habitacionReserva.precioHabitacion);
        A.precioTotal = tipoDePago(A.pagoReserva.tipoPago,total,A.pagoReserva.cuotas);


        fseek(archi,sizeof(stReserva)*(pos-1),0);
        fwrite(&A,sizeof(stReserva),1,archi);

        fclose(archi);
    }
}

stReserva tipodeHab_paramodificar(stReserva A,int control)///Verifica el tipo de habitacion para modificar.
{
    if(control<=43 && control%2==1)
    {
        strcpy(A.habitacionReserva.tipoHabitacion,"Doble");
    }
    else if(control<=44 && control%2==0)
    {
        strcpy(A.habitacionReserva.tipoHabitacion,"Triple");
    }
    else if(control>=45 && control<=49)
    {
        strcpy(A.habitacionReserva.tipoHabitacion,"Cuadruple");
    }
    else if(control>=50 && control<=55)
    {
        strcpy(A.habitacionReserva.tipoHabitacion,"Suite");
    }
    return A;
}

void condicionesDeMuestra(char archivo[], int numHab)///Muestra las habitaciones a las que puede cambiar el usuario.
{
    int pos = busquedaHabitacionposicion(archivo,numHab);
    stReserva A;
    FILE *archi=fopen(archivo,"rb");
    if(archi!=NULL)
    {
        fseek(archi,sizeof(stReserva)*(pos-1),0);
        fread(&A,sizeof(stReserva),1,archi);
        if(A.cantidadPersonas>=5)
        {
            printf("\nHabitaciones Suites Disponibles: \n");
            mostrarSuitesDisponibles("Habitaciones.bin");
        }
        else if(A.cantidadPersonas==4)
        {
            printf("\nHabitaciones Cuadruples Disponibles: \n");
            mostrarCuadruplesDisponibles("Habitaciones.bin");
            printf("\n\nHabitaciones Suites Disponibles:\n");
            mostrarSuitesDisponibles("Habitaciones.bin");
        }
        else if(A.cantidadPersonas==3)
        {
            printf("\nHabitaciones Triples Disponibles: \n");
            mostrarTriplesDisponibles("Habitaciones.bin");
            printf("\n\nHabitaciones Cuadruples Disponibles: \n");
            mostrarCuadruplesDisponibles("Habitaciones.bin");
            printf("\n\nHabitaciones Suites Disponibles: \n");
            mostrarSuitesDisponibles("Habitaciones.bin");
        }
        else if(A.cantidadPersonas<3)
        {
            mostrarDisponibles("Habitaciones.bin");
        }
        fclose(archi);
    }
}

int condicionControl(char archivo[],int numHab,int control)///Limita el tipo de habitaciones que puede seleccionar alguien que quiere cambiar de numero.
{
    stReserva A;
    stHabitacion room;
    int posR = busquedaHabitacionposicion(archivo,numHab);
    int posH = busquedaPosicionHab("Habitaciones.bin",control);
    int flag = 0;

    FILE *archiR = fopen(archivo,"rb");
    FILE *archiH = fopen("Habitaciones.bin","rb");
    if(archiR!= NULL && archiH!=NULL)
    {
        fseek(archiR,sizeof(stReserva)*(posR-1),0);
        fseek(archiH,sizeof(stHabitacion)*(posH-1),0);

        fread(&A,sizeof(stReserva),1,archiR);
        fread(&room,sizeof(stHabitacion),1,archiH);

        gotoxy(60,25);
        if(A.cantidadPersonas<=2 && (room.disponibilidad=='s'||room.disponibilidad=='S'))
        {
            flag = 1;
        }
        else if(A.cantidadPersonas<=2 && (room.disponibilidad=='n'||room.disponibilidad=='N'))
        {
            flag = 0;
        }

        if(A.cantidadPersonas ==3 && (room.disponibilidad=='s'||room.disponibilidad=='S') && ((room.numHabitacion<=44 && room.numHabitacion%2==0)||(room.numHabitacion>=45 && room.numHabitacion<=49) || (room.numHabitacion>=50 && room.numHabitacion<=55)))
        {
            flag = 1;
        }
        else if(A.cantidadPersonas==3 && (room.disponibilidad=='n'||room.disponibilidad=='N') && ((room.numHabitacion<=44 && room.numHabitacion%2==0)||(room.numHabitacion>=45 && room.numHabitacion<=49) || (room.numHabitacion>=50 && room.numHabitacion<=55)))
        {
            flag = 0;
        }

        if(A.cantidadPersonas==4 && (room.disponibilidad=='s'||room.disponibilidad=='S') && (room.numHabitacion>=45 && room.numHabitacion<=55))
        {
            flag = 1;
        }
        else if(A.cantidadPersonas==4 && (room.disponibilidad=='n'||room.disponibilidad=='N') && (room.numHabitacion>=45 && room.numHabitacion<=55))
        {
            flag = 0;
        }

        if(A.cantidadPersonas>=5 && (room.disponibilidad=='s'||room.disponibilidad=='S') && (room.numHabitacion>=50 && room.numHabitacion<=55))
        {
            flag = 1;
        }
        else if(A.cantidadPersonas>=5 && (room.disponibilidad=='n'||room.disponibilidad=='N') && (room.numHabitacion>=50 && room.numHabitacion<=55))
        {
            flag = 0;
        }

        fclose(archiR);
        fclose(archiH);
    }
    return flag;
}

void modificarNoches(char archivo[],int numHab) ///Modifica la cantidad de Noches
{
    int pos = busquedaHabitacionposicion(archivo,numHab);
    stReserva A;
    FILE *archi = fopen(archivo,"r+b");
    if(archi!=NULL)
    {
        fseek(archi,sizeof(stReserva)*(pos-1),0);
        fread(&A,sizeof(stReserva),1,archi);

        gotoxy(68,8);
        printf("Ingrese nueva cantidad de noches: ");
        scanf("%d",&A.cantNoches);
        float total = precioTotal(A,A.habitacionReserva.precioHabitacion);
        A.precioTotal = tipoDePago(A.pagoReserva.tipoPago,total,A.pagoReserva.cuotas);
        fseek(archi,sizeof(stReserva)*(pos-1),0);
        fwrite(&A,sizeof(stReserva),1,archi);

        fclose(archi);
    }
}

