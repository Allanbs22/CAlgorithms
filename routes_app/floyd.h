//E: ciudad a buscar, tamaño de la lista, lista de nombres.
//S: posicion de la ciudad en la lista.
//R: la ciudad debe estar en la lista.
//O: identificar en que posicion de la lista esta la ciudad.
int posdeciudad(char* ciudad){
        for(int i=0;i<tam;i++){
            if(strcmp((char *)gtk_entry_get_text (GTK_ENTRY (entradas[i])),ciudad)==0){
                return i;
            }
        }
        return -1;
}



//E: ciudad de inicio, ciudad destino, tamaño de la matriz, lista de ciudades, matriz P.
//S: ruta mas corta de origen a destino.
//R: origen y destino deben estar en la lista de nombres
//O: conseguir la ruta mas corta
char* rutamascorta(char* origen,char* destino, int P[tam][tam]){
    char* res = origen;
    int O = posdeciudad(origen);
    int D = posdeciudad(destino);
    int actual = 0;
    while(P[O][D] > 0){
        actual = P[O][D];
        origen = (char *)gtk_entry_get_text (GTK_ENTRY (entradas[actual-1]));
        strcat(res,"->");
        strcat(res,origen);
        O = posdeciudad(origen);
    }
    if(P[O][D] != 0){
        return "no hay ruta";
    }
    else{
        strcat(res,"->");
        strcat(res,destino);
    }
    return res;
}

//E: cantidad de ciudades matriz D(X-1), matriz p (con valores default), X Tabla deseada
//S: matriz D(X) y P (actual)
//R: D y P deben tener las mismas dimenciones
//O: aplicar el algoritmo de la ruta mas corta
void floyd(int D[tam][tam], int P[tam][tam], int X){
    int Dk[tam][tam];
    for(int I=0;I<tam;I++){ 
        for(int J=0;J<tam;J++){
            Dk[I][J] = D[I][J];
        }
    }
    int  K= (X-1);
    for(int I=0;I<tam;I++){ 
        for(int J=0;J<tam;J++){
            if((I != K) && (J != K) && ((Dk[I][J] > (Dk[I][K] + Dk[K][J])) || (Dk[I][J] < 0))) {
            	if(Dk[I][K] != -1 && Dk[K][J] != -1){
                	D[I][J] = Dk[I][K] + Dk[K][J];
                	P[I][J] = X;
                }
            }  
        }
    }
}

//E: cantidad de ciudades, matriz D(0) y matriz p (vacia)
//S: matriz P (con valores defaul)
//R: D y P deben tener las mismas dimenciones
//O: Sacar los valores defaul de P
void PDefault(int D[tam][tam], int P[tam][tam]){
    for(int I=0;I<tam;I++){ 
        for(int J=0;J<tam;J++){
            if( D[I][J] < 0){ // se con sidera a -1 como infinito
                P[I][J] = -1;
            }
            else{
                P[I][J] = 0;
            }
        }
    }
}
