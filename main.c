#include <stdio.h>

#include "list.h"
#include "delta_list.h"

void testListFunctions()
{
	printf("===================================\n");
	printf("\tTesting List functions\n");
	printf("===================================\n");

    List l;
	LIST_POS_T lLen = 1000;
	LIST_OUT_BUF_LEN_T lPrintLen = 3000;

    LIST_MEMB_T lMem[1000] = {0};
    char lPrint[3000] = {0};

    int status = 0;

    // INITIATION TESTS
    printf("Initialization tests:\n");
    status = list_init(&l, lMem, 0); // bad list len
    printf("\tstatus: %d\n", status);
    status = list_init(NULL, NULL, lLen); // NULL pointers instead of objects
    printf("\tstatus: %d\n", status);
    status = list_init(&l, lMem, lLen); // good list init
    printf("\tstatus: %d\n", status);

    // PRINTING EMPTY LIST
    status = list_print(&l, lPrint, 2); // buffer too small for 'empty' message
    printf("\tstatus: %d\n", status);
    printf("List: %s\n", lPrint);

    status = list_print(&l, lPrint, lPrintLen);
    printf("\tstatus: %d\n", status);
    printf("List: %s\n", lPrint);



    // DELETION FROM EMPTY LIST TESTS, all will return bad status codes
    printf("Deleting from empty list\n");
    status = list_delete(&l, 0);
    printf("\tstatus: %d\n", status);
    status = list_delete(&l, 3);
    printf("\tstatus: %d\n", status);

    // INSERT ELEM TO LIST TEST
    printf("Insertions\n");
    status = list_insert(&l, 3, 10); // invalid position
    printf("\tstatus: %d\n", status);

    status = list_insert(&l, 0, 12); // good insert initial element
    printf("\tstatus: %d\n", status);

    status = list_print(&l, lPrint, 2); // buffer too small for last elem, error thrown
    printf("\tstatus: %d\n", status);

    status = list_print(&l, lPrint, 3); // good print for one elem
    printf("\tstatus: %d\n", status);
    printf("List: %s\n", lPrint);


    status = list_insert(&l, 0, 10); // good insert at beginning
    printf("\tstatus: %d\n", status);
    status = list_print(&l, lPrint, 4); // buffer too small for last elem, error thrown
    printf("\tstatus: %d\n", status);
    status = list_print(&l, lPrint, lPrintLen); // good print for multiple elems
    printf("\tstatus: %d\n", status);
    printf("List: %s\n", lPrint);

    status = list_insert(&l, 1, 11); // good insert at middle
    printf("\tstatus: %d\n", status);
    status = list_print(&l, lPrint, lPrintLen);
    printf("\tstatus: %d\n", status);
    printf("List: %s\n", lPrint);

    status = list_insert(&l, 3, 13); // good insert at end
    printf("\tstatus: %d\n", status);
    status = list_print(&l, lPrint, lPrintLen);
    printf("\tstatus: %d\n", status);
    printf("List: %s\n", lPrint);

	printf("Printing after deleting an element from the list\n");
	status = list_delete(&l, 20); // bad delete
    printf("\tstatus: %d\n", status);

    status = list_delete(&l, 3);
    printf("\tstatus: %d\n", status);
    status = list_print(&l, lPrint, lPrintLen);
    printf("\tstatus: %d\n", status);
    printf("List: %s\n", lPrint);

	status = list_delete(&l, 0);
    printf("\tstatus: %d\n", status);
    status = list_print(&l, lPrint, lPrintLen);
    printf("\tstatus: %d\n", status);
    printf("List: %s\n", lPrint);

	status = list_delete(&l, 0);
    printf("\tstatus: %d\n", status);
    status = list_print(&l, lPrint, lPrintLen);
    printf("\tstatus: %d\n", status);
    printf("List: %s\n", lPrint);

	status = list_delete(&l, 0);
    printf("\tstatus: %d\n", status);
    status = list_print(&l, lPrint, lPrintLen);
    printf("\tstatus: %d\n", status);
    printf("List: %s\n", lPrint);

	printf("\n===================================\n");
}

void testDeltaListFunctions()
{
	printf("ΔΔΔΔΔΔΔΔΔΔΔΔΔΔΔΔΔΔΔΔΔΔΔΔΔΔΔΔΔΔΔΔΔΔΔ\n");
	printf("\tTesting DELTA-List functions\n");
	printf("ΔΔΔΔΔΔΔΔΔΔΔΔΔΔΔΔΔΔΔΔΔΔΔΔΔΔΔΔΔΔΔΔΔΔΔ\n");
    List l;
	LIST_POS_T lLen = 1000;
	LIST_OUT_BUF_LEN_T lPrintLen = 3000;

    LIST_MEMB_T lMem[1000] = {0};
    char lPrint[3000] = {0};

    int status = 0;

	status = list_init(&l, lMem, lLen); // good list init
    printf("\tstatus: %d\n", status);

	printf("Inserting 10 to empty list\n");
	deltaList_insert(&l, 10);

    status = list_print(&l, lPrint, lPrintLen);
    printf("List: %s\n", lPrint);

	printf("Inserting 3\n");
	// l: 3 7
	deltaList_insert(&l, 3);
    status = list_print(&l, lPrint, lPrintLen);
    printf("List: %s\n", lPrint);

	// Insert 12 at end
	// l: 3 7 2
	printf("Inserting 12\n");
	deltaList_insert(&l, 12);
    status = list_print(&l, lPrint, lPrintLen);
    printf("List: %s\n", lPrint);
	printf("ΔΔΔΔΔΔΔΔΔΔΔΔΔΔΔΔΔΔΔΔΔΔΔΔΔΔΔΔΔΔΔΔΔΔΔ\n");
}

int main(void)
{
	testListFunctions();
	// testDeltaListFunctions();

	List l;
	LIST_POS_T lLen = 1000;
    LIST_MEMB_T lMem[1000] = {0};

    char lPrint[3000] = {0};
	LIST_OUT_BUF_LEN_T lPrintLen = 3000;

    int status = 0;

	status = list_init(&l, lMem, lLen);
	printf("Delta list init status: %d\n", status);

	printf("Enter the element to be inserted into the delta list\n");
	while(1)
	{
		LIST_MEMB_T input;
		printf("Enter the element for insertion:\n");
		scanf("%"LIST_MEMB_SCN"", &input);
		status = deltaList_insert(&l, input);
		if (status != 0)
		{
			printf("Insertion failed. error code: %d\n", status);
		}
		else
		{
			printf("Insertion successful!\n");
		}
		status = list_print(&l, lPrint, 1000);
		printf("List: %s\n", lPrint);
	}

    return 0;
}
