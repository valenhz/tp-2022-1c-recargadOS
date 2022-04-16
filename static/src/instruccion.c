#include <instruccion.h>

t_instruccion* obtenerInstruccion(char* instruccionTexto){
    
    t_instruccion* instruccion = malloc(sizeof(t_instruccion));
    char** instruccionSeparada = string_split(instruccionTexto," ");
    
    if(string_contains(instruccionSeparada[0],"NO_OP")){
        instruccion->identificador=NO_OP;
        instruccion->parametro1=atoi(instruccionSeparada[1]);
    }
    else if(string_contains(instruccionSeparada[0],"I/O")){
        instruccion->identificador=IO;
        instruccion->parametro1=atoi(instruccionSeparada[1]);
    }
    else if(string_contains(instruccionSeparada[0],"READ")){
        instruccion->identificador=READ;
        instruccion->parametro1=atoi(instruccionSeparada[1]);
    }
    else if(string_contains(instruccionSeparada[0],"COPY")){
        instruccion->identificador=COPY;
        instruccion->parametro1=atoi(instruccionSeparada[1]);
        instruccion->parametro2=atoi(instruccionSeparada[2]);
    }
    else if(string_contains(instruccionSeparada[0],"WRITE")){
        instruccion->identificador=WRITE;
        instruccion->parametro1=atoi(instruccionSeparada[1]);
        instruccion->parametro2=atoi(instruccionSeparada[2]);
    }
    else if(string_contains(instruccionSeparada[0],"EXIT")){
        instruccion->identificador=EXIT;
    }
    else{
        fprintf(stderr, "La instruccion: %s no está contemplada\n", instruccionSeparada[0]);
        exit(EXIT_FAILURE);
    }
    return instruccion;
}