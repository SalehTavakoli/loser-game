#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "clui.h"

// GLOBAL INITILIZATION
const short int DEBUG = 1;
int _accounts_number;
char tried_letters[100];
char current_username[16];

typedef struct {
    char username[16];
    char password[16];
    int score;
} account;

// Functions prototypes
void show_menu_2(char* error, account* accounts);
void show_menu_1(char* error, account* accounts);
void handle_signup(char* error, account* accounts, char* filled_username);
void handle_login(char* error, account* accounts);
void handle_new_word(char* error, account* accounts);
void random_word(char word[20]);


void c(){
    system("clear");
}

void empty_tried_letters(){    
    for (int i = 0; i < 100; i++) {
        tried_letters[i] = '\0';
    }
}

void draw_title(int mode){
    switch(mode){
        case 0:
            printf(
"$$\\       $$$$$$\\   $$$$$$\\  $$$$$$$$\\ $$$$$$$\\               $$$$$$\\   $$$$$$\\  $$\\      $$\\ $$$$$$$$\\ \n"
"$$ |     $$  __$$\\ $$  __$$\\ $$  _____|$$  __$$\\             $$  __$$\\ $$  __$$\\ $$$\\    $$$ |$$  _____|\n"
"$$ |     $$ /  $$ |$$ /  \\__|$$ |      $$ |  $$ |            $$ /  \\__|$$ /  $$ |$$$$\\  $$$$ |$$ |      \n"
"$$ |     $$ |  $$ |\\$$$$$$\\  $$$$$\\    $$$$$$$  |            $$ |$$$$\\ $$$$$$$$ |$$\\$$\\$$ $$ |$$$$$\\    \n"
"$$ |     $$ |  $$ | \\____$$\\ $$  __|   $$  __$$<             $$ |\\_$$ |$$  __$$ |$$ \\$$$  $$ |$$  __|   \n"
"$$ |     $$ |  $$ |$$\\   $$ |$$ |      $$ |  $$ |            $$ |  $$ |$$ |  $$ |$$ |\\$  /$$ |$$ |      \n"
"$$$$$$$$\\ $$$$$$  |\\$$$$$$  |$$$$$$$$\\ $$ |  $$ |            \\$$$$$$  |$$ |  $$ |$$ | \\_/ $$ |$$$$$$$$\\ \n"
"\\________|\\______/  \\______/ \\________|\\__|  \\__|             \\______/ \\__|  \\__|\\__|     \\__|\\________|\n"
);
            break;

        case 1:
            printf(
                
"$$\\       $$$$$$\\   $$$$$$\\  $$$$$$\\ $$\\   $$\\       $$$$$$$\\   $$$$$$\\   $$$$$$\\  $$$$$$$$\\ \n"
"$$ |     $$  __$$\\ $$  __$$\\ \\_$$  _|$$$\\  $$ |      $$  __$$\\ $$  __$$\\ $$  __$$\\ $$  _____|\n"
"$$ |     $$ /  $$ |$$ /  \\__|  $$ |  $$$$\\ $$ |      $$ |  $$ |$$ /  $$ |$$ /  \\__|$$ |      \n"
"$$ |     $$ |  $$ |$$ |$$$$\\   $$ |  $$ $$\\$$ |      $$$$$$$  |$$$$$$$$ |$$ |$$$$\\ $$$$$\\    \n"
"$$ |     $$ |  $$ |$$ |\\_$$ |  $$ |  $$ \\$$$$ |      $$  ____/ $$  __$$ |$$ |\\_$$ |$$  __|   \n"
"$$ |     $$ |  $$ |$$ |  $$ |  $$ |  $$ |\\$$$ |      $$ |      $$ |  $$ |$$ |  $$ |$$ |      \n"
"$$$$$$$$\\ $$$$$$  |\\$$$$$$  |$$$$$$\\ $$ | \\$$ |      $$ |      $$ |  $$ |\\$$$$$$  |$$$$$$$$\\ \n"
"\\________|\\______/  \\______/ \\______|\\__|  \\__|      \\__|      \\__|  \\__| \\______/ \\________|\n"
            );
            break;

        case 2:
            printf(
                " $$$$$$\\  $$$$$$\\  $$$$$$\\  $$\\   $$\\ $$\\   $$\\ $$$$$$$\\        $$$$$$$\\   $$$$$$\\   $$$$$$\\  $$$$$$$$\\ \n"
"$$  __$$\\ \\_$$  _|$$  __$$\\ $$$\\  $$ |$$ |  $$ |$$  __$$\\       $$  __$$\\ $$  __$$\\ $$  __$$\\ $$  _____|\n"
"$$ /  \\__|  $$ |  $$ /  \\__|$$$$\\ $$ |$$ |  $$ |$$ |  $$ |      $$ |  $$ |$$ /  $$ |$$ /  \\__|$$ |      \n"
"\\$$$$$$\\    $$ |  $$ |$$$$\\ $$ $$\\$$ |$$ |  $$ |$$$$$$$  |      $$$$$$$  |$$$$$$$$ |$$ |$$$$\\ $$$$$\\    \n"
" \\____$$\\   $$ |  $$ |\\_$$ |$$ \\$$$$ |$$ |  $$ |$$  ____/       $$  ____/ $$  __$$ |$$ |\\_$$ |$$  __|   \n"
"$$\\   $$ |  $$ |  $$ |  $$ |$$ |\\$$$ |$$ |  $$ |$$ |            $$ |      $$ |  $$ |$$ |  $$ |$$ |      \n"
"\\$$$$$$  |$$$$$$\\ \\$$$$$$  |$$ | \\$$ |\\$$$$$$  |$$ |            $$ |      $$ |  $$ |\\$$$$$$  |$$$$$$$$\\ \n"
" \\______/ \\______| \\______/ \\__|  \\__| \\______/ \\__|            \\__|      \\__|  \\__| \\______/ \\________|\n"
            );
            break;

        case 3:
            printf(
                "$$\\       $$$$$$$$\\  $$$$$$\\  $$$$$$$\\  $$$$$$$$\\ $$$$$$$\\  $$$$$$$\\   $$$$$$\\   $$$$$$\\  $$$$$$$\\  $$$$$$$\\  \n"
    "$$ |      $$  _____|$$  __$$\\ $$  __$$\\ $$  _____|$$  __$$\\ $$  __$$\\ $$  __$$\\ $$  __$$\\ $$  __$$\\ $$  __$$\\ \n"
    "$$ |      $$ |      $$ /  $$ |$$ |  $$ |$$ |      $$ |  $$ |$$ |  $$ |$$ /  $$ |$$ /  $$ |$$ |  $$ |$$ |  $$ |\n"
    "$$ |      $$$$$\\    $$$$$$$$ |$$ |  $$ |$$$$$\\    $$$$$$$  |$$$$$$$\\ |$$ |  $$ |$$$$$$$$ |$$$$$$$  |$$ |  $$ |\n"
    "$$ |      $$  __|   $$  __$$ |$$ |  $$ |$$  __|   $$  __$$< $$  __$$\\ $$ |  $$ |$$  __$$ |$$  __$$< $$ |  $$ |\n"
    "$$ |      $$ |      $$ |  $$ |$$ |  $$ |$$ |      $$ |  $$ |$$ |  $$ |$$ |  $$ |$$ |  $$ |$$ |  $$ |$$ |  $$ |\n"
    "$$$$$$$$\\ $$$$$$$$\\ $$ |  $$ |$$$$$$$  |$$$$$$$$\\ $$ |  $$ |$$$$$$$  | $$$$$$  |$$ |  $$ |$$ |  $$ |$$$$$$$  |\n"
    "\\________|\\________|\\__|  \\__|\\_______/ \\________|\\__|  \\__|\\_______/  \\______/ \\__|  \\__|\\__|  \\__|\\_______/ \n"
            );
            break;

        case 4:
            printf(
                "$$\\   $$\\ $$$$$$$$\\ $$\\      $$\\       $$\\      $$\\  $$$$$$\\  $$$$$$$\\  $$$$$$$\\  \n"
    "$$$\\  $$ |$$  _____|$$ | $\\  $$ |      $$ | $\\  $$ |$$  __$$\\ $$  __$$\\ $$  __$$\\ \n"
    "$$$$\\ $$ |$$ |      $$ |$$$\\ $$ |      $$ |$$$\\ $$ |$$ /  $$ |$$ |  $$ |$$ |  $$ |\n"
    "$$ $$\\$$ |$$$$$\\    $$ $$ $$\\$$ |      $$ $$ $$\\$$ |$$ |  $$ |$$$$$$$  |$$ |  $$ |\n"
    "$$ \\$$$$ |$$  __|   $$$$  _$$$$ |      $$$$  _$$$$ |$$ |  $$ |$$  __$$< $$ |  $$ |\n"
    "$$ |\\$$$ |$$ |      $$$  / \\$$$ |      $$$  / \\$$$ |$$ |  $$ |$$ |  $$ |$$ |  $$ |\n"
    "$$ | \\$$ |$$$$$$$$\\ $$  /   \\$$ |      $$  /   \\$$ | $$$$$$  |$$ |  $$ |$$$$$$$  |\n"
    "\\__|  \\__|\\________|\\__/     \\__|      \\__/     \\__| \\______/ \\__|  \\__|\\_______/ \n"
            );
            break;
    }
    printf("\n\n");
}
// Get file lines number
int file_number(short int type){
    FILE* fp;
    if(type==1) fp = fopen("accounts.txt", "r");
    else if (type==2) fp = fopen("words.txt", "r");

    if (fp == NULL){
        return 0;
    }

    char ch;
    int lines = 1;
    while(!feof(fp)){
        ch = fgetc(fp);
        if(ch == '\n'){
            lines++;
        }
    }

    rewind(fp);
    return lines;
}

void get_accounts(account* accounts){
    char username[16], password[16];
    int score;

    FILE* fp = fopen("accounts.txt", "r");    

    for (int i = 0; i < _accounts_number; i++){        
        fscanf(fp, "%s %s %d", username, password, &score);
        strcpy(accounts[i].username, username);
        strcpy(accounts[i].password, password);
        accounts[i].score = score;
        // printf("USERNAME: '%s' - PASSWORD: '%s' - SCORE: '%d'\n", username, password, score);
    }
    strcpy(accounts[_accounts_number].username, "unset");

    // if(DEBUG) printf("IMPORTED %d ACCOUNTS", &_accounts_number);
}

char* show_error(char* error){
    if(*error != '\0'){
        change_color_rgb(150, 15, 15);
        printf("ERROR: %s\n", error);
        change_color_rgb(215, 215, 0);
    }
}

void update_accounts_file(account* accounts){
    FILE* fp = fopen("accounts.txt", "w");
    for (int i = 0; i < _accounts_number+1; i++) {
        fprintf(fp, "%s %s %d", accounts[i].username, accounts[i].password, accounts[i].score);
        if (i!=_accounts_number) {
            fputc('\n', fp);
        }
    }
    fclose(fp);
}

short int validate_password(char* password){
    int len;
    // small - capital - digit - special char
    short int flag1 = 0, flag2 = 0, flag3 = 0, flag4;

    len = strlen(password);

    if (len >= 8 && len <= 16){ //checking length of string 
        for (int i = 0; i < len; i++){
            if (islower(password[i])) //small letter 
                flag1 = 1;

            else if (isupper(password[i])) //capital letter 
                flag2 = 1;

            else if (isdigit(password[i])) //digit 
                flag3 = 1;
            else if (strchr("!@#$%&'()*+,-./:;<=>?@[]^_`{|}~", password[i])) //special chars
                flag4 = 1;
        }
        if (flag1 == 1 && flag2 == 1 && flag3 == 1 && flag4 == 1)
            return 1;
    }
    return 0;
}

void handle_signup(char* error, account* accounts, char* filled_username){
    c();
    char username[16], password[17];
    draw_title(2);
    show_error(error);

    printf("USERNAME: ");
    if(*filled_username != '\0'){
        strcpy(username, filled_username);
        printf("%s\n", filled_username);
    }
    else scanf("%s", username);

    // Check if username is taken or not
    for (int i = 0; i < _accounts_number; i++){
        if (strcmp(accounts[i].username, username) == 0){
            handle_signup("THIS USERNAME IS ALREADY TAKEN PLEASE CHOOSE ANOTHER ONE.", accounts, "\0");
            return;
        }
    }

    printf("PASSWORD: ");
    scanf("%s", password);
    
    if (!validate_password(password)){
        handle_signup("PASSWORD MUST BE 8-16 CHARACTERS, CONTAIN AT LEAST ONE SMALL LETTER, ONE CAPITAL LETTER, A DIGIT AND A SPECIAL CHARACTER(!, @, $, # ...)", accounts, username);
    }
    

    strcpy(accounts[_accounts_number].username, username);
    strcpy(accounts[_accounts_number].password, password);
    accounts[_accounts_number].score = 0;
    update_accounts_file(accounts);
    strcpy(current_username, username);
    show_menu_2("", accounts);
    return;

}

void handle_exit(){
    c();
    int wait_time = 20;
    printf(
" /$$$$$$$ \n"
"| $$__  $$\n"
"| $$  \\ $$\n"
"| $$$$$$$ \n"
"| $$__  $$\n"
"| $$  \\ $$\n"
"| $$$$$$$/\n"
"|_______/ \n"
    );
    delay(wait_time);
    
    c();
    printf(
" /$$$$$$$  /$$     /$$\n"
"| $$__  $$|  $$   /$$/\n"
"| $$  \\ $$ \\  $$ /$$/ \n"
"| $$$$$$$   \\  $$$$/  \n"
"| $$__  $$   \\  $$/   \n"
"| $$  \\ $$    | $$    \n"
"| $$$$$$$/    | $$    \n"
"|_______/     |__/    \n"
    );
    delay(wait_time);

    c();
    printf(
" /$$$$$$$  /$$     /$$ /$$$$$$$$\n"
"| $$__  $$|  $$   /$$/| $$_____/\n"
"| $$  \\ $$ \\  $$ /$$/ | $$      \n"
"| $$$$$$$   \\  $$$$/  | $$$$$   \n"
"| $$__  $$   \\  $$/   | $$__/   \n"
"| $$  \\ $$    | $$    | $$      \n"
"| $$$$$$$/    | $$    | $$$$$$$$\n"
"|_______/     |__/    |________/\n"
    );
    delay(wait_time);

    c();
    printf(
" /$$$$$$$  /$$     /$$ /$$$$$$$$       /$$$$$$$ \n"
"| $$__  $$|  $$   /$$/| $$_____/      | $$__  $$\n"
"| $$  \\ $$ \\  $$ /$$/ | $$            | $$  \\ $$\n"
"| $$$$$$$   \\  $$$$/  | $$$$$         | $$$$$$$ \n"
"| $$__  $$   \\  $$/   | $$__/         | $$__  $$\n"
"| $$  \\ $$    | $$    | $$            | $$  \\ $$\n"
"| $$$$$$$/    | $$    | $$$$$$$$      | $$$$$$$/\n"
"|_______/     |__/    |________/      |_______/ \n"
    );
    delay(wait_time);

    c();
    printf(
" /$$$$$$$  /$$     /$$ /$$$$$$$$       /$$$$$$$  /$$     /$$\n"
"| $$__  $$|  $$   /$$/| $$_____/      | $$__  $$|  $$   /$$/\n"
"| $$  \\ $$ \\  $$ /$$/ | $$            | $$  \\ $$ \\  $$ /$$/ \n"
"| $$$$$$$   \\  $$$$/  | $$$$$         | $$$$$$$   \\  $$$$/  \n"
"| $$__  $$   \\  $$/   | $$__/         | $$__  $$   \\  $$/   \n"
"| $$  \\ $$    | $$    | $$            | $$  \\ $$    | $$    \n"
"| $$$$$$$/    | $$    | $$$$$$$$      | $$$$$$$/    | $$    \n"
"|_______/     |__/    |________/      |_______/     |__/    \n"
    );
    delay(wait_time);

    c();
    printf(
" /$$$$$$$  /$$     /$$ /$$$$$$$$       /$$$$$$$  /$$     /$$ /$$$$$$$$\n"
"| $$__  $$|  $$   /$$/| $$_____/      | $$__  $$|  $$   /$$/| $$_____/\n"
"| $$  \\ $$ \\  $$ /$$/ | $$            | $$  \\ $$ \\  $$ /$$/ | $$      \n"
"| $$$$$$$   \\  $$$$/  | $$$$$         | $$$$$$$   \\  $$$$/  | $$$$$   \n"
"| $$__  $$   \\  $$/   | $$__/         | $$__  $$   \\  $$/   | $$__/   \n"
"| $$  \\ $$    | $$    | $$            | $$  \\ $$    | $$    | $$      \n"
"| $$$$$$$/    | $$    | $$$$$$$$      | $$$$$$$/    | $$    | $$$$$$$$\n"
"|_______/     |__/    |________/      |_______/     |__/    |________/\n"
    );
    delay(wait_time);

    exit(1);
}

void show_menu_1(char* error, account* accounts){
    c();
    draw_title(0);
    printf("1. Login\n2. Signup\n3. Exit\n");
    show_error(error);
    printf(">>> ");
    short int choice;
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
        handle_login("", accounts);
        return;
    case 2:
        handle_signup("", accounts, "\0");
        return;
    case 3:
        handle_exit();        
    
    default:
        show_menu_1("PLEASE ENTER A VALID MENU NUMBER.", accounts);
    }
}

short int word_exists(char* word){
    FILE *words_file = fopen("words.txt", "r");
    char file_word[100];
    while(!feof(words_file)){
        fscanf(words_file, "%s", file_word);
        if (strcmp(file_word, word) == 0) {
            return 1;
        }
    }
    return 0;
}

short int words_file_exist(){
    FILE *words_file = fopen("words.txt", "r");

    if (words_file == NULL) return 0;
    else return 1;
}

void handle_leaderboard(account* accounts){
    c();
    draw_title(3);

    for (int i = 0; i < _accounts_number+1; i++) {
        int username_length = strlen(accounts[i].username);
        if(strcmp(accounts[i].username, "unset") != 0){
            printf("%s", accounts[i].username);
            for (int i = 0; i < 20-username_length; i++) {
                printf("-");
            }
            printf("%d\n", accounts[i].score);
        }
    }
    
    change_color_rgb(15, 215, 10);
    printf("\nPRESS ANY KEY TO BACK TO MENU. ");
    change_color_rgb(215, 215, 0);
    
    getch();
    show_menu_2("", accounts);
}

void draw_loser(short int state){
    c();
    switch (state){
    case 0:
        printf(
"$$\\       $$$$$$\\   $$$$$$\\  $$$$$$$$\\ $$$$$$$\\               $$$$$$\\   $$$$$$\\  $$\\      $$\\ $$$$$$$$\\ \n"
"$$ |     $$  __$$\\ $$  __$$\\ $$  _____|$$  __$$\\             $$  __$$\\ $$  __$$\\ $$$\\    $$$ |$$  _____|\n"
"$$ |     $$ /  $$ |$$ /  \\__|$$ |      $$ |  $$ |            $$ /  \\__|$$ /  $$ |$$$$\\  $$$$ |$$ |      \n"
"$$ |     $$ |  $$ |\\$$$$$$\\  $$$$$\\    $$$$$$$  |            $$ |$$$$\\ $$$$$$$$ |$$\\$$\\$$ $$ |$$$$$\\    \n"
"$$ |     $$ |  $$ | \\____$$\\ $$  __|   $$  __$$<             $$ |\\_$$ |$$  __$$ |$$ \\$$$  $$ |$$  __|   \n"
"$$ |     $$ |  $$ |$$\\   $$ |$$ |      $$ |  $$ |            $$ |  $$ |$$ |  $$ |$$ |\\$  /$$ |$$ |      \n"
"$$$$$$$$\\ $$$$$$  |\\$$$$$$  |$$$$$$$$\\ $$ |  $$ |            \\$$$$$$  |$$ |  $$ |$$ | \\_/ $$ |$$$$$$$$\\ \n"
"\\________|\\______/  \\______/ \\________|\\__|  \\__|             \\______/ \\__|  \\__|\\__|     \\__|\\________|\n"
        );
        break;

    case 1:
        printf(
"$$\\       \n"
"$$ |      \n"
"$$ |      \n"
"$$ |      \n"
"$$ |      \n"
"$$ |      \n"
"$$$$$$$$\\ \n"
"\\________|\n"
        );
        break;

    case 2:
        printf(
"$$\\       $$$$$$\\  \n"
"$$ |     $$  __$$\\ \n"
"$$ |     $$ /  $$ |\n"
"$$ |     $$ |  $$ |\n"
"$$ |     $$ |  $$ |\n"
"$$ |     $$ |  $$ |\n"
"$$$$$$$$\\ $$$$$$  |\n"
"\\________|\\______/ \n"
        );
        break;

    case 3:
        printf(
"$$\\       $$$$$$\\   $$$$$$\\  \n"
"$$ |     $$  __$$\\ $$  __$$\\ \n"
"$$ |     $$ /  $$ |$$ /  \\__|\n"
"$$ |     $$ |  $$ |\\$$$$$$\\  \n"
"$$ |     $$ |  $$ | \\____$$\\ \n"
"$$ |     $$ |  $$ |$$\\   $$ |\n"
"$$$$$$$$\\ $$$$$$  |\\$$$$$$  |\n"
"\\________|\\______/  \\______/ \n"
        );
        break;

    case 4:
        printf(
"$$\\       $$$$$$\\   $$$$$$\\  $$$$$$$$\\ \n"
"$$ |     $$  __$$\\ $$  __$$\\ $$  _____|\n"
"$$ |     $$ /  $$ |$$ /  \\__|$$ |      \n"
"$$ |     $$ |  $$ |\\$$$$$$\\  $$$$$\\    \n"
"$$ |     $$ |  $$ | \\____$$\\ $$  __|   \n"
"$$ |     $$ |  $$ |$$\\   $$ |$$ |      \n"
"$$$$$$$$\\ $$$$$$  |\\$$$$$$  |$$$$$$$$\\ \n"
"\\________|\\______/  \\______/ \\________|\n"
        );
        break;

    case 5:
        printf(
"$$\\       $$$$$$\\   $$$$$$\\  $$$$$$$$\\ $$$$$$$\\  \n"
"$$ |     $$  __$$\\ $$  __$$\\ $$  _____|$$  __$$\\ \n"
"$$ |     $$ /  $$ |$$ /  \\__|$$ |      $$ |  $$ |\n"
"$$ |     $$ |  $$ |\\$$$$$$\\  $$$$$\\    $$$$$$$  |\n"
"$$ |     $$ |  $$ | \\____$$\\ $$  __|   $$  __$$< \n"
"$$ |     $$ |  $$ |$$\\   $$ |$$ |      $$ |  $$ |\n"
"$$$$$$$$\\ $$$$$$  |\\$$$$$$  |$$$$$$$$\\ $$ |  $$ |\n"
"\\________|\\______/  \\______/ \\________|\\__|  \\__|\n"
        );
        break;
    }
    printf("\n\n");
}

void handle_game(account* accounts, char* word, short int tries, char* error){
    short int word_length = strlen(word);
    short int win = 1;

    // lose the game
    if((word_length<=8 && tries>=6) || (word_length>8 && tries>=11)){
        c();
        change_color_rgb(150, 15, 15);
        printf(
"$$\\     $$\\  $$$$$$\\  $$\\   $$\\       $$\\       $$$$$$\\   $$$$$$\\  $$$$$$$$\\ $$\\ \n"
"\\$$\\   $$  |$$  __$$\\ $$ |  $$ |      $$ |     $$  __$$\\ $$  __$$\\ $$  _____|$$ |\n"
" \\$$\\ $$  / $$ /  $$ |$$ |  $$ |      $$ |     $$ /  $$ |$$ /  \\__|$$ |      $$ |\n"
"  \\$$$$  /  $$ |  $$ |$$ |  $$ |      $$ |     $$ |  $$ |\\$$$$$$\\  $$$$$\\    $$ |\n"
"   \\$$  /   $$ |  $$ |$$ |  $$ |      $$ |     $$ |  $$ | \\____$$\\ $$  __|   \\__|\n"
"    $$ |    $$ |  $$ |$$ |  $$ |      $$ |     $$ |  $$ |$$\\   $$ |$$ |          \n"
"    $$ |     $$$$$$  |\\$$$$$$  |      $$$$$$$$\\ $$$$$$  |\\$$$$$$  |$$$$$$$$\\ $$\\ \n"
"    \\__|     \\______/  \\______/       \\________|\\______/  \\______/ \\________|\\__|\n"
        );
        change_color_rgb(215, 215, 0);
        printf("\n\n THE WORD WAS \"%s\".", word);
        delay(2500);
        show_menu_2("", accounts);
    }

    if(word_length<=8) draw_loser(tries);
    else draw_loser(tries/2);

    show_error(error);
    for (int i = 0; i < word_length; i++) { 

        if(strchr(tried_letters, word[i]) == NULL){
            printf("_");
            win = 0;
        } else {
            printf("%c", word[i]);
        }

        printf(" ");
    }

    // win the game
    if(win){
        c();
        for (int i = 0; i < _accounts_number + 1; i++) {
            if(strcmp(current_username, accounts[i].username) == 0){
                accounts[i].score += word_length;
                update_accounts_file(accounts);
            }
        }
        change_color_rgb(15, 215, 10);
        printf(
"$$\\     $$\\  $$$$$$\\  $$\\   $$\\       $$\\      $$\\ $$$$$$\\ $$\\   $$\\ $$\\ \n"
"\\$$\\   $$  |$$  __$$\\ $$ |  $$ |      $$ | $\\  $$ |\\_$$  _|$$$\\  $$ |$$ |\n"
" \\$$\\ $$  / $$ /  $$ |$$ |  $$ |      $$ |$$$\\ $$ |  $$ |  $$$$\\ $$ |$$ |\n"
"  \\$$$$  /  $$ |  $$ |$$ |  $$ |      $$ $$ $$\\$$ |  $$ |  $$ $$\\$$ |$$ |\n"
"   \\$$  /   $$ |  $$ |$$ |  $$ |      $$$$  _$$$$ |  $$ |  $$ \\$$$$ |\\__|\n"
"    $$ |    $$ |  $$ |$$ |  $$ |      $$$  / \\$$$ |  $$ |  $$ |\\$$$ |    \n"
"    $$ |     $$$$$$  |\\$$$$$$  |      $$  /   \\$$ |$$$$$$\\ $$ | \\$$ |$$\\ \n"
"    \\__|     \\______/  \\______/       \\__/     \\__|\\______|\\__|  \\__|\\__|\n"
        );
        printf("\n\nTHE WORD WAS \"%s\".", word);
        printf("\nYou got %d score.", word_length);
        change_color_rgb(215, 215, 0);
        delay(2500);
        show_menu_2("", accounts);
    }

    printf("\n\n>>> ");
    
    char ch;
    // Check if character is repeat or not
    do{
        ch = getch();
        if(strchr(tried_letters, ch) != NULL){ //Letter is repeat
            handle_game(accounts, word, tries, "THIS CHARACTER IS REPEAT, PLEASE CHOOSE ANOTHER ONE.");
        } else {
            break;
        }
    } while(1);

    if(ch== 27) {
        show_menu_2("", accounts);
        return;
    }
    printf("%c", ch);
    strcat(tried_letters, &ch);
    
    for (int i = 0; i < word_length; i++) { 
        if(ch == word[i]){
            handle_game(accounts, word, tries, "");
            return;
        }
    }

    handle_game(accounts, word, tries+1, "");
}

void show_menu_2(char* error, account* accounts){
    c();
    draw_title(0);
    printf("1. Start game\n2. Show leaderboard\n3. New word\n4. Exit\n");
    show_error(error);
    printf("\n>>> ");
    short int choice;
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
        if(words_file_exist()){
            empty_tried_letters();
            char word[20];
            random_word(word);
            handle_game(accounts, word, 0, "");
        } else{
            show_menu_2("There is no word defined, please first add some in \"New word\" section.", accounts);
        }
        return;
    case 2:
        handle_leaderboard(accounts);
        return;
    case 3:
        handle_new_word("", accounts);
        return;
    case 4:
        handle_exit();
    
    // default:
    //     show_menu_2("PLEASE ENTER A VALID MENU NUMBER.", accounts);
    }
}

void handle_login(char* error, account* accounts){
    c();
    char username[16], password[16];
    draw_title(1);
    show_error(error);
    printf("USERNAME: ");
    scanf("%s", username);
    printf("PASSWORD: ");
    scanf("%s", password);

    for (int i = 0; i < _accounts_number; i++){
        if (strcmp(accounts[i].username, username) == 0 && strcmp(accounts[i].password, password) == 0){
            strcpy(current_username, username);
            show_menu_2("", accounts);
            return;
        }
    }
    handle_login("WRONG USERNAME OR PASSWORD. PLEASE TRY AGAIN.", accounts);
    return;

}

void handle_new_word(char* error, account* accounts){
    c();
    draw_title(4);
    show_error(error);
    
    int key = nb_getch();
    if(key==27){
        exit(1);
    }

    printf("NEW WORD: ");
    char word[100];
    scanf("%s", word);

    if(words_file_exist()){
        if(word_exists(word)){
            handle_new_word("THIS WORD ALREADY EXISTS. TRY ANOTHER ONE.", accounts);
            return;
        } else {
            FILE *words_file = fopen("words.txt", "a");
            fprintf(words_file, "%s\n", word);
            fclose(words_file);
            c();
            draw_title(4);
            change_color_rgb(15, 215, 10);
            printf("> '%s' SUCCESSFULLY ADDED TO WORDS LIST.", word);
            change_color_rgb(215, 215, 0);
            delay(2000);
        }
    } else {
        FILE *words_file = fopen("words.txt", "w");
        fprintf(words_file, "%s\n", word);
        fclose(words_file);
    }

    show_menu_2("", accounts);
    return;
}

void random_word(char word[20]){
    // Open words file
    FILE *words_file = fopen("words.txt", "r");

    // Select a word index in the file
    int file_lines = file_number(2) - 1;
    int word_index = rand() % file_lines;
    // printf("file lines: %d\n word_index: %d\n", file_lines, word_index);
    // Current file line index
    int line = 0;

    // Go to the first of the word_index line
    while(line != word_index){
        char character = fgetc(words_file);
        if (character == '\n'){
            line++;
        }
    }
    printf("lines: %d\n", line);
    int word_letter = 0;
    
    while (1){
        char character = fgetc(words_file);
        printf("-%c-", character);
        if (character == '\n'){
            break;
        } else {
            word[word_letter] = character;
            word_letter++;
        }
    }
    printf("%s", word);
}

int main(int argc, char const *argv[])
{
    // Initiliazation
    init_clui();
    srand(time(NULL));
    change_color_rgb(215, 215, 0);

    // Load accounts data
    _accounts_number = file_number(1);
    account accounts[_accounts_number+1];
    get_accounts(accounts);

    // First Page Menu
    show_menu_1("", accounts);

    // empty_tried_letters();
    // handle_game(accounts, 0, "");


    // Get a random word
    // char word[12];
    // random_word(word);

    return 0;
}