void guardar(GtkWidget *dummy, gpointer entrada){
    struct nodo lista[cantE];
    memcpy(lista,g_object_get_data(G_OBJECT(dummy), "clave"),cantE*sizeof(struct nodo));
    char nombre[255];
    sprintf(nombre,"%s",(char *)gtk_entry_get_text(entrada));
    char texto[15000];
    if(strcmp(nombre,"") != 0){
        strcat(nombre,".ha");
        FILE *archivo = fopen(nombre,"w");
        sprintf(texto,"%d\n",cantE);
        for(int i=0;i<cantE;i++){
            char buffer[255];
            sprintf(buffer,"%s,%f\n",lista[i].nombre,lista[i].peso);
            strcat(texto,buffer);
        }
        fputs(texto,archivo);
        fclose(archivo);
    }
}

void cargador(GtkWidget *dummy,gpointer widget){
    char nombre[255];
    memcpy(nombre,(char *)gtk_entry_get_text (GTK_ENTRY (ruta)),255*sizeof(char));
    if(strcmp(nombre,"") != 0){
        FILE *archivo = fopen(nombre,"r");
        char linea[255];
        fgets(linea,255,archivo);
        char *parte;
        char *parte2;
        parte = strtok(linea,"\n");
        parte2 = strtok(parte,",");
        cantE = atoi(parte2);
        fclose(archivo);
        ventanaIngresarValores(dummy,widget);
    }
}

//codigo para cargar
        char nombre[255];
        struct nodo lista[cantE];
        memcpy(nombre,(char *)gtk_entry_get_text (GTK_ENTRY (ruta)),255*sizeof(char));
        FILE *archivo = fopen(nombre,"r");
        char linea[255];
        fgets(linea,255,archivo);
        char *parte;
        parte = strtok(linea,"\n");
        for(int i=0;i<vidaUtil;i++){
            fgets(linea,255,archivo);
            parte = strtok(linea,",");
            sprintf(lista[i].nombre,parte);
            parte = strtok(NULL,",");
            lista[i].peso = atoi(parte);
           
        }
        fclose(archivo);