#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define VALUE_SIZE 256
#define FLOAT_POINT '.'

#define Columnas 15
#define Filas 9

// Función para limpiar el búfer de entrada.
void limpiarBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

// Definición de la estructura Alq_venta que almacena datos de propiedades.
struct Alq_venta
{
    int Id;
    char FechaIngreso[70];
    char Zona[20];
    char Ciudad_Barrio[20];
    int Dormitorios;
    int Banos;
    float SuperficieTotal;
    float SuperficieCubierta;
    float Precio;
    char TipMoneda[10];
    char TipPropiedad[20];
    char Operacion[30];
    char FechaSalida[70];
    int Activos;
};

/*En caso de que la tabla falle utilizo esto para visualizar los datos
void Impresion(struct Alq_venta *Datos)
{
    printf("\n");
    printf("----------Salida de datos----------\n");
    printf("Id : %d\n ", Datos->Id);

    printf("Fecha de Entrada : %s\n", Datos->FechaIngreso);

    printf("Zona : %s \n", Datos->Zona);
    printf("Ciudad o Barrio de la residencia : %s \n", Datos->Ciudad_Barrio);

    printf("Dormitorios : %d\n", Datos->Dormitorios);
    printf("Banos : %d\n", Datos->Banos);

    printf("Superficie Total de la vivienda : %.2f\n", Datos->SuperficieTotal);

    printf("Superficie Cubierta de la vivienda : %.2f\n", Datos->SuperficieCubierta);

    printf("Precio : %.2f\n", Datos->Precio);

    printf("Tipo de Moneda : %s\n", Datos->TipMoneda);

    printf("Tipo de Propiedad :%s \n", Datos->TipPropiedad);

    printf("Operacion: %s\n", Datos->Operacion);

    printf("Fecha de Salida : %s\n", Datos->FechaSalida);

    printf("Activos : %d\n", Datos->Activos);
}
void mostrarContenidoArchivo()
{
    FILE *Archivo = fopen("propiedades.dat", "rb"); // Abrir para lectura binaria
    struct Alq_venta Alquiler;

    if (!Archivo)
    {
        printf("No se pudo abrir el archivo para lectura.\n");
        return;
    }

    while (fread(&Alquiler, sizeof(struct Alq_venta), 1, Archivo))
    { // Leer mientras haya registros
        Impresion(&Alquiler);
        printf("\n"); // Agrega un espacio entre registros
    }

    fclose(Archivo);
    fflush(stdin);
}
*/

// Función para mostrar el contenido de propiedades en un formato de tabla.
void mostrarContenidoformatotabla()
{
    struct Alq_venta Propiedades;
    FILE *pArchivo;
    pArchivo = fopen("propiedades.dat", "rb");
    printf("-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("%-2s|%-19s|%-19s|%-20s|%-10s|%-5s|%-10s|%-13s|%-10s|%-6s|%-15s|%-10s|%-15s|%-7s\n",
           "ID", "Fecha de Entrada", "Zona", "Ciudad/Barrio", "Dormitorios", "Banos", "Sup. Total", "Sup. Cubierta", "Precio", "Moneda", "Tipo Propiedad", "Operacion", "Fecha de Salida", "Activos");
    printf("-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    if (pArchivo != NULL)
    {
        fread(&Propiedades, sizeof(struct Alq_venta), 1, pArchivo);

        while (!feof(pArchivo))
        {
            printf("-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
            printf("%-2d|%-19s|%-19s|%-20s| %-10d| %-4d|%-10.2f|%-13.2f|%-10.2f|%-6s|%-15s|%-10s|%-15s|%-7d\n",
                   Propiedades.Id, Propiedades.FechaIngreso, Propiedades.Zona, Propiedades.Ciudad_Barrio, Propiedades.Dormitorios, Propiedades.Banos, Propiedades.SuperficieTotal, Propiedades.SuperficieCubierta, Propiedades.Precio, Propiedades.TipMoneda, Propiedades.TipPropiedad, Propiedades.Operacion, Propiedades.FechaSalida, Propiedades.Activos);
            fread(&Propiedades, sizeof(struct Alq_venta), 1, pArchivo);
        }
        printf("-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");

        fclose(pArchivo);
    }
    else
    {
        printf("Error en la apertura del archivo");
    }
    getchar();
}

// Función para cargar un tipo de propiedad en la estructura Alq_venta.
void cargarPropiedad(struct Alq_venta *Opc_Propiedad)
{
    int opcion;
    printf("Eleccion:");
    scanf("%d", &opcion);

    switch (opcion)
    {
    case 1:
        strcpy(Opc_Propiedad->TipPropiedad, "Departamento");
        break;
    case 2:
        strcpy(Opc_Propiedad->TipPropiedad, "Casa");
        break;
    case 3:
        strcpy(Opc_Propiedad->TipPropiedad, "PH");
        break;
    default:
        printf("No se guardo");
        break;
    }
    limpiarBuffer();
    return;
}

// Función para generar datos de alquiler o venta de propiedades.
void GeneradorDeAlq(struct Alq_venta *Datos)
{
    time_t t = time(NULL);
    struct tm tiempoLocal = *localtime(&t);
    char *formato = "%d-%m-%Y %H:%M:%S";
    int bytesEscritos =
        strftime(Datos->FechaIngreso, sizeof Datos->FechaIngreso, formato, &tiempoLocal);

    if (bytesEscritos == 0)
    {
        printf("Error formateando fecha");
    }
    limpiarBuffer();

    printf("\n");
    printf("----------Entrada de datos----------\n");
    printf("Id : ");
    scanf("%d", &Datos->Id);
    limpiarBuffer();

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

    printf("Tipo de Propiedad (seleccione una opcion): ");
    printf("\n 1-Departamento\n 2-Casa\n 3-PH\n");
    cargarPropiedad(Datos);
    limpiarBuffer();

    printf("Que Operaciones va a realizar con la vivienda: ");
    scanf("%[^\n]", Datos->Operacion);
    limpiarBuffer();

    printf("Fecha de Salida : ");
    scanf("%[^\n]", Datos->FechaSalida);
    limpiarBuffer();

    printf("Activos : ");
    scanf("%d", &Datos->Activos);
    limpiarBuffer();
}

// Función para mostrar un mensaje de error en el menú.
void errorMenu()
{
    printf("xxxxxxxxxxxxxx Ingrese una opción valida xxxxxxxxxxxxxx\n");
}

// Función para buscar una propiedad por su ID.
void buscarPorId(struct Alq_venta *Propiedades)
{
    int id;
    printf("Ingrese el ID de la propiedad que desea buscar: ");
    scanf("%d", &id);

    int encontrado = 0;

    FILE *pArchivo = fopen("propiedades.dat", "rb");
    if (pArchivo == NULL)
    {
        printf("Error en la apertura del archivo.\n");
        return;
    }

    struct Alq_venta propiedad;

    while (fread(&propiedad, sizeof(struct Alq_venta), 1, pArchivo) != 0)
    {
        if (propiedad.Id == id)
        {
            printf("Propiedad encontrada:\n");
            printf("ID: %d\n", propiedad.Id);
            printf("Fecha de Entrada: %s\n", propiedad.FechaIngreso);
            printf("Zona: %s\n", propiedad.Zona);
            printf("Ciudad/Barrio: %s\n", propiedad.Ciudad_Barrio);
            printf("Dormitorios: %d\n", propiedad.Dormitorios);
            printf("Banos: %d\n", propiedad.Banos);
            printf("Superficie Total: %.2f\n", propiedad.SuperficieTotal);
            printf("Superficie Cubierta: %.2f\n", propiedad.SuperficieCubierta);
            printf("Precio: %.2f %s\n", propiedad.Precio, propiedad.TipMoneda);
            printf("Tipo Propiedad: %s\n", propiedad.TipPropiedad);
            printf("Operacion: %s\n", propiedad.Operacion);
            printf("Fecha de Salida: %s\n", propiedad.FechaSalida);
            printf("Activos: %d\n", propiedad.Activos);
            encontrado = 1;
        }
    }

    fclose(pArchivo);

    if (!encontrado)
    {
        printf("No se encontro ninguna propiedad con el ID proporcionado.\n");
    }
}

// Función para buscar propiedades por tipo de operación y tipo de propiedad.
void buscarPorTipoOperacionYPropiedad(struct Alq_venta *Propiedades)
{
    char tipoOperacion[30];
    char tipoPropiedad[20];

    printf("Ingrese el tipo de operacion (Venta/Alquiler/Alquiler temporal): ");
    scanf(" %29[^\n]", tipoOperacion); // Leer tipo de operación como cadena

    printf("Ingrese el tipo de propiedad (Departamento/Casa/PH): ");
    scanf(" %19[^\n]", tipoPropiedad); // Leer tipo de propiedad como cadena

    int encontrado = 0;

    FILE *pArchivo = fopen("propiedades.dat", "rb");
    if (pArchivo == NULL)
    {
        printf("Error en la apertura del archivo.\n");
        return;
    }

    struct Alq_venta propiedad;

    while (fread(&propiedad, sizeof(struct Alq_venta), 1, pArchivo) != 0)
    {
        // Comparar las cadenas usando strncmp para ignorar espacios en blanco
        if (strncmp(tipoOperacion, propiedad.Operacion, sizeof(tipoOperacion)) == 0 &&
            strncmp(tipoPropiedad, propiedad.TipPropiedad, sizeof(tipoPropiedad)) == 0)
        {
            printf("Propiedad encontrada:\n");
            printf("ID: %d\n", propiedad.Id);
            printf("Fecha de Entrada: %s\n", propiedad.FechaIngreso);
            printf("Zona: %s\n", propiedad.Zona);
            printf("Ciudad/Barrio: %s\n", propiedad.Ciudad_Barrio);
            printf("Dormitorios: %d\n", propiedad.Dormitorios);
            printf("Banos: %d\n", propiedad.Banos);
            printf("Superficie Total: %.2f\n", propiedad.SuperficieTotal);
            printf("Superficie Cubierta: %.2f\n", propiedad.SuperficieCubierta);
            printf("Precio: %.2f %s\n", propiedad.Precio, propiedad.TipMoneda);
            printf("Tipo Propiedad: %s\n", propiedad.TipPropiedad);
            printf("Operacion: %s\n", propiedad.Operacion);
            printf("Fecha de Salida: %s\n", propiedad.FechaSalida);
            printf("Activos: %d\n", propiedad.Activos);
            encontrado = 1;
        }
    }

    fclose(pArchivo);

    if (!encontrado)
    {
        printf("No se encontro ninguna propiedad con los tipos de operacion y propiedad proporcionados.\n");
    }
}

// Función para mostrar el submenú.
void submenu(struct Alq_venta *Propiedades)
{
    printf("------------Sub-Menu------------\n");
    printf("1 - Listar Todos\n");
    printf("2 - Solo Campos Activos\n");
    printf("3 - Ingreso por teclado de un tipo de propiedad\n");
    printf("4 - Ingreso de un rango de tiempo de ingreso (minimo y maximo)\n");
    printf("5 - Buscar por ID\n");
    printf("6 - Buscar por tipo de operación y luego por tipo de propiedad\n");

    char Opcion;
    printf("\n");
    printf("Elija opcion: ");
    scanf(" %c", &Opcion);
    limpiarBuffer();
    printf("\n");

    switch (Opcion)
    {
        case '1':
            mostrarContenidoformatotabla();
            break;
        case '2':
            // Opcion 2 del menú (aquí puedes agregar su funcionalidad)
            break;
        case '3':
            // Opcion 3 del menú (aquí puedes agregar su funcionalidad)
            break;
        case '4':
            // Opcion 4 del menú (aquí puedes agregar su funcionalidad)
            break;
        case '5':
            buscarPorId(Propiedades);
            break;
        case '6':
            buscarPorTipoOperacionYPropiedad(Propiedades);
            break;
        default:
            errorMenu();
            break;
    }
}

// Función para mostrar el menú principal.
void menu(struct Alq_venta *Alquiler_Ventas, int *PSalida)
{
    printf("--------------Menu--------------\n");
    printf("1 - Crear archivo de propiedades\n");
    printf("2 - Mirar el Contenido del Archivo\n");
    printf("3 - \n");
    printf("4 - \n");
    printf("5 - \n");
    printf("6 - \n");
    printf("7 - \n");
    printf("8 - Salida\n");

    char opcion;
    FILE *Arch_Datos;

    printf("\n");
    printf("Elija opcion: ");
    scanf(" %c", &opcion);
    limpiarBuffer();
    printf("\n");

    if (opcion > 0)
    {
        switch (opcion)
        {
        case '1':
            Arch_Datos = fopen("propiedades.dat", "wb");
            *PSalida = 0;

            GeneradorDeAlq(Alquiler_Ventas);
            fwrite(Alquiler_Ventas, sizeof(struct Alq_venta), 1, Arch_Datos);

            if (Arch_Datos != NULL)
            {
                printf("Saliendo y guardando el archivo de datos");
                fclose(Arch_Datos);
            }
            break;
        case '2':
            submenu(Alquiler_Ventas);
            break;
        case '3':
            //Opcion 3 del menu
            break;
        case '4':
            //Opcion 4 del menu
            break;
        case '5':
            //Opcion 5 del menu
            break;
        case '6':
            //Opcion 6 del menu
            break;
        case '7':
            //Opcion 7 del menu
            break;
        case '8':
            // Opcion de salida
            *PSalida = 1;
            break;
        default:
            errorMenu();
            break;
        }
    }
}

int main()
{
    int Salida = 0;
    struct Alq_venta Propiedades;
    while (Salida != 1)
    {
        menu(&Propiedades, &Salida);
    }
    return 0;
}

//---------------------- Punto Numero 6 --------------------------- //
//------------------------------------------------------------------//
// Alta de propiedad:
/*
void darAlta(struct Alq_venta Datos[])
{
    FILE *arch;
    arch=fopen("propiedades.dat","ab");

    if (arch==NULL){
        exit(1);}

    //struct Alq_venta Datos;

    printf("Ingrese el numero de ID : ");
    cargaYConsulta(&Datos);

    printf("Zona en donde se encuentra la residencia : ");
    scanf("%s ", Datos->Zona);
    printf("Ciudad o Barrio de la residencia : ");
    scanf("%s ",Datos->Ciudad_Barrio);

    do {
    printf("Cantidad de Dormitorios : ");
    scanf("%d",Datos->Dormitorios);
    } while (Datos->Dormitorios < 0);

    do {
    printf("Cantidad de Baños : ");
    scanf("%d", Datos->Banos);
    } while (Datos->Banos < 0);

    do {
    printf("Superficie Total de la vivienda : ");
    scanf("%.2f", Datos->SuperficieTotal);
    } while (Datos->SuperficieTotal < 0);

    do {
    printf("Superficie Cubierta de la vivienda : ");
    scanf("%.2f", Datos->SuperficieCubierta);
    } while (Datos->SuperficieCubierta < 0);

    do {
    printf("Precio : ");
    scanf("%.2f", Datos->Precio);
    } while (Datos->Precio < 0);

    printf("Tipo de Moneda : ");
    scanf("%.2f", Datos->TipMoneda);
    printf("Que Operaciones va a realizar con la vivienda: ");
    scanf("%s", Datos->Operacion);
    printf("Fecha de Salida: ");
    scanf("%s", Datos->FechaSalida);
    printf("Activos : ");
    scanf("%d", Datos->Activos);

    fwrite(&Datos, sizeof(Datos), 1, arch);//Alq_venta
fclose(arch);
continuar();
}
*/
//------------------------------------------------------------------//

/*
Si la variable recibe el valor de 1, quiere decir que estamos en la primera letra.
Si la variable recibe el valor de 0, quiere decir que NO estamos en la primera letra.
Este algoritmo solo funcionará si cada palabra está separado por un espacio:
*/
/*
void cambiar_a_mayusculas(char * palabras)
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
*/
//------------------------------------------------------------------//
/*
Esta función permite determinar si una cadena corresponde a:
1- Un número entero,
2- Un número con punto decimal,
3- Un valor numérico inválido (caracteres, espacios, etc.).
*/

/*int validarNumero(char  number[]) {
    int i = 0, x = 0;

    for (i = 0; i < VALUE_SIZE; i++) {

        if (number[i] == FLOAT_POINT)
            x++;

        if (!isdigit(number[i]) && number[i] != FLOAT_POINT && number[i] != '\0')
            return 3;   // Numero Invalido
    }

    if (x == 0)
        return 1;   // Numero Entero

    if (x == 1)
        return 2;   //Numero Flotante

    if (x > 1)
        return 3;   // Numero no valido
}



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

*/
//------------------------------------------------------------------//

// Control de ERROR NUMERO:
/*
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
*/
//------------------------------------------------------------------//

// Ingresa el numero de Id y valida que este no sea negativo...
// Consulta si el numero del Id ingresado ya se encuentra registrado

/*
void cargaYConsulta(struct Alq_venta Datos[])
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
    while (id<0);

    //struct Alq_venta Datos;

    int existe=0;
    fread(&Datos, sizeof (Datos), 1, arch);//Alq_venta
while (!feof(arch))
{
    if (id == Datos->Id)
    {
        printf("El id ingresado ya existe en el archivo");
        existe = 1;
        break;
    }

    }
    if (existe==0)
        fwrite(&id, sizeof (Datos), 1, arch);//Alq_venta
fclose(arch);
continuar();
}
*/
