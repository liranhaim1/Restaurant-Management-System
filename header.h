#ifndef _ header.h
#define MAX 100
#define N 15
#include <stdio.h>
#include <stdlib.h>
#include<conio.h>
#include<string.h>
typedef struct manage
{
	struct products * head;
	struct products * tail;

}manage;
typedef struct products
{
	char * name;
	int Quantity;
	int price;
	char pre;
	int amount;
	struct products * next;
}products;
typedef struct tablemanager
{
	float bill;
	struct Dish *head;
}tablemanager;
typedef struct Dishes //Each table data.
{
	char *ProductName;
	int	 Price;
	int	 Quantity;
	char Premium;
	struct Dish  *next;
	struct Dish  *prev;
} Dish;
void DeleteList(manage *pm);//Function that free the allocated memory of all the products in the kitchen.
void Errormsg(FILE* out, char *str);//A help function that informs if there is an error.
void Delete_the_table(tablemanager *TB);//A function that delete table
void CreateProduct(manage* pm, FILE* out);//#1 The function pulls data about the kitchen packets from the file and creates a linked list that each node is a packet type.
products *CheckIfNameAvailable(manage *pm, char *Name);//checks if the product's name is exist
void RemoveTable(int tablenum, tablemanager *TB, FILE * out);//#5  A function that closes a table.
void AddItems(char* name, int Quantity, manage *pm, FILE* out);// A function that adds inventory to the dish in the kitchen.
void RemoveItem(int tablenum, char *productnum, int Quantity, tablemanager *TB, FILE * out);//#4 The function cancels items ordered.
void OrderItem(int tablenum, char *productnum, int Quantity, manage *pm, tablemanager *TB, FILE * out);// #3 A function by which dishes are ordered from the kitchen to the tables.




#endif 
