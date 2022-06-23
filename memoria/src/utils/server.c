#include <utils/server.h>

void deserializarSegun(t_paquete* paquete, int socket){

	switch(paquete->codigo_operacion){
		case REQ_TRADUCCION_DIRECCIONES_CPU_MEMORIA:{
            log_info(logger, "se solicita traducciones de direciones");
            t_traduccion_direcciones * traduccionDirecciones = malloc(sizeof(t_traduccion_direcciones));
            
            traduccionDirecciones->tamanio_pagina = TAM_PAGINA;
            traduccionDirecciones->paginas_por_tabla = ENTRADAS_POR_TABLA;
            t_paquete* paquete = armarPaqueteCon(traduccionDirecciones, RES_TRADUCCION_DIRECCIONES_MEMORIA_CPU);
            enviarPaquete(paquete,socket);
            log_info(logger, "se envia traducciones de direciones");
			break;
        }
        case REQ_CREAR_PROCESO_KERNEL_MEMORIA:{
            log_info(logger, "se solicita crear proceso");
            
            t_pcb * pcb = deserializarPCB(paquete->buffer->stream, 0);
            uint32_t * tablaPaginas1erNivel = malloc(sizeof(uint32_t));
            * tablaPaginas1erNivel = inicializarEstructurasProceso(pcb->tamanioProceso);
            t_paquete* paqueteRespuesta = armarPaqueteCon(tablaPaginas1erNivel, RES_CREAR_PROCESO_KERNEL_MEMORIA);
            crearArchivoSwap(pcb->id, pcb->tamanioProceso);
            enviarPaquete(paqueteRespuesta,socket);
            eliminarPaquete(paqueteRespuesta);
            log_info(logger, "se envia tabla Paginas 1er Nivel");
			break;
        }
        case REQ_FIN_PROCESO_KERNEL_MEMORIA:{
            t_pcb * pcb = deserializarPCB(paquete->buffer->stream, 0);
            //eliminar pcb->id.swap
            suspenderProceso(pcb);
            eliminarMarcos(pcb->tablaDePaginas);
            eliminarArchivoSwap(pcb -> id);
            freePCB(pcb);
            log_info(logger, "se solicita borrar memoria y swap del proceso: %d", pcb->id);
            break;
        }

        case REQ_SUSP_PROCESO_KERNEL_MEMORIA:{
            t_pcb * pcb = deserializarPCB(paquete->buffer->stream, 0);
            suspenderProceso(pcb);
            freePCB(pcb);
            break;
        }
        case REQ_DESUSP_PROCESO_KERNEL_MEMORIA:{
            //por que hacemos esto? no sabemos que paginas necesitariamos
            //levantar del swap para colocar en memoria
            //al pasar de susp a ready no debemos mandar este mensaje
            t_pcb * pcb = deserializarPCB(paquete->buffer->stream, 0);
            desuspenderProceso(pcb);
            //RESPUESTA A KERNEL
            freePCB(pcb);
            break;
        }
        
		default:{
            break;
        }
			
    }
	eliminarPaquete(paquete);
	close(socket);
}