/*
 * Binary Search Tree #2
 *
 * Data Structures
 *
 * Department of Computer Science
 * at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int key;
	struct node* left;
	struct node* right;
} Node;

/* for stack */
#define MAX_STACK_SIZE		20
Node* stack[MAX_STACK_SIZE];
int top = -1;

Node* pop();
void push(Node* aNode);

/* for queue */
#define MAX_QUEUE_SIZE		20
Node* queue[MAX_QUEUE_SIZE];
int front = -1;
int rear = -1;

Node* deQueue();
void enQueue(Node* aNode);


int initializeBST(Node** h);

/* functions that you have to implement */
void recursiveInorder(Node* ptr);	  /* recursive inorder traversal */
void iterativeInorder(Node* ptr);     /* iterative inorder traversal */
void levelOrder(Node* ptr);	          /* level order traversal */
int insert(Node* head, int key);      /* insert a node to the tree */
int deleteNode(Node* head, int key);  /* delete the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */


int main()
{
	char command;
	int key;
	Node* head = NULL;

	do {
		printf("\n\n");
        printf("--------------------[ 2020039009 Chahyeona ]--------------------\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #2                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = i      Delete Node                  = d \n");
		printf(" Recursive Inorder    = r      Iterative Inorder (Stack)    = t \n");
		printf(" Level Order (Queue)  = l      Quit                         = q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch (command) {
		case 'z': case 'Z':
			initializeBST(&head);
			break;
		case 'q': case 'Q':
			freeBST(head);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(head, key);
			break;

		case 'r': case 'R':
			recursiveInorder(head->left);
			break;
		case 't': case 'T':
			iterativeInorder(head->left);
			break;

		case 'l': case 'L':
			levelOrder(head->left);
			break;

		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while (command != 'q' && command != 'Q');

	return 1;
}

int initializeBST(Node** h) {

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if (*h != NULL)
		freeBST(*h);

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node));
	(*h)->left = NULL;	/* root */
	(*h)->right = *h;
	(*h)->key = -9999;

	top = -1;

	front = rear = -1;

	return 1;
}



void recursiveInorder(Node* ptr)
{
	if (ptr) {
		recursiveInorder(ptr->left);
		printf(" [%d] ", ptr->key);
		recursiveInorder(ptr->right);
	}
}

/**
 * textbook: p 224s
 */
void iterativeInorder(Node* node) // 중위순회를 위한 비순환 방식
{
	top = -1;
	for (;;) {
		for (; node; node = node->left)
			push(node); // 노드가 널이 아니면, 스택에 노드를 push

		node = pop(); // 스택의 탑에 있던 데이터를 pop

		if (!node) // node가 널값이면_ 공백스택이면
			break; // 반복문 탈출

		printf(" [%d] ", node->key); // 노드 값 출력
		node = node->right; // 노드를 바꾸어 재탐색
	}
}

/**
 * textbook: p 225
 */
void levelOrder(Node* ptr) // 처음부터 levelorder 방식으로 데이터를 읽어나가는 함수
{
	if (!ptr) return; // 공백트리라면 return

	enQueue(ptr); // 루트노드 값을 큐에 삽입

	for (;;) {
		ptr = deQueue(); // 큐에서 pop
		if (ptr) // ptr이 널값이 아니면
		{
			printf(" [%d] ", ptr->key); // ptr 데이터값 출력
			if (ptr->left) // ptr->left의 값이 널이 아니면
				enQueue(ptr->left); // 큐에 해당 데이터 삽입
			if (ptr->right) // ptr->right의 값이 널이 아니면
				enQueue(ptr->right); // 큐에 해당 데이터 삽입
		}
		else // ptr이 더이상 아무것도 가리키지 않으면 반복문 탈출
			break;
	}
}

int insert(Node* head, int key)
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->key = key;
	newNode->left = NULL;
	newNode->right = NULL;

	if (head->left == NULL) {
		head->left = newNode;
		return 1;
	}

	/* head->left is the root */
	Node* ptr = head->left;

	Node* parentNode = NULL;
	while (ptr != NULL) {

		/* if there is a node for the key, then just return */
		if (ptr->key == key) return 1;

		/* we have to move onto children nodes,
		 * keep tracking the parent using parentNode */
		parentNode = ptr;

		/* key comparison, if current node's key is greater than input key
		 * then the new node has to be inserted into the right subtree;
		 * otherwise the left subtree.
		 */
		if (ptr->key < key)
			ptr = ptr->right;
		else
			ptr = ptr->left;
	}

	/* linking the new node to the parent */
	if (parentNode->key > key)
		parentNode->left = newNode;
	else
		parentNode->right = newNode;
	return 1;
}


int deleteNode(Node* head, int key)
{
	Node* parent = NULL; // 삭제하고자 하는 노드의 부모 노드를 가리킬 포인터
	Node* child = head->left; // 루트노드를 가리키는 포인터

	Node* temp; // 하나의 자식을 가지는 경우에 쓰임
	Node* namu; // 두개의 자식을 가지는 경우에 쓰임
	Node* x; // 삭제하고자 하는 노드의 위치를 기억하는 포인터

	while (1) // key값 찾기
	{
		parent = child; // 찾고자 하는 노드의 부모 노드
		if (child->key > key) // 찾고자 하는 노드가 해당 위치의 노드보다 작으면
		{
			child = child->left; // child값을 재정의하여 반복문을 다시 실행_ 왼쪽 탐색
		}
		else if (child->key < key) // 찾고자 하는 노드가 해당 위치의 노드보다 크면
		{
			child = child->right; // child값을 재정의하여 반복문을 다시 실행_ 오른쪽 탐색
		}

		if (child->key == key || (child->right == NULL && child->left == NULL))
			break; // 값을 찾았거나, 찾고자 하는 값이 없어서 트리의 끝에 도달했을 경우 반복문 탈출
	}

	if (child->key != key && child->right == NULL && child->left == NULL) // 키 값이 일치하지 않고, 트리의 끝에 도달했으면
	{
		printf("the node [%d] is not exist", key); // 키 값이 존재하지 않는다는 문구 출력
		return 1;
	}

	if (child->left != NULL && child->right != NULL) // 두개의 자식을 가지는경우
	{
		x = child; // 삭제하고자 하는 노드의 위치를 기억

		child = child->right; // 오른쪽 트리에서 가장 작은 값을 찾아서 그걸로 대체해야하기 때문에
							  // 오른쪽 트리를 탐색  
		while (1)
		{
			namu = child; // 오른쪽 트리의 루트 노드 위치를 기억
			if (child->left == NULL) // 오른쪽 트리에서 루트노드가 유일하거나, 루트노드의 왼쪽이 비어있을때
				break; // 탈출

			child = child->left; // 가장 작은 값을 찾아야하기때문에 왼쪽 노드를 계속 탐색

			if (child->left == NULL) // 오른쪽 트리의 가장 마지막 왼쪽 노드라면
			{
				namu->left = NULL; // 이 값이 대체노드로 올라가기 때문에, 해당 노드의 부모가 널값을 가리키게 해야함.
				break; // 탈출
			}
		}

		if (x->key > parent->key) //삭제하고자 하는 값이 바로 상위노드보다 크면,
		{
			parent->right = child; // 부모의 오른쪽과 대체 노드를 연결
		}
		else if (x->key < parent->key) //삭제하고자 하는 값이 바로 상위노드보다 작으면,
		{
			parent->left = child; // 부모의 오른쪽과 대체노드를 연결
		}


		if (x->left == NULL) // 삭제하고자 하는 노드의 왼쪽 노드가 없다면,
		{
			child->left = NULL; // 대체 노드의 왼쪽도 없어야함.
		}

		else if (x->left != NULL)// 삭제하고자 하는 노드의 왼쪽 노드가 존재한다면,
		{
			child->left = x->left; // 원래 가리키던 값으로 대체
		}


		if (x->right == child) // 삭제 하고자 하는 노드의 바로 오른쪽이 대체노드라면,
		{
			if (namu->right == NULL) // 대체노드의 오른쪽이 널 값이라면, 
				child->right = NULL; // 대체노드의 오른쪽은 널값.
			else // 대체노드의 오른쪽에 데이터가 있다면, 
				child->right = namu->right; // 연결시켜야함
		}
		else if (x->right != NULL)// 삭제하고자 하는 노드의 오른쪽 노드가 존재한다면,
		{
			child->right = x->right; // 원래 가리키던 값으로 대체

		}
		free(x);
		return 1;

	}
	else if (child->left != NULL || child->right != NULL) // 하나의 자식을 가지는경우
	{
		if (child->left == NULL) // 삭제하고자 하는 왼쪽노드가 비어있다면, 
			temp = child->right; // 포인터가 오른쪽 노드를 기억.
		else // 삭제하고자 하는 노드의 오른쪽이 비어있다면, 
			temp = child->left; // 포인터가 왼쪽 노드를 기억.

		if (child->key > parent->key) //삭제하고자 하는 값이 바로 상위노드보다 크면,
		{
			parent->right = temp; // 상위노드의 오른쪽이 temp를 가리킴.
			free(child); // 메모리 공간 해제
			return 1;
		}
		else if (child->key < parent->key) //식제하고자 하는 값이 바로 상위노드보다 작으면,
		{
			parent->left = temp; // 상위노드의 왼쪽이 temp를 가리킴.
			free(child); // 메모리 공간 해제
			return 1;
		}

	}

	else if (child->key == key && child->left==NULL && child->right == NULL) // 키 값을 찾았고, left와 right값이 NULL일때(리프노드 일때)
	{
		if (parent->key < child->key) // 부모 데이터보다 큰 경우
		{
			parent->right = NULL; // 오른쪽에 있는 노드를 버림
			free(child);
			return 1;
		}
		else // 부모 데이터보다 작은 경우
		{
			parent->left = NULL; // 왼쪽에 있는 노드를 버림
			free(child);
			return 1;
		}
	}

	return 0;

}


void freeNode(Node* ptr)
{
	if (ptr) {
		freeNode(ptr->left);
		freeNode(ptr->right);
		free(ptr);
	}
}

int freeBST(Node* head)
{
	if (head->left == head)
	{
		free(head);
		return 1;
	}

	Node* p = head->left;

	freeNode(p);

	free(head);
	return 1;
}



Node* pop() // iterativeInorder방식에서 사용
{
	if (top == -1) // 스택이 비어있다는 뜻
	{
		return 0;
	}
	else
		return stack[top--]; // top 이동
}

void push(Node* aNode) // iterativeInorder방식에서 사용
{
	if (top >= MAX_STACK_SIZE - 1) // 스택이 가득차서 자리가 없으면
		return;
	else
		stack[++top] = aNode; // top을 이동시키고 데이터 삽입.
}



Node* deQueue() //levelorder 방식에서 사용
{
	if (front == rear) // 큐의 공백조건_삭제할 데이터가 없음
	{
		return 0; 
	}
	else
	{
		front = (front + 1) % MAX_QUEUE_SIZE; //front 이동
		return queue[front];
	}

}

void enQueue(Node* aNode) //levelorder 방식에서 사용
{
	if ((rear + 1) % MAX_QUEUE_SIZE == front) // rear의 다음 데이터와 front의 값이 일치하면, 큐가 가득찼다는 것 
		return; // queue full
	else //그렇지않으면
	{
		rear = (rear + 1) % MAX_QUEUE_SIZE; // rear 이동
		queue[rear] = aNode; // 이동한 위치에 데이터 삽입
	}
}