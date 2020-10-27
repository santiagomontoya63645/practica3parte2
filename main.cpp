#include <fstream>
#include <iostream>
#include <string>
#include <math.h>

using namespace std;
string recogerunalinea(int linea, string a);
bool verificador(string clave,string claveingresada);
void deco_metodo2(int semilla, string nombre);
void crearusuario();
void leer_archivo(char *contenido,string b); //se leera el archivo usando y se llevara todo su contenido a contenido
void convertircadena(int *entero,char *contenido);// convierte todos lo caracteres que hay en contenido a su valor en ascii y los guarda en entero
void siste_binario(char *binario,int *entero);
void metodo2(char *binario,int semilla, string b);
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

                      deco_metodo2(2,a);// decodifica el archivo sudo
                      clavedecod=recogerunalinea(0,"usando");// abre el archivo usando y recoge la contraseña para compararla
                      remove("../practica3parte2/BD/usando");
                      claveverif=verificador(clave,clavedecod);
                      if(claveverif==false){//cave d eadministrador que ingreso esta incorrecta
                          cout<<"clave incorrecta"<<endl;
                      }
                      else{
                          cout<<"clave wryyyyyyy"<<endl;
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

                              //modificardinero("admin");//se usa para recargar las cuentas
                              break;
                          }

                      }
                      opcion=0;

                      claveverif=false;//poner despues de esto si se desea sali del sistema
                  }
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
            metodo2(binario,3,b);
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
