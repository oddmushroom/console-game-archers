#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LARGOA 20
#define LARGOCI 8
#define CANTJ 10

typedef struct {
    char palabra[LARGOA];
    int largopalabra;
}cadena;

typedef struct {
    int doc[LARGOCI];
    int largodoc;
}documento;

typedef struct {
    int dia;
    int mes;
    int anio;
}fecha;

typedef struct {
    cadena nombre;
    cadena apellido;
    cadena alias;
    documento cedula;
    fecha fechanacimiento;
    char estado;
}jugador;

typedef struct {
    cadena alias1;
    cadena alias2;
    fecha fechapartida;
    int resultado;
}result;


char p1, p2;
int i1, i2, j1, j2;
int rondaj1=1, rondaj2=1;
char comienzo;
int activo;
char continuar;
void movimiento1(int dim, char matriz[dim][dim]);
void movimiento2(int dim, char matriz[dim][dim]);
void ponerXs(int dim, char matriz[dim][dim]);
void inicializar(int dim, char matriz[dim][dim]);
void mostrar(int dim, char matriz[dim][dim]);
void disparo1 (char direccion, int dim, char matriz [dim][dim]);
void disparo2 (char direccion, int dim, char matriz [dim][dim]);
void menu();
void sub();
void sumarresultado (result resultado[], int *pos, cadena auxalias1, cadena auxalias2, fecha auxfecha, int auxganador);
void muestroAlias1(cadena alias1);
void jugar(jugador jugadores[], int *posicion,result resultado[], int *pos);
int ingop();
char ingop2();
void altajugador(jugador jugadores[], int *posicion);
int buscoJugador(jugador jugadores[],int posicion, documento ced);
int buscoJugadores(jugador jugadores[], int posicion, cadena alias);
int comparoCedulas(documento c1,documento c2);
int comparoAlias(cadena a1,cadena a2);
char confirmaSN();
cadena ingresoAlias();
cadena ingresoAlias1();
cadena ingresoAlias2();
cadena ingresoNombre();
cadena ingresoApellido();
documento ingresoCedula();
fecha ingresoFechanacimiento();
void muestroCedula(documento cedula);
void muestroNombre(cadena nombre);
void muestroApellido(cadena apellido);
void muestroAlias(cadena alias);
void muestroFechanacimiento(fecha fechanac);
void listado(jugador jugadores[], int posicion);
void listadopartida(result resultado[], int pos);
void listadojugador(result resultado[], int pos);
int main()
{
    jugador jugadores[CANTJ];
    result resultado[10];
    int opcion;
    int opcion2;
    int opcion3;
    int posicion = 0;
    int pos = 0;
    menu();
    opcion = ingop();
    while (opcion != 4)
    {
        switch(opcion)
        {
            case 1:
                sub();
                opcion2 = ingop();
                    switch(opcion2)
                    {
                    case 1:
                        altajugador(jugadores, &posicion);
                        break;
                    case 3:
                        modifico(jugadores, posicion);
                        break;

                    }
                break;
        case 2:
            sub2();
            opcion3 = ingop();
                switch(opcion3)
                {
                case 1:
                    listado(jugadores, posicion);
                    break;
                case 2:
                    listadopartida(resultado, pos);
                    break;
                case 3:
                    listadojugador(resultado, pos);
                    break;
                }
            break;
        case 3:
            jugar(jugadores, posicion , resultado, &pos);
            break;
}
menu();
opcion=ingop();
}
}



void inicializar(int dim, char matriz[dim][dim])
{
    int i, j;
    for(i=0;i<dim;i++)
    {
        for(j=0;j<dim;j++)
        {
            matriz[i][j] = ' ';
        }
    }
}

void ponerXs(int dim, char matriz[dim][dim])
{
    int contador = 0;
    do
    {
        int i, j;
        i = rand() % dim;
        j = rand() % dim;
            if(matriz[i][j]== ' ')
            {
            matriz[i][j] = 'X';
            contador++;
            }
    }
    while(contador<dim);
}

void mostrar(int dim, char matriz[dim][dim])
{
    int i, j;
    for(i=0;i<dim;i++)
    {
        for(j=0;j<dim;j++)
        {
            printf("| %c ", matriz[i][j]);
        }
        printf("|\n");
    }
}

void movimiento1(int dim, char matriz[dim][dim])
{
    char move;
    int itemp, jtemp;
    printf ("Ingrese movimiento del jugador %c \n  w (arriba), a (izquierda), s (abajo), d (derecha)\n  i (disparo arriba)     k (disparo abajo)\n  j (disparo izquierda)  l (disparo derecha)\n  r (rendirse)",p1);
    scanf(" %c", &move);
        switch(move)
        {
            case 'w':
                itemp=i1-1;
                jtemp=j1;
                break;
            case 'a':
                itemp=i1;
                jtemp=j1-1;
                break;
            case 's':
                itemp=i1+1;
                jtemp=j1;
                break;
            case 'd':
                itemp=i1;
                jtemp=j1+1;
                break;
            case 'i':
                itemp=i1;
                jtemp=j1;
                disparo1('i',dim,matriz);
                break;
            case 'k':
                itemp=i1;
                jtemp=j1;
                disparo1('k',dim,matriz);
                break;
            case 'j':
                itemp=i1;
                jtemp=j1;
                disparo1('j',dim,matriz);
                break;
            case 'l':
                itemp=i1;
                jtemp=j1;
                disparo1('l',dim,matriz);
                break;
            case 'r':
                itemp=i1;
                jtemp=j1;
                disparo1('r',dim,matriz);

                break;
            default:
        itemp = -1;
        }
    if (itemp >= 0 && itemp < dim  && jtemp >= 0 && jtemp < dim && matriz[itemp][jtemp] != 'X' && matriz[itemp][jtemp] != p2)
    {
        matriz[i1][j1]= ' ';
        i1=itemp;
        j1=jtemp;
        matriz[i1][j1]= p1;
    }
    else
    {
        printf ("Movimiento no valido\n");
        movimiento1(dim,matriz);
    }
}

void movimiento2(int dim, char matriz[dim][dim])
{
    char move;
    int itemp, jtemp;
    printf ("Ingrese movimiento del jugador %c \n  w (arriba), a (izquierda), s (abajo), d (derecha)\n  i (disparo arriba)     k (disparo abajo)\n  j (disparo izquierda)  l (disparo derecha)\n  r (rendirse)",p2);
    scanf(" %c", &move);
        switch(move)
        {
            case 'w':
                itemp=i2-1;
                jtemp=j2;
                break;
            case 'a':
                itemp=i2;
                jtemp=j2-1;
                break;
            case 's':
                itemp=i2+1;
                jtemp=j2;
                break;
            case 'd':
                itemp=i2;
                jtemp=j2+1;
                break;
            case 'i':
                itemp=i2;
                jtemp=j2;
                disparo2('i',dim,matriz);
                break;
            case 'k':
                itemp=i2;
                jtemp=j2;
                disparo2('k',dim,matriz);
                break;
            case 'j':
                itemp=i2;
                jtemp=j2;
                disparo2('j',dim,matriz);
                break;
            case 'l':
                itemp=i2;
                jtemp=j2;
                disparo2('l',dim,matriz);
                break;
            case 'r':
                itemp=i2;
                jtemp=j2;
                disparo2('r',dim,matriz);
                break;
        default:
        itemp = -1;
        }
    if (itemp >= 0 && itemp < dim  && jtemp >= 0 && jtemp < dim && matriz[itemp][jtemp] != 'X' && matriz[itemp][jtemp] != p1)
    {
        matriz[i2][j2]= ' ';
        i2=itemp;
        j2=jtemp;
        matriz[i2][j2]= p2;
    }
    else
    {
        printf ("Movimiento no valido\n");
        movimiento2(dim,matriz);
    }
}

void disparo1 (char direccion, int dim, char matriz [dim][dim])
{
    switch(direccion)
    {
        case 'i':
        for(int i=i1-1; i >= 0 && i >= i1-5; i--)
            {
                 if(matriz[i][j1] == p2)
                 {
                    i = -1;
                    printf ("\nEL JUGADOR %c GANA LA RONDA\n\n", p1);
                    activo = 0;
                    if(comienzo=='1')
                    {
                    rondaj1++;
                    }
                    else
                    {
                    rondaj2++;
                    }
                }
                else
                {
                    if(matriz[i][j1] != ' ')
                    {
                    i = -1;
                    }

                }
            }
        break;
        case 'k':
            for(int i=i1+1; i <=dim-1 && i <= i1+5; i++)
            {
                if(matriz[i][j1] == p2)
                {

                    i = 500;
                    printf ("\nEL JUGADOR %c GANA LA RONDA\n\n", p1);
                    activo = 0;
                    if(comienzo=='1')
                    {
                    rondaj1++;
                    }
                    else
                    {
                    rondaj2++;
                    }
                }
                else
                {
                    if(matriz[i][j1] == 'X'){
                        i= 500;
                    }
                }
            }
        break;
        case 'j':
            for(int j=j1-1; j >=0 && j >= j1-5; j--)
            {
                if(matriz[i1][j] == p2)
                {

                    j = -1;
                    printf ("\nEL JUGADOR %c GANA LA RONDA\n\n", p1);
                    activo = 0;
                    if(comienzo=='1')
                    {
                    rondaj1++;
                    }
                    else
                    {
                    rondaj2++;
                    }
                }
                else
                {
                    if(matriz[i1][j] != ' ')
                    {
                        j= -1;
                    }
                }
            }
        break;
        case 'l':
            for(int j=j1+1; j <=dim-1 && j <= j1+5; j++)
            {
                if(matriz[i1][j] == p2)
                {

                    j = 500;
                    printf ("\nEL JUGADOR %c GANA LA RONDA\n\n", p1);
                    activo = 0;
                    if(comienzo=='1')
                    {
                    rondaj1++;
                    }
                    else
                    {
                    rondaj2++;
                    }
                }
                else
                {
                    if(matriz[i1][j] != ' ')
                    {
                        j= 500;
                    }
                }
            }
        break;
        case 'r':
            printf ("\nEL JUGADOR %c GANA LA RONDA\n\n", p2);
            if(comienzo=='1')
            {
                rondaj2++;
                activo = 0;
            }
            else{
                rondaj1++;
                activo = 0;
            }
        break;
    }

}

void disparo2 (char direccion, int dim, char matriz [dim][dim])
{
    switch(direccion)
    {
        case 'i':
        for(int i=i2-1; i >= 0 && i >= i2-5; i--)
            {
                 if(matriz[i][j2] == p1)
                 {

                    i = -1;
                    printf ("\nEL JUGADOR %c GANA LA RONDA\n\n", p2);
                    activo = 0;
                    if(comienzo=='1')
                    {
                    rondaj2++;
                    }
                    else
                    {
                    rondaj1++;
                    }
                }
                else
                {
                    if(matriz[i][j2] != ' ')
                    {
                    i = -1;
                    }

                }
            }
        break;
        case 'k':
            for(int i=i2+1; i < dim && i <= i2+5; i++)
            {
                if(matriz[i][j2] == p1)
                {

                    i = 500;
                    printf ("\nEL JUGADOR %c GANA LA RONDA\n\n", p2);
                    activo = 0;
                    if(comienzo=='1')
                    {
                    rondaj2++;
                    }
                    else
                    {
                    rondaj1++;
                    }
                }
                else
                {
                    if(matriz[i][j2] != ' '){
                        i= 500;
                    }
                }
            }
        break;
        case 'j':
            for(int j=j2-1; j >=0 && j >= j2-5; j--)
            {
                if(matriz[i2][j] == p1)
                {

                    j = -1;
                    printf ("\nEL JUGADOR %c GANA LA RONDA\n\n", p2);
                    activo = 0;
                    if(comienzo=='1')
                    {
                    rondaj2++;
                    }
                    else
                    {
                    rondaj1++;
                    }
                }
                else
                {
                    if(matriz[i2][j] != ' ')
                    {
                        j= -1;
                    }
                }
            }
        break;
        case 'l':
            for(int j=j2+1; j <=dim-1 && j <= j2+5; j++)
            {
                if(matriz[i2][j] == p1)
                {

                    j = 500;
                    printf ("\nEL JUGADOR %c GANA LA RONDA\n\n", p2);
                    activo = 0;
                    if(comienzo=='1')
                    {
                    rondaj2++;
                    }
                    else
                    {
                    rondaj1++;
                    }
                }
                else
                {
                    if(matriz[i2][j] != ' ')
                    {
                        j= 500;
                    }
                }
            }
        break;
        case 'r':
            printf ("\nEL JUGADOR %c GANA LA RONDA\n\n", p1);
            if(comienzo=='1')
            {
                rondaj1++;
                activo = 0;
            }
            else{
                rondaj2++;
                activo = 0;
            }
        break;
    }
}

void menu()
{
    system("clear");
    printf("MENU PRINCIPAL\n");
    printf("==============\n\n");
    printf("1-Gestionar usuario\n");
    printf("2-Consultas\n");
    printf("3-Jugar\n");
    printf("4-Salir\n");
}

void sub()
{
    system("clear");
    printf("SUBMENU\n");
    printf("==============\n\n");
    printf("1-Alta jugador\n");
    printf("2-Baja jugador\n");
    printf("3-Modificar jugador\n");
    printf("4-Volver\n");
}

void sub2()
{
    system("clear");
    printf("SUBMENU\n");
    printf("==============\n\n");
    printf("1-Listado de jugadores\n");
    printf("2-Listado de todas las partidas\n");
    printf("3-Listado de partidas por jugador\n");
    printf("4-Volver\n");
}

int ingop()
{
    int op;
    do
    {
        printf("Ingrese Opción (1-4)");
        scanf("%d",&op);
    }
    while ((op < 1) || (op > 4));
    getchar();
    return op;
}

void altajugador(jugador jugadores[], int *posicion)
{
    int i=0;
    int f=0;
    int x=0;
    char confirma;
    documento auxci;
    fecha auxfecha;
    cadena auxnombre;
    cadena auxapellido;
    cadena auxalias;


    system("clear");
    printf("\nINGRESE DATOS DEL JUGADOR");
    auxci = ingresoCedula();
    i = buscoJugador(jugadores, *posicion,auxci);
    if (i != -1) {
        printf ("\nJugador ya existente");
        getchar();
        return x = -1;
    }
    auxalias = ingresoAlias();
    f = buscoJugadores(jugadores, *posicion,auxalias);
    if (f != -1) {
        printf ("\nJugador ya existente");
    }
    else{
        auxnombre = ingresoNombre();
        auxapellido = ingresoApellido();
        auxfecha = ingresoFechanacimiento();
        getchar();
        confirma = confirmaSN();
        if (confirma == 'S' || confirma == 's')
        {
            jugadores[*posicion].cedula = auxci;
            jugadores[*posicion].alias = auxalias;
            jugadores[*posicion].nombre = auxnombre;
            jugadores[*posicion].apellido = auxapellido;
            jugadores[*posicion].fechanacimiento = auxfecha;
            jugadores[*posicion].estado = 'A';
            *posicion = *posicion +1;
        }
        else{
            getchar();
            printf("\nNo se ingreso el Jugador");
            printf("\nPresione Enter para proceder");
        }
    }

    getchar();
    x = -1;
}

documento ingresoCedula()
{
    int i=0;
    documento ced;
    printf("\nIngrese Cedula del Jugador (solo 8 digitos): ");
    while (((ced.doc[i]=getchar())!= 10) && (i < LARGOCI))
    {
        ced.doc[i] = ced.doc[i]-48;
        i++;
    }

    ced.largodoc = i;
    return ced;
}

int buscoJugador(jugador jugadores[],int posicion, documento ced) {
    int i;
    for (i = 0;i<posicion;i++)
    {
        if (comparoCedulas(jugadores[i].cedula,ced) == 0) {
                return i;
        }
    }
    return -1;
}


int buscoJugadores(jugador jugadores[],int posicion, cadena alias) {
    int i;
    for (i = 0;i<posicion;i++)
    {
        if (comparoAlias(jugadores[i].alias,alias) == 0) {
                return i;
        }
    }
    return -1;
}


cadena ingresoAlias()
{
    cadena ali;
    int i;
    i = 0;
    printf("\nIngrese alias del Jugador: ");
    while ((i < LARGOA && (ali.palabra[i]=getchar()) != '\n'))
    {
            i++;
    }
    ali.largopalabra = i;
    return ali;
}

cadena ingresoNombre()
{
    cadena nom;
    int i;
    i = 0;
    printf("\nIngrese nombre del Jugador: ");
    while ((i < LARGOA && (nom.palabra[i]=getchar()) != '\n'))
    {
            i++;
    }
    nom.largopalabra = i;
    return nom;
}

cadena ingresoApellido()
{
    cadena ape;
    int i;
    i = 0;
    printf("\nIngrese apellido del Jugador: ");
    while ((i < LARGOA && (ape.palabra[i]=getchar()) != '\n'))
    {
            i++;
    }
    ape.largopalabra = i;
    return ape;
}

fecha ingresoFechanacimiento()
{
    fecha fechanac;
    int z1, z2;
    do
    {
    z1=0, z2=0;
    printf("\n >>> Fecha de nacimiento del jugador <<< ");
    printf("\n > Ingrese dia: ");scanf("%d", &fechanac.dia);getchar();
    printf(" > Ingrese mes: ");scanf("%d", &fechanac.mes);getchar();
    printf(" > Ingrese anio: ");scanf("%d", &fechanac.anio);getchar();
    if(fechanac.mes>=1 && fechanac.mes<=12)
    {
        switch (fechanac.mes)
        {
            case  1 :
            case  3 :
            case  5 :
            case  7 :
            case  8 :
            case 10 :
            case 12 : if (fechanac.dia>=1&&fechanac.dia<=31){
                        z1=0;
                        }
                        else
                            {z1=-1;}
                      break;

            case  4 :
            case  6 :
            case  9 :
            case 11 : if (fechanac.dia>=1 && fechanac.dia<=30){
                        z1=0;
                        }
                        else
                            {z1=-1;}
                      break;
            case  2 : if (fechanac.dia>=1 && fechanac.dia<=28){
                        z1=0;
                        }
                        else
                            {z1=-1;}
                      break;
        }
    }
    else
    {
    z2=-1;
    }

    if((z1!=0)||(z2!=0))
    {
            printf("\nFecha invalida, vuelva a intentarlo.\n");
    }
}
    while((z1!=0)||(z2!=0));
    return fechanac;
}


fecha ingresoFechaPartida()
{
    fecha fechapartida;
    printf("\nIngrese Fecha de partida dd/mm/aaaa: ");
    scanf("%d/%d/%d",&fechapartida.dia,&fechapartida.mes, &fechapartida.anio );

    return fechapartida;
}

char confirmaSN(){
    char conf;
    do{
        printf("Confirma S/N: ");
        scanf(" %c",&conf);
    }
    while (conf !='S' &&  conf != 's' && conf != 'N' && conf != 'n');
    return conf;
}

int comparoCedulas(documento c1,documento c2){
    int i;
    int iguales=0;
    if (c1.largodoc != c2.largodoc)
        return 1;
    for (i=0;i<c1.largodoc;i++) {
        if(c1.doc[i]==c2.doc[i])
            iguales++;
    }
    if (iguales == c1.largodoc)
        return 0;
    else
        return 1;
}

int comparoAlias(cadena a1,cadena a2){
    int i;
    int iguales=0;
    if (a1.largopalabra != a2.largopalabra)
        return 1;
    for (i=0;i<a1.largopalabra;i++) {
        if(a1.palabra[i]==a2.palabra[i])
            iguales++;
    }
    if (iguales == a1.largopalabra)
        return 0;
    else
        return 1;
}

void modifico(jugador jugadores[], int posicion){
    system("clear");
    int i;
    char confirma;
    documento auxci;
    cadena auxnombre;
    cadena auxapellido;
    cadena auxalias;
    fecha auxfecha;
    printf("\nMODIFICACION DATOS DE JUGADOR");
    printf("\n==========================\n");
    if (posicion == 0)
        printf("No se han ingresado jugadores.");
    else
    {
        auxalias = ingresoAlias();
        i = buscoJugadores(jugadores,posicion,auxalias);
        if ( i == -1) {
             printf("\nJugador no existente");
        }
        else {
            if (jugadores[i].estado == 'A')
            {
                    printf("\nDatos del jugador nro. %d ",i+1);
                    printf("\nNombre: ");
                    muestroNombre(jugadores[i].nombre);
                    printf("\nApellido:");
                    muestroApellido(jugadores[i].apellido);
                    printf("\nAlias:");
                    muestroAlias(jugadores[i].alias);
                    printf("\nCedula: ");
                    muestroCedula(jugadores[i].cedula);
                    printf("\nFecha Nacimiento: ");
                    muestroFechanacimiento(jugadores[i].fechanacimiento);
                    confirma = confirmaSN();
                    if ((confirma == 'S') || (confirma == 's'))
                    {
                        getchar();
                        auxnombre = ingresoNombre();
                        auxapellido = ingresoApellido();
                        auxci = ingresoCedula();
                        auxfecha = ingresoFechanacimiento();
                        getchar();
                        confirma = confirmaSN();
                        if (confirma =='S' || confirma == 's')
                        {
                            jugadores[i].nombre = auxnombre;
                            jugadores[i].apellido = auxapellido;
                            jugadores[i].cedula = auxci;
                            jugadores[i].fechanacimiento = auxfecha;
                        }
                        else
                        {
                            printf("No se Confirmo modificacion de datos");
                        }
                    }
                    else
                    {
                        printf("NO se Modifico datos");

                    }
                    i = posicion;
                }
                else
                {
                    printf("Paciente no Activo");
                }
            }
    }
    printf("\nPresione Enter para continuar");
    getchar();
}

void muestroCedula(documento auxci)
{
    int i;
    for (i=0;i<auxci.largodoc;i++)
    {
        printf("%d",auxci.doc[i]);
    }
}

void muestroNombre(cadena auxnombre)
{
    int i;

    for (i=0;i<auxnombre.largopalabra;i++)
    {
        printf("%c",auxnombre.palabra[i]);
    }
}

void muestroApellido(cadena auxapellido)
{
    int i;

    for (i=0;i<auxapellido.largopalabra;i++)
    {
        printf("%c",auxapellido.palabra[i]);
    }
}

void muestroAlias(cadena auxalias)
{
    int i;

    for (i=0;i<auxalias.largopalabra;i++)
    {
        printf("%c",auxalias.palabra[i]);
    }
}

void muestroFechanacimiento(fecha auxfec)
{
    printf ("%d/%d/%d\n",auxfec.dia, auxfec.mes,auxfec.anio);
}

void listado(jugador jugadores[], int posicion){
int i;
system("clear");
printf("\nLISTADO DE JUGADORES ORDENADOS POR NOMBRE");
printf("\n=========================================\n\n");
if (posicion == 0)
        printf("No se han ingresado jugadores.");
else
{
    printf("Nro.-> Cedula -> Alias -> Nombre -> Apellido -> Fecha Nacimiento\n\n");
    for(i=0;i < posicion;i++)
    {
        if (jugadores[i].estado == 'A')
        {
            printf("%d -> ",i+1);
            muestroCedula(jugadores[i].cedula);
            printf(" -> ");
            muestroAlias(jugadores[i].alias);
            printf(" -> ");
            muestroNombre(jugadores[i].nombre);
            printf(" -> ");
            muestroApellido(jugadores[i].apellido);
            printf(" -> ");
            muestroFechanacimiento(jugadores[i].fechanacimiento);
            printf("\n");
        }
    }
}
printf("\nPresione Enter para continuar");
getchar();
}

cadena ingresoAlias1()
{
    cadena ali1;
    int i;
    i = 0;
    printf("\nIngrese alias del Jugador 1: ");
    while ((i < LARGOA && (ali1.palabra[i]=getchar()) != '\n'))
    {
            i++;
    }
    ali1.largopalabra = i;
    return ali1;
}

cadena ingresoAlias2()
{
    cadena ali2;
    int i;
    i = 0;
    printf("\nIngrese alias del Jugador 2: ");
    while ((i < LARGOA && (ali2.palabra[i]=getchar()) != '\n'))
    {
            i++;
    }
    ali2.largopalabra = i;
    return ali2;
}

void sumarresultado (result resultado[], int *pos, cadena auxalias1, cadena auxalias2, fecha auxfecha, int auxganador){

    resultado[*pos].alias1 = auxalias1;
    resultado[*pos].alias2 = auxalias2;
    resultado[*pos].fechapartida = auxfecha;
    resultado[*pos].resultado = auxganador;
    *pos = *pos + 1;

}

void listadopartida(result resultado[], int pos){
int i;
system("clear");
printf("\nLISTADO DE PARTIDAS");
printf("\n=========================================\n\n");
if (pos == 0){
        printf("No se han jugado partidas.");
}
else
{
    printf("Nro.-> Alias 1 -> Alias 2 -> Fecha de partida \n\n");
    for(i=0;i < pos;i++)
    {
            printf("%d -> ",i+1);
            muestroAlias1(resultado[i].alias1);
            printf(" -> ");
            muestroAlias2(resultado[i].alias2);
            printf(" -> ");
            muestroFechaPartida(resultado[i].fechapartida);
            printf(" -> ");
            printf("El ganador es el jugador %d",resultado[i].resultado);
            printf("\n");


    }
}
printf("\nPresione Enter para continuar");
getchar();
}

void muestroAlias1(cadena auxalias1)
{
    int i;

    for (i=0;i<auxalias1.largopalabra;i++)
    {
        printf("%c",auxalias1.palabra[i]);
    }
}

void muestroAlias2(cadena auxalias2)
{
    int i;

    for (i=0;i<auxalias2.largopalabra;i++)
    {
        printf("%c",auxalias2.palabra[i]);
    }
}

void muestroFechaPartida(fecha auxfechapartida)
{
    printf ("%d/%d/%d\n",auxfechapartida.dia,auxfechapartida.mes,auxfechapartida.anio);
}

void listadojugador(result resultado[], int pos){
    cadena alias;
    alias = ingresoAlias();
    result list[10];
    int k=0;
    int i;

    for(i=0;i <= pos;i++)
    {
       if((comparoAlias(resultado[i].alias1,alias)==0) || (comparoAlias(resultado[i].alias2,alias)==0)){
                list[k].alias1=resultado[i].alias1;
                list[k].alias2=resultado[i].alias2;
                list[k].fechapartida=resultado[i].fechapartida;
                list[k].resultado=resultado[i].resultado;
                k++;
            }

    }
    listadopartida(list, k);
}

void jugar(jugador jugadores[], int *posicion, result resultado[], int *pos){
    do{
    int f = 0;
    cadena auxalias1;
    cadena auxalias2;
    fecha auxfecha;
    int auxganador=0;
    rondaj1=1;
    rondaj2=1;
    auxalias1 = ingresoAlias1();
    f = buscoJugadores(jugadores, posicion, auxalias1);
    while (f == -1) {
        printf ("Alias no existente");
        auxalias1 = ingresoAlias1();
        f = buscoJugadores(jugadores, posicion, auxalias1);
        }
    auxalias2 = ingresoAlias2();
    f = buscoJugadores(jugadores, posicion, auxalias2);
    while (f == -1) {
        printf ("Alias no existente");
        auxalias2 = ingresoAlias2();
        f = buscoJugadores(jugadores, posicion, auxalias2);
        }
    auxfecha = ingresoFechaPartida();
    while(rondaj1!=3 && rondaj2!=3)
    {
    srand(time(NULL));
    int dim;
    printf("Ingrese la dimension del mapa\n\t5: Partida corta (5x5)\n\t7: Partida media (7x7)\n\t9: Partida larga (9x9): ");
    scanf("%d", &dim);
    while(dim != 5 && dim != 7 && dim != 9)
    {
        printf("Dimension invalida, vuelva a intentarlo: ");
        scanf("%d", &dim);
    }
    char matriz[dim][dim];
    inicializar(dim, matriz);
    getchar();
    printf("Ingrese el jugador que empieza (1 o 2): ");
    scanf("%c", &comienzo);
    if(comienzo!='1'&&comienzo!='2')
    {
    do
    {
        printf("Comienzo invalido, vuelva a intentarlo: ");
        scanf(" %c", &comienzo);
    }
    while(comienzo != '1' && comienzo != '2');
    }
    if (comienzo == '1')
    {
        i1= dim-1;
        i2=0;
        j1=0;
        j2= dim-1;
        p1= '1';
        p2= '2';
    }
    else
    {
        i1=0;
        i2=dim - 1;
        j1=dim - 1;
        j2=0;
        p1='2';
        p2='1';

    }
    matriz [i1][j1] = p1;
    matriz [i2][j2] = p2;
    do{
    ponerXs(dim, matriz);
    }
    while((matriz[dim-2][0]=='X'&&matriz[dim-1][1]=='X')||(matriz[0][dim-2]=='X'&&matriz[1][dim-1]=='X'));
    mostrar(dim, matriz);
    activo = 1;
    while (activo)
    {
        movimiento1(dim, matriz);
        if (activo == 0)
        {
        break;
        }
        mostrar(dim, matriz);
        movimiento2(dim, matriz);
        mostrar(dim, matriz);
    }
    }
    if((rondaj1 == 3))
    {
    printf(" ------ EL JUGADOR 1 ES EL VENCEDOR ------ ");
    auxganador = 1;
    }
    else
    {
    printf(" ------ EL JUGADOR 2 ES EL VENCEDOR ------ ");
    auxganador = 2;
    }
    sumarresultado(resultado, pos, auxalias1, auxalias2, auxfecha, auxganador);
    printf("DESEA SEGUIR JUGANDO?\n\ts = si \n\tn = no : ");
    scanf(" %c", &continuar);
    while(continuar!='s'&&continuar!='S'&&continuar!='n'&&continuar!='N')
    {
    printf("Error, ingrese nuevamente:  ");
    scanf(" %c", &continuar);
    }
    }
    while(continuar == 's' || continuar == 'S');
    return 0;
}