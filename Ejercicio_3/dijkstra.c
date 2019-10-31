#include<stdio.h>
#include<stdlib.h>

typedef struct nodo{
  unsigned char dato;
  int *costo;
  struct nodo *sig;
  struct nodo **vertices;
}nodo;

void nuevonodo(int max,nodo *Inicio, int *cantidad);
void borrarlista(nodo *inicio);
void nuevaarista(int max,nodo *inicio);
void desplegar(nodo *inicio,int max);
void Dijkstra(nodo *inicio,int max, int cantidad);
void wazechafa(nodo *inicio, int max,int cantidad,unsigned int SDF[],char ant[],char salida,unsigned int *visitados);

int main(void){
  int max,i,op, cantidad=1;
  nodo *temp,*inicio;
  printf("Cuando vertices va a haber por nodo?\n");
  scanf("%i",&max);
  temp=(nodo*)malloc(sizeof(nodo));
  temp->vertices=(nodo**)malloc(sizeof(nodo*)*max);
  temp->costo=(int*)malloc(sizeof(int)*max);
  for(i=0;i<max;i++)
    temp->vertices[i]=NULL;
  temp->sig=NULL;
  temp->dato='A';
  inicio=temp;
  printf("Nodo \"A\" creado con 0 vertices\n");
  i=0;
  do{
    printf("Que quieres hacer?\n1. Anadir nodo\n2. Anadir vertice\n3. Desplegar grafo\n4. Dijkstra\n5. Salir\n");
    __fpurge(stdin);
    scanf("%i",&op);
    switch(op){
      case 1:
        nuevonodo(max,inicio,&cantidad);
      break;
      case 2:
        nuevaarista(max,inicio);
      break;
      case 3:
        desplegar(inicio,max);
      break;
      case 4:
        Dijkstra(inicio,max,cantidad);
      break;
      case 5:
        i=1;
        borrarlista(inicio);
        printf("No me mates...\n");
      break;
      default:
        printf("Escoja una opcion valida\n");
      break;
    }
  }while(i==0);
}

void Dijkstra(nodo *inicio,int max, int cantidad){
  nodo *temp;
  char direccion[cantidad],salida,llegada,*ant,ruta[20],desde,hola;
  unsigned int i=0,*SDF,j=0,visitados=0;
  printf("De que nodo desea salir:\n");
  __fpurge(stdin);
  scanf("%c", &salida);
  SDF=(unsigned int*)malloc(sizeof(unsigned int)*cantidad);
  ant=(char*)malloc(sizeof(char)*cantidad);
  for(i=0;i<cantidad;i++)
    SDF[i]=2147483640;
  temp=inicio;
  i=0;
  while(temp->dato!=salida){
    temp=temp->sig;
    i++;
  }
  SDF[i]=0;
  ant[i]='\0';
  for(i=0;i<cantidad;i++)
    wazechafa(inicio,max,cantidad,SDF,ant,salida,&visitados);
  system("clear");
  hola='A';
  for(i=0;i<cantidad;i++){
    printf("%c\t",hola);
    printf("%i\t",SDF[i]);
    if(ant[i]=='\0')
      printf("NULL\n");
    else
      printf("%c\n",ant[i]);
    hola++;
  }
}

void wazechafa(nodo *inicio, int max,int cantidad,unsigned int SDF[],char ant[],char salida,unsigned int *visitados){
  nodo *checar,*llegada;
  int min,sv=1,i,novertice,j,temp;
  min=2147483643;
  for(i=0;i<cantidad;i++){
    if((sv&(*visitados))==0){
      if(min>SDF[i]){
        min=SDF[i];
        novertice=i;
      }
    }
    sv<<=1;
  }
  checar=inicio;
  for(i=0;i<novertice;i++)
    checar=checar->sig;
  printf("Checando vertice %c\n",checar->dato);
  i=0;
  while(checar->vertices[i]!=NULL){
    sv=1;
    sv<<=checar->vertices[i]->dato-65;
    if((sv&(*visitados))==0){
      temp=SDF[novertice]+checar->costo[i];
      j=checar->vertices[i]->dato-65;
      if(temp<SDF[j]){
        SDF[j]=temp;
        ant[j]=checar->dato;
      }
    }
    i++;
  }
  temp=1;
  temp<<=checar->dato-65;
  (*visitados)=(*visitados)|temp;
}

void nuevonodo(int max,nodo *inicio, int *cantidad){
  int i;
  nodo *nuevo,*temp;
  nuevo=(nodo*)malloc(sizeof(nodo));
  nuevo->vertices=(nodo**)malloc(sizeof(nodo*)*max);
  nuevo->costo=(int*)malloc(sizeof(int)*max);
  for(i=0;i<max;i++)
    nuevo->vertices[i]=NULL;
  nuevo->sig=NULL;
  temp=inicio;
  while(temp->sig!=NULL)
    temp=temp->sig;
  temp->sig=nuevo;
  nuevo->dato=(temp->dato)+1;
  system("clear");
  printf("Nodo \"%c\" creado con 0 vertices\n",nuevo->dato);
  printf("\n");
  (*cantidad)++;
}

void nuevaarista(int max,nodo *inicio){
  int contador=0,contador2=0,costo;
  unsigned char letra;
  nodo *principio,*fin;
  printf("De que nodo sale la conexion?\n");
  __fpurge(stdin);
  scanf("%c",&letra);
  principio=inicio;
  while(principio->dato!=letra&&principio!=NULL)
    principio=principio->sig;
  if(principio==NULL){
    printf("Ese nodo no existe\n");
    return;
  }
  while(principio->vertices[contador]!=NULL)
    contador++;
  if(contador==max){
    printf("Ese nodo ya tiene sus conexiones llenas\n");
    return;
  }
  printf("A que nodo lo quieres juntar?\n");
  __fpurge(stdin);
  scanf("%c",&letra);
  fin=inicio;
  while(fin->dato!=letra&&fin!=NULL)
    fin=fin->sig;
  if(fin==NULL){
    printf("Ese nodo no existe\n");
    return;
  }
  while(fin->vertices[contador2]!=NULL)
    contador2++;
  if(contador2==max){
    printf("Ese nodo ya tiene sus conexiones llenas\n");
    system("clear");
    return;
  }
  printf("Cuanto es el costo?\n");
  scanf("%i",&costo);
  principio->costo[contador]=costo;
  principio->vertices[contador]=fin;
  fin->costo[contador2]=costo;
  fin->vertices[contador2]=principio;
  system("clear");
  printf("La conexion del nodo %c al nodo %c establecida\n",principio->dato,fin->dato);
  printf("\n");
}

void desplegar(nodo *inicio,int max){
  nodo *imprimir;
  int i;
  imprimir=inicio;
  system("clear");
  while(imprimir!=NULL){
    printf("El nodo \"%c\" tiene conexiones con:",imprimir->dato);
    i=0;
    for(i=0;i<max;i++){
      if(imprimir->vertices[i]!=NULL)
        printf(" %c",imprimir->vertices[i]->dato);
    }
    printf("\n\n");
    imprimir=imprimir->sig;
  }
}

void borrarlista(nodo *Inicio){
  nodo *temp;
    temp=Inicio;
    while(temp!=NULL){
      Inicio=Inicio->sig;
      free(temp);
      temp=Inicio;
    }
}
