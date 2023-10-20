#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define Columnas 15
void limpiarBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

struct Alq_venta
{
    int Id;
    char FechaIngreso[70];
    // Ingreso por teclado de aca para abajo
    char Zona[30];
    char Ciudad_Barrio[30];
    int Dormitorios;
    int Banos;
    float SuperficieTotal;
    float SuperficieCubierta;
    float Precio;
    char TipMoneda[10];
    char TipPropiedad[12];
    char Operacion[30];
    char FechaSalida[70];
    int Activos;
};

void GeneradorDeAlq(struct Alq_venta Datos[])
{
    printf("----------Entrada de datos----------\n");
    printf("Zona en donde se encuentra la residencia : ");
    scanf("%[^\n]", Datos->Zona);
    limpiarBuffer();

    printf("Ciudad o Barrio de la residencia : ");
    scanf("%[^\n]", Datos->Ciudad_Barrio);
    limpiarBuffer();

    printf("Cantidad de Dormitorios : ");
    scanf("%d", &Datos->Dormitorios);
    limpiarBuffer();

    printf("Cantidad de Banos : ");
    scanf("%d", &Datos->Banos);
    limpiarBuffer();

    printf("Superficie Total de la vivienda : ");
    scanf("%f", &Datos->SuperficieTotal);
    limpiarBuffer();

    printf("Superficie Cubierta de la vivienda : ");
    scanf("%f", &Datos->SuperficieCubierta);
    limpiarBuffer();

    printf("Precio : ");
    scanf("%f", &Datos->Precio);
    limpiarBuffer();

    printf("Tipo de Moneda : ");
    scanf("%[^\n]", Datos->TipMoneda);
    limpiarBuffer();

    printf("Tipo de Propiedad : ");
    scanf("%[^\n]", Datos->TipPropiedad);
    limpiarBuffer();

    printf("Que Operaciones va a realizar con la vivienda: ");
    scanf("%[^\n]", Datos->Operacion);
    limpiarBuffer();

    printf("Fecha de Salida: ");
    scanf("%[^\n]", Datos->FechaSalida);
    limpiarBuffer();

    printf("Activos : ");
    scanf("%d", &Datos->Activos);
    limpiarBuffer();
}

void errorMenu()
{
    printf("Ingrese una opcion valida");
}

int Menu()
{
    int opcion;
    printf("----------Menu----------\n");       // Cada funcion del menu invoca una funcion especifica o submenu
    printf("1 - Crear archivo de propiedades"); // Crea el archivo de propiedades.bin
    printf("2 - ");
    printf("3 - ");
    printf("4 - ");
    printf("5 - ");
    printf("6 - ");
    printf("7 - ");
    printf("8 - ");
    scanf("%i", &opcion);
    return opcion;
}

void Impresion(struct Alq_venta Datos[])
{
    printf("----------Salida de datos----------\n");
    printf("Fecha de Entrada:%s\n", Datos->FechaIngreso);

    printf("Zona : %s \n", Datos->Zona);
    printf("Ciudad o Barrio de la residencia : %s \n", Datos->Ciudad_Barrio);

    printf("Dormitorios : %d\n", Datos->Dormitorios);
    printf("Cantidad de Banos : %d\n", Datos->Banos);

    printf("Superficie Total de la vivienda : %.2f\n", Datos->SuperficieTotal);

    printf("Superficie Cubierta de la vivienda : %.2f\n", Datos->SuperficieCubierta);

    printf("Precio : %.2f\n", Datos->Precio);

    printf("Tipo de Moneda : %s\n", Datos->TipMoneda);

    printf("Tipo de Propiedad :%s \n", Datos->TipPropiedad);

    printf("Operacion: %s\n", Datos->Operacion);

    printf("Fecha de Salida : %s\n", Datos->FechaSalida);

    printf("Activos : %d\n", Datos->Activos);
}

int main()
{
    int opcion;
    FILE *pPropiedades;

    struct Alq_venta Alquiler_Ventas[1];
    // Tiempo Actual
    time_t t = time(NULL);
    struct tm tiempoLocal = *localtime(&t);
    // El formato. Mira más en https://en.cppreference.com/w/c/chrono/strftime
    char *formato = "%Y-%m-%d %H:%M:%S";
    // Intentar formatear
    int bytesEscritos =
        strftime(Alquiler_Ventas[0].FechaIngreso, sizeof Alquiler_Ventas[0].FechaIngreso, formato, &tiempoLocal);
    // Alquiler_Ventas es donde se va a guardar la feche local
    if (bytesEscritos != 0)
    {
        // Si no hay error, los bytesEscritos no son 0
        printf("Fecha y hora: %s \n", Alquiler_Ventas[0].FechaIngreso);
    }
    else
    {
        printf("Error formateando fecha");
    }

    opcion = menu();
    if (opcion > 0)
    {
        switch (opcion)
        {
        case '1':
            // Opcion 1 del menu (Crear)
            // Genera el archivo binario propiedades.dat
            pPropiedades = fopen("propiedades.dat", "wb+");
            if (pPropiedades != NULL)
            {
                printf("Archivo creado con exito");
            }
            else
            {
                printf("Error en la creacion del archivo");
            };
            break;
        case '2':
            // Opcion 2 del menu (Listar Propiedades)
            // Lista los valores escritos en propiedades.dat
            break;
        case '3':
            // Opcion 3 del menu
            break;
        case '4':
            // Opcion 4 del menu
            break;
        case '5':
            // Opcion 5 del menu
            break;
        case '6':
            // Opcion 6 del menu
            break;
        case '7':
            // Opcion 7 del menu
            break;
        case '8':
            // Opcion 8 del menu
            break;

        default:
            errorMenu();
            break;
        }
    }
    else
    {
        errorMenu()
    }

    GeneradorDeAlq(&Alquiler_Ventas[0]);
    Impresion(&Alquiler_Ventas[0]);
}