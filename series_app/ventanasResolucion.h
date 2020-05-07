
//E: dirrecion a crear el archivo(dirreccion\nombre.extencion), tamaño de la matriz, matriz y la lista de nombres.
//S: archivo con los datos de la matriz.
//R: la matiz debe ser cuadrada.
//O: crear archivo con los datos de una matriz.
void crear_archivo(GtkWidget *dummy, gpointer widget){
    char nombre[32];
    snprintf(nombre,sizeof(nombre),"%s",(char *)gtk_entry_get_text (GTK_ENTRY (g_object_get_data(G_OBJECT(dummy), "nombre"))));
    //verifica que el nombre tenga caracteres
    if(strlen(nombre)>0 && tamSerie>0){
        char texto[100000];
        char visita[10];
        char tamS[10];
        snprintf(texto,sizeof(texto),"%f\n",houseG);
        snprintf(visita,sizeof(visita),"%f\n",visitG);
        strcat(texto,visita);
        snprintf(tamS,sizeof(tamS),"%i\n",tamSerie);
        strcat(texto,tamS);
        for(int i=0;i<tamSerie;i++){
            char temp[100];
            snprintf(temp,sizeof(temp),"%i\n",valoresEntradas[i]);
            strcat(texto,temp);
        }
        strcat(nombre,".mti");
        FILE *archivo;
        archivo = fopen (nombre, "w" );
        fprintf(archivo, "%s",texto);
        fclose(archivo);
    }
    
}




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


void ventanaResultados(GtkWidget *dummy, gpointer widget, float house, float visit){
    //cierra la ventana anterior
    gtk_widget_hide(widget);
    gtk_main_quit();

    //fondo de pantalla
    GtkWidget *logo, *fixed, *fixedScroll, *wallpaper, *scrolled_window, *windowResultados, *btnGuardar, *nombreArchivo, *btnVolver;
    windowResultados = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    g_signal_connect(windowResultados, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    
    //configuración de ventana
    gtk_window_set_position(GTK_WINDOW(windowResultados), GTK_WIN_POS_CENTER);
    gtk_window_set_title(GTK_WINDOW(windowResultados), "Mostrando resultados");
    gtk_window_set_default_size(GTK_WINDOW(windowResultados),1300,750);
    gtk_window_set_resizable(GTK_WINDOW(windowResultados), FALSE);

    //fondo de pantalla y marco
    wallpaper = gtk_image_new_from_file("wallpaper2.jpg");
    fixed = gtk_fixed_new();
    gtk_fixed_put(GTK_FIXED(fixed), wallpaper, 0, 0);

    logo = gtk_image_new_from_file("nba.png");
    //gtk_fixed_put(GTK_FIXED(fixed), logo, 30, 200);


    GtkWidget *frame2 = gtk_frame_new("Guardar Datos");
    gtk_fixed_put(GTK_FIXED(fixed),frame2,20,300);
    gtk_widget_set_size_request(frame2,250,120);

    //Creación y configuración del entry de nombre del archivo
    nombreArchivo = gtk_entry_new();
    gtk_fixed_put(GTK_FIXED(fixed), nombreArchivo, 40, 325);
    gtk_widget_set_size_request(nombreArchivo,30,30);


    //Creación y configuración del botón de guardar
    btnGuardar = gtk_button_new_with_label("");
    g_signal_connect(btnGuardar, "clicked", G_CALLBACK(crear_archivo), (gpointer) windowResultados);
    g_object_set_data(G_OBJECT(btnGuardar),"nombre",(gpointer)nombreArchivo);
    gtk_fixed_put(GTK_FIXED(fixed), btnGuardar, 30, 360);
    GtkWidget *imgGuardar = gtk_image_new_from_file("button_guardar.png");
    gtk_button_set_always_show_image(GTK_BUTTON(btnGuardar),TRUE);
    gtk_button_set_image(GTK_BUTTON(btnGuardar), imgGuardar);



    GtkWidget *frame = gtk_frame_new("Probabilidades");
    gtk_fixed_put(GTK_FIXED(fixed),frame,20,60);
    gtk_widget_set_size_request(frame,300,200);


    //Creación y configuración del label de probabilidad casa

    char txtPh[200];
    sprintf(txtPh,"Prob. de ganar en casa    (Ph)  = %lf",house);

    GtkWidget *lblPh = gtk_label_new(txtPh);
    gtk_fixed_put(GTK_FIXED(fixed), lblPh, 30, 85);

    //Creación y configuración del label de probabilidad visita

    char txtPr[200];
    sprintf(txtPr,"Prob. de ganar en visita  (Pr)  = %lf",visit);

    GtkWidget *lblPr = gtk_label_new(txtPr);
    gtk_fixed_put(GTK_FIXED(fixed), lblPr, 30, 120);

    //Creación y configuración del label de probabilidad visita

    char txtQh[200];
    sprintf(txtQh,"Prob. de perder en casa  (Qh) = %lf",1-visit);


    GtkWidget *lblQh = gtk_label_new(txtQh);
    gtk_fixed_put(GTK_FIXED(fixed), lblQh, 30, 155);

    //Creación y configuración del label de probabilidad visita

    char txtQr[200];
    
    sprintf(txtQr,"Prob. de perder en visita(Qr) = %lf",1-house);

    GtkWidget *lblQr = gtk_label_new(txtQr);
    gtk_fixed_put(GTK_FIXED(fixed), lblQr, 30, 190);


    scrolled_window = gtk_scrolled_window_new (NULL, NULL);
    gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled_window),GTK_POLICY_AUTOMATIC,GTK_POLICY_AUTOMATIC);

    int tam = (tamSerie/2)+1;
    float matriz[tam+1][tam+1];

    fixedScroll = gtk_fixed_new();

    for(int i=0;i<=tam;i++){
        for(int j=0;j<=tam;j++){
            if(i==0){
                matriz[i][j]=0;
            }
            else if(j==0){
                matriz[i][j]=1;
            }
            else{
                int juegoActual = tamSerie+1-i-j;
                if(valoresEntradas[juegoActual]==1){
                    matriz[i][j]= (1-house)*matriz[i-1][j]+house*matriz[i][j-1];
                }
                else{
                    matriz[i][j]= (1-visit)*matriz[i-1][j]+visit*matriz[i][j-1];
                }
                
            }
        }
    }


    for(int i=0;i<=tam;i++){
        char txtCuadro[200];
        sprintf(txtCuadro,"%i",i);
        GtkWidget *cuadro = gtk_label_new(txtCuadro);
        gtk_widget_set_size_request (cuadro, 80, 60);
        gtk_fixed_put(GTK_FIXED(fixedScroll), cuadro, 100*(i+1), 10);


        GtkWidget *cuadro2 = gtk_label_new(txtCuadro);
        gtk_widget_set_size_request (cuadro2, 80, 60);
        gtk_fixed_put(GTK_FIXED(fixedScroll), cuadro2, 20, 70*(i+1));
    }


    for(int i=0;i<=tam;i++){
        for(int j=0;j<=tam;j++){
            if(i>0 || j>0){
                char txtCuadro[200];
                sprintf(txtCuadro,"%lf",matriz[i][j]);
                GtkWidget *cuadro = gtk_label_new(txtCuadro);
                GdkColor color;
                if(i==tam && j==tam){
                    gdk_color_parse ("#FFFFFF", &color);
                    gtk_widget_modify_fg (cuadro, GTK_STATE_NORMAL, &color);
                    gdk_color_parse ("#0101DF", &color);
                }
                else{
                    gdk_color_parse ("#F7FE2E", &color);
                }
                gtk_widget_modify_bg (cuadro, GTK_STATE_NORMAL, &color);
                gtk_widget_set_size_request (cuadro, 80, 60);
                gtk_fixed_put(GTK_FIXED(fixedScroll), cuadro, 100+100*i, 70+70*j);
            }
        }
    }

    char txtRes[200];
    
    sprintf(txtRes,"Prob. de ganar al iniciar la serie: %lf",matriz[tam-1][tam-1]);

    GtkWidget *lblRes = gtk_label_new(txtRes);
    gtk_fixed_put(GTK_FIXED(fixed), lblRes, 30, 225);


    //define color de fondo de la ventana
    GdkColor color;
    gdk_color_parse("#FFFFFF", &color);
    gtk_widget_modify_bg(scrolled_window, GTK_STATE_NORMAL, &color);

    gtk_widget_set_size_request (scrolled_window, 710, 500);

    gtk_container_add(GTK_CONTAINER(scrolled_window),fixedScroll);


    gtk_fixed_put(GTK_FIXED(fixed),scrolled_window, 355, 85);

    //Creación y configuración del botón de volver
    btnVolver = gtk_button_new_with_label("");
    g_signal_connect(btnVolver, "clicked", G_CALLBACK(volverAPrincipal), (gpointer) windowResultados);
    gtk_fixed_put(GTK_FIXED(fixed), btnVolver, 960,600);
    GtkWidget *imgVolver = gtk_image_new_from_file("button_volver.png");
    gtk_button_set_always_show_image(GTK_BUTTON(btnVolver),TRUE);
    gtk_button_set_image(GTK_BUTTON(btnVolver), imgVolver);

    //configuración final
    gtk_container_add(GTK_CONTAINER(windowResultados),fixed);
    gtk_widget_show_all(windowResultados);
    gtk_main();
}