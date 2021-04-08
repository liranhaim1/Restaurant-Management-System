#include "header.h"
void CreateProduct(manage* pm, FILE* out)//#1 The function pulls data about the kitchen packets from the file and creates a linked list that each node is a packet type.
{
	products* temp;
	FILE * in;
	char namehelp[MAX + 1];
	int temp2;
	in = fopen("manot.txt", "rt");
	if (in == NULL)
	{
		Errormsg(out, "ERROR in opening the file");
		exit(1);
	}
	while ((fscanf(in, "%s", namehelp)) != EOF)
	{
		if (CheckIfNameAvailable(pm, namehelp) != NULL)//Sends the name of the recorded packet and the function that checks if the name already exists.
		{
			Errormsg(out, "there is a problem in the name");
			fscanf(in, "%d %d %c", &temp2, &temp2, &temp2);
		}
		else
		{//In case the name does not exist, memory is allocated to a node in a linked list
			temp = (products*)malloc(sizeof(products));
			if (temp == NULL)//If the assignment fails, a message will be sent and the list will be deleted.
			{
				Errormsg(out, "ERROR in the allocation");
				DeleteList(pm);
				exit(1);
			}
			temp->name = (char*)malloc((sizeof(char)*strlen(namehelp) + 1));//Assign memory to the name field at the auxiliary string size.
			if (temp->name == NULL)
			{
				Errormsg(out, "there is a problem in the allocation name");
				DeleteList(pm);
				exit(1);
			}
			temp->next = NULL;
			strcpy(temp->name, namehelp);
			fscanf(in, "%d %d %c", &temp->Quantity, &temp->price, &temp->pre);//Receiving the data from the file and inserting it into the appropriate fields at the intersection
			temp->amount = 0;
			if (temp->Quantity <= 0 || temp->price <= 0)
			{
				Errormsg(out, "the input isnt valid");
				free(temp->name);
				free(temp);
				break;
			}
			else
			{

				if (pm->head == NULL)//if the list is empty
				{
					pm->head = temp;
					pm->tail = temp;

				}


				else
				{
					temp->next = pm->head;
					pm->head = temp;

				}
			}
		}
	}
	if (pm->head != NULL)
		fprintf(out, "The kitchen was created.");
	fclose(in);
}

void Errormsg(FILE* out, char *str)//A help function that informs if there is an error.
{
	fprintf(out, " %s.\n", str);
}

products *CheckIfNameAvailable(manage *pm, char *Name)/*A function that accepts a manager structure and a string
													  And checks whether the string is in one of the nodes of the linked list.If you do not return NULL.*/
{
	products *temp = pm->head;
	while (temp != NULL)
	{
		if (strcmp(temp->name, Name) == 0)
			return temp;
		temp = temp->next;
	}
	return NULL;
}
//Function that free the allocated memory of all the products in the kitchen.
void DeleteList(manage *pm)
{
	products *temp;
	while (pm->head)
	{
		temp = pm->head;
		pm->head = pm->head->next;
		if (temp->name)
			free(temp->name);
		free(temp);
	}
}
void AddItems(char* name, int Quantity, manage *pm, FILE* out)//#2 A function that adds inventory to the dish in the kitchen.
{
	products* temp;
	temp = pm->head;
	if (Quantity <= 0)//If the function receives less than or equal to 0, an error message will be sent.
	{
		fprintf(out, "Error,cant add %d of %s to the kitchen", Quantity, name);
		return;//back to the main.
	}
	while (temp != NULL)
	{
		if ((strcmp(temp->name, name)) == 0)//The function receives a packet name, and now with a loop, you check for a node that contains a name in the same name field.
		{
			temp->Quantity += Quantity;//Adds the quantity required to the field of quantity of product in the kitchen.
			fprintf(out, "\n %d of %s was added to the kitchen.\n", Quantity, name);
			return;
		}
		temp = temp->next;
	}
	fprintf(out, "Error,this dish isnt exist in our kitchen.\n");
	return;
}
//Function that free the allocated memory of a specific table.
void Delete_the_table(tablemanager *TB)
{
	Dish* temp;
	while (TB->head != NULL)
	{
		temp = TB->head;
		TB->head = temp->next;
		free(temp->ProductName);
		free(temp);
	}
}

// #3 A function by which dishes are ordered from the kitchen to the tables.
void OrderItem(int tablenum, char *productnum, int Quantity, manage *pm, tablemanager *TB, FILE * out)
{
	int i;
	tablemanager * temp1;
	Dish *temp2, *temp3;
	products *p = pm->head;
	if (tablenum > N || tablenum <= 0)//There are 15 tables. Check if the serial number of the table is working.
	{
		fprintf(out, "\nError!Wrong table number %d!\n", tablenum);
		return;
	}
	if (Quantity <= 0)//If the number of packets ordered is less than or equal to 0 you will leave an error message.
	{
		fprintf(out, "\nError!Cannot order %d dishes of %s!\n", Quantity);
		return;
	}
	if ((p = CheckIfNameAvailable(pm, productnum)) == NULL)//Check if the received dish name is in the kitchen.
	{
		fprintf(out, "we don't have %s, sorry! \n", productnum);
		return;
	}
	if ((p->Quantity -= Quantity)< 0)//In case the quantity of dishes ordered is greater than the quantity of dishes in the kitchen.
	{
		p->Quantity += Quantity;
		fprintf(out, "\nError! Not enough stock in the kitchen of %s!\n", productnum);
		return;

	}
	temp2 = TB[tablenum - 1].head;
	while (temp2 != NULL)//Check if product already exist, if not, update the order.
	{
		if (strcmp(temp2->ProductName, productnum) == 0)
		{
			temp2->Quantity += Quantity;//Update the quantity.

			TB[tablenum - 1].bill += (temp2->Price)*Quantity;//Update the bill.
			fprintf(out, "%d %s were added to the table number %d.\n", Quantity, productnum, tablenum);
			return;

		}
		temp2 = temp2->next;
	}
	temp2 = (Dish*)malloc(sizeof(Dish));//if the dish doesn't exist, creates a new node.
	if (temp2 == NULL)
	{//In case allocation failed, frees all the allocated memory, prints an error message and exit the program.
		fprintf(out, "There is a problem with memory allocation/n");

		for (i = 0; i < N; i++)
		{
			if (TB[i].head != NULL)
				Delete_the_table(&TB[i]);
		}
		DeleteList(pm);
		exit(1);
	}
	temp2->ProductName = (char*)malloc(sizeof(char)*(strlen(p->name)) + 1);
	if (temp2->ProductName == NULL)
	{
		fprintf(out, "There is a problem with memory allocation/n");
		for (i = 0; i < N; i++)
		{
			if (TB[i].head != NULL)
				Delete_the_table(&TB[i]);
		}
		DeleteList(pm);
		free(TB);
		exit(1);
	}
	strcpy(temp2->ProductName, p->name);//Copy the fields from the pointer to the P structure into temp2
	temp2->Price = p->price;
	temp2->Quantity = Quantity;
	temp2->Premium = p->pre;
	temp2->next = NULL;
	temp2->prev = NULL;
	TB[tablenum - 1].bill += (Quantity*temp2->Price);
	p->amount += Quantity;
	fprintf(out, "%d %s were added to the table number %d.\n", Quantity, productnum, tablenum);

	temp3 = TB[tablenum - 1].head;
	if ((TB[tablenum - 1].head) == NULL)
		(TB[tablenum - 1]).head = temp2;
	else
	{
		while (temp3->next != NULL)
		{
			temp3 = temp3->next;
		}
		temp2->prev = temp3;
		temp3->next = temp2;
	}
	return;
}
//#4 The function cancels items ordered.
void RemoveItem(int tablenum, char *productnum, int Quantity, tablemanager *TB, FILE * out)
{
	
	Dish * temp = TB[tablenum - 1].head;
	Dish * temp2;
	int flag = 1;
	if (Quantity <= 0)
	{
		fprintf(out, "the quantity is not a positive number");//
		return;
	}
	if (tablenum > N || tablenum < 0)
	{
		fprintf(out, "the table number %d  is not exist and therefore no cancellation was made\n", tablenum);
	}
	if (temp == NULL)
	{
		fprintf(out, "the table number %d  is inactive and therefore no cancellation was made\n", tablenum);
		return;
	}
	if (temp != NULL)
	{
		while (temp != NULL)
		{
			
			if (strcmp(temp->ProductName, productnum) == 0)
			{
				if (Quantity > temp->Quantity)//In case the amount of portions that you want to return is greater than the number of dishes on the table.
				{
					fprintf(out, "the number of the quantity is bigger then the real amount. \n");
					return;
				}
				else
				{
					if (temp->Quantity == Quantity)
					{
						fprintf(out, "Table %d returned %d dishes of %s and the quantity now is 0  \n", tablenum, Quantity, productnum);
						temp->Quantity -= Quantity;
						TB[tablenum - 1].bill -= Quantity*temp->Price;
						return;
					}
					temp->Quantity -= Quantity;
					TB[tablenum - 1].bill -= Quantity*temp->Price;
					fprintf(out, "%d %s was returned to the table number %d\n", Quantity, productnum, tablenum);
					return;
				}
			}
			
			
				temp = temp->next;
			

		}
		fprintf(out, "the dishe doesnt cacelled cause one of the details was incorrect.\n");


	}
}
void RemoveTable(int tablenum, tablemanager *TB, FILE * out)//#5  A function that closes a table.
{
	int flag = 0;
	Dish * temp = TB[tablenum - 1].head;
	Dish * temp2 = TB[tablenum - 1].head;
	if (tablenum > N || tablenum < 0)
	{
		fprintf(out, "the table number %d  is not exist\n", tablenum);
	}
	if (temp == NULL)
	{
		fprintf(out, "The table number %d is not ordered yet\n ", tablenum);
		return;
	}
	if (temp != NULL)
	{
		while (temp2 != NULL)
		{
			if (temp2->Premium == 'Y')
			{
				flag = 1;

			}
			temp2 = temp2->next;
		}
		if (flag == 1)
		{
			fprintf(out, "you invite premiuem meal.");
		}
		else
		{
			fprintf(out, "you didn't invite premiuem meal.");
		}

		while (temp != NULL)
		{

			if (temp->Quantity > 0)
			{
				fprintf(out, "%d %s", temp->Quantity, temp->ProductName);

			}
			temp = temp->next;
		}
		if (flag == 1)
		{
			fprintf(out, " %.2f nis,please!\n", (TB[tablenum - 1].bill)*1.1);
		}
		else
		{
			fprintf(out, " %.2f nis,please!\n", TB[tablenum - 1].bill);
		}
	}
	Delete_the_table(&TB[tablenum - 1]);

}