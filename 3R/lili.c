#include <stdlib.h>
#include <stdio.h>
#include "lili.h"

element_t *head;

/* Einfügen von Elementen */
unsigned int insert_element(unsigned int value)
{
	/* Erstellung eines Elements */
	element_t *newElement;
	newElement = (element_t *) malloc(1 * sizeof(element_t));

  // debug lol
  //printf("value: %d, pointer: %p, size: %d\n", value, newElement, (int) (1 * sizeof(element_t)));

	if ( newElement == NULL )
	{
		return 0; // fehlerwert
	}


	newElement->data = value;
  newElement->next = NULL; // fu !!! vergessen das einfach müll im speicher stehen kann

	element_t *lauf = head;

	if (lauf) { // lauf hat elemente

		while ( lauf->next ) // beendet wenn lauf auf null zeigt
		{
			lauf = lauf->next;
		}

		lauf->next = newElement;
	} else { // lauf war leer
		head = newElement;
	}
	return value;
}

/* Löschen von Elementen*/
unsigned int remove_element(void)
{
	unsigned int value = 0;
	if (head) { // wenn head nicht leer, Speicher sichern
		value = head->data;		
		element_t *temp = head;
		head = head->next; // auf nächstes Element übergehen
		free(temp);
	}
	return value;
}
void print_lili(void)
{
	if (head) {
		element_t *lauf = head;
    //printf("head: %p\n", head);
		printf("%d, ", lauf->data);
		while (lauf->next) {
      lauf = lauf->next;
      //printf("lauf: %p\n", lauf);
			printf("%d, ", lauf->data);
		}
	} else {
    printf("leer");
  }
  printf("\n"); // umbruch am ende
}
