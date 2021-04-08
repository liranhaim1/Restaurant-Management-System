#include "header.h"
void main()
{
	FILE *instructions;
	FILE* out;
	manage pm;
	tablemanager array[N];
	int i, function_num, Quantity, tablenum;
	char name[MAX + 1];
	out = fopen("out.txt", "wt");
	if (out == NULL)
	{
		printf("ERROR in opening the output file");
		exit(1);
	}

	for (i = 0; i < N; i++)
	{ 	//Initialize the array of the tabels.
		array[i].head = NULL;
		array[i].bill = 0;
	}
	pm.head = NULL;
	pm.tail = NULL;
	instructions = fopen("Instructions.txt", "r");//Open the file Instructions.txt.
	if (instructions == NULL) {
		fprintf(out, "ERROR in opening the Instructions file");
		exit(1);
	}
	while (fscanf(instructions, " %d ", &function_num) != EOF)
	{
		switch (function_num)
		{
		case 1: //Function 1-CreateProduct
		{
			if (pm.head == NULL)
			{ //In case there are no products
				CreateProduct(&pm, out);
				if (pm.head == NULL)
				{
					fprintf(out, "Theres not products in the kitchen.\n");
					free(array);
					exit(1);
				}
				break;
			}
			else {
				fprintf(out, "Cannot enter fucntion number one cause we got all the proudcts in the kitchen.\n");
				break;
			}
		}
		case 2: //Function 2-AddItems
		{
			fscanf(instructions, "%s %d", name, &Quantity);
			if (pm.head != NULL)
			{ //In case there are no products in the kitchen.
				AddItems(name, Quantity, &pm, out);
				break;
			}
			else {
				fprintf(out, "Error! There are no products in our kitchen.\n");
				break;
			}
		}
		case 3: //Function 3-OrderItem
		{
			fscanf(instructions, "%d %s %d", &tablenum, name, &Quantity);
			if (pm.head != NULL)
			{ //In case there are no products in the kitchen.
				OrderItem(tablenum, name, Quantity, &pm, array, out);
				break;
			}
			else {
				fprintf(out, "Error,There are no products in our kitchen.\n");
				break;
			}
		}
		case 4: //Function 4-RemoveItem
		{
			fscanf(instructions, "%d %s %d", &tablenum, name, &Quantity);
			if (pm.head != NULL)
			{ //In case there are no products in the kitchen.
				RemoveItem(tablenum, name, Quantity, array, out);
				break;
			}
			else {
				fprintf(out, "Error,There are no products in our kitchen.\n");
				break;
			}
		}
		case 5: //Function 5-RemoveTable
		{
			fscanf(instructions, "%d", &tablenum);
			if (pm.head != NULL)
			{ //In case there are no products in the kitchen.
				RemoveTable(tablenum, array, out);
				break;
			}
			else {
				fprintf(out, "Error,There are no products in our kitchen.\n");
				break;
			}
		}
		default: //In case the number of the function is diffrent from the numbers one till five
		{
			printf("you entered a wrong function number!");
			break;
		}
		}
	}
	for (i = 0; i < N; i++)//Frees the allocated memory of the array of the tabels.
	{
		if (array[i].head != NULL)
			Delete_the_table(&array[i]); //each table.
	}
	DeleteList(&pm); //Frees the allocated memory of the products in our kitchen.
	fclose(instructions);//closing the file instructions
	fclose(out);

}

