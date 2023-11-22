#include <stdlib.h>
#include <stdio.h>
#include "lib.h"
#include <string.h>



// Helper function which counts the items in the database
 int item_count(const Item *db){
    int i;
    for(i=0; *db[i].name != '\0'; i++) continue;
    return i;
}

/* 
This function returns the new database with the new item if no problem occurrs.
In case of a problem exits the program.
The actual adding happens in the main function. 
 */

Item *add_game(Item *db, char *name, float price){
    int i;
    Item *new;
    i = item_count(db);
    
    new = realloc(db, (i+2) * sizeof(Item));

    if(new == NULL){
        free(new);
        printf("Memory reallocation failed! Terminating program...");
        exit(0);
    }

    strcpy(new[i].name, name);
    new[i].price = price;
    new[i].profit = 0.00;
    *new[i+1].name='\0';

    printf("Added a game with name: %s and price: %.2f\n", new[i].name, new[i].price);

    return new;

}

void buy_game(Item *db, const char *name, const int n){
    int i;
    int count = item_count(db);
    int found = 0;   // 1 if the item was found 0 otherwise.

    if(n>=1){
        for(i = 0; i<count; i++){
            if( strcmp(db[i].name, name) == 0 ){
                found = 1;
                db[i].profit += n * db[i].price;
                break;
            }
        }
    }
    else{
        printf("Invalid value of n\n");
        return;
    }
        
    if(found==0){
        printf("Item not found\n");
    }
    else{
        printf("%d copies of %s bought - Total profit: %.2f\n", n, db[i].name, db[i].profit);
    }
    

}
/*Used as an argument to the qsort function in the print_db function.
 Primarily sorts based on the profit of the items and secondly on their names. */
int compare_profit(const void *item_1, const void *item_2){

    const Item *i_1 = item_1;
    const Item *i_2 = item_2;

    if(i_1->profit < i_2->profit){
        return 1;
    }
    else if(i_1->profit > i_2->profit){
        return -1;
    }
    return strcmp(i_1->name, i_2->name);
}

//Prints the database. Returns -1 if the database is empty.
int print_db(Item *db){
    int i = 0;
    int amount = item_count(db);
    float total_profit = 0;
    if(*db[0].name != '\0'){
        qsort(db, amount, sizeof(Item), compare_profit);
        printf("Format: name price profit\n");
       while (i<amount){
           printf("%s %.2f %.2f\n", db[i].name, db[i].price, db[i].profit);
           total_profit += db[i].profit;
           i++;
       }
       printf("\nTotal profit: %.2f", total_profit);
    }
    else{
        return -1; // When empty
    }
    return 0;
}

int save_to_file(Item *db, const char *filename){
    int i;
    char *name = malloc(14*sizeof(char*) + (strlen(filename)+1)*sizeof(char*));
    strcpy(name, "./Databases/");
    strcat(name, filename);
    FILE *f = fopen(name, "w+");
    
    if(!f){
        printf("Save to file Failed! Check that the folder Databases exists.");
        return -1;
    }

    for(i=0; i<item_count(db);i++){
        int r = fprintf(f, "%s %f %f\n", db[i].name, db[i].price, db[i].profit);
        if(r<0){
            return -1;
        }
    }
    fclose(f);
    free(name);
    return 0;
}

Item *load_file(Item *db, const char *filename){
    char *name = malloc(14*sizeof(char*) + (strlen(filename)+1)*sizeof(char*));
    strcpy(name, "./Databases/");
    strcat(name, filename);
    FILE *f = fopen(name, "r");
    if(!f){
        printf("File not found!\n");
        return db;
    }
    int i = 0;
    Item *new = calloc(1, sizeof(Item));

    int output;
    output = fscanf(f, "%s %f %f\n", new[i].name, &new[i].price, &new[i].profit);


    while(output > 0){
        i++;
        new = realloc(new, (i+1) * sizeof(Item));

        if(new==NULL){
            free(new);
            printf("Reallocting memory failed. Terminating program...\n");
            exit(0);
        }
        output = fscanf(f, "%s %f %f\n", new[i].name, &new[i].price, &new[i].profit);
    }
    *new[i].name = '\0';

    printf("Successfully loaded items from file with name: %s\n", filename); 
    free(db);
    free(name);
    fclose(f);

    return new;   
}