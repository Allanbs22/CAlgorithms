//formato de los archivos:
//En la primera linea del archivo van los nombres separandos por coma(,)
//despues aparir de la segunda linea cada columna de la matris es una linea
//separando los balores por coma(,) y las filas son conjunt de columnas separadas
//por el salto de linea ej:
//
//      A,B,C                                     A B C 
//      3,2,4                                   A 3 2 4
//      1,3,5        es igual a la matriz       B 1 3 5
//      4,5,6                                   C 4 5 6
// (en el archivo)                          (en la aplicacion)
//


//E: Dirreccion del archivo a leer(dirreccion\nombre.extencion).
//S: tamño de la matriz
//R: el archivo debe respetar el formato de los archivos.
//O: conseguir el tamaño de una matiz en el archivo.
int tamanomatriz(char* direccion){
    char linea[255];
    FILE *archivo;
    int tam = -1;
	char* def;
    archivo=fopen(direccion,"r");
    do{
        def = fgets(linea,255,archivo);
        tam++;
    } while (def != NULL);
    fclose(archivo);
    return tam-1;
}

//E: Direccion del archivo a leer(direccion\nombre.extencion), tamaño de la matriz,
//la matriz y lista de nombres.
//S: matriz compuesta por los datos del archivo.
//R: el archivo debe respetar el formato de los archivos.
//O: convertir un archivo a matriz.
void  leer_archivo(char* dirrecion, int matriz[tam][tam], char *nombre[tam]){
    char linea[2550];
    FILE *archivo;
    char *ch;
	char *dev;
    int lineanum = -1;
    int pos = 0;
    archivo=fopen(dirrecion,"r");
    do{
        dev = fgets(linea,2550,archivo);
        ch = strtok(linea, ",");
        while (ch != NULL) {
            if(lineanum == -1){
				nombre[pos] = ch;
				
            }
            else{
                matriz[lineanum][pos] = atoi(ch);
            }
            pos++;
            ch = strtok(NULL,",");
        }
        pos =0;
        lineanum++;
    } while (dev != NULL);
    fclose(archivo);
	
	archivo=fopen(dirrecion,"r");
   	dev = fgets(linea,2550,archivo);
	strtok(linea, "\n");
    ch = strtok(linea, ",");
	pos = 0;
    while (ch != NULL) {
    	nombre[pos] = ch;
		ch = strtok(NULL,",");
		pos++;
    }
    fclose(archivo);
				
	
}

//E:  tamaño de la matriz y matriz.
//S: cadena de caracteres en el formato de archivos establecido.
//R: la matiz debe ser cuadrada.
//O: crear una cadema de caracteres con los datos de una matriz.
char* Pasarachar(int matriz[tam][tam]){
    char num[10];
    char *texto;
    for(int I=0;I<tam;I++){
        for(int J=0;J<tam;J++){
            sprintf(num,"%d", matriz[I][J]);
            strcat(texto,num);
            if(J != tam-1){
                strcat(texto,",");
            }
            else{
                strcat(texto,"\n");
            }
        }
    }
    return texto;
}


//E: tamaño de la lista y lista de adena de caracteres.
//S: lista combinada en una sola cadena de caracteres.
//R: n/a
//O: crear una cadema de caracteres con los datos de la lista.
//char* combinarlista(){
//    char *texto ="";
//    for(int i=0;i<tam;i++){
//		char *actual = (char *)gtk_entry_get_text (GTK_ENTRY (entradas[0]));
		//snprintf(actual,sizeof(actual),"%s",gtk_entry_get_text (GTK_ENTRY (entradas[i])));
        //strcat(texto,actual);
//        if(i != tam-1){
//            strcat(texto,",");
//         }
//         else{
//            strcat(texto,"\n");
//         }
//    }
//    return texto;
//}

//E: dirrecion a crear el archivo(dirreccion\nombre.extencion), tamaño de la matriz, matriz y la lista de nombres.
//S: archivo con los datos de la matriz.
//R: la matiz debe ser cuadrada.
//O: crear archivo con los datos de una matriz.
void crear_archivo(GtkWidget *dummy, int matriz[tam][tam]){
	char nombre[32];
	snprintf(nombre,sizeof(nombre),"%s",(char *)gtk_entry_get_text (GTK_ENTRY (nombreArchivo)));
	//verifica que el nombre tenga caracteres
	if(strlen(nombre)>0){
		char texto[100000];
		snprintf(texto,sizeof(texto),"%s",(char *)gtk_entry_get_text (GTK_ENTRY (entradas[0])));
		if(tam != 1){
				strcat(texto,",");
		}
		for(int i=1;i<tam;i++){
			char *actual = (char *)gtk_entry_get_text (GTK_ENTRY (entradas[i]));
			strcat(texto,actual);
			if(i != tam-1){
				strcat(texto,",");
			 }
			 else{
				strcat(texto,"\n");
			 }
		}

		for(int I=0;I<tam;I++){
			for(int J=0;J<tam;J++){
				char num[2550];
				sprintf(num,"%d", matriz[I][J]);
				strcat(texto,num);
				if(J != tam-1){
					strcat(texto,",");
				}
				else{
					strcat(texto,"\n");
				}

			}
		}
		strcat(nombre,".mti");
		FILE *archivo;
		archivo = fopen (nombre, "w" );
		fprintf(archivo, "%s",texto);
		fclose(archivo);
	}
 	
}
