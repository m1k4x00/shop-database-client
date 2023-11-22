#include <stdlib.h>
#include <stdio.h>
#include "lib.h"
#include <string.h>

// Compile: gcc -Wvla -Wall -g -std=c99 -o app projekti.c
// Valgrind: valgrind --leak-check=yes app


int main(int argc, char *argv[]) {
    printf("-------------Game Shop-------------\n");
    printf("Type {H} to see commands: \n");
    int autosave = 0;
    Item *db = calloc(1, sizeof(Item));
    int continues = 1;
    char fileName[80] = "Database.db";
    if (argc == 2){
        if(strcmp(argv[1], "autosave")==0){
            autosave = 1;
            printf("Autosave is on!\n");
        }
    }

    while(continues){
        char user_input[80];

        char *argument = fgets(user_input, 80, stdin);
        char name[80] = "404";  //Allocating the variable with chosen value "404". Used when the user doesn't input a name.
        
        float amount = 0.00; // If the user doen't input any amount the default amount is 0.00
        

        char *parse = strstr(argument, " ");
        
        
        if(argument[1] == ' '){     //Checking if the second argument is a space to prevent certain bugs.
            sscanf(parse,"%s %f", name, &amount);
        }
        
        if(argument == NULL){
            continues = 0;
        }
        switch(argument[0]) {

            case 'A':
                if(strcmp(name, "404")==0){
                    printf("Please add a name. Use the followng format: 'A name price'\n");
                    break;
                }
                db = add_game(db, name, amount); //Assigning the new database. Messages inside the function for convenience
                break;

            case 'B':
                buy_game(db, name, amount); //Messages are printed inside the function for convenience
                break;

            case 'L':
                if(print_db(db)==0){
                    printf("\n--Items printed successfully!--\n");
                }
                else{
                    printf("Database is empty\n");
                }
                break;

            case 'W':
                if(save_to_file(db, name) == 0){
                    printf("File saved successfully!\n");
                }
                else{
                    printf("Something went wrong!\n");
                }
                break;

            case 'O':
                db = load_file(db, name);
                if (autosave == 1){
                    strcpy(fileName, name);
                }
                break;
                
            case 'Q':
                printf("Exiting!\n");
                continues = 0;
                if (autosave == 1){
                    if(save_to_file(db, fileName) == 0){
                        printf("File saved successfully to file: %s\n", fileName);
                    }
                    else printf("Something went wrong!\n");
                }
                free(db);
                break;
            case 'H':
                printf("Commands:\n");
                printf("O {DatabseName}: Loads a database file with name: {DatabseName}\n");
                printf("L: - Lists the current databse and shows total sales\n");
                printf("W {fileName}: - Write database to file with name: {fileName}\n");
                printf("A {gameName} {price}: - Adds a game with name: {gameName} and price: {price} to the database\n");
                printf("B {gameName} {amount}: - Buys a game with name: {gameName}, {amount} times\n");
                printf("Q: Exits the database. Doens't save to a file automatically.\n");

                break;

            default:
                printf("Unknown command!\n");
                break;
        }
    }

    return 0;
}
