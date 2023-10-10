#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define Columnas 15

struct Alq_venta
{
    int Id;
    char FechaIngreso[70];
    //Ingreso por teclado de aca para abajo
    char Zona[30];
    char Ciudad_Barrio[30];
    int Dormitorios;
    int Baños;
    float SuperficieTotal;
    float SuperficieCubierta;
    float Precio;
    char TipMoneda[5];
    char TipPropiedad[12];
    char Operacion[30];
    char FechaSalida[70];
    bool Activos;
};
void GeneradorDeAlq(struct Alq_venta Datos[])
{
    printf("Zona en donde se encuentra la residencia : ");
    scanf("%s ", Datos->Zona);
    printf("Ciudad o Barrio de la residencia : ");
    scanf("%s ",Datos->Ciudad_Barrio);
    printf("Cantidad de Dormitorios : ");
    scanf("%d",Datos->Dormitorios);
    printf("Cantidad de Baños : ");
    scanf("%d", Datos->Baños);
    printf("Superficie Total de la vivienda : ");
    scanf("%.2f", Datos->SuperficieTotal);
    printf("Superficie Cubierta de la vivienda : ");
    scanf("%.2f", Datos->SuperficieCubierta);
    printf("Precio : ");
    scanf("%.2f", Datos->Precio);
    printf("Tipo de Moneda : ");
    scanf("%.2f", Datos->TipMoneda);
    printf("Tipo de Propiedad : ");
    scanf("%s", Datos->TipPropiedad);
    printf("Que Operaciones va a realizar con la vivienda: ");
    scanf("%s", Datos->Operacion);
    printf("Fecha de Salida: ");
    scanf("%s", Datos->FechaSalida);
    printf("Activos : ");
    scanf("%d", Datos->Activos);
}

int main()
{
    struct Alq_venta Alquiler_Ventas;
    // Tiempo Actual
    time_t t = time(NULL);
    struct tm tiempoLocal = *localtime(&t);
    // El formato. Mira más en https://en.cppreference.com/w/c/chrono/strftime
    char *formato = "%Y-%m-%d %H:%M:%S";
    // Intentar formatear
    int bytesEscritos =
        strftime(Alquiler_Ventas.FechaIngreso, sizeof Alquiler_Ventas.FechaIngreso, formato, &tiempoLocal);
    // Alquiler_Ventas es donde se va a guardar la feche local
    if (bytesEscritos != 0)
    {
        // Si no hay error, los bytesEscritos no son 0
        printf("Fecha y hora: %s", Alquiler_Ventas.FechaIngreso);
    }
    else
    {
        printf("Error formateando fecha");
    }
}