#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

// include <time.h>
#define cls system("cls");
#define mainsize system("mode con cols=90 lines=30");

int NUM = 8;
//����Ű
#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80
#define SUBMIT 13
#define ESC 27

struct Node {
	int key;
	struct Node* left;
	struct Node* right;
};
typedef struct Meeting {
	int start, end;
	int id;  // ȸ�� ��ȣ
}Meeting;
//
// ���ο� ��� ����
struct Node* createNode(int key) {
	struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
	newNode->key = key;
	newNode->left = newNode->right = NULL;
	return newNode;
}
struct Node* insert(struct Node* root, int key) {
	// Ʈ���� ��������� ���ο� ��带 �����Ͽ� ��ȯ
	if (root == NULL) {
		return createNode(key);
	}

	// ������ Ű�� ���� ����� Ű���� ������ ���� ����Ʈ���� �̵�
	if (key < root->key) {
		root->left = insert(root->left, key);
	}
	// ������ Ű�� ���� ����� Ű���� ũ�� ������ ����Ʈ���� �̵�
	else if (key > root->key) {
		root->right = insert(root->right, key);
	}

	// ����� Ʈ���� ��ȯ
	return root;
}

int keyControl();
void gotoXY(int x, int y);
void setColor(int n);

// â
void intro();  // ��Ʈ��
int Main_Select();  // select main ȭ��
void sort();// ���� (����, ����, ����, ��, �պ�, ��, ��, ���)
void graph(); // �׷��� (DFS, BFS, Kruskal, Prim, ����)
void tree(); // Ʈ�� (��, ��, ��)


//���� �Լ�
void selectionSort(); // ���� ����
void insertionSort(); // ���� ����
void bubbleSort(); // ���� ����
void shellSort(); // �� ����

void mergeSort(); // �պ� ����
void mergeSorting(int data[], int left, int right);
void merge(int data[], int left, int mid, int right);

int quickPartition(int data[], int left, int right); // ��Ƽ�� ���� ����
void quickSort(); // �� ����

void heapSorting(int data[], int size);
void heapSort(); // �� ����
int getMaxRadix(int data[], int size);
void radixSort(); // ��� ����

// �׷��� �Լ�
void DFS(); // Depth-First Search, DFS   ���� �켱 Ž��
void BFS(); // Breadth-Firsh Search, BFS  �ʺ� �켱 Ž��
void Kruskal(); // Kruskal's Algorithm

void Prim(); // Prim's Algorithm
void TopologicalSortin(); // ���� ����

// �׸���
int compareMeetings(const void* a, const void* b);
void printMaxMeetings(struct Meeting meetings[], int n);
void myGreed();
void Greedy();
//Ʈ�� (��ȸ)
void inorderTraversal(struct Node* root);
void preorderTraversal(struct Node* root);
void postorderTraversal(struct Node* root);
void freeTree(struct Node* root);
void myBinary();
void binaryTree();

// ť�� ���� ����ü �� �Լ�
typedef struct QNode {
	char data;
	struct QNode* link;
}QNode;
typedef struct LQueueType{
	QNode* front;
	QNode* rear;
}LQueueType;

LQueueType* createLinkedQueue(void);
int isLQEmpty(LQueueType* LQ);
void enLQueue(LQueueType* LQ, char item);
char deLQueue(LQueueType* LQ);
char peekLQ(LQueueType* LQ);
void printLQ(LQueueType* LQ);

//���ÿ� ���� ����ü �� �Լ�
typedef struct stackNode {
	char data;
	struct stackNode* link;
}stackNode;
stackNode* top;

int isStackEmpty(void);
void push(char item);
char pop(void);
char peek(void);

// �׷����� ���� ����ü �� �Լ�
typedef struct graphNode {
	int vertex;
	struct graphNode* link;
}graphNode;
typedef struct graphType {
	int n;
	graphNode* adjList_H[30];
	int visited[30];
}graphType;

// ������ ���� ����ü
typedef struct Edge {
	int v1;
	int v2;
	int weight;
}Edge;
//������ ����ġ�� �����ϴ� ����ü
typedef struct {
	int vertex;
	int weight;
} Vertex;


int findParent(int parent[], int vertex);
void unionVertices(int parent[], int x, int y);
int compareEdges(const void* a, const void* b);
void runKruskal(Edge edges[], int numVertices, int numEdges);

void runprim(int graph[5][5], int numVertices);

void createGraph(graphType* g);
void insertVertex(graphType* g, int v);
void insertEdge(graphType* g, int u, int v);
void print_adjList(graphType* g);
void DFS_adjList(graphType* g, int v);
void BFS_adjList(graphType* g, int v);
void printInitialGraph(Edge edges[], int numEdges);

///////////////////////// ------------- main ---------------
int main(void) {
	//SetConsoleSize(30, 30, 30);
	//system("pause");

	//GotoXY(14, 28);
	while (1) {
		int select = Main_Select();
		if (select == 0) { sort(); }
		else if (select == 3) { graph(); }
		else if (select == 6) { cls;  return 0; }  // ������
		cls;
	}
	return 0;
}
/////////////////////////

int Main_Select() {
	int x = 30;
	int y = 10;
	cls;
	gotoXY(x + 18, y - 5);	setColor(13);	printf("�˰��� �н� ���α׷�");
	gotoXY(x, y);		setColor(7);	printf("�н��� �˰��� ���� ����");
	gotoXY(x - 2, y + 3);					printf("> 1. ����");
	gotoXY(x, y + 6);						printf("2. �׷���");
	gotoXY(x, y + 9);						printf("3. ����");
	gotoXY(x - 1, y + 3);

	while (1) {
		int select_n = keyControl();

		switch (select_n) {
		case UP:
			if (y > 13) {
				gotoXY(x - 2, y);
				printf(" ");
				y = y - 3;
				gotoXY(x - 2, y);
				printf(">");
			}
			break;
		case DOWN:
			if (y < 19) {
				gotoXY(x - 2, y);
				printf(" ");
				y = y + 3;
				gotoXY(x - 2, y);
				printf(">");
			}
			break;
		case SUBMIT:
			return y - 13;
		}
	}
}

void gotoXY(int x, int y) {
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void setColor(int n) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), n);
}

int keyControl() {  // ����Ű �Է� �޾ƿ�
	char key = getch();

	if (key == 224) {
		key = getch(); // 224 �� �� �޾ƿ�
		switch (key) {
		case UP:
			return UP;
			//case LEFT:
			//	return LEFT;
		case DOWN:
			return DOWN;
			//case RIGHT:
			//	return RIGHT;
		case SUBMIT:
			return SUBMIT;
		}
	}
	if (key == ESC) {
		return ESC;
	}
}

/////////////////////////// ���� ///////////////////////////
// ���� (����, ����, ����, ��, �պ�, ��, ��, ���)
void sort() {
	printf(" ");
	int x = 50;
	int y = 13;

	setColor(7);	//gotoXY(x, y);	printf("���� �˰��� ����");
	gotoXY(x - 2, y);	printf("> 1. ����");
	gotoXY(x, y + 2);	printf("2. ����");
	gotoXY(x, y + 4);	printf("3. ����");
	gotoXY(x, y + 6);	printf("4. ��");
	gotoXY(x, y + 8);	printf("5. �պ�");
	gotoXY(x, y + 10);	printf("6. ��");
	gotoXY(x, y + 12);	printf("7. ��");
	gotoXY(x, y + 14);	printf("8. ���");
	gotoXY(x - 1, y);

	while (1) {
		int select_n = keyControl();

		switch (select_n) {
		case ESC:
			return 0;
		case UP:
			if (y > 13) {
				gotoXY(x - 2, y);
				printf(" ");
				y = y - 2;
				gotoXY(x - 2, y);
				printf(">");
				break;
			}
		case DOWN:
			if (y < 27) {
				gotoXY(x - 2, y);
				printf(" ");
				y = y + 2;
				gotoXY(x - 2, y);
				printf(">");
				break;
			}
		case SUBMIT:
			switch (y - 13) {
			case 0: selectionSort(); break;
			case 2: insertionSort(); break;
			case 4: bubbleSort(); break;
			case 6: shellSort(); break;
			case 8: mergeSort(); break;
			case 10: quickSort(); break;
			case 12: heapSort(); break;
			case 14: radixSort(); break;
			}
		}
	}
	return 0;
}

//�׷��� 
// �׷��� (DFS, BFS, Kruskal, Prim, ����)
void graph() {
	printf(" ");
	int x = 50;
	int y = 16;

	setColor(7);	//gotoXY(x, y-3);	printf("�׷��� �˰��� ����");
	gotoXY(x - 2, y);	printf("> 1. DFS (���� �켱 Ž��)");
	gotoXY(x, y + 2);	printf("2. BFS (�ʺ� �켱 Ž��) ");
	gotoXY(x, y + 4);	printf("3. Kruskal");
	gotoXY(x, y + 6);	printf("4. Prim");
	gotoXY(x, y + 8);	printf("5. Greedy");
	gotoXY(x, y + 10);	printf("6. ����");
	gotoXY(x, y + 12);	printf("7. ����Ʈ��");
	gotoXY(x - 1, y);

	while (1) {
		int select_n = keyControl();

		switch (select_n) {
		case ESC:
			return 0;
		case UP:
			if (y > 16) {
				gotoXY(x - 2, y);
				printf(" ");
				y = y - 2;
				gotoXY(x - 2, y);
				printf(">");
				break;
			}
		case DOWN:
			if (y < 28) {
				gotoXY(x - 2, y);
				printf(" ");
				y = y + 2;
				gotoXY(x - 2, y);
				printf(">");
				break;
			}
		case SUBMIT:
			switch (y - 16) {
			case 0: DFS(); break;  // ����
			case 2: BFS(); break;  // �ʺ�
			case 4: Kruskal(); break;
			case 6: Prim(); break;
			case 8: Greedy(); break;
			case 10: TopologicalSortin(); break;
			case 12: binaryTree();
			}
		}
	}
	return 0;
}


//���� ����Ʈ
//���� ����
void selectionSort() {
	cls;	int x = 10;		int y = 10;		int temp;		int min = 0;
		gotoXY(x + 38, y - 5);	setColor(13);	printf("���� ���� (SelectionSort) �˰���");
		gotoXY(x, y);	setColor(7);			printf("������ ���� Ž���ؼ� �ּڰ��� ã�´�.");
		gotoXY(x, y + 2);							printf("�ּڰ��� ���� ���� ���� �ִ� ���� ��ȯ�ϰ� ������ �Ϸ��Ѵ�.");
		gotoXY(x, y + 4);							printf("(�ּڰ��� �̹� ���� ���� ������ �ƹ��� �۾��� ���� �ʴ´�)");
		gotoXY(x, y + 6);							printf("������ �۾��� ��� ���� ������ ��ĥ ������ �ݺ��Ѵ�.");

		int data[8];
		gotoXY(x + 45, y + 14);					printf("���");
		gotoXY(x + 45, y + 15);					printf("[    ][    ][    ][    ][    ][    ][    ][    ]");
		gotoXY(x + 45, y + 10);					printf("����� �����ؼ� ���� �Է� >> ");
		scanf("%d %d %d %d %d %d %d %d", &data[0], &data[1], &data[2], &data[3], &data[4], &data[5], &data[6], &data[7]);
		gotoXY(x + 45, y + 15);					printf("                                                     ");
		gotoXY(x + 45, y + 15);					printf("[ %d ] [ %d ] [ %d ] [ %d ] [ %d ] [ %d ] [ %d ] [ %d ]", data[0], data[1], data[2], data[3], data[4], data[5], data[6], data[7]);
		getch();
		/////////////////////////
		for (int i = 0; i < NUM; i++) {
			min = i;
			gotoXY(x + 45 + (i * 6), y + 14);			setColor(7);		printf("���");
			for (int j = i + 1; j < NUM; j++) {
				gotoXY(x + 45 + (j * 6), y + 15);		setColor(14);		 printf("[ %d ] ", data[j]);
				getch();
				if (data[min] > data[j]) {
					gotoXY(x + 45 + (min * 6), y + 15);		setColor(7);		 printf("[ %d ] ", data[min]);
					min = j;
					gotoXY(x + 45 + (min * 6), y + 15);		setColor(3);		 printf("[ %d ] ", data[j]);
					getch();
				}
				else {
					gotoXY(x + 45 + (j * 6), y + 15);		setColor(7);		 printf("[ %d ] ", data[j]);
				}
			}
			// swap
			if (min != i) {
				temp = data[i];
				data[i] = data[min];
				gotoXY(x + 45 + (i * 6), y + 15);		setColor(3);		 printf("[ %d ] ", data[i]);
				data[min] = temp;
				gotoXY(x + 45 + (min * 6), y + 15);		setColor(14);		 printf("[ %d ] ", data[min]);
				getch();
				gotoXY(x + 45 + (min * 6), y + 15);		setColor(7);		 printf("[ %d ] ", data[min]);
			}
			else {
				gotoXY(x + 45 + (i * 6), y + 15);		setColor(3);		 printf("[ %d ] ", data[i]);
				getch();
			}
			gotoXY(x + 45 + (i * 6), y + 14);					printf("     ");
		}
		/////////////////////////
		return 0;
}

void insertionSort() { 
	cls;	int x = 10;		int y = 10;		int temp;		int plus = 45;		
	gotoXY(x + 38, y - 5);	setColor(13);		printf("���� ���� (InsertSort) �˰���");
	gotoXY(x, y);	setColor(7);				printf(" �� ��° ���Һ��� �����Ͽ� �� ���� ���ҵ�� ���Ͽ� ������ ��ġ�� ������ ��, ");
	gotoXY(x, y + 2);							printf("���Ҹ� �ڷ� �ű�� ������ �ڸ��� �ڷḦ �����Ͽ� �����ϴ� �˰����̴�.");
	gotoXY(x, y + 4);							printf("2��° �ڷ�� 1��° �ڷ�, 3��° �ڷ�� 2��°�� 1��° �ڷ�, 4��° �ڷ�� 3��°, 2��°,");
	gotoXY(x, y + 6);							printf("1��° �ڷ�� ���� �� �ڷᰡ ���Ե� ��ġ�� ã�´�.");

	int data[8];
	gotoXY(x + plus, y + 14);					printf("���");
	gotoXY(x + plus, y + 15);					printf("[    ][    ][    ][    ][    ][    ][    ][    ]");
	gotoXY(x + plus, y + 10);					printf("����� �����ؼ� ���� �Է� >> ");
	scanf("%d %d %d %d %d %d %d %d", &data[0], &data[1], &data[2], &data[3], &data[4], &data[5], &data[6], &data[7]);
	gotoXY(x + plus, y + 15);					printf("                                                     ");
	gotoXY(x + plus, y + 15);					printf("[ %d ] [ %d ] [ %d ] [ %d ] [ %d ] [ %d ] [ %d ] [ %d ]", data[0], data[1], data[2], data[3], data[4], data[5], data[6], data[7]);
	gotoXY(x + plus, y + 14);					printf("     ");
	
	/////////////////////////
	for (int i = 1; i < NUM; i++) {
		//gotoXY(x + plus + ((i + 1) * 6), y + 14);			setColor(14);		printf("���");
		for (int j = i; j > 0; j--) {
			gotoXY(x + plus + (j * 6), y + 14);			setColor(14);		 printf("���");
			gotoXY(x + 45 + (j * 6), y + 15);			setColor(14);		 printf("[ %d ] ", data[j]);
			gotoXY(x + plus + ((j - 1) * 6), y + 15);	setColor(13);		 printf("[ %d ] ", data[j - 1]);
			getch();
			if (data[j] < data[j - 1]) {
				temp = data[j];
				data[j] = data[j - 1];
				data[j - 1] = temp;
			}
			gotoXY(x + plus + ((j - 1) * 6), y + 15);	setColor(3);		 printf("[ %d ] ", data[j - 1]);
			gotoXY(x + 45 + (j * 6), y + 15);			setColor(14);		 printf("[ %d ] ", data[j]);
			getch();
			gotoXY(x + 45 + (j * 6), y + 14);								 printf("     ");
			gotoXY(x + 45 + (j * 6), y + 15);			setColor(3);		 printf("[ %d ] ", data[j]);
		}
	}
	///////////////////////////
	return 0;
} // ���� ����

void bubbleSort() { 
	cls;	int x = 10;		int y = 10;		int temp;		int plus = 45;
	gotoXY(x + 38, y - 5);	setColor(13);		printf("���� ����(bubble sort) �˰���");
	gotoXY(x, y);	setColor(7);				printf("���� ������ �� ���Ҹ� �˻��Ͽ� �����ϴ� �˰���");
	gotoXY(x, y + 2);							printf("������ 2���� ���ڵ带 ���Ͽ� ũ�Ⱑ ������� �Ǿ� ���� ������ ���� ��ȯ�Ѵ�.");
	gotoXY(x, y + 4);							printf("1ȸ���� �����ϰ� ���� ���� ū �ڷᰡ �� �ڷ� �̵�");

	int data[8];
	gotoXY(x + plus, y + 14);					printf("���");
	gotoXY(x + plus, y + 15);					printf("[    ][    ][    ][    ][    ][    ][    ][    ]");
	gotoXY(x + plus, y + 10);					printf("����� �����ؼ� ���� �Է� >> ");
	scanf("%d %d %d %d %d %d %d %d", &data[0], &data[1], &data[2], &data[3], &data[4], &data[5], &data[6], &data[7]);
	gotoXY(x + plus, y + 15);					printf("                                                       ");
	gotoXY(x + plus, y + 15);					printf("[ %d ] [ %d ] [ %d ] [ %d ] [ %d ] ] [ %d ] [ %d ] [ %d ]", data[0], data[1], data[2], data[3], data[4], data[5], data[6], data[7]);
	gotoXY(x + plus, y + 14);					printf("     ");
	/////////////////////////
	for (int i = NUM-1; i >= 0; i--) {
		for (int j = 0; j < i; j++) {
			gotoXY(x + plus + (j * 6), y + 14);		setColor(14);			printf("���");
			gotoXY(x + 45 + (j * 6), y + 15);		setColor(14);			printf("[ %d ] ", data[j]);
			getch();
			if (data[j] > data[j + 1]) {
				temp = data[j];
				data[j] = data[j + 1];
				data[j + 1] = temp;
			}
	/////////////////////////
			gotoXY(x + plus + (j * 6), y + 15);		setColor(5);			printf("[ %d ] ", data[j]);
			gotoXY(x + plus + ((j+1) * 6), y + 15);	setColor(14);		printf("[ %d ] ", data[j+1]);
			gotoXY(x + plus + (j * 6), y + 14);								printf("     ");
			gotoXY(x + plus + ((j+1) * 6), y + 14);	setColor(14);			printf("���");
			getch();
			gotoXY(x + plus + (j * 6), y + 15);		setColor(7);			printf("[ %d ] ", data[j]);
		}
		//getch();
		gotoXY(x + plus + (i * 6), y + 14);			setColor(3);			printf("���");
		gotoXY(x + 45 + (i * 6), y + 15);			setColor(3);			printf("[ %d ] ", data[i]);
		getch();
		gotoXY(x + plus + (i * 6), y + 14);					printf("     ");
	}
	return 0;
} // ���� ����
void shellSort() { 
	cls;	int x = 10;		int y = 10;		int temp;		int plus = 45;		int n = NUM;		int k;			int cur;
	gotoXY(x + 38, y - 5);	setColor(13);		printf("�� ����(ShellSort) �˰���");
	gotoXY(x, y);	setColor(7);				printf("�� �������� ������ ���� �����Ͽ� �����ϴ� ������� ���������� �ذ��ϴ� �˰���");
	gotoXY(x, y + 2);							printf("���� ���� �˰����� �̿��ϴ� ���� ���");
	gotoXY(x, y + 4);							printf("���� �����͸� ���� �з��� ������ ���������� ����");
	gotoXY(x, y + 6);							printf("���� ������ ���Ͽ� ������ �з�(�׷�)�� ���� �ش� �з� ������ ����");

	int data[8];
	
	gotoXY(x + plus, y + 15);					printf("[    ][    ][    ][    ][    ][    ][    ][    ]");
	gotoXY(x + plus, y + 10);					printf("����� �����ؼ� ���� �Է� >> ");
	scanf("%d %d %d %d %d %d %d %d", &data[0], &data[1], &data[2], &data[3], &data[4], &data[5], &data[6], &data[7]);
	gotoXY(x + plus, y + 15);					printf("                                                      ");
	gotoXY(x + plus, y + 15);					printf("[ %d ] [ %d ] [ %d ] [ %d ] [ %d ] [ %d ] [ %d ] [ %d ]", data[0], data[1], data[2], data[3], data[4], data[5], data[6], data[7]);
	//gotoXY(x + plus, y + 14);					printf("     ");

	// �з��� ���� 1�� �Ǹ� Ż��
	while (n != 1) {
		n = n / 2;
		
		// i���� �� �з��� ��� ��ȣ
		for (int i = 0; i < n; i++) {
			for (int j = i+n; j < 8; j += n) {
				k = j - n;  // �տ� 
				if(i==0){ setColor(6); }
				else if (i==1) {setColor(12);}
				else if (i==2) {setColor(3);}
				else if (i==3) {setColor(14);}
				gotoXY(x + plus + (k*6), y + 15);		 printf("[ %d ] ", data[k]);
				getch();
				gotoXY(x + plus + (j*6), y + 15);		 printf("[ %d ] ", data[j]);
				getch();

				while (1) {
					cur = data[j];
					if (cur < data[k]) {
						temp = data[k];
						data[k] = data[k+n];
						data[k+n] = temp;

						j = k;   // j�� k ���� �־��ش�.  �� ������ ��.
					}
					k -= n;      // k���� -n�� ������. ���������� �񱳴�� ��ġ�� �׻� ���ҽ�Ű�� ����.
					if (k < 0) break;
				}
			}
		}
	}
	return 0;
} // �� ����
void mergeSort() {
	cls;	int x = 10;		int y = 10;		int temp;		int plus = 45;		int mid;	int left=0;		int right = 7;
	gotoXY(x + 38, y - 5);	setColor(13);		printf("�պ� ����(Merge sort) �˰���");
	gotoXY(x, y);	setColor(7);				printf("���� �� ���̸�(John von Neumann)���̶�� ����� ������ ���");
	gotoXY(x, y + 2);							printf("�Ϲ����� ������� �������� �� �� ������ ���� ���� �� ���ϸ�, ���� ���� �˰����� �ϳ� �̴�.");
	gotoXY(x, y + 4);							printf("�ϳ��� ����Ʈ�� �� ���� �յ��� ũ��� �����ϰ� ���ҵ� �κ� ����Ʈ�� ������ ����,");
	gotoXY(x, y + 6);							printf("�� ���� ���ĵ� �κ� ����Ʈ�� ���Ͽ� ��ü�� ���ĵ� ����Ʈ�� �ǰ� �ϴ� ����̴�.");


	int data[8];

	gotoXY(x + plus, y + 15);					printf("[    ][    ][    ][    ][    ][    ][    ][    ]");
	gotoXY(x + plus, y + 10);					printf("����� �����ؼ� ���� �Է� >> ");
	scanf("%d %d %d %d %d %d %d %d", &data[0], &data[1], &data[2], &data[3], &data[4], &data[5], &data[6], &data[7]);
	gotoXY(x + plus, y + 15);					printf("                                                      ");
	gotoXY(x + plus, y + 15);					printf("[ %d ] [ %d ] [ %d ] [ %d ] [ %d ] [ %d ] [ %d ] [ %d ]", data[0], data[1], data[2], data[3], data[4], data[5], data[6], data[7]);
	mergeSorting(data, left, right);
} // �պ� ����

void merge(int data[], int left, int mid, int right) {
	int sy = 27;
	int i = left;
	int k = left;   // sort �迭 �ε��� ��
	int j = mid+1;
	int a;
	int sort[8];
	// ���� ���ĵ� list�� �պ�
	while (i <= mid && j <= right) {  // ������ �κ� ���� ��
		if (data[i] <= data[j]) {  // ���� ���ʰ��� mid������ �۴ٸ�

			sort[k] = data[i];   // ���ʰ��� sort �迭�� �߰�
			gotoXY(55 + (i * 6), 25);		setColor(13);		printf("[ %d ] ", data[i]);
			gotoXY(55 + (j * 6), 25);		setColor(12);		printf("[ %d ] ", data[j]);
			getch();
			gotoXY(55 + (k * 6), sy);	setColor(13);	 printf("[ %d ] ", sort[k]);  // ���
			gotoXY(55 + (i * 6), 25);		setColor(7);		printf("[ %d ] ", data[i]);
			gotoXY(55 + (j * 6), 25);		setColor(7);		printf("[ %d ] ", data[j]);
			i++;
			getch();
		}
		else {   // ���� mid ���� �� ũ�ٸ�
			sort[k] = data[j];   // ������ ���� sort �迭�� �߰�
			gotoXY(55 + (i * 6), 25);		setColor(13);		printf("[ %d ] ", data[i]);
			gotoXY(55 + (j * 6), 25);		setColor(12);		printf("[ %d ] ", data[j]);
			getch();
			gotoXY(55 + (k * 6), sy);		setColor(13);		printf("[ %d ] ", sort[k]); // ���
			gotoXY(55 + (i * 6), 25);		setColor(7);		printf("[ %d ] ", data[i]);
			gotoXY(55 + (j * 6), 25);		setColor(7);		printf("[ %d ] ", data[j]);
			j++;
			getch();
		}
		k++;
	}
	// ���� �ִ� ������ �ϰ� ���� 
	// l <= mid && m <= right  .
	// ��������.. ���� �����°� �����žƴ�... ������ ����Ʈ ������ ���� ���ο� ����Ʈ�� ������.
	if (i > mid) {      // ���� �ε����� mid���� Ŭ ��
		for (a = j; a <= right; a++) {   // a = mid+1�� ����.  �߰�����... right�̶� ������ ������ a++
			gotoXY(55 + (a * 6), 25);		setColor(12);		printf("[ %d ] ", data[a]);
			sort[k] = data[a];    // sort���ٰ� data�� a �ε�����°�� ����
			getch();
			gotoXY(55 + (k * 6), sy);		setColor(13);		printf("[ %d ] ", sort[k]);	
			k++;
			getch();
			gotoXY(55 + (a * 6), 25);		setColor(7);		printf("[ %d ] ", data[a]);
		}
	}
	// ���� �ִ� ������ �ϰ� ����
	else {			// �� �� ��... mid���� ���� ��?
		for (a = i; a <= mid; a++) {   // 
			gotoXY(55 + (a * 6), 25);		setColor(12);		printf("[ %d ] ", data[a]);
			sort[k] = data[a];
			getch();
			gotoXY(55 + (k * 6), sy);		setColor(13);		printf("[ %d ] ", sort[k]);
			k++;
			getch();
			gotoXY(55 + (a * 6), 25);		setColor(7);		printf("[ %d ] ", data[a]);
		}
	}

	// �迭 sorted[](�ӽ� �迭)�� ����Ʈ�� �迭 list[]�� �纹��
	for (a = left; a <= right; a++) {
		data[a] = sort[a];
		gotoXY(55 + (a * 6), 25);	setColor(14);	 printf("[ %d ] ", data[a]);
		gotoXY(55 + (a * 6), sy);	setColor(7);	 printf("[ %d ] ", sort[a]);
	}
	getch();
	return 0;
}
void mergeSorting(int data[], int left, int right) {
	int mid;

	if (left < right) {
		mid = (left + right) / 2;
		mergeSorting(data, left, mid);
		mergeSorting(data, mid + 1, right);
		merge(data, left, mid, right);
	}
}
int quickPartition(int data[], int left, int right) {
	int pivot, temp, i, j;

	i = left;
	j = right;
	pivot = i;  // ���� ����
	i = i + 1;

	if (left >= right) return;

	while (i<=j) { // �����Ҷ����� �ݺ�
		gotoXY(55 + (left * 6), 24);			setColor(13);		printf("���");
		gotoXY(55 + (left *6), 25);			setColor(13);		printf("[ %d ] ", data[pivot]);
		while (i <= right && data[i] <= data[pivot]) {  // ���ų� ������ ����        false�� �Ǹ� ���ⵥ. pivot ���� i���� �۾����� ������
			gotoXY(55 + (i * 6),25);	setColor(14);		 printf("[ %d ] ", data[i]);
			getch();
			gotoXY(55 + (i * 6), 25);	setColor(7);		 printf("[ %d ] ", data[i]);
			i++;
		} // ������ ���鼭 pivot���� ���� ���� ���������� i++  ū ���ڸ� ���ʺ��� ã���ϴ�.   // ũ�ų� ������ ����
		gotoXY(55 + (i * 6), 25);	setColor(14);		 printf("[ %d ] ", data[i]);
		getch();
		while (j > left && data[j] >= data[pivot]) {				/// pivot���� i���� Ŀ���� ������.
			gotoXY(55 + (j * 6), 25);	setColor(3);		 printf("[ %d ] ", data[j]);
			getch();
			gotoXY(55 + (j * 6), 25);	setColor(7);		 printf("[ %d ] ", data[j]);
			j--;
		}
		gotoXY(55 + (i * 6), 25);	setColor(14);		 printf("[ %d ] ", data[i]);
		gotoXY(55 + (j * 6), 25);	setColor(3);		 printf("[ %d ] ", data[j]);
		getch();
		if (i > j) { // ū ���ڰ� ������, ���� ���ڰ� ���ʿ� �ִ� ������ ��..! �� i>j �϶�!   ��ȯ�ϴٰ� ������ �����!
			temp = data[j];     // pivot���� ���� ���� �ӽ��������ְ�
			data[j] = data[left];   // ���� ��ġ���� pivot���� ����
			data[left] = temp;    // �� �� ���� pivot���� ���� ������ �������ش�!
			gotoXY(55 + (left * 6), 25);	setColor(3);		 printf("[ %d ] ", data[left]);
			gotoXY(55 + (j * 6), 25);		setColor(13);		 printf("[ %d ] ", data[j]);

			gotoXY(55 + (left * 6), 24);								printf("    ");
			gotoXY(55 + (j * 6), 24);			setColor(13);			printf("���");
			getch();
			gotoXY(55 + (left * 6), 25);	setColor(7);		 printf("[ %d ] ", data[left]);
			gotoXY(55 + (j * 6), 25);		setColor(7);		 printf("[ %d ] ", data[j]);
			gotoXY(55 + (i * 6), 25);	setColor(7);		 printf("[ %d ] ", data[i]);
			gotoXY(55 + (j * 6), 24);								printf("    ");
		}
		else {     // 
			temp = data[j];  // 7��°�� 6 2��°�� 8....              
			data[j] = data[i];   // 
			data[i] = temp;
			gotoXY(55 + (i * 6), 25);		setColor(14);		 printf("[ %d ] ", data[i]);
			gotoXY(55 + (j * 6), 25);		setColor(3);		 printf("[ %d ] ", data[j]);
			getch();
			gotoXY(55 + (i * 6), 25);		setColor(7);		 printf("[ %d ] ", data[i]);
			gotoXY(55 + (j * 6), 25);		setColor(7);		 printf("[ %d ] ", data[j]);
		}
		gotoXY(55 + (left * 6), 24);								printf("    ");
	}
	
	quickPartition(data, left, j - 1);  // left~ �ǹ� �ٷ� �� ����
	quickPartition(data, j+1, right); // �ǹ� �ٷ� ��~right ����    �� ���� �ǹ����� pivot�� ���� �ε�������, �� �迭�� ù��° ���!
}

void quickSort() {
	cls;	int x = 10;		int y = 10;		int temp;		int plus = 45;	int left = 0;		int right = 7;
	gotoXY(x + 38, y - 5);	setColor(13);		printf("�� ����(Quick sort) �˰���");
	gotoXY(x, y);			setColor(7);		printf("������ ���ʹ� ��ó�� ȣ��(Charles Antony Richard Hoare)���� ������ ���� �˰���");
	gotoXY(x, y + 2);							printf("�� ������ �Ҿ��� ���� �� ���ϸ�, �ٸ� ���ҿ��� �񱳸����� ������ �����ϴ� �� ���� �� ���Ѵ�.");
	gotoXY(x, y + 4);							printf("���� ���� �˰����� �ϳ���, ��������� �ſ� ���� ���� �ӵ��� �ڶ��ϴ� ���� ���");
	gotoXY(x, y + 6);							printf("�ǹ��� ����Ͽ� ����Ʈ�� ��յ��ϰ� �����Ѵ�.");

	int data[8];

	gotoXY(x + plus, y + 15);					printf("[    ][    ][    ][    ][    ][    ][    ][    ]");
	gotoXY(x + plus, y + 10);					printf("����� �����ؼ� ���� �Է� >> ");
	scanf("%d %d %d %d %d %d %d %d", &data[0], &data[1], &data[2], &data[3], &data[4], &data[5], &data[6], &data[7]);
	gotoXY(x + plus, y + 15);					printf("                                                      ");
	gotoXY(x + plus, y + 15);					printf("[ %d ] [ %d ] [ %d ] [ %d ] [ %d ] [ %d ] [ %d ] [ %d ]", data[0], data[1], data[2], data[3], data[4], data[5], data[6], data[7]);
	quickPartition(data, left, right);

	return 0;
} // �� ����

void heapSorting(int data[], int size) {
	for (int i = 1; i < size; i++) {
		int child = i;
		// Ʈ�� ������ �������� �ٲ۴� (���� ���� ū ���� ������)
		do {
			int root = (child - 1) / 2;   // �θ��� ��ġ. Ư�� ��ġ -1 /2 �ϸ� �θ��� ��ġ��
			if (data[root] < data[child]) {
				int temp = data[root];
				data[root] = data[child];
				data[child] = temp;
			}
			child = root;   // �ڽ��� �θ� ��
		} while (child != 0);
	}
	
	for (int i = size - 1; i >= 0; i--) {
		int temp = data[0];
		data[0] = data[i];  // �� ������ ���̶� ��ȯ
		data[i] = temp;  // ���� ū ���� ����ؼ� �ڷ� ����
		int root = 0;
		int child = 1;
		do {
			child = 2 * root + 1;
			if (data[child] < data[child + 1] && child < i - 1) {
				child++;
			}
			if (data[root] < data[child] && child < i) {
				int temp = data[root];
				data[root] = data[child];
				data[child] = temp;
			}
			root = child;
		} while (child < i);
	}
	getch();
	for (int i = 0; i < size; i++) {
		gotoXY(55 + (i * 6), 25);	setColor(14);		 printf("[ %d ] ", data[i]);
	}
}
void heapSort() {
	cls;	int x = 10;		int y = 10;		int temp;		int plus = 45;	
	gotoXY(x + 38, y - 5);	setColor(13);		printf("���� ����(Heap sort) �˰���");
	gotoXY(x, y);			setColor(7);		printf("�׻� ���� ū ���Ұ� ��Ʈ ��尡 �ǰ�, ���� ������ �����ϸ�");
	gotoXY(x, y + 2);							printf(" �׻� ��Ʈ ����� ���Ҹ� �����Ͽ� ��ȯ�ϴ� Ư¡�� �ִ�. ");
	gotoXY(x, y + 4);							printf("�׷��Ƿ�, �ּ� ������ ���ؼ� ���� ������ŭ ���� ������ �����ϸ�");
	gotoXY(x, y + 6);							printf("������������ ���ĵ� ���Ҹ� ���� �� �ִ�. ������ n���� ���Ҹ� ���� �ִ� ������ �����Ѵ�.");

	int data[8];

	gotoXY(x + plus, y + 15);					printf("[    ][    ][    ][    ][    ][    ][    ][    ]");
	gotoXY(x + plus, y + 10);					printf("����� �����ؼ� ���� �Է� >> ");
	scanf("%d %d %d %d %d %d %d %d", &data[0], &data[1], &data[2], &data[3], &data[4], &data[5], &data[6], &data[7]);
	gotoXY(x + plus, y + 15);					printf("                                                      ");
	gotoXY(x + plus, y + 15);					printf("[ %d ] [ %d ] [ %d ] [ %d ] [ %d ] [ %d ] [ %d ] [ %d ]", data[0], data[1], data[2], data[3], data[4], data[5], data[6], data[7]);
	heapSorting(data, NUM);
	return 0;
} // �� ����
int getMaxBucket(int data[], int size) {
	int max_val = 0;
	for (int i = 0; i < size; i++) {
		if (max_val < data[i])
			max_val = data[i];
	}
	int max_bucket = 1; // �ڸ���
	while (max_val / 10 > 0) {
		max_val /= 10;  // ��� 10���� ����
		max_bucket += 1;   // �ڸ����� ���������� �ø�
	}
	return max_bucket;
}
void radixSort() { 
	cls;	int x = 10;		int y = 10;		int k;		int plus = 45;	int i; int d; int f = 1;
	gotoXY(x + 38, y - 5);	setColor(13);		printf("��� ����(Radix Sort)");
	gotoXY(x, y);			setColor(7);		printf("������ ���ڿ��� ���� Ű�� ���� ���ҵ��� �����ϴ� �� ���ȴ�.");
	gotoXY(x, y + 2);							printf("��� ������ �ڸ����� �̿��Ͽ� ������ �����ϴ� ���� ������ �˰����̴�. ");
	gotoXY(x, y + 4);							printf("�Ϲ������� ������ ���Ŀ� ���Ǹ�, Ư�� ������ �ڸ����� ���� ���� �� ȿ�����̴�.");
	gotoXY(x, y + 6);							printf("������ Ű�� ũ�Ⱑ ũ�� �ڸ����� ���� ��� �޸� �Һ� Ŀ�� �� �ִ�.");

	int data[8];

	gotoXY(x + plus, y + 15);					printf("[    ][    ][    ][    ][    ][    ][    ][    ]");
	gotoXY(x + plus, y + 10);					printf("����� �����ؼ� ���� �Է� >> ");
	scanf("%d %d %d %d %d %d %d %d", &data[0], &data[1], &data[2], &data[3], &data[4], &data[5], &data[6], &data[7]);
	gotoXY(x + plus, y + 15);					printf("                                                      ");
	gotoXY(x + plus, y + 15);					printf("[ %d ] [ %d ] [ %d ] [ %d ] [ %d ] [ %d ] [ %d ] [ %d ]", data[0], data[1], data[2], data[3], data[4], data[5], data[6], data[7]);
	
	int bucket = getMaxBucket(data, NUM);

	LQueueType* Q[10];
	for (i = 0; i < 10; i++) {
		Q[i] = createLinkedQueue();
	}

	for (d = 0; d < bucket; d++) {
		for (k = 0; k < NUM; k++) {
			enLQueue(Q[(data[k] / f) % 10], data[k]);
		}
		for (i = 0, k = 0; i < 10; i++) {
			while (!isLQEmpty(Q[i])) data[k++] = deLQueue(Q[i]);
		}
		getch();
		for (k = 0; k < NUM; k++) {
			gotoXY(55 + (k * 6), 25);						 printf("                                                           ");
			gotoXY(55 + (k * 6), 25);	setColor(14);		 printf("[ %d ] ", data[k]);
		}

		f = f * 10;
	}
	return 0;
} // ��� ����

void DFS_adjList(graphType *g, int v) {
	graphNode* w;
	top = NULL;
	push(v);
	g->visited[v] = 1;
	getch();
	gotoXY(75, 22);		setColor(7); printf(" %c",v+65);
	
	// ������ ������ �ƴ� ���� ���� �켱 Ž�� �ݺ�
	while (!isStackEmpty()) {
		w = g->adjList_H[v];
		while (w) {
			if (!g->visited[w->vertex]) {
				push(w->vertex);
				g->visited[w->vertex] = 1;
				getch();
				printf(" %c", w->vertex + 65);
				v = w->vertex;
				w = g->adjList_H[v];
			}
			else {
				w = w->link;
			}
		}
		v = pop();
	}
}
void DFS() {
	cls;	int x = 10;		int y = 10;			int plus = 45;			int i;			graphType* G;
	gotoXY(x + 38, y - 5);	setColor(13);		printf("���� �켱 Ž��(DFS, Depth-First Search) �˰���");
	gotoXY(x, y);			setColor(7);		printf("�׷����� Ʈ���� ���� �ڷ� �������� Ư�� ��带 �������� ���̸� �켱�Ͽ� Ž���Ѵ�.");
	gotoXY(x, y + 2);							printf("����(Stack)�̳� ��� �Լ��� ���� �����ȴ�.");
	gotoXY(x, y + 4);							printf("�׷����� ��� ������ �湮�ϰ�, Ư�� �� �̻� �� ���� ���� ������ �� ��θ� ���󰡸� ���̸� �켱������ Ž��");
	gotoXY(x, y + 6);							printf("�׷����� ���� �κ��� Ž���ϴ� ���� �����ϸ�, �ַ� ����� �߰�, ���� ����� ���� ����, ����Ŭ ���� � ���ȴ�.");


	getch();
	G = (graphType*)malloc(sizeof(graphType));
	createGraph(G);

	for (i = 0; i < 8; i++)	insertVertex(G, i);

	insertEdge(G, 0, 2);
	insertEdge(G, 0, 1);
	insertEdge(G, 1, 3);
	insertEdge(G, 1, 5);
	insertEdge(G, 2, 7);
	insertEdge(G, 3, 7);
	insertEdge(G, 3, 4);
	insertEdge(G, 3, 1);
	insertEdge(G, 4, 3);
	insertEdge(G, 4, 5);
	insertEdge(G, 5, 1);
	insertEdge(G, 5, 6);
	insertEdge(G, 6, 5);
	insertEdge(G, 6, 7);
	insertEdge(G, 7, 2);
	insertEdge(G, 7, 3);
	insertEdge(G, 7, 6);
	
	gotoXY(15, 18);		setColor(14); printf("<< G�� ���� ����Ʈ >>");
	getch();
	print_adjList(G);


	getch();
	gotoXY(75, 18);		setColor(14); printf("<<���� �켱 Ž�� >>");

	DFS_adjList(G, 0);
	getch();
	return 0;
} // Depth-First Search, DFS   ���� �켱 Ž��

void BFS_adjList(graphType* g, int v) {
	graphNode* w;
	LQueueType* Q;
	Q = createLinkedQueue();
	g->visited[v] = 1;
	getch();
	gotoXY(75, 22);		setColor(7); printf(" %c", v + 65);
	enLQueue(Q, v);
	// ť�� ������ �ƴ� ���� �ʺ� �켱 Ž�� �ݺ�
	while (!isLQEmpty(Q)) {
		v = deLQueue(Q);
		for (w = g->adjList_H[v]; w; w = w->link) {
			if (!g->visited[w->vertex]) {
				g->visited[w->vertex] = 1;
				getch();
				printf(" %c", w->vertex + 65);
				enLQueue(Q, w->vertex);
			}
		}
	}
}
void BFS() {
	cls;	int x = 10;		int y = 10;			int plus = 45;			int i;			graphType* G;
	gotoXY(x + 38, y - 5);	setColor(13);		printf("BFS(�ʺ� �켱 Ž��, Breadth-First Search) �˰���");
	gotoXY(x, y);			setColor(7);		printf("�׷����� Ʈ�� ���� �ڷ� �������� ���� ���κ��� ������ ��带 ���� ��� Ž���� ��,");
	gotoXY(x, y + 2);							printf(" �� ���� �ܰ迡���� �ش� ���� ����� ���� ��带 ���������� Ž���Ѵ�.");
	gotoXY(x, y + 4);							printf(" ť(Queue) �ڷ� ������ ����Ͽ� �����Ǹ�,");
	gotoXY(x, y + 6);							printf("�ִ� ��θ� ã�� ���� �ַ� ���Ǹ�, �׷��������� �ִ� ���, �ִ� �Ÿ�, �ּ� ��� ���� ���ϴ� ���� �����ϴ�.");

	int data[8];

	getch();
	G = (graphType*)malloc(sizeof(graphType));
	createGraph(G);

	for (i = 0; i < 8; i++)	insertVertex(G, i);

	insertEdge(G, 0, 2);
	insertEdge(G, 0, 1);
	insertEdge(G, 1, 3);
	insertEdge(G, 1, 5);
	insertEdge(G, 2, 7);
	insertEdge(G, 3, 7);
	insertEdge(G, 3, 4);
	insertEdge(G, 3, 1);
	insertEdge(G, 4, 3);
	insertEdge(G, 4, 5);
	insertEdge(G, 5, 1);
	insertEdge(G, 5, 6);
	insertEdge(G, 6, 5);
	insertEdge(G, 6, 7);
	insertEdge(G, 7, 2);
	insertEdge(G, 7, 3);
	insertEdge(G, 7, 6);

	gotoXY(15, 18);		setColor(14); printf("<< G�� ���� ����Ʈ >>");
	getch();
	print_adjList(G);


	getch();
	gotoXY(75, 18);		setColor(14); printf("<<�ʺ� �켱 Ž�� >>");

	BFS_adjList(G, 0);
	getch();
	return 0;
} // Breadth-Firsh Search, BFS  �ʺ� �켱 Ž��

// ũ�罺Į
// ������ �θ� ã�� �Լ� (Union-Find�� Find ����)
int findParent(int parent[], int vertex) {
	if (parent[vertex] == -1) {
		return vertex;
	}
	return findParent(parent, parent[vertex]);
}

// �� ������ ��ġ�� �Լ� (Union-Find�� Union ����)   
void unionVertices(int parent[], int x, int y) {
	int xSet = findParent(parent, x);
	int ySet = findParent(parent, y);
	parent[xSet] = ySet;
}

// ������ ����ġ �������� ���ϴ� �Լ�
int compareEdges(const void* a, const void* b) {
	return ((Edge*)a)->weight - ((Edge*)b)->weight;
}

// �ʱ� �׷����� ������ ����ϰ� ũ�罺Į �˰����� ȣ���ϴ� �Լ�
void runKruskal(Edge edges[], int numVertices, int numEdges) {
	// �ʱ� �׷��� ���
	printf("  �ʱ� �׷����� ����:\n");
	for (int i = 0; i < numEdges; i++) {
		printf("  (%d - %d) ����ġ: %d\n", edges[i].v1, edges[i].v2, edges[i].weight);
	}
	printf("\n");

	// ũ�罺Į �˰��� ȣ��
	qsort(edges, numEdges, sizeof(Edge), compareEdges);

	int parent[50];
	for (int i = 0; i < numVertices; i++) {
		parent[i] = -1;
	}

	printf("  �ּ� ��� ���� Ʈ���� ����:\n");
	for (int i = 0; i < numEdges; i++) {
		int v1 = edges[i].v1;
		int v2 = edges[i].v2;
		int weight = edges[i].weight;

		// ����Ŭ�� �������� ������ �ش� ������ ����
		if (findParent(parent, v1) != findParent(parent, v2)) {
			printf("  (%d - %d) ����ġ: %d\n", v1, v2, weight);
			unionVertices(parent, v1, v2);
		}
	}
}

void printInitialGraph(Edge edges[], int numEdges) {
	printf("Initial Graph:\n");

	for (int i = 0; i < numEdges; ++i) {
		printf("  Edge %d: %d -- %d, Weight: %d\n", i + 1, edges[i].v1, edges[i].v2, edges[i].weight);
	}

	printf("\n");
}
void Kruskal() { 
	cls;	int x = 10;		int y = 10;			int plus = 45;			int i;			graphType* G;
	gotoXY(x + 38, y - 5);	setColor(13);		printf("ũ�罺Į(Kruskal) �˰���");
	gotoXY(x, y);			setColor(7);		printf("�׷����� ��� ������ �ּ� ������� �����ϴ� �ּ� ���� Ʈ��(Minimum Spanning Tree)�� ã�� �˰��� �� �ϳ��̴�.");
	gotoXY(x, y + 2);							printf("�� �˰����� ������ ����ġ�� ������� �����ϸ�, ���� ����ġ�� ���� �������� �����Ͽ� ���� Ʈ���� �����Ѵ�.");
	gotoXY(x, y + 4);							printf("Union-Find(Disjoint Set) �ڷᱸ���� �ַ� ���Ǿ� �� ������ � ���տ� ���ϴ����� �����Ѵ�.");
	gotoXY(x, y + 6);							printf("�̸� ���� ����Ŭ�� �˻��ϰ� ����Ŭ�� �������� �ʵ��� ������ �����Ѵ�.");

	getch();
	int numVertices = 6;
	int numEdges = 9;

	struct Edge edges[50] = {
		{0, 1, 4}, {0, 2, 4}, {1, 2, 2},
		{1, 0, 4}, {2, 0, 4}, {2, 1, 2},
		{2, 3, 3}, {3, 2, 3}, {3, 4, 7},
	};
	getch();
	system("cls");
	gotoXY(5, 0);		setColor(14); printf("<<Kuruskal �˰��� >>\n\n");
	// �ʱ� �׷��� ���
	printInitialGraph(edges, numEdges);

	// ũ�罺Į �˰��� ȣ��
	runKruskal(edges, numVertices, numEdges);

	return 0;

} // Kruskal's Algorithm
void Prim() {
	cls;	int x = 10;		int y = 10;			int plus = 45;			int i;			graphType* G;
	gotoXY(x + 38, y - 5);	setColor(13);		printf("����(Prim) �˰���");
	gotoXY(x, y);			setColor(7);		printf("�ּ� ���� Ʈ���� �׷��� ���� ��� ������ �����ϸ鼭 ������ ����ġ�� ���� �ּ��� Ʈ���̴�.");
	gotoXY(x, y + 2);							printf("������ �׷������� �ּ� ���� Ʈ��(Minimum Spanning Tree)�� ã�� ���� Ž�� �˰��� �� �ϳ��̴�.");
	gotoXY(x, y + 4);							printf("�켱���� ť(�Ǵ� �ּ� ��)�� ����Ͽ� ���� �ּ� ���� Ʈ���� ����� ������ �׿� ���� �ĺ� �������� ȿ�������� �����Ѵ�.");
	gotoXY(x, y + 6);							printf("������ ���� ���� ������ ȿ�������� �����ϸ�, �ð� ���⵵�� �ַ� ������ ��(E)�� ������ ��(V)�� �����Ѵ�.");

	getch();

	int INF = 555;  // ū������ ����
	int graph[5][5] = {
		{INF, 2, INF, 6, INF},
		{2, INF, 3, 8, 5},
		{INF, 3, INF, INF, 7},
		{6, 8, INF, INF, 9},
		{INF, 5, 7, 9, INF}
	};

	int numVertices = 5;  // ������ ��
	getch();
	system("cls");
	gotoXY(5, 2);		setColor(14);  printf("Prim's Algorithm Minimum Spanning Tree:\n\n");
	printf("  Initial Graph:\n");

	for (int i = 0; i < numVertices; ++i) {
		for (int j = 0; j < numVertices; ++j) {
			if (graph[i][j] != INF) {
				printf("  Edge: %d -- %d, Weight: %d\n", i, j, graph[i][j]);
			}
		}
	}
	runprim(graph, numVertices);

	return 0;
} // Prim's Algorithm

void runprim(int graph[5][5], int numVertices) {
	int INF = 555;
	int parent[5];  // �θ� ������ �����ϴ� �迭
	int key[5];     // ���� ����� ������ ����ġ�� �����ϴ� �迭
	int mstSet[5]; // �ּ� ���� Ʈ���� ���Ե� ������ ��Ÿ���� �迭

	// �ʱ�ȭ
	for (int i = 0; i < numVertices; ++i) {
		key[i] = INF;
		mstSet[i] = 0;
	}

	key[0] = 0;      // ���� ���� ����
	parent[0] = -1;  // ���� ������ �θ� ����

	for (int count = 0; count < numVertices - 1; ++count) {
		// ���� key �迭���� �ּҰ��� ã�� u�� ����
		int u, min = INF;
		for (int v = 0; v < numVertices; ++v) {
			if (!mstSet[v] && key[v] < min) {
				min = key[v];
				u = v;
			}
		}

		mstSet[u] = 1;  // u�� �ּ� ���� Ʈ���� �߰�

		// u�� ���� �����鿡 ���� key ����
		for (int v = 0; v < numVertices; ++v) {
			if (graph[u][v] && !mstSet[v] && graph[u][v] < key[v]) {
				parent[v] = u;
				key[v] = graph[u][v];
			}
		}
	}
	printf("\n  Minimum Graph:\n");
	// ��� ���
	for (int i = 1; i < numVertices; ++i) {
		printf("  Edge %d: %d -- %d, Weight: %d\n", i, parent[i], i, graph[i][parent[i]]);
	}
}

// ���� ���� ����
void topologicalSort(graphType *g){
	stackNode stack;
	top = NULL;

	// ���� ������ 0�� ������ ���ÿ� �߰�
	for (int i = 0; i < 8; ++i) {
		if (g->visited[i] == 0) {
			push(i);
		}
	}

	// ���� ���� ����
	while (!isStackEmpty()) {
		int currentVertex = pop();
		printf("%d ", currentVertex);
		getch();
		// ���� ������ ����� �������� ���� ������ ���ҽ�Ű��,
		// ���� ������ 0�� �Ǹ� ���ÿ� �߰�
		graphNode* current = g->adjList_H[currentVertex];
		while (current != NULL) {
			int adjacentVertex = current->vertex;
			g->visited[adjacentVertex]--;
			if (g->visited[adjacentVertex] == 0) {
				push(adjacentVertex);
			}
			current = current->link;
		}
	}
}

void TopologicalSortin() {
	cls;	int x = 10;		int y = 10;			int plus = 45;			int i;			graphType* G;
	gotoXY(x + 38, y - 5);	setColor(13);		printf("���� ����(Topological Sorting)");
	gotoXY(x, y);			setColor(7);		printf("���� �׷���(Directed Graph)���� ������ ������ ��Ű�鼭 ��� ������ �����ϴ� �˰����̴�.");
	gotoXY(x, y + 2);							printf(". �� �˰����� ���� �۾��� ���� �������� �ִ� �׷������� �۾��� ������ ã�� ���� ���ȴ�.");
	gotoXY(x, y + 4);							printf("���� �׷��������� �����ϸ�, �׷����� ����Ŭ�� ����� �ϰ� ���� ���� ���� ������ ������ �� �ִ�.");
	gotoXY(x, y + 6);							printf("�۾� �����ٸ�, ������ �м�, ������Ʈ ���� �� �پ��� �о߿��� Ȱ��ȴ�.");

	getch();

	G = (graphType*)malloc(sizeof(graphType));
	createGraph(G);

	for (i = 0; i < 8; i++)	insertVertex(G, i);

	insertEdge(G, 0, 1);
	insertEdge(G, 1, 2);
	insertEdge(G, 2, 3);
	insertEdge(G, 3, 4);
	insertEdge(G, 4, 5);
	insertEdge(G, 5, 6);
	insertEdge(G, 6, 7);
	insertEdge(G, 7, 0);
	insertEdge(G, 0, 2);
	insertEdge(G, 2, 4);
	insertEdge(G, 4, 6);
	insertEdge(G, 6, 1);
	insertEdge(G, 1, 3);
	insertEdge(G, 3, 5);
	insertEdge(G, 5, 7);
	insertEdge(G, 7, 2);

	gotoXY(15, 18);		setColor(14); printf("<< G�� ���� ����Ʈ >>");
	getch();
	print_adjList(G);


	getch();
	gotoXY(75, 18);		setColor(14); printf("<< Topological Sort: >>\n");
	gotoXY(75, 22);		setColor(7);
	topologicalSort(G);

	return 0;
} // ���� ����


//// ť /////////
LQueueType* createLinkedQueue(void) {
	LQueueType* LQ;
	LQ = (LQueueType*)malloc(sizeof(LQueueType));
	LQ->front = NULL;
	LQ->rear = NULL;
	return LQ;
}
int isLQEmpty(LQueueType* LQ) {
	if (LQ->front == NULL) {
		//printf("Linked Queue is empty!");
		return 1;
	}
	else  return 0;
}
void enLQueue(LQueueType* LQ, char item) {
	QNode* newNode = (QNode*)malloc(sizeof(QNode));
	newNode->data = item;
	newNode->link = NULL;
	if (LQ->front == NULL) {
		LQ->front = newNode;
		LQ->rear = newNode;
	}
	else {
		LQ->rear->link = newNode;
		LQ->rear = newNode;
	}
}
char deLQueue(LQueueType* LQ) {
	QNode* old = LQ->front;
	char item;
	if (isLQEmpty(LQ)) return;
	else {
		item = old->data;
		LQ->front = LQ->front->link;
		if (LQ->front == NULL)
			LQ->rear = NULL;
		free(old);
		return item;
	}
}
char peekLQ(LQueueType* LQ) {
	char item;
	if (isLQEmpty(LQ)) return;
	else {
		item = LQ->front->data;
		return item;
	}
}
void printLQ(LQueueType* LQ) {
	QNode* temp = LQ->front;
	printf("Linked Queue : [");
	while (temp) {
		printf("%3c", temp->data);
		temp = temp->link;
	}
	printf("]");
}

///////////////// ����
int isStackEmpty(void) {
	if (top == NULL) return 1;
	else return 0;
}
void push(char item) {
	stackNode* temp = (stackNode*)malloc(sizeof(stackNode));
	temp->data = item;
	temp->link = top;
	top = temp;
}
char pop(void) {
	char item;
	stackNode* temp = top;
	if (isStackEmpty()) {
		printf("stack is empty!");
		return 0;
	}
	else {
		item = temp->data;
		top = temp->link;
		free(temp);
		return item;
	}
}
char peek(void) {
	if (isStackEmpty()) {
		printf("stack is empty!");
		return 0;
	}
	else {
		return(top->data);
	}
}


///////////// �׷��� //////////
void createGraph(graphType* g) {
	int v;
	g->n = 0;
	for (v = 0; v < 30; v++) {
		g->adjList_H[v] = NULL;
		g->visited[v] = 0;
	}
}
void insertVertex(graphType* g, int v) {
	if ((g->n) + 1 > 30) {
		printf("�׷��� ���� ���� �ʰ�");
		return;
	}
	g->n++;
}
void insertEdge(graphType* g, int u, int v) {
	graphNode* node;

	if (u >= g->n || v >= g->n) {
		printf("�׷����� ���� ������");
		return;
	}
	node = (graphNode*)malloc(sizeof(graphNode));
	node->vertex = v;
	node->link = g->adjList_H[u];
	g->adjList_H[u] = node;
}
void print_adjList(graphType* g) {
	int i; int y = 20; int x = 15;
	graphNode* p;
	for (i = 0; i < g->n; i++) {
		gotoXY(15, y);		setColor(7);		printf("���� %c�� ���� ����Ʈ", i + 65);
		p = g->adjList_H[i];
		while (p) {
			getch();
			gotoXY(x+20, y);		setColor(7);	printf(" -> %c", p->vertex + 65);
			p = p->link;
			x = x + 6;
		}
		x = 15;
		y++;
		getch();
	}
}


// Ž��, �׸��� �˰��� 

// �� ȸ�Ǹ� ���Ͽ� �����ϱ� ���� �� �Լ�
int compareMeetings(const void* a, const void* b) {
	return ((struct Meeting*)a)->end - ((struct Meeting*)b)->end;
}

// �׸��� �˰����� ����Ͽ� �ִ�� ������ �� �ִ� ȸ�Ǹ� ����ϴ� �Լ�
void printMaxMeetings(struct Meeting meetings[], int n) {
	// ȸ�Ǹ� ������ �ð��� �������� ����
	qsort(meetings, n, sizeof(struct Meeting), compareMeetings);

	printf("�ִ�� ������ �� �ִ� ȸ��:\n");

	// ù ��° ȸ�Ǵ� �׻� ����
	int i = 0;
	printf("ȸ�� %d: ���� �ð� = %d, ������ �ð� = %d\n", meetings[i].id, meetings[i].start, meetings[i].end);

	// ������ ȸ���� ������ �ð����� �ڿ� �����ϴ� ȸ�Ǹ� ����
	for (int j = 1; j < n; j++) {
		if (meetings[j].start >= meetings[i].end) {
			printf("ȸ�� %d: ���� �ð� = %d, ������ �ð� = %d\n", meetings[j].id, meetings[j].start, meetings[j].end);
			i = j;
		}
	}
}

void myGreed() {
	int n;
	setColor(7);

	printf("ȸ���� ������ �Է��ϼ���: ");
	scanf_s("%d", &n);

	struct Meeting* meetings = (struct Meeting*)malloc(n * sizeof(struct Meeting));

	// ����ڷκ��� ȸ�� ���� �Է� �ޱ�
	for (int i = 0; i < n; i++) {
		printf("ȸ�� %d�� ���� �ð��� �Է��ϼ���: ", i + 1);
		scanf_s("%d", &meetings[i].start);

		printf("ȸ�� %d�� ������ �ð��� �Է��ϼ���: ", i + 1);
		scanf_s("%d", &meetings[i].end);

		meetings[i].id = i + 1;  // ȸ�� ��ȣ �ο�
	}

	printMaxMeetings(meetings, n);

	free(meetings);  // �������� �Ҵ��� �޸� ����

	getchar();
	while (1) {
		if (keyControl() == SUBMIT) {
			main(); // main �Լ� ȣ��
		}
	}
}

void Greedy() {
	cls;	int x = 10;		int y = 10;			int plus = 45;			
	gotoXY(x + 38, y - 5);	setColor(13);		printf("�׸��� �˰��� (Greedy)");
	gotoXY(x, y);			setColor(7);		printf("Greedy �˰����� �� �ܰ迡�� ���� ���¿��� ���� ���� ���̴� ������ �ϸ鼭 ������ �ذ��ϴ� ����ȭ �˰����̴�.");
	gotoXY(x, y + 2);							printf("�� �˰����� �� �ܰ迡�� ���� �����ظ� �����ϸ�, �̷��� ���õ��� �� ���� �����ظ� ã�´�.");
	gotoXY(x, y + 4);							printf("���� �κ� ����, Ž���� ���� �Ӽ�, �ּ�(�Ǵ� �ִ�) ���� ���� �����ط� ���� ������ ����");
	gotoXY(x, y + 6);							printf("Greedy �˰����� Ư¡�� ������ ����, �Ž����� ���� �ذ� � �ַ� ���ȴ�.");

	getch();
	cls;
	myGreed();
}

void freeTree(struct Node* root) {
	if (root != NULL) {
		freeTree(root->left);
		freeTree(root->right);
		free(root);
	}
}
// ���� Ž�� Ʈ�� ���� ��ȸ
void preorderTraversal(struct Node* root) {
	if (root != NULL) {
		printf("%d ", root->key);
		preorderTraversal(root->left);
		preorderTraversal(root->right);
	}
}

// ���� Ž�� Ʈ�� ���� ��ȸ
void inorderTraversal(struct Node* root) {
	if (root != NULL) {
		inorderTraversal(root->left);
		printf("%d ", root->key);
		inorderTraversal(root->right);
	}
}


// ���� Ž�� Ʈ�� ���� ��ȸ
void postorderTraversal(struct Node* root) {
	if (root != NULL) {
		postorderTraversal(root->left);
		postorderTraversal(root->right);
		printf("%d ", root->key);
	}
}


void myBinary() {
	struct Node* root = NULL;
	int size;
	setColor(7);

	// ����ڷκ��� ���ϴ� ���� ���� �Է�
	printf("���� ������ �Է��ϼ���: ");
	scanf_s("%d", &size);

	// ����ڷκ��� ���� �Է� �� ���� Ž�� Ʈ���� ����
	printf("���Ҹ� �Է��ϼ���: ");
	for (int i = 0; i < size; ++i) {
		int element;
		scanf_s("%d", &element);
		root = insert(root, element);
	}

	// ���� ��ȸ�� Ʈ�� ���
	printf("���� ��ȸ ���: ");
	preorderTraversal(root);
	printf("\n");

	// ���� ��ȸ�� Ʈ�� ���
	printf("���� ��ȸ ���: ");
	inorderTraversal(root);
	printf("\n");

	// ���� ��ȸ�� Ʈ�� ���
	printf("���� ��ȸ ���: ");
	postorderTraversal(root);
	printf("\n");

	// �޸� ����
	free(root);

	getchar();
	while (1) {
		if (keyControl() == SUBMIT) {
			main(); // main �Լ� ȣ��
		}
	}
}

void binaryTree() {
	cls;	int x = 10;		int y = 10;			int plus = 45;			
	gotoXY(x + 38, y - 5);	setColor(13);		printf("���� Ʈ��(Binary Tree)");
	gotoXY(x, y);			setColor(7);		printf("�� ��尡 �ִ� �� ���� �ڽ� ��带 ������ Ʈ�� �����̴�.");
	gotoXY(x, y + 2);							printf("���� Ʈ������ �� ���� �� ���� ���� Ʈ���� ������, �� ���� Ʈ���� ���� ���� Ʈ���� ������ ���� Ʈ���� ������.");
	gotoXY(x, y + 4);							printf("���� Ʈ���� �پ��� ���� �о߿��� ���Ǹ�, Ư�� ���ĵ� �������� ���� �� �˻��� ȿ�������� ���ȴ�.");
	gotoXY(x, y + 6);							printf("��Ʈ, �θ�, �ڽ�, ����, ����Ʈ�� ���� ��Ұ� �����Ѵ�.");

	getch();
	cls;
	myBinary();
}