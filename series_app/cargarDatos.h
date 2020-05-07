
/*
*E:Widget
*S:File dialog abierto y archivo cargado en label
*R:Archivo debe ser válido
*O:Cargar un archivo externo con una tabla
*/
void cargarArchivo(GtkWidget *dummy, gpointer widget){
	GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_OPEN;
	GtkWidget *dialog = gtk_file_chooser_dialog_new ("Open File",widget,action,("_Cancel"),GTK_RESPONSE_CANCEL,("_Open"),GTK_RESPONSE_ACCEPT,NULL);
	gint res = gtk_dialog_run (GTK_DIALOG (dialog));
	if (res == GTK_RESPONSE_ACCEPT){
	    char *filename;
	    GtkFileChooser *chooser = GTK_FILE_CHOOSER (dialog);
	    filename = gtk_file_chooser_get_filename (chooser);
	    gtk_entry_set_text(GTK_ENTRY(ruta), filename);
	}
	gtk_widget_destroy (dialog);
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
        cantObj = atoi(parte2);
        parte2 = strtok(NULL,",");
        tamMochila = atoi(parte2);
        ventanaIngresarValores(dummy,widget);
    }
}