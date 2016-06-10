#include "uthash.h"
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <time.h>

typedef struct node {
	int data;
	UT_hash_handle hh;
} Node;

Node *mainhash = NULL;

int datacmp (Node* a, Node* b)
{
	if (a->data > b->data) {
		return 1;
	} else if (a->data < b->data) {
		return -1;
	} else {
		return 0;
	}
}

int print_menu(int selection)
{
	printf("\n\t.::Hash Menu::.\n");
	printf("\n>Enter 1 to add data into hash");
	printf("\n>Enter 2 to show hash info");
	printf("\n>Enter 3 to delete entire table");
	printf("\n>Enter 4 to search an element in table");
	printf("\n>Enter 5 to delete a specific element");
	printf("\n>Enter 6 to sort the table");
	printf("\n>Enter 7 to exit");
	printf("\n>>>Enter here: ");

	while (!scanf("%d", &selection)) {
		while (getchar() != '\n');
		printf("\nPlease enter a valid menu option: ");
	}

	return selection;
}

void hash_add ()
{
	char user_yn;
	Node* newnode = malloc(sizeof(Node));

	printf("\nEnter the data you want to add: ");

	while (!scanf("%d", &(newnode->data))) {
		printf("\nPlease enter a valid data: ");
		while (getchar() != '\n');
	}

	HASH_ADD_INT(mainhash,data,newnode);

	printf("\nElement added. More? (y/n): ");
	scanf(" %c", &user_yn);

	if(user_yn == 'y') {
		hash_add(mainhash);
	}

	return;
}

void hash_print ()
{
	Node *current;
	for (current = mainhash; current != NULL; current=current->hh.next) {
	        printf("%d\t", current->data);
	    }
			return;
}

int hash_size ()
{
	int len = HASH_COUNT(mainhash);
	return len;
}

void hash_info ()
{
	printf("\n___INFO___\nHash Keys:\n");
	hash_print ();
	printf("\n\nHash Size: %d\n", hash_size());
	return;
}

void hash_delete ()
{
	if((mainhash) == NULL) {
		printf("\nERR: Hash is empty.\n");
		return;
	}
	char user_yn;

	printf("\nWARNING! Are you sure? This will erase entire table! (y/n): ");
	scanf(" %c", &user_yn);

	if(user_yn == 'y'){
		Node *current, *tmp;

		HASH_ITER(hh, mainhash, current, tmp) {
		    HASH_DEL(mainhash,current);
		    free(current);
		  }

		printf("\nTable Deleted.\n");
	}
	return;
}

void hash_search ()
{
	if (mainhash == NULL) {
		printf("\nERR: You can't search a table which has 0 elements.\n");
		return;
	}

	printf("\nEnter the value you want to search for: ");

	int user_value;

	while (!scanf("%d", &user_value)) {
		printf("You can't search that. Please enter a valid data: ");
		while (getchar() != '\n');
	}

	Node *current = NULL;
	HASH_FIND_INT(mainhash,&user_value,current);

	if (current == NULL) {
		printf("\nElement is not in the table.\n");
	} else {
		printf("\nElement %d found in table.\n", current->data);
	}

	return;
}

void hash_sort ()
{
	if (mainhash == NULL) {
		printf("\nERR: You can't sort a table with no elements.\n");
		return;
	}

	HASH_SORT(mainhash, datacmp);
	printf("\nTable sorted.\n");

	return;
}

void node_delete ()
{
	if(mainhash == NULL) {
		printf("\nERR: Table is empty.\n");
		return;
	}

	printf("\nEnter the value you want to delete: ");

	int user_value;
	while (!scanf("%d", &user_value)) {
		printf("\nPlease enter a valid data: ");
		while (getchar() != '\n');
	}

	Node *current = NULL;
	HASH_FIND_INT(mainhash,&user_value,current);

	if(current == NULL) {
		printf("\nElement is not in the list.\n");
	} else {
	    printf("\nNode found and deleted.\n");
	    HASH_DEL( mainhash, current);
	    free(current);
	}

	return;
}

void silent_hash_delete ()
{
	if((mainhash) == NULL) {
		return;
	} else {
		Node *current, *tmp;

		HASH_ITER(hh, mainhash, current, tmp) {
			HASH_DEL(mainhash,current);
			free(current);
		}
	  }

	return;
}

void add_and_search (int a, int b, int c)
{
    	clock_t begin, end;
        double time_spent;

        begin = clock();
        int i;

        for (i = 1; i <= a; i++) {

            Node *newnode = malloc(sizeof(Node));
            newnode->data = i;

            HASH_ADD_INT(mainhash,data,newnode);
        }

        end = clock();
        time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

        printf("\nConstruction: %.8f\n", time_spent);

        int counter;
        for (counter = 0; counter<10000; counter++) {

        	double time_spent_searching;

        	begin = clock();

        	int j;
        	int found_elements = 0;
        	for (j = b; j < c; j++) {
        		Node *current = NULL;
        		HASH_FIND_INT(mainhash,&j,current);
        		if (current) {
        			found_elements++;
        		}
        	}

        	end = clock();
        	time_spent_searching = (double)(end - begin) / CLOCKS_PER_SEC;

        	printf("Search: %.8f ", time_spent_searching);

        	printf("| Elements: %d/%d\n", found_elements, c-b);
        }
}

int main (int argc, char *argv[])
{
	if (argc < 3) {
	        printf("\nERROR: Too few arguments.\nAt least 3 arguments expected.\n");
	        return 1;

	    }

	    add_and_search(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]));

	int user_menu_choice = 0;
	int exit_request = 0;

	while(!exit_request){
	    user_menu_choice = print_menu(user_menu_choice);

		switch (user_menu_choice)
		{
			case 1:
			        hash_add();
					break;

			case 2:
			        hash_info();
					break;

			case 3:
			        hash_delete();
					break;

			case 4:
			        hash_search();
					break;

			case 5:
			        node_delete();
					break;

			case 6:
			        hash_sort();
					break;

			case 7:
			        exit_request = 1;
					break;

			default:
			        printf("\nERR: Please enter option 1-7.\n");
					break;
		}
	}

	silent_hash_delete();
	return 0;
}
