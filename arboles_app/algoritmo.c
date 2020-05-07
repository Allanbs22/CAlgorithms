#include <stdlib.h>
#include <stdio.h>
#include <string.h>



void conseguirP(struct nodo elementos[cantE],float P[cantE]){
    float todos = 0;
    for(int i=0;i<cantE;i++){
        todos +=  elementos[i].peso;
    }
    for(int x = 0;x<cantE;x++){
        P[x] = elementos[x].peso/todos;
    }

}

float clacularP(int i,int f,float P[cantE]){
    float res = 0;
    for(int x = i;x<f;x++){
        res += P[x];
    }
    return res;
}

void ordenar(struct nodo elementos[cantE]){
    struct nodo temp;   
	for(int i=0; i<cantE-1; i++){
		for(int j=i+1; j<cantE; j++){
			if(strcmp(elementos[i].nombre, elementos[j].nombre) > 0){
				
				temp.peso = elementos[i].peso;
				sprintf(temp.nombre,"%s",elementos[i].nombre);

				elementos[i].peso = elementos[j].peso;
				sprintf(elementos[i].nombre,"%s",elementos[j].nombre);

				elementos[j].peso = temp.peso;
				sprintf(elementos[j].nombre,"%s",temp.nombre);
			}
		}
	}	

}

void arboles(float A[cantE+1][cantE+1],int R[cantE+1][cantE+1],struct nodo elementos[cantE]){
    for(int i=0;i<cantE+1;i++){
		for(int j=0;j<6;j++){
			A[i][j] = 0;
			R[i][j] = 0;
		}
	}
    float P[cantE];
    ordenar(elementos);
    conseguirP(elementos,P);
  	for(int i =0;i<cantE+1;i++){
        A[i][i] = 0;
        A[i][i+1] = P[i];
        R[i][i] = 0;
        R[i][i+1] = i+1; 
    }

    int x = 0;
    int y = 2;
    float actual;
    float peon;
    int k  = 0;
    int ciclo = 1;
    int vuelta = 1;
    while(ciclo == 1){
        actual = -1;
        for(int i =x;i<y;i++){
            peon = A[x][i] + A[i+1][y] + clacularP(x,y,P);
            if(actual == -1  ||  actual>peon){
                k= i+1;
                actual  = peon;
            }
        }
        A[x][y] = actual;
        R[x][y] = k;
        x++;
        y++;
        if(y == cantE+1){
            x = 0;
            y = vuelta+2;
            vuelta++;
            if(y == cantE+1){
                ciclo = 0;
            }
        }
    }
}