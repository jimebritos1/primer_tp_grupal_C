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
// Funcion para reiniciar el Archivo/Borrar Todo
void BorrarTodo()
{
    FILE *pArchivo;
    pArchivo = fopen("propiedades.dat", "wb");
    struct Alq_venta Propiedades;

    memset(&Propiedades, 0, sizeof(struct Alq_venta));
    for (int i = 0; i < 16; i++)
    {
        Propiedades.Id = i;
        fwrite(&Propiedades, sizeof(struct Alq_venta), 1, pArchivo);
    }

    if (pArchivo != NULL)
    {
        fclose(pArchivo);
    }
    else
    {
        printf("Error en la apertura del archivo");
    }
};

// Función para mostrar el contenido de propiedades en un formato de tabla.
void mostrarContenidoformatotabla()
{
    struct Alq_venta Propiedades;
    FILE *pArchivo;
    pArchivo = fopen("propiedades.dat", "rb");

    if (pArchivo != NULL)
    {
        printf("-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
        printf("%-2s|%-19s|%-19s|%-20s|%-10s|%-5s|%-10s|%-13s|%-10s|%-6s|%-15s|%-10s|%-15s|%-7s\n",
               "ID", "Fecha de Entrada", "Zona", "Ciudad/Barrio", "Dormitorios", "Banos", "Sup. Total", "Sup. Cubierta", "Precio", "Moneda", "Tipo Propiedad", "Operacion", "Fecha de Salida", "Activos");
        printf("-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
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
void GeneradorDeProp(struct Alq_venta *Datos)
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

            printf("-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
            printf("%-2s|%-19s|%-19s|%-20s|%-10s|%-5s|%-10s|%-13s|%-10s|%-6s|%-15s|%-10s|%-15s|%-7s\n",
                   "ID", "Fecha de Entrada", "Zona", "Ciudad/Barrio", "Dormitorios", "Banos", "Sup. Total", "Sup. Cubierta", "Precio", "Moneda", "Tipo Propiedad", "Operacion", "Fecha de Salida", "Activos");
            printf("-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
            printf("-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
            printf("%-2d|%-19s|%-19s|%-20s| %-10d| %-4d|%-10.2f|%-13.2f|%-10.2f|%-6s|%-15s|%-10s|%-15s|%-7d\n",
                   propiedad.Id, propiedad.FechaIngreso, propiedad.Zona, propiedad.Ciudad_Barrio, propiedad.Dormitorios, propiedad.Banos, propiedad.SuperficieTotal, propiedad.SuperficieCubierta, propiedad.Precio, propiedad.TipMoneda, propiedad.TipPropiedad, propiedad.Operacion, propiedad.FechaSalida, propiedad.Activos);
        
            printf("-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
            encontrado = 1;
        }
    }

    fclose(pArchivo);
    limpiarBuffer();

    if (!encontrado)
    {
        printf("\n");
        printf("No se encontro ninguna propiedad con el ID proporcionado.\n");
        printf("\n");
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
            printf("-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
            printf("%-2s|%-19s|%-19s|%-20s|%-10s|%-5s|%-10s|%-13s|%-10s|%-6s|%-15s|%-10s|%-15s|%-7s\n",
                   "ID", "Fecha de Entrada", "Zona", "Ciudad/Barrio", "Dormitorios", "Banos", "Sup. Total", "Sup. Cubierta", "Precio", "Moneda", "Tipo Propiedad", "Operacion", "Fecha de Salida", "Activos");
            printf("-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
            printf("-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
            printf("%-2d|%-19s|%-19s|%-20s| %-10d| %-4d|%-10.2f|%-13.2f|%-10.2f|%-6s|%-15s|%-10s|%-15s|%-7d\n",
                   propiedad.Id, propiedad.FechaIngreso, propiedad.Zona, propiedad.Ciudad_Barrio, propiedad.Dormitorios, propiedad.Banos, propiedad.SuperficieTotal, propiedad.SuperficieCubierta, propiedad.Precio, propiedad.TipMoneda, propiedad.TipPropiedad, propiedad.Operacion, propiedad.FechaSalida, propiedad.Activos);

            printf("-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
            encontrado = 1;
        }
    }

    fclose(pArchivo);
    limpiarBuffer();
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
    printf("3 - Dar el alta una Nueva Propiedad\n");
    printf("4 - \n");
    printf("5 - \n");
    printf("6 - \n");
    printf("7 - Reiniciar Tabla\n");
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
            Arch_Datos = fopen("propiedades.dat", "rb+");
            *PSalida = 0;

            GeneradorDeProp(Alquiler_Ventas);
            fseek(Arch_Datos, Alquiler_Ventas->Id * sizeof(struct Alq_venta), SEEK_SET);
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
            // Opcion 3 del menu
             // Da de alta nuevas propiedades
            {
            FILE *arch = fopen("propiedades.dat", "ab+");
            if (arch == NULL){
            printf("Error al abrir el archivo");
            return 1;
            }
            char opcion;
            do {
                darAlta(arch);
                printf("¿Desea ingresar otra propiedad? (S/N): ");
                scanf(" %c", &opcion);
                limpiarBuffer();
            } while (opcion == 'S' || opcion == 's');

            fclose(arch);
            }
            
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
            BorrarTodo();
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
//Si la variable recibe el valor de 1, quiere decir que estamos en la primera letra.
//Si la variable recibe el valor de 0, quiere decir que NO estamos en la primera letra.
//Este algoritmo solo funcionará si cada palabra está separado por un espacio:


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

//------------------------------------------------------------------//

//Esta función permite determinar si una cadena corresponde a:
//1- Un número entero,
//2- Un número con punto decimal,
//3- Un valor numérico inválido (caracteres, espacios, etc.).


void esUnNumero(const char number[], int *result) {
    int i = 0, x = 0;

    for (i = 0; i < VALUE_SIZE; i++) {
        if (number[i] == '.') {
            x++;
        }
        if (!isdigit(number[i]) && number[i] != '.' && number[i] != '\0') {
            *result = 3; // Numero Invalido
            return;
        }
    }

    if (x == 0) {
        *result = 1; // Numero Entero
    } else if (x == 1) {
        *result = 2; // Numero Flotante
    } else {
        *result = 3; // Numero no valido
    }


//Verifica que lo ingresado por el ususario sea un Caracter

int esCaracterOString(const char input[]) {
    if (strlen(input) == 1) {
        return 1; // Es un Caracter
    } else {
        return 2; // Es un string
    }
   }



//---------------------- Punto Numero 6 --------------------------- //
//------------------------------------------------------------------//
// Alta de propiedad:

void validarQueNoSeRepitaId(int id, struct Alq_venta *Datos, FILE *arch) {
    int existe = 0;
    rewind(arch);

    while (fread(Datos, sizeof(struct Alq_venta), 1, arch) == 1) {
        if (id == Datos->Id) {
            printf("El ID ingresado ya existe en el archivo\n");
            existe = 1;
            break;
        }
    }

    if (existe == 0) {
        fseek(arch, 0, SEEK_END);
        fwrite(Datos, sizeof(struct Alq_venta), 1, arch);
    }
}

void darAlta(FILE *arch) {
    struct Alq_venta Datos;
    int id;
    char input[VALUE_SIZE];

    time_t t = time(NULL);
    struct tm tiempoLocal = *localtime(&t);
    char formato[] = "%Y-%m-%d %H:%M:%S";
    strftime(Datos.FechaSalida, sizeof Datos.FechaSalida, formato, &tiempoLocal);

    // INGRESA Y VALIDA LOS DATOS DEL ID
    printf("----------Entrada de datos----------\n");
    do {
        printf("Ingrese el número de Id: ");
        scanf("%i", &id);
    } while (id < 0);

    Datos.Id = id;
    validarQueNoSeRepitaId(id, &Datos, arch);
    limpiarBuffer();

    //INGRESA Y VALIDA LOS DATOS DE LA ZONA
    printf("Zona en donde se encuentra la residencia: ");
    scanf("%s", input);
    int tipoDato = esCaracterOString(input);

    if (tipoDato == 1) {
        printf("Es un carácter valido. Valor asignado: %c\n", input[0]);
        Datos.Zona[0] = input[0]; // Asigna el valor a Datos.Zona
    } else if (tipoDato == 2) {
        printf("Es una cadena valida. Valor asignado: %s\n", input);
        strncpy(Datos.Zona, input, sizeof(Datos.Zona)); // Aigna el valor a Datos.Zona
    } else {
        printf("El dato ingresado es incorrecto. No se ha asignado a Zona.\n");
    }
    cambiar_a_mayusculas(Datos.Zona);
    limpiarBuffer();

    //INGRESA Y VALIDA DATO CIUDAD_BARRIO
    printf("Ciudad o Barrio de la residencia: ");
    scanf("%s", input);
    int tipoDato2 = esCaracterOString(input);

    if (tipoDato2 == 1) {
        printf("Es un carácter valido. Valor asignado: %c\n", input[0]);
        Datos.Ciudad_Barrio[0] = input[0]; // Asigna el valor a Datos.Ciudad_Barrio
        printf("Es una cadena valida. Valor asignado: %s\n", input);
        strncpy(Datos.Ciudad_Barrio, input, sizeof(Datos.Ciudad_Barrio)); // Asigna el valor de Datos.Ciudad_Barrio
    } else {
        printf("El dato ingresado es incorrecto. No se ha asignado a Zona.\n");
    }
    cambiar_a_mayusculas(Datos.Ciudad_Barrio);
    limpiarBuffer();

    //INGRESA Y VALIDA DATO DORMITORIOS
    printf("Cantidad de Dormitorios: ");
    scanf("%d", &Datos.Dormitorios);
    int resultadoValidacion;
    printf("Ingrese un numero: ");
    scanf("%s", input);

    esUnNumero(input, &resultadoValidacion);

    if (resultadoValidacion == 1) {
        // Valor entero
        Datos.Dormitorios = atoi(input);
        printf("Es un numero entero valido. Valor asignado: %d\n", Datos.Dormitorios);
    } else if (resultadoValidacion == 2) {
        // Valor Flotante
        Datos.Dormitorios = (int)atof(input);
        printf("Es un numero flotante valido. Valor asignado: %d\n", Datos.Dormitorios);
    } else {
        printf("El numero ingresado es incorrecto. No se ha asignado a Dormitorios.\n");
    limpiarBuffer();

    //INGRESA Y VALIDA DATO BAÑOS
    printf("Cantidad de Banos: ");
    scanf("%s", input);

     esUnNumero(input, &resultadoValidacion);

    //Verifica el resultado de validacion y valida el tipo de dato...
    if (resultadoValidacion == 1) {
        // Valor entero
        Datos.Banos = atoi(input);
        printf("Es un numero entero valido. Valor asignado: %d\n", Datos.Banos);
    } else if (resultadoValidacion == 2) {
        // Valor Flotante
        Datos.Banos = (int)atof(input);
        printf("Es un numero flotante valido. Valor asignado: %d\n", Datos.Banos);
    } else {
        printf("El numero ingresado es incorrecto. No se ha asignado a Banos.\n");
    limpiarBuffer();

    //INGRESA Y VALIDA DATO DE SUPERFICIE TOTAL

    printf("Superficie Total de la vivienda: ");
    scanf("%s", input);

     esUnNumero(input, &resultadoValidacion);

     //Verifica el resultado de validacion y valida el tipo de dato
    if (resultadoValidacion == 1) {
        // Valor entero
        Datos.SuperficieTotal = atoi(input);
        printf("Es un numero entero valido. Valor asignado: %d\n", Datos.SuperficieTotal);
    } else if (resultadoValidacion == 2) {
        // Valor Flotante
        Datos.SuperficieTotal = (int)atof(input);
        printf("Es un numero flotante valido. Valor asignado: %d\n", Datos.SuperficieTotal);
    } else {
        printf("El numero ingresado es incorrecto. No se ha asignado a Superficie Total.\n");
    limpiarBuffer();


    //INGRESA Y VALIDA DATO DE SUPERFICIE CUBIERTA
    printf("Superficie Cubierta de la vivienda: ");
    scanf("%s", input);

     esUnNumero(input, &resultadoValidacion);

     //Verifica el resultado de validacion y valida el tipo de dato...
    if (resultadoValidacion == 1) {
        // Valor entero
        Datos.SuperficieCubierta = atoi(input);
        printf("Es un numero entero valido. Valor asignado: %d\n", Datos.SuperficieCubierta);
    } else if (resultadoValidacion == 2) {
        // Valor Flotante
        Datos.SuperficieCubierta = (int)atof(input);
        printf("Es un numero flotante valido. Valor asignado: %d\n", Datos.SuperficieCubierta);
    } else {
        printf("El numero ingresado es incorrecto. No se ha asignado a Superficie Total.\n");
    limpiarBuffer();


    //INGRESA Y VALIDA DATO DE PRECIO
     printf("Precio: ");
     scanf("%s", input);

     esUnNumero(input, &resultadoValidacion);

     //Verifica el resultado de validacion y valida el tipo de dato...
    if (resultadoValidacion == 1) {
        // Valor entero
        Datos.Precio = atoi(input);
        printf("Es un numero entero valido. Valor asignado: %d\n", Datos.Precio);
    } else if (resultadoValidacion == 2) {
        // Valor Flotante
        Datos.Precio = (int)atof(input);
        printf("Es un numero flotante valido. Valor asignado: %d\n", Datos.Precio);
    } else {
        printf("El numero ingresado es incorrecto. No se ha asignado a Superficie Total.\n");
    limpiarBuffer();

    //INGRESA Y VALIDA EL TIPO DE MONEDA

    printf("Tipo de Moneda: ");
     scanf("%s", input);
    int tipoDato3 = esCaracterOString(input);

    if (tipoDato3 == 1) {
        printf("Es un caracter valido. Valor asignado: %c\n", input[0]);
        Datos.TipMoneda[0] = input[0]; // Asigna el valor a Datos.TipMoneda
    } else if (tipoDato3 == 2) {
        printf("Es una cadena valida. Valor asignado: %s\n", input);
        strncpy(Datos.TipMoneda, input, sizeof(Datos.TipMoneda)); // Asigna el valor de Datos.Moneda
    } else {
        printf("El dato ingresado es incorrecto. No se ha asignado a Zona.\n");
    }
    cambiar_a_mayusculas(Datos.TipMoneda);
    limpiarBuffer();

    //-----------------------------------------------------------//
    cargarPropiedad(&Datos);
    limpiarBuffer();

    printf("Qué Operaciones va a realizar con la vivienda: ");
    scanf("%99[^\n]", Datos.Operacion);
    limpiarBuffer();

    printf("Activos: ");
    scanf("%d", &Datos.Activos);
    limpiarBuffer();

    fseek(arch, 0, SEEK_END);
    fwrite(&Datos, sizeof(struct Alq_venta), 1, arch);
    printf("Datos guardados con éxito.\n");

         }
