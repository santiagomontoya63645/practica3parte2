#include <fstream>
#include <iostream>
#include <string>
#include <math.h>
// para ingresar como administrador debes darle en la opcion  ingresar al a sistema y cuando te pida el usuario ingresar administrador, luego te pide la clave que es 1234
//la clave de administrador es 1234 y la cuenta de administrador es administrador
//pd el archivo usando es un archivo temporal donde se realizaran cambios de las demas cuentas y posteriormente se guardaran en dichas cuentas
//se esta encryptando y desencryptando con el metodo 2 con semilla 4
// muchas de las funciones se explican solas con el nombre
//este archivo debe eestar en una una carpeta llamada practica3parte2
// el dinero debe ser representado hasta con un maximo de 8 bits
//todos los archivos cuando se crean cuando se modifica el dinero se realizan los cambios y luego se procede a encryptarlos
//la unica manera de verificar los cambios es atravez del cmd cuando se aumenta o se disminuye el dinero
//todos los aarchivos de los ususarios estan encryptados



//recalco esto este archivo debe eestar en una una carpeta llamada practica3parte2
using namespace std;
string recogerunalinea(int linea, string a);
bool verificador(string clave,string claveingresada);
void deco_metodo2(int semilla, string nombre);
void crearusuario();
void leer_archivo(char *contenido,string b); //se leera el archivo usando y se llevara todo su contenido a contenido
void convertircadena(int *entero,char *contenido);// convierte todos lo caracteres que hay en contenido a su valor en ascii y los guarda en entero
void siste_binario(char *binario,int *entero);
void metodo2(char *binario,int semilla, string b);
void modificardinero(string descision);
void retirardinero(string usuario);
void aumentardinero(string usuario);
bool ingresarcomousuario(string a);
void versaldo(string usuario);
int main()
{
    string clave;
    string a,clavedecod,salida;
    int opcion=0,opcion2=0,opcion3=0;
    bool claveverif=false,f=true,usuario=false;
    while(f==true){
        while(opcion2!=2){//opcion 2 determinara si se apaga el sistema o si desea ingresar usuario
          cout<<"ingrese 1 si desea ingresar al sistema"<<endl<<"2 si desea salir"<<endl;cin>>opcion2;
          switch (opcion2) {
          case 2:
              return 0;
          case 1:
              cout<<"ingrese usuario "<<endl;cin>>a;//ingrese administrador si quieres entrar como tal
              if(a=="administrador"){
                  claveverif=false;
                  while(claveverif==false){
                      a="sudo";
                      cout<<"ingrese clave de admin"<<endl;cin>>clave;

                      deco_metodo2(4,a);// decodifica el archivo sudo
                      clavedecod=recogerunalinea(0,"usando");// abre el archivo usando y recoge la contraseña para compararla
                      remove("../practica3parte2/BD/usando");
                      claveverif=verificador(clave,clavedecod);
                      if(claveverif==false){//cave de administrador que ingreso esta incorrecta
                          cout<<"clave incorrecta"<<endl;
                      }
                  }
                  while (claveverif==true){

                      while(opcion!=3){//opciones del administrador
                          cout<<"ingrese 1 si quiere crear usuarios"<<endl<<"2 si el usuario desea recargar"<<endl<<"3 para cerrar seccion"<<endl;//puedes poner 4 para salir f=false
                          cin>>opcion;
                          switch (opcion) {
                          case 1:
                              crearusuario();// omg que hace esto? solo diosito y chuck norrys lo sabran (sarcasmo)
                              break;
                          case 2:

                              modificardinero("admin");//se usa para recargar las cuentas
                              break;
                          }

                      }
                      opcion=0;

                      claveverif=false;//poner despues de esto si se desea sali del sistema
                  }

              }
              else{

                  usuario=ingresarcomousuario(a);//poner los cassos de mirar saldo o retirar saldoo errar seccion
                  opcion3=0;
                  if (usuario==true){
                      while(opcion3!=3){
                          cout<<"ingrese 1 si desea ver su saldo"<<endl<<"ingrese 2 si desea retirar dinero"<<endl<<"ingrese 3 para cerrar seccion"<<endl;
                          cin>>opcion3;
                          cout<<endl<<endl<<endl<<endl<<endl;
                          switch (opcion3) {//aca el usuario escoge que desea hacer
                            case 1:
                              versaldo(a);
                              break;
                            case 2:
                              modificardinero(a);
                              break;

                          }

                      }
                  }
                  f=false;

                  remove("usando");//como aca se realizaron cambios y despues se codifico eliminamos este achivo

              }
          }
        }
    }
}
void deco_metodo2(int semilla,string nombre){
    string codificado;
    string bloques,nombresalida="usando";
    string prueba="../practica3parte2/BD/";
    string auxprueba=prueba;
    prueba+=nombre;
    ifstream leer;
    leer.open(prueba);
    if(leer.is_open()){
        getline(leer,codificado);
    }
    else {
        cout<<"el archivo no existe"<<endl;
        }
   leer.close();

   string decodificado=codificado;
   int size=codificado.length();
   char chartem;

   for (int i=0;i<=size-semilla;i=i+semilla) {
       bloques=codificado.substr(i,semilla);//Extrae del string codificado los #semilla primeros caracteres desde la posicion i
       for (int b=0;b < semilla-1;b++){//El primer valor del bloque queda al final y los otros se corren a la izquierda
           chartem=bloques[b];
           bloques[b]=bloques[b+1];
           bloques[b+1]=chartem;
       }
       for (int b=i,c=0;b < i+semilla;c++,b++) {
           decodificado[b]=bloques[c];
       }
   }

   //Vamos a cambiar de binario a ascii

   string texto=decodificado;//Creo otro string donde se guardara los caracteres

   for (int i=0,a=0;i<size;i=i+8,a++) {
       bloques=decodificado.substr(i,8);
       int expdos=1,sum=0;
       for (int e=7;e>=0;e--) {
           if(bloques[e]=='1'){
               sum=sum+expdos;
           }
           expdos=expdos*2;
       }
       texto[a]=sum;
   }

   texto.resize(size/8);//Redefinimos el tamaño del texto donde me quede solo los caracteres ya que hay size/8 caracteres
   auxprueba+=nombresalida;
   ofstream escribir;//Enviamos lo decodificado al archivo fuente2.txt
   //prueba+="decodificado.txt";
   escribir.open(auxprueba);
   escribir<<texto;
   escribir.close();

}
bool verificador(string clave,string clavedecod){ //verificador de claves

    if (clave==clavedecod){
        return true;
    }
    else{
        return false;
    }
}
string recogerunalinea(int linea, string a){//retorna una linea en especifico del archivo a
    string cadena,contrasenaverdadera,prueba="../practica3parte2/BD/";
    prueba+=a;
    int contador=0;
    ifstream leer;
    leer.open(prueba);
    if(leer.is_open()){
        while(getline(leer,cadena)){
            if (contador==linea){ //guardo la linea que quiero retornar
                contrasenaverdadera=cadena;

            }
            contador++;
        }
    }
    leer.close();//agregado nuevo probar denuevo
    return contrasenaverdadera;
}
void crearusuario(){
    // como su nombre lo dice crea usuarios y codifica la contraseña y saldo de los usuaios creados
    // no necesite ningun dato de entrada, lo que hace es crear una carpeta que tiene de nombre el nombre del usuario que deseas crear
    // en b:se ingresa si para crear si ingresa no sale de esta funcion, si ingresa otro caracter volvera a preguntar
    string a,b,z,saldoinicial;
    string prueba="../practica3parte2/BD/";
    while (true){
        cout<<"desea crear usuario?(ingrese si para crear o no para salir de esta opcion)"<<endl;cin>>a;
        if (a=="no"){
            break;
        }
        else if (a=="si"){
            cout<<"ingrese el nombre del usuario"<<endl;cin>>b;
            b=prueba+b;
            ofstream escribir;
            escribir.open(b);
            cout<<"ingrese contrasena"<<endl;cin>>z;
            escribir<<z;
            escribir<<"\n";
            escribir<<"saldo:\n";
            cout<<"ingrese saldo inicial"<<endl;cin>>saldoinicial;
            escribir<<saldoinicial;
            escribir.close();
            char contenido[10000]={};//variables necesarias para la codificacion
            int entero[10000]={};//
            char binario[80000]={};
            leer_archivo(contenido,b);//ya fue explicado al inicio del archivo
            convertircadena(entero,contenido);
            siste_binario(binario,entero);
            metodo2(binario,4,b);
        }
    }
}
void convertircadena(int *entero,char *contenido){
   int k=0;
   char *p=contenido;
   while (*(p++)!='\0')k++;	//longitud de la cadena
   for (int i=0;i<k;i++){
       *(entero+i)=*(contenido+i);	//conversion a entero
   }
}
void leer_archivo(char *contenido, string b){
string nombre_arch=b;
char linea[10000]={};
int posicion=0;
ifstream leer;
         leer.open(nombre_arch);
         if(leer.is_open()){
             while(!leer.eof()){ //si llega a fin del archivo me retorna false
             int sizelinea=0;
             leer.getline(linea,100);//Solo me esta leyendo la ultima linea
             while (*(linea+sizelinea)!='\0') sizelinea++;
             for (int i=posicion, b=0;i<posicion+sizelinea;i++,b++) {
                 *(contenido+i)=*(linea+b);                  //concactenamos liea por linea en el chart
             }
             *(contenido+posicion+sizelinea)='\n';
             posicion+=sizelinea+1;
             }
         }
         else {
             cout<<"el archivo no existe."<<endl;
         }
        leer.close();
}
void siste_binario(char *binario,int *entero){
    int dividendo=0, resto=0, divisor = 2,i=7,k=0,aux=0,iaux=7;
    int *p=entero;
    while (*(p++)!='\0')k++;	//longitud de la cadena
    for (int j=0;j<k;j++){
        dividendo = entero[j];
        aux=dividendo;
        while(dividendo >= divisor){ //Mientras el dividendo sea mayor o igual que el divisor, es decir, mayor o igual que 2.
            resto = dividendo % 2;
            if(resto == 1){
                 *(binario+i)= 49; //Si el resto es igual a 1 concatenamos 1 a la variable char llamada binario
            }
            else{
                *(binario+i)= 48; // Sino concatemanos 0
            }

              dividendo = dividendo/divisor; // Actualizamos el valor del dividendo dividiendolo entre 2.
              i--;
        }
             if(dividendo == 1){
              *(binario+i)= 49; // Por último sí el valor final del dividendo es 1 concatenamos 1 sino concatenamos 0.
             }
             else {
              *(binario+i)= 48;
             }
             for(int c=0;c<8;c++){
                 if(aux<pow(2,c)){
                     i--;           //primero cambio la posicion para poder agregar los ceros faltantes
                     aux=0;
                     *(binario+i)= 48;    //for para agregar los primeros ceros en binario de cada caracter
                 }
             }
             iaux+=8; // variable auxiliar para conservar el valor inicial de i
             i=iaux;// varaiable que inicia des de primera posicion del numero binario
   }
}
void metodo2(char *binario,int semilla, string b){
    char bloques_bits[20]={};
    char codificado [50000]={};
    char prueba[200]={};
    int contprueba=0;
    int k=0;

    char *p=binario;
    while (*(p++)!='\0')k++;	//k es la longitud de la cadena

    char temporal;
    for (int i=0;i<k;i=i+semilla) {//recorremos el binario sin codificar con saltos del valor de la semilla
        for (int e=i,a=0;e<i+semilla;e++,a++) {//Para ir separando los bloques y guardarlos en bloques_bits
            *(bloques_bits+a)=*(binario+e);
        }
        for (int b=semilla-1;b>0;b--) {//Para mover una posicion a la derecha cada bit y el ultimo quede a la izquierda del bloque
            if(*(bloques_bits+b)!='\0'){//Si un valor del bloque es '\0' no cambie posiciones
                temporal=*(bloques_bits+b); //bit que va ir en la primera posicion
                *(bloques_bits+b)=*(bloques_bits+b-1);
                *(bloques_bits+b-1)=temporal;// se guarda el bit temporal en la primera posicion
            }
        }
        for (int a=i,b=0;a<i+semilla;a++,b++) {//Iremos guardando los bloques codificados en el arreglo codificado
            *(codificado+a)=*(bloques_bits+b);
        }
    }


    ofstream escribir;
    escribir.open(b);
    escribir<<codificado;
    escribir.close();

}
void modificardinero(string descision){//aca se decide si se va a recargar o retirar
    // si el que ingresa esel administrador solamente es para aumentar su dinero
    string prueba="../practica3parte2/BD/";

    if (descision=="admin"){// caso en que se va a recargar dinero
        cout<<"ingrese usuario que va a recargar"<<endl;cin>>descision;
        string auxdescision=descision;

        deco_metodo2(4,descision);
        descision=prueba+descision;
        ifstream leer;
            leer.open(descision);
            if(leer.is_open()){
                leer.close();
                descision=auxdescision;
               aumentardinero(descision);
            }
            else{
                cout<<"usuario no encontrado"<<endl;

            }

    }
    else{//caso en el que el usuario desee retirar el dinero

        retirardinero(descision);
    }

}
void retirardinero(string usuario){
    //recive el nombre del archivo del usuario que desee retirar el dinero
    string lo_que_tiene,guardarpasword;
    long int lo_que_desea_retirar;

    deco_metodo2(4,usuario);
    //decodificara os datos del usuario y los llevara al archivo usando
    lo_que_tiene=recogerunalinea(2,"usando");// recogo la tercer linea del archivo usando que es donde estara el saldo del usuario que desee retirar dinero
    cout<<endl<<endl<<"su saldo actual es :"<<lo_que_tiene<<endl;
    long int x=stoi(lo_que_tiene,nullptr,10);//convierte el saldo que esta en string a int
    cout<<"ingrese la cantidad que desea retirar"<<endl;cin>>lo_que_desea_retirar;
    x=x-lo_que_desea_retirar-1000;
    cout<<endl<<endl<<"retiro exitoso su nuevo saldo es:"<<x<<endl;
    guardarpasword=recogerunalinea(0,"usando");// recoge la linea donde esta contraseña
    ofstream escribir;
    usuario="../practica3parte2/BD/"+usuario;
    escribir.open(usuario);// el resto de lafuncion lo que hace es guardar los cambios
    // reescribo el archivo usando  con los cambios que se hicieron al usuario al retirar dinero

    escribir<<guardarpasword;
    escribir<<"\nsaldo:";
    escribir<<"\n";
    escribir<<x;
    escribir.close();
    char contenido[10000]={};
    int entero[10000]={};
    char binario[80000]={};
    // encripto los cambios de usando y los guardo en el archivo del usuario que esta retirando dinero y borro el archivo usando
    leer_archivo(contenido,usuario);
    convertircadena(entero,contenido);
    siste_binario(binario,entero);
    metodo2(binario,4,usuario);
    remove("../practica3parte2/BD/usando");//como aca se realizaron cambios y despues se codifico eliminamos este achivo

}
void aumentardinero(string usuario){//solo el admin puede aumentar el dinero si el usuario quiere recargar que vaya alas oficinas de los admins
    // recive d eentrada el nombre del archivo del usuario que senecesita decodificar, aumentar sus aldo y despues codificar
    long int lo_que_desea_recargar;
    string lo_que_tiene,guardarpasword;
    cout<<"cuanto va a recargar?"<<endl;cin>>lo_que_desea_recargar;
    deco_metodo2(4,usuario);
    lo_que_tiene=recogerunalinea(2,"usando");// recoge la linea del saldo que posteriormente se convertia a enetero para poder modificar el saldo
    long int x=stoi(lo_que_tiene,nullptr,10);
    x+=lo_que_desea_recargar;
    cout<<"recarga exiosa"<<endl<<" su nuevo saldo es :"<<x<<endl;
    guardarpasword=recogerunalinea(0,"usando");
    usuario="../practica3parte2/BD/"+usuario;
    ofstream escribir;
    escribir.open(usuario);// el resto de lafuncion lo que hace es guardar los cambios
    escribir<<guardarpasword;
    escribir<<"\nsaldo:";
    escribir<<"\n";
    escribir<<x;
    escribir.close();
    char contenido[10000]={};//guarda el contenido del archivo que desea modificar en este casoo el usuario
    int entero[10000]={};// se guardara cada caracter de contenido pero en ascii (convertircadena)
    char binario[80000]={};// todo lo que haya en entero se llevara a binario
    leer_archivo(contenido,usuario);
    convertircadena(entero,contenido);
    siste_binario(binario,entero);
    metodo2(binario,4,usuario);
    remove("../practica3parte2/BD/usando");//como aca se realizaron cambios y despues se codifico eliminamos este achivo
}
bool ingresarcomousuario(string a){// en esta funcion es donde se verificara el inreso del usuario y se sumara o restara dinero
    // se recive el nombre del usuario que desee ingresar al cajero
    string contrasena;
    string contrasenaverdadera;
    string auxa=a;
    bool con=true;

    while(con==true){
        a=auxa;
        deco_metodo2(4,a);// decodifico el archivo  del usuario que desee ingresar, si no existe saldra de la funcion y se le preguntara si desea ingresar al sistema
        a="../practica3parte2/BD/"+a;
        ifstream leer;
            leer.open(a);
            if(leer.is_open()){
                leer.close();
               contrasenaverdadera=recogerunalinea(0,"usando");//recogo la linea que tiene las contraseñas para compararlas
               remove("usando");//como aca se realizaron cambios y despues se codifico eliminamos este achivo
                cout<<"ingrese contrasena"<<endl;
                cin>>contrasena;

                if (contrasena==contrasenaverdadera){
                    cout<<"sesion iniciada"<<endl;
                    return true;
                    con=false;
                }
                else{
                    cout<<"contrasena incorrecta"<<endl;
                }
            }
            else{
                cout<<"usuaio no encontrado"<<endl;
                return false;
                con=false;
            }
    }
}
void versaldo(string usuario){// funcion que  le muestra al usuario su saldo actual con los -1000 por la revision
    // recive como entrada el nombre del usuario para que el pueda ver su saldo actual
    // se recalcara que cuando un usuario ingresa se llevaran todos los datos a un archivo llamado usando donde se realizaran los cambios
    // y despues se codificaran dichos cambios y se llevaran codificados al archivo del usuario que esta viendo su saldo
    string saldo,guardarpasword;
    deco_metodo2(4,usuario);
    saldo=recogerunalinea(2,"usando");//abre el archivo y como la linea 3 de los archivos es donde esta el saldo se debe de ingresar 2
    //por que dicho archivo se sobreescreibira
    long int x=stoi(saldo,nullptr,10);//funcion que me ayuda a llevar de string a enteros
    x=x-1000;
    cout<<"su saldo es : "<<x<<endl;
    guardarpasword=recogerunalinea(0,"usando");// como reescribire el archivo usando se necesita guardar la contraseña dle usuario para que no se pierda
    //se codificara el archivo
    ofstream escribir;
    usuario="../practica3parte2/BD/"+usuario;
    escribir.open(usuario);// el resto de lafuncion lo que hace es guardar los cambios y los codifica
    // se sobreescrive usando con los nuevos cambios
    escribir<<guardarpasword;
    escribir<<"\nsaldo:";
    escribir<<"\n";
    escribir<<x;
    escribir.close();
    char contenido[10000]={};
    int entero[10000]={};
    char binario[80000]={};
    leer_archivo(contenido,usuario);// se leera el archivo usando y se llevara todo su contenido a contenido
    convertircadena(entero,contenido);// convierte todos lo caracteres que hay en contenido a su valor en ascii y los guarda en entero
    siste_binario(binario,entero);// funcion que convierte todo lo que hay en enterno a numeros binarios
    metodo2(binario,4,usuario);
    remove("../practica3parte/usando");//como aca se realizaron cambios y despues se codifico eliminamos este achivo

}
