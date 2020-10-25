#include <fstream>
#include <iostream>
#include <string>
#include <math.h>

using namespace std;
string recogerunalinea(int linea, string a);
bool verificador(string clave,string claveingresada);
void deco_metodo2(int semilla, string nombre);
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
    return contrasenaverdadera;
}
