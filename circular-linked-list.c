/*
 *  doubly circular linked list
 *
 *  Data Structures
 *
 *  Department of Computer Science
 *  at Chungbuk National University
 *
 */



#include<stdio.h>
#include<stdlib.h>
 /* 필요한 헤더파일 추가 */

typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;

/* 함수 리스트 */
int initialize(listNode** h);
int freeList(listNode* h);
int insertLast(listNode* h, int key);
int deleteLast(listNode* h);
int insertFirst(listNode* h, int key);
int deleteFirst(listNode* h);
int invertList(listNode* h);

int insertNode(listNode* h, int key);
int deleteNode(listNode* h, int key);

void printList(listNode* h);



int main()
{
	char command;
	int key;
	listNode* headnode = NULL;

	do {
		printf("----------------------------------------------------------------\n");
		printf("                  Doubly Circular Linked List                   \n");
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
			initialize(&headnode);
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


int initialize(listNode** h) {

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if (*h != NULL)
		freeList(*h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	*h = (listNode*)malloc(sizeof(listNode));
	(*h)->rlink = *h;
	(*h)->llink = *h;
	(*h)->key = -9999;
	return 1;
}

/* 메모리 해제 */
int freeList(listNode* h) {

	return 0;
}



void printList(listNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if (h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->rlink;

	while (p != NULL && p != h) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;
		i++;
	}
	printf("  items = %d\n", i);


	/* print addresses */
	printf("\n---checking addresses of links\n");
	printf("-------------------------------\n");
	printf("head node: [llink]=%p, [head]=%p, [rlink]=%p\n", h->llink, h, h->rlink);

	i = 0;
	p = h->rlink;
	while (p != NULL && p != h) {
		printf("[ [%d]=%d ] [llink]=%p, [node]=%p, [rlink]=%p\n", i, p->key, p->llink, p, p->rlink);
		p = p->rlink;
		i++;
	}

}



/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(listNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); // 동적할당 받기
	node->key = key; // 데이터필드에 key값 넣기

	listNode* n = h;

	while (n->rlink != h) // list의 마지막칸에 도달할때까지 반복문 돌리기
	{
		n = n->rlink; // 마지막에 도달할때까지 계속 다음 노드로 전진 
	}
	n->rlink = node;
	node->llink = n; // node의 llink와 n의 rlink연결
	node->rlink = h; // node의 rlink가 제일 처음을 가리키게 하여 순환할 수 있게함.
	h->llink = node; // 제일 처음과 마지막 노드를 연결

	return 1;
}

/**
 * list의 마지막 노드 삭제
 */
int deleteLast(listNode* h) {

    listNode* trail = NULL; // 삭제할 노드의 선행 노드를 가리키는 포인터
	listNode* x = h; // 삭제하고자 하는 노드를 가리키는 포인터

	if ((h->llink == h) && (h->rlink == h)) // 공백리스트이면, 비어있다는 메세지 출력
		printf("Node does not exist\n");
	else
	{
		while (x->rlink!=h)// list의 마지막에 도달할때까지
		{
			trail = x; // trail과 x를 함께 앞으로 전진
			x = x->rlink;
		}
		trail->rlink = h;// 삭제하고자 하는 노드를 무시하고 trail과 head를 연결시켜줌
		h->llink = trail;
		
		free(x); // 삭제될 메모리 공간 해제
	}

	return 1;


	return 1;
}


/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(listNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); // 동적할당 받기
	node->key = key; // 데이터필드에 key값 넣기

	listNode* n = h;

	if ((h ->llink == h) && (h->rlink ==h)) // 공백리스트이면,
	{
		h->rlink = node; // 해당 노드를 가장 첫 노드로 설정
		node->llink = h; // head노드와 해당 노드를 연결
		node->rlink = h;
		h->llink = node; // head노드와 해당 노드를 연결
		return 1;
	}
	else // 공백리스트가 아니면
	{

		while (n->rlink != h) // list의 마지막칸에 도달할때까지 반복문 돌리기
		{
			n = n->rlink; // 마지막에 도달할때까지 계속 다음 노드로 전진 
		}

		node->llink = h; // head노드와 해당 노드를 연결
		node->rlink = h->rlink; // node의 rlink를 h->rlink가 가리키고 있던 곳을 가리키게함. 
		h->rlink->llink = node; // 해당 node와 다음 위치의 노드를 연결
		h->rlink = node; // head노드와 해당 노드를 연결
		h->llink = n; // 가장 마지막 노드와 head노드 연결
		n->rlink = h;
	}

	return 1;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(listNode* h) {
    
    listNode* n = h;

	if ((h->llink == h) && (h->rlink == h)) // list가 비어있으면 비어있다고 알려주기
		printf("Node does not exist\n");
	else
	{
		h->rlink = h->rlink->rlink; // head를 원래 가리키고 있던 다음 노드를 가리키게 해줌.
		h->rlink->rlink->rlink->llink = h; // 삭제하고자 하는 해당 노드의 다음 노드와 head를 연결
	}
    // 메모리 해제 해야하는데 모르겠다
	return 1;

}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(listNode* h) {


	return 0;
}



/**
 *  리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입
 **/
int insertNode(listNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); // 동적할당 받기
	(node->key) = key; // 삽입할 노드 만들기

	listNode* trail = NULL; // listNode 구조체를 가리키는 구조체 포인터 trail
	listNode* x = h; // listNode 구조체를 가리키는 구조체 포인터 x


	if ((h->llink == h) && (h->rlink == h)) // 공백리스트이면,
	{
		h->rlink = node;
		node->llink = h;
		node->rlink = h;
		h->llink = node;
		return 1;
	}
	// 공백 list가 아니면,
	else
	{

		if ((h->rlink->key) > key) // 첫번째에 바로 추가되어야하는 상황이라면( 값이 가장 작다면)
		{
			listNode* n = h;

			while (n->rlink != h) // list의 마지막칸에 도달할때까지 반복문 돌리기
			{
				n = n->rlink; // 마지막에 도달할때까지 계속 다음 노드로 전진 
			}

			node->llink = h; // insertFirst 와 같은 로직
			node->rlink = h->rlink;
			h->rlink->llink = node;
			h->rlink = node;
			h->llink = n;
			n->rlink = h;

			return 1;

		}
		else // 숫자를 차례대로 비교하기
		{
			while ((x->key) < key) // 넣고자 하는 key값과 x의 key값을 비교
			{
				trail = x; // trail포인터와 x포인터가 함께 한칸씩 전진
				x = x->rlink;
				if (trail->rlink == h) // list의 마지막에 추가되어야 하는 상황이라면, 
				{
					trail->rlink = node; // trail의 바로 뒤에 연결 = list의 가장 마지막 노드가 됨.
					node->llink = trail; // node와 trail 연결
					node->rlink = h; // 해당노드인 마지막 노드와 head노드(처음)을 연결
					h->llink = node;
					return 1;
				}

			}
			// 노드들의 중간에 삽입되는 경우
			trail->rlink = node; // node와 trail을 연결
			node->llink = trail;
			node->rlink = x; // 해당 node와 다음 node를 연결 
			x->llink = node;
		}
	}

	return 1;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(listNode* h, int key) {


	listNode* trail = NULL; // 삭제할 노드의 선행 노드를 가리키는 포인터
	listNode* x = h; // 삭제하고자 하는 노드를 가리키는 포인터

	if ((x->key) == key) // 첫번째 노드를 삭제해야하면, 
	{
		h->rlink = h->rlink->rlink; // head를 원래 가리키고 있던 다음 노드를 가리키게 해줌.
		h->rlink->rlink->rlink->llink = h; // 삭제하고자 하는 해당 노드의 다음 노드와 head를 연결
		return 0;
	}

	while ((x->key) != key) // 삭제하고자 하는 key값을 찾을때까지
	{
		trail = x; //trail과 x는 함께 앞으로 한칸씩 전진
		x = x->rlink;
		if (trail->rlink == h) // 삭제하고자 하는 key값이 없다면 없다고 알려주기
		{
			printf("There is no data you are looking for!\n");
			return 0;
		}
	}

	if (x->rlink == h) // 마지막 노드가 삭제되는 상황이면
	{
		trail->rlink = h;// 삭제하고자 하는 노드를 무시하고 trail과 head를 연결시켜줌
		h->llink = trail;

		free(x); // 삭제될 메모리 공간 해제
		return 0;
	}
	else
	{
		trail->rlink = x->rlink; // 노드 삭제
		x->rlink->llink = trail;

		free(x); // 삭제될 메모리 공간 해제
		return 0;
	}

}


