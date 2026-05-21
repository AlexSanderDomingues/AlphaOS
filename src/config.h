/* * AlphaOS - Painel de Configuração (Compile to Configure)
 * Modifique os valores abaixo para personalizar o sistema sem mexer na lógica do init.c
 */

#ifndef CONFIG_H
#define CONFIG_H

// --- Identidade e Textos ---
#define OS_TITLE        "AlphaOS - Kernel Iniciado"
#define OS_DESCRIPTION  "Alpha OS esta rodando atraves de binario estatico."
#define OS_ABOUT        "Alpha OS e um sistema operacional Compile-To-Configure feito puramente em C\nDesenvolvido por Alex Sander Domingues\n"
#define PROMPT_STYLE    "AlphaOS# "
#define DEVELOPER_NAME  "Alex Sander Domingues"

// --- Cores do Terminal (Códigos ANSI) ---
// \033[0;32m = Verde, \033[0m = Reset
#define OS_COLOR_FILE   "\033[1;34m"  // Azul Negrito
#define OS_COLOR_BANNER "\033[0;32m"
#define OS_COLOR_RESET  "\033[0m"
// --- Disco --- 
#define DISCO_PERSISTENCIA "/dev/sdb1"
#define PONTO_MONTAGEM "/data"



// --- Limites do Sistema ---
#define MAX_COMMAND_LENGTH 256
#define MAX_LINE_LENGTH    256

#endif // CONFIG_H
