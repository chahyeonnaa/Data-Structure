/*
 * Binary Search Tree #1
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

int initializeBST(Node** h);

/* functions that you have to implement */
void inorderTraversal(Node* ptr);	  /* recursive inorder traversal */
void preorderTraversal(Node* ptr);    /* recursive preorder traversal */
void postorderTraversal(Node* ptr);	  /* recursive postorder traversal */
int insert(Node* head, int key);  /* insert a node to the tree */
int deleteLeafNode(Node* head, int key);  /* delete the leaf node for the key */
Node* searchRecursive(Node* ptr, int key);  /* search the node for the key */
Node* searchIterative(Node* head, int key);  /* search the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */


int main()
{
	char command;
	int key;
	Node* head = NULL;
	Node* ptr = NULL;	/* temp */

	do {
		printf("\n\n");
        printf("-------------------[ 2020039009 Chahyeona ]---------------------\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #1                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = n      Delete Leaf Node             = d \n");
		printf(" Inorder Traversal    = i      Search Node Recursively      = s \n");
		printf(" Preorder Traversal   = p      Search Node Iteratively      = f\n");
		printf(" Postorder Traversal  = t      Quit                         = q\n");
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
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteLeafNode(head, key);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchIterative(head, key);
			if (ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;
		case 's': case 'S':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchRecursive(head->left, key);
			if (ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;

		case 'i': case 'I':
			inorderTraversal(head->left);
			break;
		case 'p': case 'P':
			preorderTraversal(head->left);
			break;
		case 't': case 'T':
			postorderTraversal(head->left);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while (command != 'q' && command != 'Q');

	return 1;
}

int initializeBST(Node** h) { // 초기화 

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if (*h != NULL) // 트리가 비어있지않으면
		freeBST(*h); // 메모리 공간 해제

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node)); // 공간 할당 받기
	(*h)->left = NULL;	/* root */ // 헤드 노드 만들기
	(*h)->right = *h;
	(*h)->key = -9999;
	return 1;
}



void inorderTraversal(Node* ptr) // 중위 순회( 왼쪽-부모-오른쪽 )
{
	if (ptr != NULL)
	{
		inorderTraversal(ptr->left); // 왼쪽 끝까지 가기
		printf("[%d] ", ptr->key); // 데이터 값 찍기
		inorderTraversal(ptr->right); // 오른쪽 끝까지 도달
	}
}

void preorderTraversal(Node* ptr) // 전위순회(부모-오른쪽-왼쪽)
{
	if (ptr != NULL)
	{
		printf("[%d] ", ptr->key); // 데이터 값 찍고
		preorderTraversal(ptr->left); // 왼쪽 방문
        preorderTraversal(ptr->right); // 오른쪽 방문
	}
}

void postorderTraversal(Node* ptr) // 후위순회(왼쪽-오른쪽-부모)
{
	if (ptr != NULL)
	{
		postorderTraversal(ptr->left);// 왼쪽방문
		postorderTraversal(ptr->right); // 오른쪽방문
		printf("[%d] ", ptr->key); // 값 찍기
	}
}

int insert(Node* head, int key) // 데이터 삽입
{

	Node* node = (Node*)malloc(sizeof(Node)); // 동적할당 받기
	node->key = key; // 데이터필드에 key값 넣기

	Node* root = head->left; // 헤드노드가 가리키는 곳(루트노드)를 가리킬 포인터
	Node* temp = NULL;

	if (head->left == NULL) // 트리가 비어있으면
	{
		head->left = node; // 헤드노드와 해당노드를 연결하여 루트노드를 생성
		node->left = NULL;
		node->right = NULL;
		return 1;
	}
	else // 트리가 비어있지않으면
	{
		while (root != NULL) // 루트노드가 아무것도 가리키지 않을때까지(트리의 끝에 도달할때까지) 반복문을 시행
		{
			temp = root; // root 포인터와 함께 다니는 temp 포인터
			if (root->key > key) // 해당노드가 루트노드가 가진 값보다 작으면,
			{
				root = root->left; // 왼쪽으로 이동
			}
			else if (root->key < key) // 해당 노드가 루트노브가 가진 값보다 크면,
			{
				root = root->right; // 오른쪽으로 이동
			}
		}
        // 반복문을 나와서 데이터가 들어갈 위치 선정_temp는 트리의 끝부분에 와있음
		if (temp->key < key) // 데이터값이 현재 위치 값(temp가 가지고 있는 값)보다 크면
		{
			temp->right = node; // 오른쪽에 삽입
			node->left = NULL;
			node->right = NULL;
			return 1;
		}
		else if (temp->key > key) // 데이터값이 현재 위치 값보다 작으면
		{
			temp->left = node; // 왼쪽에 삽입
			node->left = NULL;
			node->right = NULL;
			return 1;
		}
	}
}

int deleteLeafNode(Node* head, int key)
{
	

}

Node* searchRecursive(Node* ptr, int key) // 반복적 탐색방법
{
    if (!ptr) // 일치하는 값이 없는 경우 널값을 반환
		return NULL;
	if (key == ptr->key) // 일치하는 값을 찾았을 경우, 해당 노드에 대한 포인터를 반환
		return ptr;
	if (key < ptr->key) // 키 값을 찾아가는 과정_ 키값이 해당 위치의 데이터값보다 작으면
		return searchRecursive(ptr->left, key); // 해당 위치를 인자로하여 함수를 새로 호출_왼쪽 탐색
	else //키값이 해당 위치의 데이터값보다 크면
		return searchRecursive(ptr->right, key); // 해당 위치를 인자로하여 함수를 새로 호출_오른쪽 탐색

}

Node* searchIterative(Node* head, int key) // iterative 탐색 방법
{
    Node* tree = head->left; // 헤드가 가리키는 값(루트노드)을 가리키는 포인터
	while (tree) // tree가 널값을 가지는지 체크
	{
		if (key == tree->key) // 일치하는 값을 찾았을 경우, 해당 노드에 대한 포인터를 반환
			return tree;
		if (key < tree->key) // 키 값을 찾아가는 과정_ 찾고자 하는 값이 현위치의 값보다 작으면
			tree = tree->left; // tree포인터를 왼쪽으로 이동하여 재정의
		else // 찾고자 하는 값이 현위치의 값보다 크면
			tree = tree->right; // tree포인터를 오른쪽으로 이동하여 재정의
	}
	return NULL; // 원하는 값을 찾지 못했으면 널값을 반환

}


int freeBST(Node* head)
{

}

