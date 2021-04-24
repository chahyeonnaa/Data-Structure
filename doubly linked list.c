/*
 *  doubly-linked-list.c
 *
 *  Doubly Linked List
 *
 *  Data Structures
 *  Department of Computer Science
 *  at Chungbuk National University
 *
 */



#include<stdio.h>
#include<stdlib.h>
 /* 필요한 헤더파일 추가 if necessary */


typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;



typedef struct Head {
	struct Node* first;
}headNode;

/* 함수 리스트 */

/* note: initialize는 이중포인터를 매개변수로 받음
		 singly-linked-list의 initialize와 차이점을 이해 할것 */
int initialize(headNode** h);

/* note: freeList는 싱글포인터를 매개변수로 받음
		- initialize와 왜 다른지 이해 할것
		- 이중포인터를 매개변수로 받아도 해제할 수 있을 것 */
int freeList(headNode* h);

int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);
int insertFirst(headNode* h, int key);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int deleteFirst(headNode* h);
int invertList(headNode* h);

void printList(headNode* h);


int main()
{
	char command;
	int key;
	headNode* headnode = NULL;

	do {
		printf("---------------- [2020039009] [Chahyeona] ----------------------\n");
		printf("----------------------------------------------------------------\n");
		printf("                     Doubly Linked  List                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch (command) {
		case 'z': case 'Z':
			initialize(&headnode); // headnode 구조체의 주소를 함수의 인자로 호출
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while (command != 'q' && command != 'Q');

	return 1;
}


int initialize(headNode** h) { // headNode 구조체를 가리키는 이중포인터 h를 함수의 매개변수로 선정
	                           // headNode의 first가 가리킬 공간을 할당받아야함.

	/* headNode가 NULL이 아니면, freeList를 호출하여 할당된 메모리 모두 해제 */
	if (*h != NULL)  // (*h)= 이중포인터 h가 가리키는 곳의 값(주소)= 기본 포인터 headNode의 first
		freeList(*h);

	(*h) = (headNode*)malloc(sizeof(headNode));
	(*h)->first = NULL;

	return 1;
}

int freeList(headNode* h) {

	listNode* p = h->first; // 첫번째 노드를 가리키는 포인터를 가리키는 포인터 

	listNode* prev = NULL;

	while (p != NULL) { // 연결리스트가 비어있지않으면, 
		prev = p; // prev가 p를 가리키게함.
		p = p->rlink; //p는 p의 rlink가 가리키던 곳을 가리키게함. 
		free(prev); // prev 가 가리키는 메모리 공간 해제
	}
	free(h);

	return 0;
}


void printList(headNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if (h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;

	while (p != NULL) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;
		i++;
	}

	printf("  items = %d\n", i);
}




/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); // 동적할당 받기
	node->key = key; // 데이터필드에 key값 넣기

	listNode* n = h->first;

	while (n->rlink != NULL) // list의 마지막칸에 도달할때까지 반복문 돌리기
	{
		n = n->rlink; // 마지막에 도달할때까지 계속 다음 노드로 전진 
	}

	n->rlink = node; 
	node->llink = n->rlink; // node의 llink와 n의 rlink연결
	node->rlink = NULL; // node가 마지막 노드이므로 rlink에는 널값을 넣어줌.

	return 0;
}



/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {

	listNode* trail = NULL; // 삭제할 노드의 선행 노드를 가리키는 포인터
	listNode* x = (h->first); // 삭제하고자 하는 노드를 가리키는 포인터

	if (h->first == NULL) // list가 비어있다면, 비어있다고 알려주기
		printf("Node does not exist\n");
	else
	{
		while (x->rlink != NULL) // list의 마지막에 도달할때까지
		{
			trail = x; // trail과 x를 함께 앞으로 전진
			x = x->rlink;
		}
		trail->rlink = NULL; // 삭제하고자 하는 노드 무시

		free(x); // 삭제될 메모리 공간 해제
	}

	return 0;
}



/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {


}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {


}



/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {


}



/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {


}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {

}



