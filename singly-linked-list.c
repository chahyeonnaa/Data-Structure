/*
 * singly linked list
 *
 *  Data Structures
 *  Department of Computer Science
 *  at Chungbuk National University
 */


#include<stdio.h>
#include<stdlib.h>

typedef struct Node { // 노드 구조체
	int key;
	struct Node* link; // 자기와 동일한 타입의 구조체를 가리키는 포인터
} listNode;

typedef struct Head {
	struct Node* first; // 노드를 가리키는 구조체 포인터(첫번째 노드를 가리킬 포인터)
}headNode;


/* 함수 리스트 */
headNode* initialize(headNode* h);
int freeList(headNode* h);

int insertFirst(headNode* h, int key);
int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);

int deleteFirst(headNode* h);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int invertList(headNode* h);

void printList(headNode* h);

int main()
{
	char command;
	int key;
	headNode* headnode = NULL;

	do {
		printf("------------------ [Chahyeona   2020039009] --------------------\n");
		printf("\n");
		printf("----------------------------------------------------------------\n");
		printf("                     Singly Linked List                         \n");
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
		case 'z': case 'Z': // z누르면 초기화
			headnode = initialize(headnode);
			break;
		case 'p': case 'P': // p누르면 내역 출력
			printList(headnode);
			break;
		case 'i': case 'I': // i누르면 오름차순으로 삽입
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D': // d누르면, 입력된 key값 삭제
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N': // 노드의 마지막에 key삽입
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E': // 노드의 젤 마지막 숫자 삭제
			deleteLast(headnode);
			break;
		case 'f': case 'F': // 노드의 가장 첫번째에 숫자 삽입
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T': // 노드의 가장 첫번째 숫자 삭제
			deleteFirst(headnode);
			break;
		case 'r': case 'R': // 순서 뒤집기
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode); // 메모리 해제- 프로그램 종료
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while (command != 'q' && command != 'Q');

	return 1;
}

headNode* initialize(headNode* h) // 초기화_동적으로 공간할당
{

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if (h != NULL)
		freeList(h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	headNode* temp = (headNode*)malloc(sizeof(headNode)); // 구조체 포인터 temp
	temp->first = NULL; // 연결리스트가 비어있음
	return temp;
}

int freeList(headNode* h) {
	/* h와 연결된 listNode 메모리 해제
	 * headNode도 해제되어야 함.
	 */
	listNode* p = h->first; // 첫번째 노드를 가리키는 포인터를 가리키는 포인터 

	listNode* prev = NULL;
	while (p != NULL) { // 연결리스트가 비어있지않으면, 
		prev = p; // prev가 p를 가리키게함.
		p = p->link; //p는 p의 link가 가리키던 곳을 가리키게함. 
		free(prev); // prev 가 가리키는 메모리 공간 해제
	}
	free(h);
	return 0;
}



/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) { // 가장 앞부분에 새로운 노드 추가

	listNode* node = (listNode*)malloc(sizeof(listNode)); // 동적할당 받기
	node->key = key; // 데이터필드에 key값 넣기

	node->link = h->first; // 링크필드가 first가 가리키고 있던 곳을 가리키게함.
	h->first = node; // first는 새로 생성한 노드를 가리키게함.

	return 0;
}

/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {

	return 0;
}

/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) { // list의 마지막에 노드 삽입

	return 0;
}


/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {


	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {

	return 0;

}

/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {

	return 0;
}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {

	return 0;
}


void printList(headNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;

	while(p != NULL) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->link;
		i++;
	}

	printf("  items = %d\n", i);
}
