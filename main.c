#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "Hotel.h"

int main()
{
    FILE *archi=fopen("Habitaciones.bin","rb");
    if(archi==NULL)
        cargarArchivoHabitaciones("Habitaciones.bin");
    fclose(archi);
    menu();
    return 0;
}

void menu() ///Muestra el menu
{

    int op,op2,op3,op4,op2a,op2a1,op2a2,control;
    int flag,cant,habit,huesped,bDNI,bNumHab,estado,c2;
    char bNombre[30], bTipoHab[30],seguro;
    stReserva reserva;
    do
    {
        system("cls");
        gotoxy(50,2);
        printf("HOTEL YAPEYU");
        gotoxy(50,4);
        printf("ADMINISTRADOR");
        gotoxy(8,6);
        printf("1 - Ingresar una Nueva Reserva");
        gotoxy(8,8);
        printf("2 - Ver Reservas y Modificar");
        gotoxy(8,10);
        printf("3 - Ver Habitaciones Disponibles");
        gotoxy(8,12);
        printf("4 - Consulta de Reserva");
        gotoxy(8,14);
        printf("5 - Cancelar Reserva");
        gotoxy(8,16);
        printf("0 - Salir");
        gotoxy(8,20);
        printf("Ingrese una opcion: ");
        scanf("%d",&op);
        switch(op)
        {
        ///------------------------1) CARGAR RESERVA----------------------------///
        case 1:
            system("cls");
            gotoxy(50,2);
            printf("HOTEL YAPEYU");
            gotoxy(44,4);
            printf("ADMINISTRADOR - RESERVA");
            cargarReserva("Reservas.bin");
            printf("\n");
            system("PAUSE");
            break;

        ///----------------------2) VER Y MODIFICAR RESERVAS--------------------------///
        case 2:
            do
            {
                cant = cantidadRegistros("Reservas.bin");
                system("cls");
                gotoxy(50,2);
                printf("HOTEL YAPEYU");
                gotoxy(68,6);
                printf("Cantidad de Reservas registradas: %d",cant);
                printf("\n");
                gotoxy(45,4);
                printf("Historial de Reservas");
                printf("\n");
                mostrarArchivo("Reservas.bin");
                gotoxy(68,8);
                printf("1 - Ordenar por numero de Habitacion");
                gotoxy(68,10);
                printf("2 - Modificar Reserva");
                gotoxy(68,12);
                printf("0 - Regresar");
                gotoxy(68,14);
                printf("Ingrese una opcion: ");
                fflush(stdin);
                scanf("%d",&op2);
                switch(op2)
                {
                ///----------------2)1.Ordenar---------------///
                case 1:
                    ordenarPorHabitacion("Reservas.bin");
                    break;
                ///----------------2)2.Modificar-------------///
                case 2:
                    system("cls");
                    gotoxy(50,2);
                    printf("HOTEL YAPEYU");
                    gotoxy(68,6);
                    printf("Cantidad de Reservas registradas: %d",cant);
                    printf("\n");
                    gotoxy(45,4);
                    printf("Historial de Reservas");
                    printf("\n");
                    mostrarArchivo("Reservas.bin");

                    gotoxy(68,8);
                    printf("Ingrese numero de habitacion de la reserva a modificar: ");
                    scanf("%d",&habit);

                    system("cls");
                    gotoxy(50,2);
                    printf("HOTEL YAPEYU");
                    gotoxy(68,6);
                    printf("Cantidad de Reservas registradas: %d",cant);
                    flag = busquedaPorHabitacion("Reservas.bin",habit);
                    while(flag !=1)
                    {
                        gotoxy(68,8);
                        printf("Habitaciones Ocupadas: ");
                        gotoxy(68,10);
                        mostrarOcupadas("Habitaciones.bin");
                        gotoxy(68,12);
                        printf("La habitacion no se encuentra cargada...Ingrese otra habitacion: ");
                        scanf("%d",&habit);
                        flag = busquedaPorHabitacion("Reservas.bin",habit);
                    }

                    do
                    {
                        system("cls");
                        gotoxy(50,2);
                        printf("HOTEL YAPEYU");
                        gotoxy(45,4);
                        printf("Modificar Reserva Habitacion %d\n",habit);
                        flag = busquedaPorHabitacion("Reservas.bin",habit);
                        gotoxy(68,6);
                        printf("Cantidad de Reservas registradas: %d",cant);
                        gotoxy(68,8);
                        printf("1 - Modificar Huespedes");
                        gotoxy(68,10);
                        printf("2 - Modificar Servicios");
                        gotoxy(68,12);
                        printf("3 - Modificar Numero y/o Tipo de Habitacion");
                        gotoxy(68,14);
                        printf("4 - Modificar Cantidad de Noches");
                        gotoxy(68,16);
                        printf("0 - Regresar");
                        gotoxy(68,18);
                        printf("Ingrese una opcion: ");
                        scanf("%d",&op2a);
                        switch(op2a)
                        {
                        ///--------------2)2.[1]Modificar Huesped-----------------///
                        case 1:
                            system("cls");
                            gotoxy(50,2);
                            printf("HOTEL YAPEYU");
                            gotoxy(40,4);
                            printf("Modificando Reserva Habitacion %d\n",habit);
                            flag = busquedaPorHabitacion("Reservas.bin",habit);
                            gotoxy(68,6);
                            printf("Ingrese huesped a modificar: ");
                            scanf("%d",&huesped);
                            int flag = verificacionHuesped("Reservas.bin",habit,huesped);
                            while(flag==1)
                            {
                                gotoxy(68,7);
                                printf("ERROR, ingrese nuevamente el huesped a modificar: ");
                                scanf("%d",&huesped);
                                flag = verificacionHuesped("Reservas.bin",habit,huesped);
                            }
                            do
                            {
                                system("cls");
                                gotoxy(50,2);
                                printf("HOTEL YAPEYU");
                                gotoxy(36,4);
                                printf("Modificando Huesped %d de la Habitacion %d\n",huesped,habit);
                                flag = busquedaPorHabitacion("Reservas.bin",habit);
                                gotoxy(68,6);
                                printf("Que desea modificar del huesped %d?",huesped);
                                gotoxy(68,8);
                                printf("1 - Nombre y Apellido");
                                gotoxy(68,10);
                                printf("2 - Edad");
                                gotoxy(68,12);
                                printf("3 - Documento");
                                gotoxy(68,14);
                                printf("0 - Regresar...");
                                gotoxy(68,16);
                                printf("Ingrese una opcion: ");
                                fflush(stdin);
                                scanf("%d",&op2a1);
                                switch(op2a1)
                                {
                                ///--------------2)2.[1,1]Modificar Nombre-----------------///
                                case 1:
                                    system("cls");
                                    gotoxy(50,2);
                                    printf("HOTEL YAPEYU");
                                    gotoxy(32,4);
                                    printf("Modificando Nombre y Apellido del Huesped %d de la Habitacion %d\n",huesped,habit);
                                    flag = busquedaPorHabitacion("Reservas.bin",habit);
                                    modificarNombreHuesped("Reservas.bin",habit,huesped);
                                    break;

                                ///--------------2)2.[1,2]Modificar Edad-----------------///
                                case 2:
                                    system("cls");
                                    gotoxy(50,2);
                                    printf("HOTEL YAPEYU");
                                    gotoxy(35,4);
                                    printf("Modificando Edad del Huesped %d de la Habitacion %d\n",huesped,habit);
                                    flag = busquedaPorHabitacion("Reservas.bin",habit);
                                    modificarEdadHuesped("Reservas.bin",habit,huesped);
                                    break;

                                ///--------------2)2.[1,3]Modificar DNI-----------------///
                                case 3:
                                    system("cls");
                                    gotoxy(50,2);
                                    printf("HOTEL YAPEYU");
                                    gotoxy(34,4);
                                    printf("Modificando Documento del Huesped %d de la Habitacion %d\n",huesped,habit);
                                    flag = busquedaPorHabitacion("Reservas.bin",habit);
                                    modificarDocumento("Reservas.bin",habit,huesped);
                                    break;
                                ///--------------2)2.[1,0]REGRESAR-----------------///
                                case 0:
                                    break;
                                default:
                                    gotoxy(68,16);
                                    printf("La opcion ingresada no existe...");
                                    gotoxy(68,20);
                                    system("PAUSE");
                                    break;
                                }
                            }
                            while(op2a1!=0);
                            break;
                        ///-----------2)2.[2]Modificar Servicios--------------///
                        case 2:
                            do
                            {
                                system("cls");
                                gotoxy(50,2);
                                printf("HOTEL YAPEYU");
                                gotoxy(35,4);
                                printf("Modificar Servicios de la Reserva Habitacion %d\n",habit);
                                flag = busquedaPorHabitacion("Reservas.bin",habit);
                                gotoxy(68,6);
                                printf("Que servicio desea modificar?");
                                gotoxy(68,8);
                                printf("1 - Gym y Spa");
                                gotoxy(68,10);
                                printf("2 - Pension");
                                gotoxy(68,12);
                                printf("3 - Estacionamiento");
                                gotoxy(68,14);
                                printf("0 - Regresar...");
                                gotoxy(68,16);
                                printf("Ingrese una opcion: ");
                                scanf("%d",&op2a2);
                                switch(op2a2)
                                {
                                ///--------------------------2)2.[2,1]Modificar GYM y SPA--------------------///
                                case 1:
                                    system("cls");
                                    gotoxy(50,2);
                                    printf("HOTEL YAPEYU");
                                    gotoxy(35,4);
                                    printf("Modificar Gym y Spa de la Reserva Habitacion %d\n",habit);
                                    flag = busquedaPorHabitacion("Reservas.bin",habit);
                                    modificarGymSpa("Reservas.bin",habit);
                                    break;
                                ///-------------------------2)2.[2,2]Modificar Pension-----------------------///
                                case 2:
                                    system("cls");
                                    gotoxy(50,2);
                                    printf("HOTEL YAPEYU");
                                    gotoxy(35,4);
                                    printf("Modificar Pension de la Reserva Habitacion %d\n",habit);
                                    flag = busquedaPorHabitacion("Reservas.bin",habit);
                                    modificarPension("Reservas.bin",habit);
                                    break;
                                ///------------------------2)2.[2,3]Modificar Estacionamiento----------------///
                                case 3:
                                    system("cls");
                                    gotoxy(50,2);
                                    printf("HOTEL YAPEYU");
                                    gotoxy(35,4);
                                    printf("Modificar Estacionamiento de la Reserva Habitacion %d\n",habit);
                                    flag = busquedaPorHabitacion("Reservas.bin",habit);
                                    modificarEstacionamiento("Reservas.bin",habit);
                                    break;
                                ///-----------------------2)2.[2,0]Regresar----------------------------------///
                                case 0:
                                    break;
                                default:
                                    gotoxy(68,17);
                                    printf("La opcion Ingresada no existe...");
                                    gotoxy(68,20);
                                    system("PAUSE");
                                    break;
                                }
                            }
                            while(op2a2!=0);
                            break;


                        ///--------------------2)2.[3]Modificar Numero y Tipo de Habitacion------------------///
                        case 3:
                            system("cls");
                            gotoxy(50,2);
                            printf("HOTEL YAPEYU");
                            gotoxy(30,4);
                            printf("Modificar Numero y Tipo de Habitacion de la Reserva Habitacion %d\n\n",habit);
                            condicionesDeMuestra("Reservas.bin",habit);
                            gotoxy(50,8);
                            printf("Habitacion Actual: %d",habit);
                            gotoxy(50,10);
                            printf("Desea cambiar de habitacion? (s/n): ");
                            fflush(stdin);
                            scanf("%c",&seguro);
                            if(seguro=='s' || seguro=='S')
                            {
                                gotoxy(50,12);
                                printf("Ingrese una Habitacion Disponible a cambiar: ");
                                scanf("%d",&control);

                                while(control<=0 && control>55)
                                {
                                    gotoxy(50,14);
                                    printf("Error, la habitacion no existe... Ingrese nuevamente: ");
                                    scanf("%d",&control);
                                }
                                c2 = condicionControl("Reservas.bin",habit,control);

                                while(c2!=1)
                                {
                                    gotoxy(50,14);
                                    printf("Habitacion no disponible o sobrepada el limite de personas permitido. Ingrese nuevamente: ");
                                    scanf("%d",&control);
                                    c2 = condicionControl("Reservas.bin",habit,control);
                                }
                                modificarHabitacion("Reservas.bin",habit,control);
                                op2a=0;
                            }

                            break;
                        case 4:
                                system("cls");
                                gotoxy(50,2);
                                printf("HOTEL YAPEYU");
                                gotoxy(36,4);
                                printf("Modificando Cantidad de Noches de la Habitacion %d\n",huesped,habit);
                                flag = busquedaPorHabitacion("Reservas.bin",habit);
                                modificarNoches("Reservas.bin",habit);
                            break;
                        case 0:
                            break;
                        default:
                            gotoxy(68,20);
                            printf("La opcion Ingresada no existe...");
                            gotoxy(68,22);
                            system("PAUSE");
                            break;
                        }
                    }
                    while(op2a!=0);

                ///----------2)2.[3,0]Regresar--------------///
                case 0:
                    break;
                }
            }
            while(op2!=0);
            break;

        ///--------------------3) MOSTRAR HABITACIONES DISPONIBLES----------------------------------///

        case 3:
            do
            {
                system("cls");
                gotoxy(50,2);
                printf("HOTEL YAPEYU");
                gotoxy(44,4);
                printf("Habitaciones Disponibles");
                gotoxy(8,6);
                printf("1 - Mostrar todas las Habitaciones disponibles");
                gotoxy(8,8);
                printf("2 - Mostrar solo Dobles disponibles");
                gotoxy(8,10);
                printf("3 - Mostrar solo Triples disponibles");
                gotoxy(8,12);
                printf("4 - Mostrar solo Cuadruples disponibles");
                gotoxy(8,14);
                printf("5 - Mostrar solo Suites disponibles");
                gotoxy(8,16);
                printf("0 - Regresar...");
                gotoxy(8,18);
                printf("Elige una opcion: ");
                scanf("%d",&op3);
                switch(op3)
                {
                ///-------------3)1.VER TODAS LAS HABITACIONES DISPONIBLES------------------------------///
                case 1:
                    system("cls");
                    gotoxy(50,2);
                    printf("HOTEL YAPEYU");
                    gotoxy(44,4);
                    printf("Habitaciones Disponibles");
                    printf("\n");
                    mostrarDisponibles("Habitaciones.bin");
                    printf("\n\n");
                    system("PAUSE");
                    break;
                ///-------------3)2.VER TODAS LAS HABITACIONES DISPONIBLES DOBLES------------------------------///
                case 2:
                    system("cls");
                    gotoxy(50,2);
                    printf("HOTEL YAPEYU");
                    gotoxy(40,4);
                    printf("Habitaciones Dobles Disponibles");
                    printf("\n");
                    printf("Habitaciones Dobles:\n\n");
                    mostrarDoblesDisponibles("Habitaciones.bin");
                    printf("\n\n");
                    system("PAUSE");
                    break;
                ///-------------3)3.VER TODAS LAS HABITACIONES DISPONIBLES TRIPLES-----------------------------///
                case 3:
                    system("cls");
                    gotoxy(50,2);
                    printf("HOTEL YAPEYU");
                    gotoxy(40,4);
                    printf("Habitaciones Triples Disponibles");
                    printf("\n");
                    printf("\n\nHabitaciones Triples: \n\n");
                    mostrarTriplesDisponibles("Habitaciones.bin");
                    printf("\n\n");
                    system("PAUSE");
                    break;
                ///-------------3)4.VER TODAS LAS HABITACIONES DISPONIBLES CUADRUPLES----------------------///
                case 4:
                    system("cls");
                    gotoxy(50,2);
                    printf("HOTEL YAPEYU");
                    gotoxy(40,4);
                    printf("Habitaciones Cuadruples Disponibles");
                    printf("\n");
                    printf("\n\nHabitaciones Cuadruples: \n\n");
                    mostrarCuadruplesDisponibles("Habitaciones.bin");
                    printf("\n\n");
                    system("PAUSE");
                    break;
                ///-------------3)5.VER TODAS LAS HABITACIONES DISPONIBLES SUITES-----------------------------///
                case 5:
                    system("cls");
                    gotoxy(50,2);
                    printf("HOTEL YAPEYU");
                    gotoxy(40,4);
                    printf("Habitaciones Suites Disponibles");
                    printf("\n");
                    printf("\n\nHabitaciones Suites: \n\n");
                    mostrarSuitesDisponibles("Habitaciones.bin");
                    printf("\n\n");
                    system("PAUSE");
                    break;
                ///-------------------------3)0-REGRESAR-----------------------------------------///
                case 0:
                    break;
                default:
                    printf("\nLa opcion ingresada no existe...");
                    printf("\n\n");
                    system("PAUSE");
                    break;
                }
            }
            while(op3!=0);
            break;

        ///-------------------4) CONSULTAR RESERVA-----------------------------------///

        case 4:
            do
            {
                system("cls");
                gotoxy(50,2);
                printf("HOTEL YAPEYU");
                gotoxy(46,4);
                printf("Opciones de Busqueda");
                gotoxy(8,6);
                printf("1 - Busqueda por DNI");
                gotoxy(8,8);
                printf("2 - Busqueda por Nombre");
                gotoxy(8,10);
                printf("3 - Busqueda por Habitacion");
                gotoxy(8,12);
                printf("4 - Busqueda por Tipo de Habitacion");
                gotoxy(8,14);
                printf("0 - Regresar...");
                gotoxy(8,16);
                printf("Ingrese una opcion: ");
                scanf("%d",&op4);
                switch(op4)
                {
                ///--------------------------4)1.BUSCAR POR DNI--------------------///
                case 1:
                    system("cls");
                    gotoxy(50,2);
                    printf("HOTEL YAPEYU");
                    gotoxy(46,4);
                    printf("Busqueda por DNI");
                    gotoxy(8,6);
                    printf("Ingrese DNI a buscar: ");
                    scanf("%d",&bDNI);
                    flag = busquedaPorDNI("Reservas.bin",bDNI);
                    if(flag !=1)
                    {
                        gotoxy(8,8);
                        printf("El DNI buscado no se encuentra registrado en una reserva...");
                    }
                    printf("\n\n");
                    system("PAUSE");
                    break;
                ///--------------------------4)2.BUSCAR POR NOMBRE--------------------///
                case 2:
                    system("cls");
                    gotoxy(50,2);
                    printf("HOTEL YAPEYU");
                    gotoxy(46,4);
                    printf("Busqueda por Nombre");
                    gotoxy(8,6);
                    printf("Ingrese Nombre y Apellido a buscar: ");
                    fflush(stdin);
                    gets(bNombre);
                    flag = busquedaPorNombre("Reservas.bin",bNombre);
                    if(flag !=1)
                    {
                        gotoxy(8,8);
                        printf("El Nombre y Apellido buscado no se encuentra registrado en una reserva...");
                    }
                    printf("\n\n");
                    system("PAUSE");
                    break;
                ///--------------------------4)3.BUSCAR POR NUMERO--------------------///
                case 3:
                    system("cls");
                    gotoxy(50,2);
                    printf("HOTEL YAPEYU");
                    gotoxy(40,4);
                    printf("Busqueda por Numero de Habitacion");
                    gotoxy(8,6);
                    printf("Ingrese numero de habitacion a buscar: ");
                    scanf("%d",&bNumHab);
                    flag = busquedaPorHabitacion("Reservas.bin",bNumHab);
                    if(flag !=1)
                    {
                        gotoxy(8,8);
                        printf("El numero de Habitacion no se encuentra registrada en una reserva...");
                    }
                    printf("\n\n");
                    system("PAUSE");
                    break;
                ///--------------------------4)4.BUSCAR POR TIPO----------------------///
                case 4:
                    system("cls");
                    gotoxy(50,2);
                    printf("HOTEL YAPEYU");
                    gotoxy(40,4);
                    printf("Busqueda por Tipo de Habitacion");
                    gotoxy(8,6);
                    printf("Ingrese tipo de habitacion a buscar: ");
                    fflush(stdin);
                    gets(bTipoHab);
                    flag = busquedaPorTipoHabitacion("Reservas.bin",bTipoHab);
                    if(flag !=1)
                    {
                        gotoxy(8,8);
                        printf("El tipo de Habitacion no se encuentra registrada en una reserva...");
                    }

                    printf("\n\n");
                    system("PAUSE");
                    break;
                ///---------------------------4)0.REGRESAR-----------------------------///
                case 0:
                    break;
                default:
                    printf("La opcion ingresada no existe...");
                    system("PAUSE");
                    break;
                }
            }
            while(op4!=0);
            break;

        ///---------------------5) CANCELAR RESERVA---------------------------------///

        case 5:
            system("cls");
            gotoxy(50,2);
            printf("HOTEL YAPEYU");
            gotoxy(47,4);
            printf("Cancelar Reserva");
            printf("\n\nHabitaciones Ocupadas: \n\n");
            mostrarOcupadas("Habitaciones.bin");
            gotoxy(8,9);
            printf("\nIngrese el numero de habitacion: ");
            scanf("%d", &bNumHab);
            flag = busquedaPorHabitacion("Reservas.bin",bNumHab);
            if(flag !=1)
            {
                gotoxy(8,10);
                printf("\nEl numero de Habitacion no se encuentra registrada en una reserva...");
            }
            else
            {
                printf("\nSeguro desea cancelar la reserva? Presione 's' o 'n': ");
                fflush(stdin);
                scanf("%c",&seguro);
            }

            if(seguro=='s'||seguro=='S')
            {
                borrarRegistro(bNumHab);
                printf("\nReserva cancelada exitosamente!");
            }
            else if(seguro=='n'||seguro=='N')
            {
                printf("\nUsted ha decidido no cancelar la reserva...");
            }
            getch();
            break;
        case 0:
            break;
        default:
            gotoxy(8,22);
            printf("La opcion no existe...");
            gotoxy(8,24);
            system("PAUSE");
            break;
        }
    }
    while(op!=0);
}

