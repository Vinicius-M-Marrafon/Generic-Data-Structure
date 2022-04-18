/*
 *	Por: Vinicius Mari Marrafon
 *	Linguagem: C99
 *	Sistema Operacional: Windows 10
 *	Compilacao do Codigo Abaixo: gcc challenger1.c -o challenger1.exe -Wall -Werror -std=c99 -ggdb
 *
 *	--- Lista Circular Duplamente Encadeada Generica ---
 *
 *	Assinatura: ViMM
 *
 * */
#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define byte uint8_t

// No da lista
typedef struct node
{
	size_t data_s;
	void *data;
	struct node *next, *prev;
}
node;

// Demarca o inicio, final e o terminal (tambem conhecido como no cabeca) da lista circular
typedef struct list
{
	size_t len;
	node *head, *last;
	node *terminal;
}
list;

// Prototipo das funcoes
void start(list *l);
void push_back(list *l, void *data, size_t data_s);
void push_front(list *l, void *data, size_t data_s);
void pop_back(list *l);
void pop_front(list *l);
bool is_empty(list *l);
void destroy(list *l);
node *at(list *l, unsigned index);
node *nalloc(void *data, size_t data_s);

void *get_fn(list *l, unsigned index);
#define get_addr(type, l, index) (type *)(get_fn(&l, index))
#define get_string(l, index) (char *)(get_fn(&l, index))
#define get_value(type, l, index) *(type *)(get_fn(&l, index))

// tipo simples de dado
#define type_list(type, fmt, L)										\
	for (node *it = L.head; it != L.terminal; it = it->next) {		\
		printf("[ ");												\
		for (int u = 0; u < it->data_s/ sizeof(type); u++)			\
			printf(fmt, *(type *)(it->data + (u * sizeof(type))));	\
		printf("] -> ");											\
	}																\
	puts("\\");														\


struct ponto
{
	double x, y, z;
};

struct gato
{
	char nome[20], sexo[10];
	float peso;
	byte idade;
};

int main(void)
{
	list l1, l2, l3, l4;
	
	// Espaco Lista 1 (Teste Armazenando Somente Inteiros)
	start(&l1);

	int i1 = 1, i2 = 2, i3 = 3, v[] = {4, 5, 6}, m[2][2] = {{7, 8}, {9, 10}};
	
	push_back(&l1, &i1, sizeof(i1));
	push_back(&l1, &i2, sizeof(i2));
	push_back(&l1, &i3, sizeof(i3));

	for (int i = 0; i < l1.len; i++)
		printf("[%d] -> ", get_value(int, l1, i));
	puts("\\");

	push_front(&l1, v, sizeof(v));
	push_back(&l1, &m[0], sizeof(m));

	int *a = get_addr(int, l1, 0);
	for (int i = 0; i < 3; i++)
		printf("(%d)", *(a + i));
	puts("-> \\");
	
	// So funciona desde que a lista armazene 1 tipo de dado
	type_list(int, "%d ", l1);

	destroy(&l1);
	
	// Espaco Lista 2 (char | strings);
	start(&l2);
	
	push_back(&l2, "Nao se esqueca de tomar o seu nescau!", sizeof("Nao se esqueca de tomar o seu nescau!"));
	push_front(&l2, "Lista generica", sizeof("Lista generica"));
	push_back(&l2, "Kin Lai", sizeof("Kin Lai"));

	type_list(char, "%c", l2);

	char dont_care[9][10] = {
		"Pessoa1", "Endereco1", "Numero1",
		"Pessoa2", "Endereco2", "Numero2",
		"Pessoa3", "Endereco3", "Numero3"
	};

	push_back(&l2, dont_care[0], sizeof(dont_care));

	type_list(char, "%c", l2);

	destroy(&l2);

	// Espaco Lista 3 (struct ponto)
	start(&l3);
	
	struct ponto p0 = { .x = 0.0, .y = 0.0, .z = 0.0 };
	struct ponto p1 = { .x = 1.0, .y = 0.0, .z = 0.0 };
	struct ponto p2 = { .x = 0.0, .y = 1.0, .z = 0.0 };
	struct ponto p3 = { .x = 0.0, .y = 0.0, .z = 1.0 };

	push_back(&l3, &p0, sizeof(p0));
	push_back(&l3, &p1, sizeof(p1));
	push_back(&l3, &p2, sizeof(p2));
	push_back(&l3, &p3, sizeof(p3));
	
	for (int i = 0; i < l3.len; i++)
		printf("P%d = (%.1lf, %.1lf, %.1lf)\n", i, (get_addr(struct ponto, l3, i))->x, 
											       (get_addr(struct ponto, l3, i))->y,
											       (get_addr(struct ponto, l3, i))->z );
	
	// Como ponto eh uma strutura de apenas doubles, entao pode
	type_list(double, "%.1lf ", l3);
	
	// Adicionando outras structs
	struct gato mia = {
		.nome = "Mia", .sexo = "Femea", .idade = 12, .peso = 4.5
	};

	push_front(&l3, &mia, sizeof(mia));
	
	printf("Mia = {%s, %s, %.1f, %u)\n", (get_addr(struct gato, l3, 0))->nome, 
										 (get_addr(struct gato, l3, 0))->sexo,
										 (get_addr(struct gato, l3, 0))->peso,
										 (get_addr(struct gato, l3, 0))->idade);

	destroy(&l3);	
	
	// Espaco Lista 4 (Generica mesmo!)
	start(&l4);

	int val1 = 53;
	float val2 = 23.45;
	double val3 = 1.618033;
	char autor[] = "Vinicius Mari Marrafon";
	char desafio[] = "Lista Circular Duplamente Encadeada Generica";
	struct ponto p = { .x = 0.0, .y = 4.6, .z = -0.5 };
	struct gato molly = { .nome = "Molly", .sexo = "Femea", .peso = 5., .idade = 8 };

	push_back(&l4, &val1, sizeof(val1));	
	push_back(&l4, &val2, sizeof(val2));	
	push_back(&l4, &val3, sizeof(val3));	
	push_front(&l4, autor, sizeof(autor));	
	push_front(&l4, desafio, sizeof(desafio));	
	push_back(&l4, &p, sizeof(p));	
	push_back(&l4, &molly, sizeof(molly));

	printf("[%s] -> ", get_string(l4, 0));
	printf("[%s] -> ", get_string(l4, 1));
	printf("[%d] -> ", get_value(int, l4, 2));
	printf("[%.1f] -> ", get_value(float, l4, 3));
	printf("[%.4lf] -> ", get_value(double, l4, 4));
	printf("[(%.1lf, %.1lf, %.1lf)] -> ", (get_addr(struct ponto, l4, 5))->x,
										  (get_addr(struct ponto, l4, 5))->y,
										  (get_addr(struct ponto, l4, 5))->z);

	printf("[%s, %s, %.1f, %u] -> ", (get_addr(struct gato, l4, 6))->nome, 
									 (get_addr(struct gato, l4, 6))->sexo,
									 (get_addr(struct gato, l4, 6))->peso,
									 (get_addr(struct gato, l4, 6))->idade);

	puts("\\\nE Isto eh Tudo por hoje!\n\n");
	printf("List size: %u\n", l4.len);
	
	pop_front(&l4);

	printf("List size: %u\n", l4.len);
	
	destroy(&l4);
	
	printf("List size: %u\n", l4.len);
	printf("%lf\n", get_value(float, l4, 0));
	
	return 0;
}

void start(list *l)
{
	l->head = l->last = NULL;
	
	l->terminal = (node *)malloc(sizeof(node));
	if (l->terminal == NULL) return;
	
	l->terminal->prev = l->last;
	l->terminal->next = l->head;
	
	l->len = 0;
}

// node alloc
node *nalloc(void *data, size_t data_s)
{
	node *new_node = (node *)malloc(sizeof(node));
	if (new_node == NULL) return NULL;

	new_node->data_s = data_s;
	new_node->data = malloc(data_s);
	memcpy(new_node->data, data, data_s);
	new_node->next = new_node->prev = NULL;

	return new_node;	
}

void push_back(list *l, void *data, size_t data_s)
{
	node *new_node = nalloc(data, data_s);
	if (new_node == NULL) return;

	l->len++;
	if (l->last == NULL)
	{
		l->last = l->head = new_node;
		
		l->terminal->prev = l->terminal->next = new_node;
		new_node->prev = new_node->next = l->terminal;
		
		l->last->next = l->last->prev = l->terminal;
		l->head->next = l->head->prev = l->terminal;
	}
	else
	{
		l->terminal->prev = new_node;
		new_node->next = l->terminal;
		new_node->prev = l->last; 
		l->last->next = new_node;
		l->last = new_node;
	}
}

void push_front(list *l, void *data, size_t data_s)
{
	node *new_node = nalloc(data, data_s);
	if (new_node == NULL) return;

	l->len++;
	if (l->head == NULL)
	{
		l->terminal->prev = l->terminal->next = new_node;
		new_node->prev = new_node->next = l->terminal;
		
		l->last = l->head = new_node;

		l->last->next = l->last->prev = l->terminal;
		l->head->next = l->head->prev = l->terminal;
	}
	else
	{
		l->terminal->next = new_node;
		new_node->prev = l->terminal;
		new_node->next = l->head;
		l->head->prev = new_node;
		l->head = new_node;
	}
}

void pop_back(list *l)
{
	if (!is_empty(l))
	{
		node *iterator = l->head;
		for (int i = 0; i < l->len - 1; i++)
			iterator = iterator->next;

		iterator->next = l->last->next;
		free(l->last->data);
		free(l->last);
		l->last = iterator;

		l->len--;
		if (l->len == 0) l->head = l->terminal;
	}	
}

void pop_front(list *l)
{
	if (!is_empty(l))
	{
		node *tmp = l->head->next;
		free(l->head->data);
		free(l->head);
		l->head = tmp;

		l->len--;
		if (l->len == 0) l->last = l->terminal;
	}	
}

bool is_empty(list *l)
{
	return l->len == 0;
}

void destroy(list *l)
{
	while (!is_empty(l))
		pop_front(l);

	free(l->terminal);
}

void *get_fn(list *l, unsigned index)
{
	assert(index >= 0 && index < l->len && !is_empty(l));

	node *iterator = l->head;
	for (int i = 0; i < index; i++)
		iterator = iterator->next;

	return iterator->data;
}

node *at(list *l, unsigned index)
{
	assert(index >= 0 && index < l->len && !is_empty(l));
	
	node *iterator = l->head;
	for (int i = 0; i < index; i++)
		iterator = iterator->next;

	return iterator;
}
