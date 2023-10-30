/* -----------------------------------------------------------
   Proyecto: Gesti�n de Propiedades
   L�der de Proyecto: Franco Fontanello
   Desarrolladores: -Javier Ignacio Cordero.
                    -Mar�a Jimena Britos.
   ----------------------------------------------------------- */
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define VALUE_SIZE 256
#define FLOAT_POINT '.'

#define Columnas 15
#define Filas 9

// Funci�n para limpiar el b�fer de entrada.
void limpiarBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

// Definici�n de la estructura Alq_venta que almacena datos de propiedades.
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
    for (int i = 0; i < 20; i++)
    {
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

// Funci�n para mostrar el contenido de propiedades en un formato de tabla.
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

/*-------------- VALIDACIONES --------------*/
// Funcion para saber si es un numero entero o flotante
void esUnNumero(const char number[], int *result)
{
    int x = 0;

    for (int i = 0; number[i] != '\0'; i++)
    {
        if (number[i] == '.')
        {
            x++;
        }
        else if (!isdigit(number[i])) //&& number[i] != '.' && number[i] != '\0'
        {
            *result = 3; // Numero Invalido
            return;
        }
    }
    if (x == 0)
    {
        *result = 1; // Numero Entero
    }
    else if (x == 1)
    {
        *result = 2; // Numero Flotante
    }
    else
    {
        *result = 3; // Numero no valido
    }

    // Verifica que lo ingresado por el ususario sea un Caracter
}
// Funcion para saber si se repite la ID
void validarQueNoSeRepitaId(int id, int *result, struct Alq_venta *Datos)
{
    FILE *arch;
    arch = fopen("propiedades.dat", "rb");
    if (arch == NULL)
    {
        printf("Error al abrir el archivo.\n");
        return;
    }

    rewind(arch);
    fseek(arch, (id - 1) * sizeof(struct Alq_venta), SEEK_SET);
    /*
       while (fread(Datos, sizeof(struct Alq_venta), 1, arch))
       {
           if (id == Datos->Id)
           {
               *result = 3; // El ID ya existe en el archivo
               break;
           }
       }*/

    if (fread(Datos, sizeof(struct Alq_venta), 1, arch) == 1)
    {
        if (id == Datos->Id)
        {
            *result = 3; // El ID ya existe en el archivo
        }
    }
    else
    {
        printf("Error al leer el registro o el ID no existe.\n");
    }

    fclose(arch);
}
/* Si la variable recibe el valor de 1, quiere decir que estamos en la primera letra.
   Si la variable recibe el valor de 0, quiere decir que NO estamos en la primera letra.
   Este algoritmo solo funcionar� si cada palabra est� separado por un espacio: */
void cambiar_a_mayusculas(char *palabras)
{
    for (int primeraLetra = 1; *palabras; ++palabras)
    {
        if (primeraLetra && isalpha(*palabras))
        {
            *palabras = toupper(*palabras);
            primeraLetra = 0;
        }
        if (*palabras == ' ')
            primeraLetra = 1;
    }
}
/* Esta funci�n permite determinar si es caracter o string*/
int esCaracterOString(const char input[])
{
    if (strlen(input) == 1)
    {
        return 1; // Es un Caracter
    }
    else
    {
        return 2; // Es un string
    }
}

/*-------------- OPCIONES PARA CAMPOS ESPECIFICO --------------*/
// Funci�n para ingresar un nuevo tipo de propiedad por teclado.
void ingresarTipoPropiedad(struct Alq_venta *Propiedades)
{
    printf("Ingrese el nuevo tipo de propiedad: ");
    scanf("%s", Propiedades->TipPropiedad);
    printf("Nuevo tipo de propiedad '%s' ingresado.\n", Propiedades->TipPropiedad);
    limpiarBuffer();
}
//  Funci�n para cargar un tipo de propiedad en la estructura Alq_venta.
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
    case 4:
        ingresarTipoPropiedad(Opc_Propiedad);
        break;
    default:
        printf("No se guardo");
        break;
    }
    limpiarBuffer();
}
// Funcion para carga un tipo de Operacion para la propiedad en la estrucura Alq_Venta
void cargarOperacion(struct Alq_venta *Opc_Operacion)
{
    int opcion;
    printf("Eleccion:");
    scanf("%d", &opcion);

    switch (opcion)
    {
    case 1:
        strcpy(Opc_Operacion->Operacion, "Alquiler");
        break;
    case 2:
        strcpy(Opc_Operacion->Operacion, "Alq.Temp.");
        break;
    case 3:
        strcpy(Opc_Operacion->Operacion, "Venta");
        break;
    default:
        printf("No se guardo");
        break;
    }
    limpiarBuffer();
}
// Funcion para cargar un Tipo de Moneda en el cual se abonara la propiedad en la estructura Alq_Venta
void cargarTipoMoneda(struct Alq_venta *Opc_TipoMoneda)
{
    int opcion;
    printf("Eleccion:");
    scanf("%d", &opcion);

    switch (opcion)
    {
    case 1:
        strcpy(Opc_TipoMoneda->TipMoneda, "PESOS");
        break;
    case 2:
        strcpy(Opc_TipoMoneda->TipMoneda, "USD");
        break;
    case 3:
        strcpy(Opc_TipoMoneda->TipMoneda, "Euro");
        break;
    default:
        printf("No se guardo");
        break;
    }
    limpiarBuffer();
}

// Funci�n para generar datos de alquiler o venta de propiedades.
void GeneradorDeProp(struct Alq_venta *Datos)
{
    char input[VALUE_SIZE];
    int resultadoValidacion = 0;
    int id, ConfNum, tipoDato;
    float ConfNumF;

    time_t t = time(NULL);
    struct tm tiempoLocal = *localtime(&t);
    char *formato = "%d-%m-%Y %H:%M:%S";
    int bytesEscritos = strftime(Datos->FechaIngreso, sizeof Datos->FechaIngreso, formato, &tiempoLocal);
    if (bytesEscritos == 0)
    {
        printf("Error formateando fecha\n");
    }
    limpiarBuffer();
    printf("\n");

    printf("----------Entrada de datos----------\n");

    do
    {
        printf("ID : ");
        scanf("%s", input);
        limpiarBuffer();
        esUnNumero(input, &resultadoValidacion);

        if (resultadoValidacion == 1)
        {
            id = atoi(input);
        }
        else if (resultadoValidacion == 2)
        {
            id = (int)atof(input);
            resultadoValidacion = 1;
        }
        else
        {
            printf("El valor ingresado no es un n�mero.\n");
            memset(input, 0, sizeof(input));
        }

        validarQueNoSeRepitaId(id, &resultadoValidacion, Datos);
        if (resultadoValidacion == 3)
        {
            printf("El ID ingresado ya existe en el archivo. Por favor, ingrese otro.\n");
            memset(input, 0, sizeof(input));
        }

    } while (resultadoValidacion != 1);
    Datos->Id = id;
    // Reinicio Variable para volver a ulizarlas
    resultadoValidacion = 0;
    memset(input, 0, sizeof(input));

    do
    {
        printf("Zona en donde se encuentra la residencia : ");
        fgets(input, sizeof(input), stdin); // Utilizo fgets para tomar los espacios

        // Eliminamos el salto de l�nea al final si existe
        char *newline = strchr(input, '\n');
        if (newline)
        {
            *newline = '\0';
        }

        tipoDato = esCaracterOString(input);
        limpiarBuffer();

        if (tipoDato == 1)
        {
            Datos->Zona[0] = input[0]; // Asigna el valor a Datos->Zona
        }
        else if (tipoDato == 2)
        {
            strncpy(Datos->Zona, input, sizeof(Datos->Zona)); // Aigna el valor a Datos->Zona
            Datos->Zona[sizeof(Datos->Zona) - 1] = '\0';      // Asegura que sea una cadena terminada en NULL.
        }
        else
        {
            printf("El dato ingresado es incorrecto. No se ha asignado a Zona.\n");
        }
    } while (tipoDato != 1 && tipoDato != 2);

    cambiar_a_mayusculas(Datos->Zona);
    // Reinicio Variable para volver a ulizarlas
    tipoDato = 0;
    memset(input, 0, sizeof(input));

    do
    {
        printf("Ciudad o Barrio de la residencia : ");
        fgets(input, sizeof(input), stdin); // Utilizo fgets para tomar los espacios

        // Eliminamos el salto de l�nea al final si existe
        char *newline = strchr(input, '\n');
        if (newline)
        {
            *newline = '\0';
        }

        tipoDato = esCaracterOString(input);
        limpiarBuffer();

        if (tipoDato == 1)
        {
            Datos->Ciudad_Barrio[0] = input[0]; // Asigna el valor a Datos->Zona
        }
        else if (tipoDato == 2)
        {
            strncpy(Datos->Ciudad_Barrio, input, sizeof(Datos->Ciudad_Barrio)); // Aigna el valor a Datos->Zona
            Datos->Ciudad_Barrio[sizeof(Datos->Ciudad_Barrio) - 1] = '\0';      // Asegura que sea una cadena terminada en NULL.
        }
        else
        {
            printf("El dato ingresado es incorrecto. No se ha asignado a Zona.\n");
        }

    } while (tipoDato != 1 && tipoDato != 2);
    cambiar_a_mayusculas(Datos->Ciudad_Barrio);
    // Reinicio Variable para volver a ulizarlas
    tipoDato = 0;
    memset(input, 0, sizeof(input));

    do
    {
        printf("Cantidad de Dormitorios : ");
        scanf("%s", input);
        limpiarBuffer();

        esUnNumero(input, &resultadoValidacion);

        if (resultadoValidacion == 1)
        {
            ConfNum = atoi(input);
        }
        else if (resultadoValidacion == 2)
        {
            ConfNum = (int)atof(input);
            resultadoValidacion = 1;
        }
        else
        {
            printf("El valor ingresado no es un n�mero.\n");
            memset(input, 0, sizeof(input));
        }
    } while (resultadoValidacion != 1);
    Datos->Dormitorios = ConfNum;
    // Reinicio Variable para volver a ulizarlas
    ConfNum = 0;
    resultadoValidacion = 0;
    memset(input, 0, sizeof(input));

    do
    {
        printf("Cantidad de Banos : ");
        scanf("%s", input);
        limpiarBuffer();

        esUnNumero(input, &resultadoValidacion);

        if (resultadoValidacion == 1)
        {
            ConfNum = atoi(input);
        }
        else if (resultadoValidacion == 2)
        {
            ConfNum = (int)atof(input);
            resultadoValidacion = 1;
        }
        else
        {
            printf("El valor ingresado no es un n�mero.\n");
            memset(input, 0, sizeof(input));
        }
    } while (resultadoValidacion != 1);
    Datos->Banos = ConfNum;
    // Reinicio Variable para volver a ulizarlas
    ConfNum = 0;
    resultadoValidacion = 0;
    memset(input, 0, sizeof(input));

    do
    {
        printf("Superficie Total de la vivienda : ");
        scanf("%s", input);
        limpiarBuffer();

        esUnNumero(input, &resultadoValidacion);

        if (resultadoValidacion == 1)
        {
            ConfNumF = (float)atoi(input);
            resultadoValidacion = 2;
        }
        else if (resultadoValidacion == 2)
        {
            ConfNumF = atof(input);
        }
        else
        {
            printf("El valor ingresado no es un n�mero.\n");
            memset(input, 0, sizeof(input));
        }

    } while (resultadoValidacion != 2);
    Datos->SuperficieTotal = ConfNumF;
    // Reinicio Variable para volver a ulizarlas
    ConfNumF = 0.0;
    resultadoValidacion = 0;
    memset(input, 0, sizeof(input));

    do
    {
        printf("Superficie Cubierta de la vivienda : ");
        scanf("%s", input);
        limpiarBuffer();

        esUnNumero(input, &resultadoValidacion);

        if (resultadoValidacion == 1)
        {
            ConfNumF = (float)atoi(input);
            resultadoValidacion = 2;
        }
        else if (resultadoValidacion == 2)
        {
            ConfNumF = atof(input);
        }
        else
        {
            printf("El valor ingresado no es un n�mero.\n");
            memset(input, 0, sizeof(input));
        }

    } while (resultadoValidacion != 2);
    Datos->SuperficieCubierta = ConfNumF;
    // Reinicio Variable para volver a ulizarlas
    ConfNumF = 0.0;
    resultadoValidacion = 0;
    memset(input, 0, sizeof(input));

    do
    {
        printf("Precio : ");
        scanf("%s", input);
        limpiarBuffer();

        esUnNumero(input, &resultadoValidacion);

        if (resultadoValidacion == 1)
        {
            ConfNumF = (float)atoi(input);
            resultadoValidacion = 2;
        }
        else if (resultadoValidacion == 2)
        {
            ConfNumF = atof(input);
        }
        else
        {
            printf("El valor ingresado no es un n�mero.\n");
            memset(input, 0, sizeof(input));
        }

    } while (resultadoValidacion != 2);
    Datos->Precio = ConfNumF;
    // Reinicio Variable para volver a ulizarlas
    ConfNumF = 0.0;
    resultadoValidacion = 0;
    memset(input, 0, sizeof(input));

    printf("Tipo de Moneda : ");
    printf("\n 1-PESOS\n 2-USD\n 3-Euro\n");
    cargarTipoMoneda(Datos);
    limpiarBuffer();

    printf("Tipo de Propiedad (Seleccione una opcion): ");
    printf("\n 1-Departamento\n 2-Casa\n 3-PH\n 4-Otro\n");
    cargarPropiedad(Datos);
    limpiarBuffer();

    printf("Que Operaciones va a realizar con la vivienda(Seleccione una opcion): ");
    printf("\n 1-Alquiler\n 2-Alquiler Temporal\n 3-Venta\n");
    cargarOperacion(Datos);
    limpiarBuffer();

    printf("Fecha de Salida : \n");
    do
    {
        printf("Dia : ");
        scanf("%s", input);
        printf("\n");
        limpiarBuffer();

        esUnNumero(input, &resultadoValidacion);

        if (resultadoValidacion == 1)
        {
            ConfNum = atoi(input);
            if (ConfNum > 31 || ConfNum < 1)
            {
                resultadoValidacion = 0;
            }
        }
        else if (resultadoValidacion == 2)
        {

            ConfNum = (int)atof(input);
            resultadoValidacion = 1;
            if (ConfNum > 31 || ConfNum < 1)
            {
                resultadoValidacion = 0;
            }
        }
        else
        {
            printf("El valor ingresado no es coherente.\n");
            memset(input, 0, sizeof(input));
        }
    } while (resultadoValidacion != 1);
    int Dia = ConfNum;
    ConfNum = 0;
    resultadoValidacion = 0;
    memset(input, 0, sizeof(input));

    do
    {
        printf("Mes : ");
        scanf("%s", input);
        printf("\n");
        limpiarBuffer();

        esUnNumero(input, &resultadoValidacion);

        if (resultadoValidacion == 1)
        {
            ConfNum = atoi(input);
            if (ConfNum > 12 || ConfNum < 1)
            {
                resultadoValidacion = 0;
            }
        }
        else if (resultadoValidacion == 2)
        {

            ConfNum = (int)atof(input);
            resultadoValidacion = 1;
            if (ConfNum > 12 || ConfNum < 1)
            {
                resultadoValidacion = 0;
            }
        }
        else
        {
            printf("El valor ingresado no es coherente.\n");
            memset(input, 0, sizeof(input));
        }
    } while (resultadoValidacion != 1);
    int Mes = ConfNum;
    ConfNum = 0;
    resultadoValidacion = 0;
    memset(input, 0, sizeof(input));

    do
    {
        printf("Año(Ultimos 2 digitos) : ");
        scanf("%s", input);
        printf("\n");
        limpiarBuffer();

        esUnNumero(input, &resultadoValidacion);

        if (resultadoValidacion == 1)
        {
            ConfNum = atoi(input);
            if (ConfNum < 23 || ConfNum > 99)
            {
                resultadoValidacion = 0;
            }
        }
        else if (resultadoValidacion == 2)
        {

            ConfNum = (int)atof(input);
            resultadoValidacion = 1;
            if (ConfNum < 23 || ConfNum > 99)
            {
                resultadoValidacion = 0;
            }
        }
        else
        {
            printf("El valor ingresado no es coherente.\n");
            memset(input, 0, sizeof(input));
        }
    } while (resultadoValidacion != 1);
    int Ano = ConfNum;
    printf("%d", Ano);
    ConfNum = 0;
    resultadoValidacion = 0;
    memset(input, 0, sizeof(input));

    sprintf(Datos->FechaSalida, "%d/%d/ %d", Dia, Mes, Ano);
    limpiarBuffer();

    Datos->Activos = 1;
}

// Funcion para mostrar un mensaje de error en el menu.
void errorMenu()
{
    printf("xxxxxxxxxxxxxx Ingrese una opci�n valida xxxxxxxxxxxxxx\n");
}

// -------------- Buscador (Punto 7) --------------//
// Funci�n para buscar una propiedad por su ID.

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
// Funci�n para buscar propiedades por tipo de operaci�n y tipo de propiedad.
void buscarPorTipoOperacionYPropiedad(struct Alq_venta *Propiedades)
{
    char tipoOperacion[30];
    char tipoPropiedad[20];

    printf("Ingrese el tipo de operacion (Venta/Alquiler/Alquiler temporal): ");
    scanf(" %29[^\n]", tipoOperacion); // Leer tipo de operaci�n como cadena

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
// Funci�n para buscar por Activo
void buscarPorActivos(struct Alq_venta *Propiedades)
{
    int Activo = 1;
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
        if (propiedad.Activos == Activo)
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
        printf("No se encontro ningun activo.\n");
    }
}

// -------------- Menus --------------//
// Funci�n para mostrar el submen�.
void submenu(struct Alq_venta *Propiedades)
{
    printf("------------Sub-Menu------------\n");
    printf("1 - Listar Todos\n");
    printf("2 - Solo Campos Activos\n");
    printf("3 - Buscar por ID\n");
    printf("4 - Buscar por tipo de operacion y luego por tipo de propiedad\n");

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
        buscarPorActivos(Propiedades);
        break;
    case '3':
        buscarPorId(Propiedades);
        break;
    case '4':
        buscarPorTipoOperacionYPropiedad(Propiedades);
        break;
    default:
        errorMenu();
        break;
    }
}

// Funci�n para mostrar el men� principal.
void menu(struct Alq_venta *Alquiler_Ventas, int *PSalida)
{
    printf("--------------Menu--------------\n");
    printf("1 - Crear nuevo alta de propiedades\n");
    printf("2 - Mirar el Contenido del Archivo\n");
    printf("3 - Salida\n");

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
            fseek(Arch_Datos, (Alquiler_Ventas->Id - 1) * sizeof(struct Alq_venta), SEEK_SET);
            fwrite(Alquiler_Ventas, sizeof(struct Alq_venta), 1, Arch_Datos);

            if (Arch_Datos != NULL)
            {
                printf("Saliendo y guardando el archivo de datos\n");
                fclose(Arch_Datos);
            }
            break;
        case '2':
            submenu(Alquiler_Ventas);
            break;
        case '3':

            *PSalida = 1;
            break;
            /* case '4':
                 BorrarTodo();  //Habilitar funcion para reiniciar la tabla
                 break; */
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