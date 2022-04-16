#include <utils/inicializacion.h>

void validarParametros(int argc, char* argv[]){
    if (argc < 3) {
        fprintf(stderr, "Se esperaban: %s [INSTRUCCIONES_PROCESO], [TAMANIO_PROCESO]\n", argv[0]);
        exit(EXIT_FAILURE);
    }
}
t_list* obtenerInstrucciones(char* pathInstruccion){
    char** instruccionesSeparadas = string_split(pathInstruccion,"\n");
    int i = 0;
    t_list* instrucciones = list_create();
    
    while(instruccionesSeparadas[i]!=NULL){
        t_instruccion* instruccion = obtenerInstruccion(instruccionesSeparadas[i]);
        list_add(instrucciones, (void *) instruccion);
        i++;
    }
    return instrucciones;
}