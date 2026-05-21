#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/reboot.h>
#include <linux/reboot.h>
#include <sys/mount.h>
#include <dirent.h>
#include "config.h" // <--- Injeta as configurações aqui!

// Declarações corretas das funções
void criar_arquivo(const char *nome_arquivo);
void ler_arquivo(const char *nome_arquivo);
void listar_arquivo();
void remover_arquivo(const char *nome_arquivo);

int main() {
    // Remonta o rootfs se necessário
    mount("none", "/", NULL, MS_REMOUNT, NULL);
    mkdir(PONTO_MONTAGEM, 0777); 
    
    // Tenta montar o HD externo (/dev/sdb1) na pasta /data usando o sistema Ext4
    if (mount(DISCO_PERSISTENCIA, PONTO_MONTAGEM, "ext4", 0, NULL) == 0) {
        printf("\033[0;32m[SUCESSO] Persistencia ativada em %s\033[0m\n", PONTO_MONTAGEM);
    } else {
        printf("\033[0;31m[AVISO] Nao foi possivel montar o HD Externo. Rodando apenas em RAM.\033[0m\n");
    }


    // Banner Inicial usando as cores e textos do config.h
    printf("%s", OS_COLOR_BANNER);
    printf("##############################################\n");
    printf("#\t%s\t#\n", OS_TITLE);
    printf("##############################################\n");
    printf("%s", OS_COLOR_RESET);

    printf("%s\n", OS_DESCRIPTION);
    printf("Aguardando comandos...\n");

    char comando[MAX_COMMAND_LENGTH];

    while (1) {
        printf("%s", PROMPT_STYLE);
        fflush(stdout); // Garante que o prompt apareça antes do input

        // Leitura de teclado
        if (fgets(comando, sizeof(comando), stdin) != NULL) {
            comando[strcspn(comando, "\n")] = 0;

            if (strlen(comando) == 0) {
                continue;
            }
            
            // --- COMANDO: ajuda ---
            if (strcmp(comando, "ajuda") == 0) {
                printf("Comandos disponiveis:\n");
                printf("\tajuda            -    Mostrar ajuda\n");
                printf("\tsobre            -    Informaçoes sobre sistema\n");
                printf("\tsair             -    Desligar o computador\n");
		printf("\tlimpar           -    Limpa a tela do terminal\n");
                printf("    criar <arquivo>  -    Criar um arquivo de texto\n");
                printf("    ler <arquivo>    -    Ler um arquivo de texto\n");
		printf("    remover  ou  rm <arq>    -    Deletar um arquivo de texto\n");
                printf("\tlistar ou ls     -    Lista os arquivos da pasta atual\n");
            }
            // --- COMANDO: sobre ---
            else if (strcmp(comando, "sobre") == 0) {
                printf("%s", OS_ABOUT);
            }
            // --- COMANDO: sair ---
            else if (strcmp(comando, "sair") == 0) {
                printf("Saindo do Alpha OS ...\n");
                sync();
                reboot(LINUX_REBOOT_CMD_POWER_OFF); 
            }
	    // --- COMANDO: limpar  ---
	    else if (strcmp(comando, "limpar") == 0 || strcmp(comando, "clear") == 0) {
                printf("\033[H\033[J");
            }
            // --- COMANDO: listar/ls ---
            else if (strcmp(comando, "listar") == 0 || strcmp(comando, "ls") == 0) {
                listar_arquivo();
            }
            // --- COMANDO: ler/cat ---
            else if (strncmp(comando, "ler ", 4) == 0) {
                ler_arquivo(comando + 4);    
            }
            else if (strncmp(comando, "cat ", 4) == 0) {
                ler_arquivo(comando + 4);    
            }
            // --- COMANDO: criar/touch ---
            else if (strncmp(comando, "criar ", 6) == 0) {
                criar_arquivo(comando + 6);
            }
            else if (strncmp(comando, "touch ", 6) == 0) {
                criar_arquivo(comando + 6);
            }
	    // --- COMANDO: remover/rm (Recurso 2) ---
            else if (strncmp(comando, "remover ", 8) == 0) {
                remover_arquivo(comando + 8);
            }
            else if (strncmp(comando, "rm ", 3) == 0) {
                remover_arquivo(comando + 3);
            }
            // --- COMANDO DESCONHECIDO ---
            else {
                printf("Comando nao encontrado: %s\n", comando);
            }
        }
    }

    return 0;
}

// --- FUNÇÃO: Criar Arquivo ---
void criar_arquivo(const char *nome_arquivo) {
    FILE *arquivo = fopen(nome_arquivo, "a");
    
    if (arquivo == NULL) {
        printf("Erro ao criar arquivo!\n");
        return;
    }

    printf("==========================================\n");
    printf("MODO DE ESCRITA\nPara salvar e sair digite ':q' e de enter em uma nova linha\n");
    printf("==========================================\n");
    
    char linha[MAX_LINE_LENGTH];

    while (1) {
        printf("> ");
        if (fgets(linha, sizeof(linha), stdin) != NULL) {
            // Verifica o comando de saída :q
            if (strncmp(linha, ":q\n", 3) == 0 || strcmp(linha, ":q") == 0) {
                break;
            }
            fputs(linha, arquivo);
        }
    }

    fclose(arquivo);
}

// --- FUNÇÃO: Ler Arquivo ---
void ler_arquivo(const char *nome_arquivo) {
    FILE *arquivo = fopen(nome_arquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao ler arquivo!\n");
        return;
    }
    
    char linha[MAX_LINE_LENGTH];

    while (fgets(linha, sizeof(linha), arquivo)) {
        printf("%s", linha);
    }
    fclose(arquivo);
}

void remover_arquivo(const char *nome_arquivo) {
    if (remove(nome_arquivo) == 0) {
        printf("Arquivo '%s' removido com sucesso.\n", nome_arquivo);
    } else {
        printf("Erro: Nao foi possivel remover o arquivo '%s'.\n", nome_arquivo);
    }
}

// --- FUNÇÃO: Listar Arquivos ---

void listar_arquivo() {
    DIR *d;
    struct dirent *dir;
    
    d = opendir(".");

    if (d) {
        printf("Conteudo da pasta atual:\n");
        while ((dir = readdir(d)) != NULL) {
            if (dir->d_name[0] != '.') {
                // Aplica a cor do config.h antes de printar o nome do arquivo
                printf("   [Arquivo] %s%s%s\n", OS_COLOR_FILE, dir->d_name, OS_COLOR_RESET);
            }
        }
        closedir(d);
    } else {
        printf("Erro: Nao foi possivel leer o diretorio!\n");
    }
}
