#include<stdio.h>
#include<stdlib.h>
#define FALSE 0
#define TRUE 1
#define MAX_VERTEX 10

typedef struct Node {
	int key;
	struct Node* link;
} listNode;

typedef struct graph {
	listNode* list[MAX_VERTEX];
	int iden[MAX_VERTEX];
}graph;

graph* Initialize(graph* h);
void InsertVertex(graph* h, int key);
void InsetEdge(graph* h, int connect1, int connect2);
void printgraph(graph* h);
void dfs(graph* h, int key);
int visited[MAX_VERTEX];

int main()
{
	graph* h = NULL;
	char command;
	int key;
	int connect1, connect2; // 연결하고자 하는 vertex

	do {
		printf("\n");
		printf("----------------------------------------------------------------\n");
		printf("                          Graph Searches                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize Graph    = z                              \n");
		printf(" Insert Vertex       = v     Insert Edge          = e \n");
		printf(" Depth First Search  = d     Breath First Search  = b \n");
		printf(" Print Graph         = p     Quit                 = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch (command) {
		case 'z': case 'Z':
			h = Initialize(h);
			break;
		case 'v': case 'V':
			printf("Your Key(0~9) :");
			scanf("%d", &key);
			InsertVertex(h, key);
			break;
		case 'd': case 'D':
			printf("Your Key(0~9) :");
			scanf("%d", &key);
			dfs(h,key);
			for (int i = 0; i < MAX_VERTEX; i++)
			{
				visited[i] = FALSE;
			}
			break;
		case 'p': case 'P':
			printgraph(h);
			break;
		case 'e': case 'E':
			printf("Two vertex :");
			scanf("%d %d", &connect1, &connect2);
			InsetEdge(h, connect1, connect2);
			break;
		case 'b': case 'B':

			break;
		case 'q': case 'Q':
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while (command != 'q' && command != 'Q');

	return 1;
}

graph* Initialize(graph* h)
{
	if (h != NULL)
	{
		free(h->list);
	}
	else
	{
		graph* p = (graph*)malloc(sizeof(graph));
		for (int i = 0; i < MAX_VERTEX; i++)
		{
			p->list[i] = NULL;
		}
		return p;
	}

}

void InsertVertex(graph* h, int key)
{
	h->iden[key] = 1;
	if (key > 9 || key < 0)
		printf("Vertex number exceeded\n");

}

void InsetEdge(graph* h, int connect1, int connect2)
{
	listNode* trail = NULL;
	listNode* trail2 = NULL;

	if (h->iden[connect1] != 1 || h->iden[connect2] != 1)
	{
		printf("vertex is not exist\n");
		return;
	}

	listNode* vertex1 = (listNode*)malloc(sizeof(listNode)); // 정점 생성
	vertex1->key = connect1; // 값 할당
	vertex1->link = NULL;

	if (h->list[connect2] == NULL) // 해당하는 인접 리스트가 아무것도 가리키고 있지 않으면, 
	{
		h->list[connect2] = vertex1; // 바로 생성 vertex를 가리킴.
	}
	else // 해당 인접리스트가 무언가를 가리키고 있는 상태라면,
	{
		trail = h->list[connect2];
		if (trail->key > connect1)
		{
			vertex1->link = trail;
			h->list[connect2] = vertex1;
		}

		else
		{
			while (trail->key < connect1) // 해당 vertex가 들어갈 위치 찾기
			{
				if (trail->link == NULL || trail->link->key > connect1)
					break;
				trail = trail->link;
			}

			vertex1->link = trail->link;
			trail->link = vertex1;
		}
	}


	listNode* vertex2 = (listNode*)malloc(sizeof(listNode));
	vertex2->key = connect2;
	vertex2->link = NULL;

	if (h->list[connect1] == NULL) // 해당하는 인접 리스트가 아무것도 가리키고 있지 않으면, 
	{
		h->list[connect1] = vertex2; // 바로 생성 vertex를 가리킴.
	}
	else // 해당 인접리스트가 무언가를 가리키고 있는 상태라면,
	{
		trail2 = h->list[connect1];

		if (trail2->key > connect2)
		{
			vertex2->link = trail2;
			h->list[connect1] = vertex2;
			return;
		}

		else
		{
			while (trail2->key < connect2) // 해당 vertex가 들어갈 위치 찾기
			{
				if (trail2->link == NULL || trail2->link->key > connect2)
					break;
				trail2 = trail2->link;

			}

			vertex2->link = trail2->link;
			trail2->link = vertex2;

		}
	}

	return;
}
void printgraph(graph* h)
{
	listNode* prev;
	printf("\n--PRINT--\n");
	for (int i = 0; i < MAX_VERTEX; i++)
	{
		if (h->iden[i] == 1)
		{
			printf("정점 %d의 인접리스트 : ", i);
			if (h->list[i] == NULL)
			{
				printf("\n");
				continue;
			}

			prev = h->list[i];
			while (prev != NULL)
			{
				printf("%d ->", prev->key);
				prev = prev->link;
			}
			printf("\n");
		}
	}
	return;

}

void dfs(graph* h,int key)
{

	if (h->iden[key] != 1)
	{
		printf("vertex is not exist\n");
		return;
	}

	visited[key] = TRUE;

	listNode* p = NULL;

	printf("%5d", key);

	for (p = h->list[key]; p; p = p->link)
	{
		if ((visited[p->key])!=TRUE)
			dfs(h, p->key);
	}
}



