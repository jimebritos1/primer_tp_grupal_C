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
    printf("Ingrese una opcion valida\n");
}

void menu()
{
    printf("---------------Menu--------------\n");       // Cada funcion del menu invoca una funcion especifica o submenu
    printf("1 - Crear archivo de propiedades\n"); // Crea el archivo de propiedades.bin
    printf("2 - \n");
    printf("3 - \n");
    printf("4 - \n");
    printf("5 - \n");
    printf("6 - \n");
    printf("7 - \n");
    printf("8 - \n");
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
    char opcion;
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

    menu();
    scanf("%c", &opcion);
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
        errorMenu();
    }

    //GeneradorDeAlq(&Alquiler_Ventas[0]);
    //Impresion(&Alquiler_Ventas[0]);
}

/*---------------------- Punto Numero 6 --------------------------- */
/*------------------------------------------------------------------*/
// Alta de propiedad:

void darAlta()
{
    FILE *arch;
    arch=fopen("propiedades.dat","ab");
    if (arch==NULL)
        exit(1);
    Alq_venta Datos;
    printf("Ingrese el numero de ID : ");
    cargaYConsulta();
    printf("Zona en donde se encuentra la residencia : ");
    scanf("%s ", Datos->Zona);
    printf("Ciudad o Barrio de la residencia : ");
    scanf("%s ",Datos->Ciudad_Barrio);
    do {
    printf("Cantidad de Dormitorios : ");
    scanf("%d",Datos->Dormitorios);
    }
    while (Dormitorios<0)

    do {
    printf("Cantidad de Baños : ");
    scanf("%d", Datos->Baños);
    }
    while (Baños<0)

    do {
    printf("Superficie Total de la vivienda : ");
    scanf("%.2f", Datos->SuperficieTotal);
    }
    while (SuperficieTotal<0)
    do {
    printf("Superficie Cubierta de la vivienda : ");
    scanf("%.2f", Datos->SuperficieCubierta);
    }
    while (SuperficieCubierta<0)
    do {
    printf("Precio : ");
    scanf("%.2f", Datos->Precio);
    }
    while (Precio<0)
    printf("Tipo de Moneda : ");
    scanf("%.2f", Datos->TipMoneda);

    printf("Que Operaciones va a realizar con la vivienda: ");
    scanf("%s", Datos->Operacion);
    printf("Fecha de Salida: ");
    scanf("%s", Datos->FechaSalida);
    printf("Activos : ");
    scanf("%d", Datos->Activos);
    fwrite(&Datos, sizeof(Alq_venta), 1, arch);
    fclose(arch);
    continuar();
}

/*------------------------------------------------------------------*/
//// Carga la propiedad y su tipo...

void cargarPropiedad(){

 int opcion;

 printf("Selecciones una opcion:\n 1-Departamento\n 2-Casa \n 3-PH\n");
  printf("Tipo de Propiedad : ");
    scanf("%s", Datos->TipPropiedad);
 switch(opcion){
 case 1:
    break;
 case 2:
    break;
 case 3:
    break;
 default:
    break;

 }

}
/*------------------------------------------------------------------*/

/*
Si la variable recibe el valor de 1, quiere decir que estamos en la primera letra.
Si la variable recibe el valor de 0, quiere decir que NO estamos en la primera letra.
Este algoritmo solo funcionará si cada palabra está separado por un espacio:
*/

void cambiar_a_mayusculas(char* palabras)
{
    for(int primeraLetra = 1; *palabras; ++palabras)
    {
        if(primeraLetra && isalpha(*palabras))
        {
            *palabras = toupper(*palabras);
            primeraLetra = 0;
        }
        if(*palabras == ' ')
            primeraLetra = 1;
    }
}

/*------------------------------------------------------------------*/
/*
Esta función permite determinar si una cadena corresponde a:
1- Un número entero,
2- Un número con punto decimal,
3- Un valor numérico inválido (caracteres, espacios, etc.).
*/

/*

#include <ctype.h>

#define VALUE_SIZE 256
#define FLOAT_POINT '.'
*/
int validarNumero(char[]);

int validarNumero(char number[]) {
    int i = 0, x = 0;

    for (i = 0; i < VALUE_SIZE; i++) {

        if (number[i] == FLOAT_POINT)
            x++;

        if (!isdigit(number[i]) && number[i] != FLOAT_POINT && number[i] != '\0')
            return 3;   /* Numero Invalido */
    }

    if (x == 0)
        return 1;   /* Numero Entero */

    if (x == 1)
        return 2;   /* Numero Flotante */

    if (x > 1)
        return 3;   /* Numero no valido */
}

*/

//Verifica que lo ingresado por el usuario sea un Numero...
void esUnNumero(validarNumero()){

     if (validarNumero() != 3 ){


     }
}

//Verifica que lo ingresado por el ususario sea un Caracter...

void esUnCaracter(validarNumero()){

    if(validarNumero() == 3){


    }
}
/*------------------------------------------------------------------*/

//Control de ERROR NUMERO:

void controlErrorNumero(char num[]){
{
    for (int i = 0; i < strlen(num); i++)
    {
        if(!isdigit(num[i]) ) {
            printf("Ingrese un numero valido");
            break;
        }
    }
}


}

/*------------------------------------------------------------------*/

// Ingresa el numero de Id y valida que este no sea negativo...
//Consulta si el numero del Id ingresado ya se encuentra registrado

void cargaYConsulta()
{
    int id;
    FILE *arch;
    arch=fopen("propiedades.dat","rb");
    if (arch==NULL)
        exit(1);

    do {
    printf("Ingrese Id:");
    scanf("%i", &id);
    }
    while (id<0)
    Alq_venta Datos;
    int existe=0;
    fread(&Datos, sizeof(Alq_venta), 1, arch);
    while(!feof(arch))
    {
        if (Id==Datos.Id)
        {
           printf("El id ingresado ya existe en el archivo");
           existe=1;
           break;
        }

    }
    if (existe==0)
        fwrite(&id, sizeof(Alq_venta), 1, arch);
    fclose(arch);
    continuar();
}
