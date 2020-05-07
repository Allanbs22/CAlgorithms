#include <stdlib.h>
#include <stdio.h>
#include <string.h>


int cantE;


void Matrices(int M[cantE][cantE],int P[cantE][cantE],int D[cantE+1]){
    for(int i=0;i<cantE;i++){
		for(int j=0;j<cantE;j++){
		M[i][j] = 0;
		P[i][j] = 0;
		}
	}
  	for(int i =0;i<cantE;i++){
        M[i][i] = 0;
        P[i][i] = 0;
        if(i+1 != cantE){
            M[i][i+1] = D[i]*D[i+1]*D[i+2];
            P[i][i+1] = i+1;
        }
    }

    int x = 0;
    int y = 2;
    int actual;
    int peon;
    int k  = 0;
    int ciclo = 1;
    int vuelta = 1;
    while(ciclo == 1 && cantE > 2){
        actual = -1;
        for(int i =x;i<y;i++){
        	if(i <= y-1){
            	peon = M[x][i] + M[i+1][y] + (D[x]*D[y+1]*D[i+1]);
            	if(actual == -1  ||  actual>peon){
                	k= i+1;
                	actual  = peon;
            	}
            }
        }
        M[x][y] = actual;
        P[x][y] = k;
        x++;
        y++;
        if(y == cantE){
            x = 0;
            y = vuelta+2;
            vuelta++;
            if(y == cantE){
                ciclo = 0;
            }
        }
    }
}



int main(){
	cantE = 6;

	int D[7];
	D[0] = 5;
	D[1] = 2;
	D[2] = 3;
	D[3] = 4;
	D[4] = 6;
	D[5] = 7;
	D[6] = 8;
	int M[6][6];
	int P[6][6];


	Matrices(M,P,D);

	for(int i=0;i<6;i++){
		for(int j=0;j<6;j++){
			printf("%d ",P[i][j]);
		}
		printf("\n");
	}


	return 0;
}