# shop-database-client

## 1. Introduction
This application creates a simple database client for a small shop. This implementation uses files as databases where for each item there is a field for name, price and amount sold. The application allows the user to create and load databases, list the the items of a already created database, add items to databases, and buy items. The implementation of the application is dynamic and, therefor, supports large files. The created databases are saved in the ./Databases folder.

## 2. Usage
### 2.1. Compiling
The application can be compiled by running the command:  
`$ make` <br> 
Manual compilation is possible using the given gcc compilation command found in the app.c source file.
### 2.2. Running
The application can be run from the command line using the following commands: <br> 
`$ ./app` or using make `$ make run` <br> 
### 2.2. Commands
Loading a database: `O {DatabseName}` <br>
Listing current database and total sales. Primarily ordered, in ascending order, by profit. Seondarily by name : `L`<br>
Save database to file: `W {fileName}`<br>
Add a game to database: `A {gameName} {price}`<br>
Buy a game n times: `A {gameName} {amount}`<br>
Exits the database. Doesnt't save to a file automatically: `Q`<br>
### 2.4. Autosave
To save automatically when quitting the application can be run with the arugment autosave: <br>
`./app autosave`
If no dabase is loaded using the `O`command the modifications will be done to the default file `Database.db` when quitting without saving.
If a datavase is loaded then the modifications will be done to the same file which was loaded automatically without the need to save.

## 3.Example
The follwing example shows an example usage for the application. First a new database is created then a few items are added to the database. After we have a database with items some items are bought. Then the database is closed and opened with again with the autosave argument. Lastly, a few additional commands are made.

Running the application: <br>
```
$ ./app
-------------Game Shop-------------
Type {H} to see commands: 
H
Commands:
O {DatabseName}: Loads a database file with name: {DatabseName}
L: - Lists the current databse and shows total sales
W {fileName}: - Write database to file with name: {fileName}
A {gameName} {price}: - Adds a game with name: {gameName} and price: {price} to the database
B {gameName} {amount}: - Buys a game with name: {gameName}, {amount} times
Q: Exits the database. Doens't save to a file automatically
```

Adding items using the `A` command by typing `A {gameName} {price}`

```
A Game1 10
Added a game with name: Game1 and price: 10.00
A Game2 20
Added a game with name: Game2 and price: 20.00
```

Buying 2x Game1 and 3x Game2 and listing the database
```
B Game1 2
2 copies of Game1 bought - Total profit: 20.00
B Game2 3
3 copies of Game2 bought - Total profit: 60.00
L
Format: name price profit
Game2 20.00 60.00
Game1 10.00 20.00

Total profit: 80.00
--Items printed successfully!--
```

Saving the database to file `shop.db` and quitting

```
W shop.db
File saved successfully!
Q
```
Now a new file called `shop.db` was created to the folder `./Databases`
the `shop.db` database file has the following contents:
```
Game2 20.000000 60.000000
Game1 10.000000 20.000000
```

Rerunning the application with autosave argument and loading the database `shop.db`
```
$ ./app autosave
-------------Game Shop-------------
Type {H} to see commands: 
Autosave is on!
O shop.db
Successfully loaded items from file with name: shop.db
```

Adding Game3 with price 40 and buying it once
```
A Game3 40
Added a game with name: Game3 and price: 40.00
B Game3 1
1 copies of Game3 bought - Total profit: 40.00
L
Format: name price profit
Game2 20.00 60.00
Game3 40.00 40.00
Game1 10.00 20.00

Total profit: 120.00
--Items printed successfully!--
```
Quitting without saving
```
Q   
Exiting!
File saved successfully to file: shop.db
```
The `shop.db` database file now has the following contents:
```
Game2 20.000000 60.000000
Game3 40.000000 40.000000
Game1 10.000000 20.000000
```






