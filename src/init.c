#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/reboot.h>
#include <linux/reboot.h>


int main(){

printf("\033[0;32m\n");
printf("##############################################\n");
printf("#	AlphaOS - Kernel Iniciado	#\n");
printf("##############################################\n");

printf("\033[0m");

printf("Alpha OS esta rodando atraves de binario estatico.\n");
printf("Aguardando comandos...\n");

char comando[256];

while(1){
	printf("AlphaOS# ");
	//leitura de teclado
	if(fgets(comando,sizeof(comando),stdin) != NULL){
		comando[strcspn(comando,"\n")] = 0;

		if (strlen(comando) == 0){

			continue;
		}
		
		if(strcmp(comando , "ajuda") == 0){
			printf("Comando disponiveis:\n");
			printf("    ajuda   -    Mostrar ajuda\n");
			printf("    sobre   -    Informaçoes sobre sistema\n");
			printf("    sair    -    Desligar o computador\n");
		}
		else if(strcmp(comando, "sobre") == 0){
			printf("Alpha OS e um sistema operacional Compile-To-Configure feito puramente em C\n");
		}
		else if(strcmp(comando, "sair") == 0){
			printf("Saindo do Alpha OS ...\n");
			sync();
			reboot(LINUX_REBOOT_CMD_POWER_OFF); //REBOOT PARA PLACA MAE
		
		}
		else{
			printf("Comando nao encontrado: %s",comando);
		}
	}
	

}

	return 0;



}
