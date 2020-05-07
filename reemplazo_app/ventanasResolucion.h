double mantenimientos(int matriz[vidaUtil][3],int inicio,int tam){
    double res = 0;
	double nuevo = inflacion;
	double precio;
    for(int i =0;i<tam;i++){
    	precio = matriz[i][2];
    	for(int x=0; x<inicio+i+1; x++){
			precio += precio*(nuevo/100);
		}
        res += precio;
    }
    return res;
}



double precioactual(int A){
	double res = costoInicial;
	double nuevo = inflacion;
	for(int i=0; i<A; i++){
		res += res*(nuevo/100);
	}
	return res;

}

double inflar(int monto,int A){
	double res = monto;
	double nuevo = inflacion;
	for(int i=0; i<A; i++){
		res += res*(nuevo/100);
	}
	return res;

}






void remplazo(double res[plazo+1],int plan[plazo+1][plazo+2],int matriz[vidaUtil][3]){
    int cantidad;
    double actual =-1;
    double peon;
   	int masbajo;
   	for(int x =0;x<plazo+1;x++){
   		for(int y =0;y<plazo+2;y++){
   			plan[x][y] = -1;
   		}
   	}
    for(int i=plazo-1;i > -1;i--){
     	cantidad = i+1;
        actual =-1;
        masbajo = 0;
        while(cantidad <= plazo && cantidad-i <= vidaUtil){
        	peon = precioactual(i)+mantenimientos(matriz,i,cantidad-i)-inflar(matriz[cantidad-i-1][1],cantidad)-inflar(matriz[cantidad-i-1][0],cantidad)+res[cantidad];
            if(actual == -1 || actual >= peon){
            	if(peon != actual && actual != -1){
                	masbajo--;
                }
                actual = peon;
                res[i] = peon;
                plan[i][masbajo] = cantidad;
                masbajo++;
                   
            }
                cantidad++;
            
        }
    }
}

/*
*E: lWidget y entrada de texto
*S: archivo .ha con los datos 
*R: Ninguna
*O: guardar todos los datos de un proyecto en un archivo
*/

void guardar(GtkWidget *dummy, gpointer entrada){
    int lista[vidaUtil][3];
    memcpy(lista,g_object_get_data(G_OBJECT(dummy), "datos"),vidaUtil*3*sizeof(int));
    char nombre[255];
    sprintf(nombre,"%s",(char *)gtk_entry_get_text(entrada));
    char texto[15000];
    if(strcmp(nombre,"") != 0){
        strcat(nombre,".ha");
        FILE *archivo = fopen(nombre,"w");
        sprintf(texto,"%d,%d,%d,%d\n",costoInicial,vidaUtil,inflacion,plazo);
        for(int i=0;i<vidaUtil;i++){
            char buffer[255];
            sprintf(buffer,"%d,%d,%d\n",lista[i][0],lista[i][1],lista[i][2]);
            strcat(texto,buffer);
        }
        fputs(texto,archivo);
        fclose(archivo);
    }
}


/*
*E: lista de plan
*S: char *  con el plan
*R: Ninguna
*O: expresar el plan en plabras
*/


void solucion(int plan[plazo+1][plazo+2],char texto[2550]){
	int num = 0; 
	while(plan[num][0] != -1){
		char buffer[255];
		sprintf(buffer,"Se compra en el año %d y se usa por %d año(s)\n",num,plan[num][0]-num);
		strcat(texto,buffer);
		num = plan[num][0];
	}
}

/*
*E:Widget
*S:Ventana del widget cerrada y ventana de calculos abierta
*R:Ninguna
*O:Abrir la ventana de calculos de tabla
*/
void ventanaSolucion(GtkWidget *dummy, gpointer widget){
	//cierra la ventana anterior
	gtk_widget_hide(widget);
	gtk_main_quit();
	
	//fondo de pantalla
	GtkWidget *wallpaper, *fixed, *scrolled_window, *btnSiguiente, *windowFinal, *btnVolver, *lblMensaje2, *btnGuardar, *nombreArchivo;
	windowFinal = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    g_signal_connect(windowFinal, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    
    //configuración de ventana
    gtk_window_set_position(GTK_WINDOW(windowFinal), GTK_WIN_POS_CENTER);
    gtk_window_set_title(GTK_WINDOW(windowFinal), "Mostrando respuesta");
    gtk_window_set_default_size(GTK_WINDOW(windowFinal),1000,550);
    gtk_window_set_resizable(GTK_WINDOW(windowFinal), FALSE);

    //fondo de pantalla y marcos
    scrolled_window = gtk_scrolled_window_new (NULL, NULL);
    gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled_window),GTK_POLICY_AUTOMATIC,GTK_POLICY_AUTOMATIC);
    gtk_widget_set_size_request (scrolled_window, 1000, 550);
    fixed = gtk_fixed_new();

    //define color de fondo de la ventana
    GdkColor color;
    gdk_color_parse("#119BAB", &color);
    gtk_widget_modify_bg(scrolled_window, GTK_STATE_NORMAL, &color);


    //Creación y configuración del label de mensaje
    GtkWidget *lblMensaje = gtk_label_new("Plan:");
    gtk_fixed_put(GTK_FIXED(fixed), lblMensaje, 50, 50);
    int lista[vidaUtil][3];
    int plan[plazo+1][plazo+2];
    memcpy(lista,g_object_get_data(G_OBJECT(dummy), "lista"),vidaUtil*3*sizeof(int));
    memcpy(plan,g_object_get_data(G_OBJECT(dummy), "plan"),(plazo+1)*(plazo+2)*sizeof(int));
	char valorR[2600];
	char texto[2550] = "";
    solucion(plan,texto);
	sprintf(valorR,"<span font_desc=\"15.0\">%s</span>",texto);
	GtkWidget *lblMensajeR = gtk_label_new(texto);
    gtk_fixed_put(GTK_FIXED(fixed), lblMensajeR, 50, 100);
    gtk_label_set_markup(GTK_LABEL(lblMensajeR),valorR);
   
  
   
    //Creación y configuración del entry de nombre del archivo
	nombreArchivo = gtk_entry_new();
	gtk_fixed_put(GTK_FIXED(fixed), nombreArchivo, 350, 420);

	//creación de label de mensaje 2
	lblMensaje2 = gtk_label_new("Indique el nombre del archivo a guardar:");
	gtk_fixed_put(GTK_FIXED(fixed), lblMensaje2, 250, 400);

	//Creación y configuración del botón de guardar
	btnGuardar = gtk_button_new_with_label("");
	g_signal_connect(btnGuardar, "clicked", G_CALLBACK(guardar),nombreArchivo);
    g_object_set_data(G_OBJECT(btnGuardar),"datos",lista);
	gtk_fixed_put(GTK_FIXED(fixed), btnGuardar, 530, 420);
	GtkWidget *imgGuardar = gtk_image_new_from_file("button_guardar.png");
	gtk_button_set_always_show_image(GTK_BUTTON(btnGuardar),TRUE);
	gtk_button_set_image(GTK_BUTTON(btnGuardar), imgGuardar);


    //Creación y configuración del botón de volver
    btnVolver = gtk_button_new_with_label("");
    g_signal_connect(btnVolver, "clicked", G_CALLBACK(volverAPrincipal), (gpointer) windowFinal);
    gtk_fixed_put(GTK_FIXED(fixed), btnVolver, 50, 430);
    GtkWidget *imgVolver = gtk_image_new_from_file("button_volver.png");
    gtk_button_set_always_show_image(GTK_BUTTON(btnVolver),TRUE);
    gtk_button_set_image(GTK_BUTTON(btnVolver), imgVolver);

    

    //configuración final
    gtk_container_add(GTK_CONTAINER(scrolled_window),fixed);
    gtk_container_add(GTK_CONTAINER(windowFinal),scrolled_window);
    gtk_widget_show_all(windowFinal);
    gtk_main();
}


/*
*E:Widget
*S:Ventana del widget cerrada y ventana de calculos abierta
*R:Ninguna
*O:Abrir la ventana de calculos de tabla
*/
void ventanaResolver(GtkWidget *dummy, int lista[vidaUtil][3]){

	//fondo de pantalla
	GtkWidget *wallpaper, *fixed, *scrolled_window, *btnSiguiente, *windowTabla, *btnVolver;
	windowTabla = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    g_signal_connect(windowTabla, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    
    //configuración de ventana
    gtk_window_set_position(GTK_WINDOW(windowTabla), GTK_WIN_POS_CENTER);
    gtk_window_set_title(GTK_WINDOW(windowTabla), "Mostrando valores G(t)");
    gtk_window_set_default_size(GTK_WINDOW(windowTabla),1000,550);
    gtk_window_set_resizable(GTK_WINDOW(windowTabla), FALSE);

    //fondo de pantalla y marcos
    scrolled_window = gtk_scrolled_window_new (NULL, NULL);
    gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled_window),GTK_POLICY_AUTOMATIC,GTK_POLICY_AUTOMATIC);
    gtk_widget_set_size_request (scrolled_window, 1000, 550);
    fixed = gtk_fixed_new();

    //define color de fondo de la ventana
    GdkColor color;
    gdk_color_parse("#119BAB", &color);
    gtk_widget_modify_bg(scrolled_window, GTK_STATE_NORMAL, &color);
    double res[plazo+1];
    int plan[plazo+1][plazo+2];
    remplazo(res,plan,lista);
    char texto[512];
    int num = 0;
    for(int i=-1;i <plazo+1;i++){
    	num =0;
    	char buffer[255] = "";
    	char buffer2[255] ="";
    	if(i != -1){
    		while(plan[i][num] != -1){
    			if(plan[i][num+1] == -1){
    				sprintf(buffer2,"%d",plan[i][num]);
    			}
    			else{
    				sprintf(buffer2,"%d,",plan[i][num]);
    			}
    			strcat(buffer,buffer2);
    			num++;
    		}
    		strcat(texto,buffer);
        	sprintf(texto,"%d",i);
        	GtkWidget *lblName1 = gtk_label_new(texto);
        	gtk_fixed_put(GTK_FIXED(fixed), lblName1, 60+120, 100+50*i);

        	sprintf(texto,"%f",res[i]);
        	GtkWidget *lblName2 = gtk_label_new(texto);
        	gtk_fixed_put(GTK_FIXED(fixed), lblName2, 110+170, 100+50*i);



        	GtkWidget *lblName3 = gtk_label_new(buffer);
        	gtk_fixed_put(GTK_FIXED(fixed), lblName3,  70+370, 100+50*i);
    	}
    	else{
    		sprintf(texto,"Valor T");
        	GtkWidget *lblName1 = gtk_label_new(texto);
        	gtk_fixed_put(GTK_FIXED(fixed), lblName1, 50+120, 50);
        	
        	sprintf(texto,"G(T)");
        	GtkWidget *lblName2 = gtk_label_new(texto);
        	gtk_fixed_put(GTK_FIXED(fixed), lblName2, 125+170,50);

        	sprintf(texto,"Próximo");
        	GtkWidget *lblName3 = gtk_label_new(texto);
        	gtk_fixed_put(GTK_FIXED(fixed), lblName3, 50+370,50);
    	}
    }
	//Creación y configuración del botón de siguiente
    btnSiguiente = gtk_button_new_with_label("");
    g_signal_connect(btnSiguiente, "clicked", G_CALLBACK(ventanaSolucion), (gpointer) windowTabla);
    gtk_fixed_put(GTK_FIXED(fixed), btnSiguiente, 550, 200+50*(plazo+2));
    GtkWidget *imgSiguiente = gtk_image_new_from_file("button_siguiente.png");
    gtk_button_set_always_show_image(GTK_BUTTON(btnSiguiente),TRUE);
    gtk_button_set_image(GTK_BUTTON(btnSiguiente), imgSiguiente);
    g_object_set_data(G_OBJECT(btnSiguiente), "lista",lista);
    g_object_set_data(G_OBJECT(btnSiguiente), "plan",plan);


    //Creación y configuración del botón de volver
    btnVolver = gtk_button_new_with_label("");
    g_signal_connect(btnVolver, "clicked", G_CALLBACK(volverAPrincipal), (gpointer) windowTabla);
    gtk_fixed_put(GTK_FIXED(fixed), btnVolver, 50, 200+50*(plazo+2));
    GtkWidget *imgVolver = gtk_image_new_from_file("button_volver.png");
    gtk_button_set_always_show_image(GTK_BUTTON(btnVolver),TRUE);
    gtk_button_set_image(GTK_BUTTON(btnVolver), imgVolver);

    

    //configuración final
    gtk_container_add(GTK_CONTAINER(scrolled_window),fixed);
    gtk_container_add(GTK_CONTAINER(windowTabla),scrolled_window);
    gtk_widget_show_all(windowTabla);
    gtk_main();
}
