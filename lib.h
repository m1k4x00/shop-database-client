typedef struct {
    char name[80];
    float price;
    float profit;
    
} Item;


int item_count(const Item *db);
Item *add_game(Item *db, char *name, float price);
void buy_game(Item *db, const char *name, const int n);
int compare_profit(const void *item_1, const void *item_2);
int print_db(Item *db);
int save_to_file(Item *db, const char *filename);
Item *load_file(Item *db, const char *filename);