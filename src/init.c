#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/reboot.h>
#include <linux/reboot.h>
#include <sys/mount.h>
#include <dirent.h>


void criar_arquivo(const char *nome_arquivo);
void ler_arquivo(const char *nome_arquivo);
void listas_arquivo();

int main(){

mount("none", "/", NULL, MS_REMOUNT, NULL);


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
			printf("	ajuda   -    Mostrar ajuda\n");
			printf("	sobre   -    Informaçoes sobre sistema\n");
			printf("	sair    -    Desligar o computador\n");
			printf("    criar <arquivo>  -    criar um arquivo de texto\n");
			printf("     ler <arquivo>  -    ler uma arquivo de texto\n");
			printf("	listar ou ls - lista os arquivo da pasta atual\n");
		}
		else if(strcmp(comando, "sobre") == 0){
			printf("Alpha OS e um sistema operacional Compile-To-Configure feito puramente em C\nDesenvolvido por Alex Sander Domingues\n");
		}
		else if(strcmp(comando, "sair") == 0){
			printf("Saindo do Alpha OS ...\n");
			sync();
			reboot(LINUX_REBOOT_CMD_POWER_OFF); //REBOOT PARA PLACA MAE
		
		}
		else if(strcmp(comando,"listar") == 0 || strcmp(comando,"ls") == 0){
			listar_arquivo();
		}
		else if(strncmp(comando,"ler ",4) == 0 || strncmp(comando,"cat ",4) == 0){
			ler_arquivo(comando + 4);	
		}
		else if(strncmp(comando,"criar ",6) == 0 || strncmp(comando,"touch ",6) == 0){
			criar_arquivo(comando + 6);
		}
		else{
			printf("Comando nao encontrado: %s",comando);
		}
	}
	

}

	return 0;

}

void criar_arquivo(const char *nome_arquivo){
	
	FILE *arquivo = fopen(nome_arquivo,"a");
	
	if(arquivo == NULL){
		printf("Erro ao criar arquivo!\n");
		return;
	}

	printf("==========================================\n");
	printf("MODO DE ESCRITA\nPara salvar e sair digite ':q' e de enter em uma nova linha\n");
	printf("==========================================\n");
	
	char linha[256];

	while(1){

		printf("> ");
		
		if(fgets(linha,sizeof(linha),stdin) != NULL){
		
			if(strncmp(linha, ":q\n", 3) == 0 || strcmp(linha,":q") == 0){
				break;
			}
			fputs(linha,arquivo);
		}

	}

	fclose(arquivo);

}

void ler_arquivo(const char *nome_arquivo){

	FILE *arquivo = fopen(nome_arquivo,"r");
	if(arquivo == NULL){
		printf("Erro ao ler arquivo!\n");
		return;
	}
	
	char linha[256];

	while(fgets(linha,sizeof(linha),arquivo)){
		printf("%s",linha);
	}
	fclose(arquivo);

}

void listar_arquivo(){

	DIR *d;
	struct dirent *dir;
	
	d = opendir(".");

	if(d){
		printf("Conteudo da pasta atual:\n");
		while((dir= readdir(d)) != NULL){
			if(dir->d_name[0] != "."){
				printf("   [Arquivo] %s\n",dir->d_name);
			}
		}
		closedir(d);
	
	}else{
		printf("Erro: Nao foi possivel ler o diretorio!");
	}

}
