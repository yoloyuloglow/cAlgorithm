#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

// include <time.h>
#define cls system("cls");
#define mainsize system("mode con cols=90 lines=30");

int NUM = 8;
//방향키
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
	int id;  // 회의 번호
}Meeting;
//
// 새로운 노드 생성
struct Node* createNode(int key) {
	struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
	newNode->key = key;
	newNode->left = newNode->right = NULL;
	return newNode;
}
struct Node* insert(struct Node* root, int key) {
	// 트리가 비어있으면 새로운 노드를 생성하여 반환
	if (root == NULL) {
		return createNode(key);
	}

	// 삽입할 키가 현재 노드의 키보다 작으면 왼쪽 서브트리로 이동
	if (key < root->key) {
		root->left = insert(root->left, key);
	}
	// 삽입할 키가 현재 노드의 키보다 크면 오른쪽 서브트리로 이동
	else if (key > root->key) {
		root->right = insert(root->right, key);
	}

	// 변경된 트리를 반환
	return root;
}

int keyControl();
void gotoXY(int x, int y);
void setColor(int n);

// 창
void intro();  // 인트로
int Main_Select();  // select main 화면
void sort();// 정렬 (선택, 삽입, 버블, 쉘, 합병, 퀵, 힙, 기수)
void graph(); // 그래프 (DFS, BFS, Kruskal, Prim, 위상)
void tree(); // 트리 (전, 중, 후)


//정렬 함수
void selectionSort(); // 선택 정렬
void insertionSort(); // 삽입 정렬
void bubbleSort(); // 버블 정렬
void shellSort(); // 쉘 정렬

void mergeSort(); // 합병 정렬
void mergeSorting(int data[], int left, int right);
void merge(int data[], int left, int mid, int right);

int quickPartition(int data[], int left, int right); // 파티션 나눠 정렬
void quickSort(); // 퀵 정렬

void heapSorting(int data[], int size);
void heapSort(); // 힙 정렬
int getMaxRadix(int data[], int size);
void radixSort(); // 기수 정렬

// 그래프 함수
void DFS(); // Depth-First Search, DFS   깊이 우선 탐색
void BFS(); // Breadth-Firsh Search, BFS  너비 우선 탐색
void Kruskal(); // Kruskal's Algorithm

void Prim(); // Prim's Algorithm
void TopologicalSortin(); // 위상 정렬

// 그리디
int compareMeetings(const void* a, const void* b);
void printMaxMeetings(struct Meeting meetings[], int n);
void myGreed();
void Greedy();
//트리 (순회)
void inorderTraversal(struct Node* root);
void preorderTraversal(struct Node* root);
void postorderTraversal(struct Node* root);
void freeTree(struct Node* root);
void myBinary();
void binaryTree();

// 큐에 대한 구조체 및 함수
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

//스택에 대한 구조체 및 함수
typedef struct stackNode {
	char data;
	struct stackNode* link;
}stackNode;
stackNode* top;

int isStackEmpty(void);
void push(char item);
char pop(void);
char peek(void);

// 그래프에 대한 구조체 및 함수
typedef struct graphNode {
	int vertex;
	struct graphNode* link;
}graphNode;
typedef struct graphType {
	int n;
	graphNode* adjList_H[30];
	int visited[30];
}graphType;

// 간선에 대한 구조체
typedef struct Edge {
	int v1;
	int v2;
	int weight;
}Edge;
//정점과 가중치를 저장하는 구조체
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
		else if (select == 6) { cls;  return 0; }  // 종료임
		cls;
	}
	return 0;
}
/////////////////////////

int Main_Select() {
	int x = 30;
	int y = 10;
	cls;
	gotoXY(x + 18, y - 5);	setColor(13);	printf("알고리즘 학습 프로그램");
	gotoXY(x, y);		setColor(7);	printf("학습할 알고리즘 유형 선택");
	gotoXY(x - 2, y + 3);					printf("> 1. 정렬");
	gotoXY(x, y + 6);						printf("2. 그래프");
	gotoXY(x, y + 9);						printf("3. 종료");
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

int keyControl() {  // 방향키 입력 받아옴
	char key = getch();

	if (key == 224) {
		key = getch(); // 224 뒤 값 받아옴
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

/////////////////////////// 정렬 ///////////////////////////
// 정렬 (선택, 삽입, 버블, 쉘, 합병, 퀵, 힙, 기수)
void sort() {
	printf(" ");
	int x = 50;
	int y = 13;

	setColor(7);	//gotoXY(x, y);	printf("정렬 알고리즘 선택");
	gotoXY(x - 2, y);	printf("> 1. 선택");
	gotoXY(x, y + 2);	printf("2. 삽입");
	gotoXY(x, y + 4);	printf("3. 버블");
	gotoXY(x, y + 6);	printf("4. 쉘");
	gotoXY(x, y + 8);	printf("5. 합병");
	gotoXY(x, y + 10);	printf("6. 퀵");
	gotoXY(x, y + 12);	printf("7. 힙");
	gotoXY(x, y + 14);	printf("8. 기수");
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

//그래프 
// 그래프 (DFS, BFS, Kruskal, Prim, 위상)
void graph() {
	printf(" ");
	int x = 50;
	int y = 16;

	setColor(7);	//gotoXY(x, y-3);	printf("그래프 알고리즘 선택");
	gotoXY(x - 2, y);	printf("> 1. DFS (깊이 우선 탐색)");
	gotoXY(x, y + 2);	printf("2. BFS (너비 우선 탐색) ");
	gotoXY(x, y + 4);	printf("3. Kruskal");
	gotoXY(x, y + 6);	printf("4. Prim");
	gotoXY(x, y + 8);	printf("5. Greedy");
	gotoXY(x, y + 10);	printf("6. 위상");
	gotoXY(x, y + 12);	printf("7. 이진트리");
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
			case 0: DFS(); break;  // 깊이
			case 2: BFS(); break;  // 너비
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


//정렬 리스트
//선택 정렬
void selectionSort() {
	cls;	int x = 10;		int y = 10;		int temp;		int min = 0;
		gotoXY(x + 38, y - 5);	setColor(13);	printf("선택 정렬 (SelectionSort) 알고리즘");
		gotoXY(x, y);	setColor(7);			printf("수열을 선형 탐색해서 최솟값을 찾는다.");
		gotoXY(x, y + 2);							printf("최솟값을 열의 왼쪽 끝에 있는 값과 교환하고 정렬을 완료한다.");
		gotoXY(x, y + 4);							printf("(최솟값이 이미 왼쪽 끝에 있으면 아무런 작업도 하지 않는다)");
		gotoXY(x, y + 6);							printf("동일한 작업을 모든 값이 정렬을 마칠 때까지 반복한다.");

		int data[8];
		gotoXY(x + 45, y + 14);					printf("■■");
		gotoXY(x + 45, y + 15);					printf("[    ][    ][    ][    ][    ][    ][    ][    ]");
		gotoXY(x + 45, y + 10);					printf("띄어쓰기로 구분해서 숫자 입력 >> ");
		scanf("%d %d %d %d %d %d %d %d", &data[0], &data[1], &data[2], &data[3], &data[4], &data[5], &data[6], &data[7]);
		gotoXY(x + 45, y + 15);					printf("                                                     ");
		gotoXY(x + 45, y + 15);					printf("[ %d ] [ %d ] [ %d ] [ %d ] [ %d ] [ %d ] [ %d ] [ %d ]", data[0], data[1], data[2], data[3], data[4], data[5], data[6], data[7]);
		getch();
		/////////////////////////
		for (int i = 0; i < NUM; i++) {
			min = i;
			gotoXY(x + 45 + (i * 6), y + 14);			setColor(7);		printf("■■");
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
	gotoXY(x + 38, y - 5);	setColor(13);		printf("삽입 정렬 (InsertSort) 알고리즘");
	gotoXY(x, y);	setColor(7);				printf(" 두 번째 원소부터 시작하여 그 앞의 원소들과 비교하여 삽입할 위치를 지정한 후, ");
	gotoXY(x, y + 2);							printf("원소를 뒤로 옮기고 지정된 자리에 자료를 삽입하여 정렬하는 알고리즘이다.");
	gotoXY(x, y + 4);							printf("2번째 자료는 1번째 자료, 3번째 자료는 2번째와 1번째 자료, 4번째 자료는 3번째, 2번째,");
	gotoXY(x, y + 6);							printf("1번째 자료와 비교한 후 자료가 삽입될 위치를 찾는다.");

	int data[8];
	gotoXY(x + plus, y + 14);					printf("■■");
	gotoXY(x + plus, y + 15);					printf("[    ][    ][    ][    ][    ][    ][    ][    ]");
	gotoXY(x + plus, y + 10);					printf("띄어쓰기로 구분해서 숫자 입력 >> ");
	scanf("%d %d %d %d %d %d %d %d", &data[0], &data[1], &data[2], &data[3], &data[4], &data[5], &data[6], &data[7]);
	gotoXY(x + plus, y + 15);					printf("                                                     ");
	gotoXY(x + plus, y + 15);					printf("[ %d ] [ %d ] [ %d ] [ %d ] [ %d ] [ %d ] [ %d ] [ %d ]", data[0], data[1], data[2], data[3], data[4], data[5], data[6], data[7]);
	gotoXY(x + plus, y + 14);					printf("     ");
	
	/////////////////////////
	for (int i = 1; i < NUM; i++) {
		//gotoXY(x + plus + ((i + 1) * 6), y + 14);			setColor(14);		printf("■■");
		for (int j = i; j > 0; j--) {
			gotoXY(x + plus + (j * 6), y + 14);			setColor(14);		 printf("■■");
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
} // 삽입 정렬

void bubbleSort() { 
	cls;	int x = 10;		int y = 10;		int temp;		int plus = 45;
	gotoXY(x + 38, y - 5);	setColor(13);		printf("버블 정렬(bubble sort) 알고리즘");
	gotoXY(x, y);	setColor(7);				printf("서로 인접한 두 원소를 검사하여 정렬하는 알고리즘");
	gotoXY(x, y + 2);							printf("인접한 2개의 레코드를 비교하여 크기가 순서대로 되어 있지 않으면 서로 교환한다.");
	gotoXY(x, y + 4);							printf("1회전을 수행하고 나면 가장 큰 자료가 맨 뒤로 이동");

	int data[8];
	gotoXY(x + plus, y + 14);					printf("■■");
	gotoXY(x + plus, y + 15);					printf("[    ][    ][    ][    ][    ][    ][    ][    ]");
	gotoXY(x + plus, y + 10);					printf("띄어쓰기로 구분해서 숫자 입력 >> ");
	scanf("%d %d %d %d %d %d %d %d", &data[0], &data[1], &data[2], &data[3], &data[4], &data[5], &data[6], &data[7]);
	gotoXY(x + plus, y + 15);					printf("                                                       ");
	gotoXY(x + plus, y + 15);					printf("[ %d ] [ %d ] [ %d ] [ %d ] [ %d ] ] [ %d ] [ %d ] [ %d ]", data[0], data[1], data[2], data[3], data[4], data[5], data[6], data[7]);
	gotoXY(x + plus, y + 14);					printf("     ");
	/////////////////////////
	for (int i = NUM-1; i >= 0; i--) {
		for (int j = 0; j < i; j++) {
			gotoXY(x + plus + (j * 6), y + 14);		setColor(14);			printf("■■");
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
			gotoXY(x + plus + ((j+1) * 6), y + 14);	setColor(14);			printf("■■");
			getch();
			gotoXY(x + plus + (j * 6), y + 15);		setColor(7);			printf("[ %d ] ", data[j]);
		}
		//getch();
		gotoXY(x + plus + (i * 6), y + 14);			setColor(3);			printf("■■");
		gotoXY(x + 45 + (i * 6), y + 15);			setColor(3);			printf("[ %d ] ", data[i]);
		getch();
		gotoXY(x + plus + (i * 6), y + 14);					printf("     ");
	}
	return 0;
} // 버블 정렬
void shellSort() { 
	cls;	int x = 10;		int y = 10;		int temp;		int plus = 45;		int n = NUM;		int k;			int cur;
	gotoXY(x + 38, y - 5);	setColor(13);		printf("쉘 정렬(ShellSort) 알고리즘");
	gotoXY(x, y);	setColor(7);				printf("정 간격으로 떨어진 값을 삽입하여 정렬하는 방법으로 점진적으로 해결하는 알고리즘");
	gotoXY(x, y + 2);							printf("삽입 정렬 알고리즘을 이용하는 정렬 방식");
	gotoXY(x, y + 4);							printf("먼저 데이터를 여러 분류로 나누어 삽입정렬을 진행");
	gotoXY(x, y + 6);							printf("일정 구간을 정하여 각각의 분류(그룹)를 만들어서 해당 분류 내에서 정렬");

	int data[8];
	
	gotoXY(x + plus, y + 15);					printf("[    ][    ][    ][    ][    ][    ][    ][    ]");
	gotoXY(x + plus, y + 10);					printf("띄어쓰기로 구분해서 숫자 입력 >> ");
	scanf("%d %d %d %d %d %d %d %d", &data[0], &data[1], &data[2], &data[3], &data[4], &data[5], &data[6], &data[7]);
	gotoXY(x + plus, y + 15);					printf("                                                      ");
	gotoXY(x + plus, y + 15);					printf("[ %d ] [ %d ] [ %d ] [ %d ] [ %d ] [ %d ] [ %d ] [ %d ]", data[0], data[1], data[2], data[3], data[4], data[5], data[6], data[7]);
	//gotoXY(x + plus, y + 14);					printf("     ");

	// 분류의 값이 1이 되면 탈출
	while (n != 1) {
		n = n / 2;
		
		// i값은 각 분류의 요소 번호
		for (int i = 0; i < n; i++) {
			for (int j = i+n; j < 8; j += n) {
				k = j - n;  // 앞에 
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

						j = k;   // j에 k 값을 넣어준다.  즉 앞으로 감.
					}
					k -= n;      // k에는 -n을 누적함. 삽입정렬은 비교대상 위치를 항상 감소시키기 때문.
					if (k < 0) break;
				}
			}
		}
	}
	return 0;
} // 쉘 정렬
void mergeSort() {
	cls;	int x = 10;		int y = 10;		int temp;		int plus = 45;		int mid;	int left=0;		int right = 7;
	gotoXY(x + 38, y - 5);	setColor(13);		printf("합병 정렬(Merge sort) 알고리즘");
	gotoXY(x, y);	setColor(7);				printf("‘존 폰 노이만(John von Neumann)’이라는 사람이 제안한 방법");
	gotoXY(x, y + 2);							printf("일반적인 방법으로 구현했을 때 이 정렬은 안정 정렬 에 속하며, 분할 정복 알고리즘의 하나 이다.");
	gotoXY(x, y + 4);							printf("하나의 리스트를 두 개의 균등한 크기로 분할하고 분할된 부분 리스트를 정렬한 다음,");
	gotoXY(x, y + 6);							printf("두 개의 정렬된 부분 리스트를 합하여 전체가 정렬된 리스트가 되게 하는 방법이다.");


	int data[8];

	gotoXY(x + plus, y + 15);					printf("[    ][    ][    ][    ][    ][    ][    ][    ]");
	gotoXY(x + plus, y + 10);					printf("띄어쓰기로 구분해서 숫자 입력 >> ");
	scanf("%d %d %d %d %d %d %d %d", &data[0], &data[1], &data[2], &data[3], &data[4], &data[5], &data[6], &data[7]);
	gotoXY(x + plus, y + 15);					printf("                                                      ");
	gotoXY(x + plus, y + 15);					printf("[ %d ] [ %d ] [ %d ] [ %d ] [ %d ] [ %d ] [ %d ] [ %d ]", data[0], data[1], data[2], data[3], data[4], data[5], data[6], data[7]);
	mergeSorting(data, left, right);
} // 합병 정렬

void merge(int data[], int left, int mid, int right) {
	int sy = 27;
	int i = left;
	int k = left;   // sort 배열 인덱스 값
	int j = mid+1;
	int a;
	int sort[8];
	// 분할 정렬된 list의 합병
	while (i <= mid && j <= right) {  // 각자의 부분 집합 비교
		if (data[i] <= data[j]) {  // 만약 왼쪽값이 mid값보다 작다면

			sort[k] = data[i];   // 왼쪽값을 sort 배열에 추가
			gotoXY(55 + (i * 6), 25);		setColor(13);		printf("[ %d ] ", data[i]);
			gotoXY(55 + (j * 6), 25);		setColor(12);		printf("[ %d ] ", data[j]);
			getch();
			gotoXY(55 + (k * 6), sy);	setColor(13);	 printf("[ %d ] ", sort[k]);  // 출력
			gotoXY(55 + (i * 6), 25);		setColor(7);		printf("[ %d ] ", data[i]);
			gotoXY(55 + (j * 6), 25);		setColor(7);		printf("[ %d ] ", data[j]);
			i++;
			getch();
		}
		else {   // 만약 mid 값이 더 크다면
			sort[k] = data[j];   // 오른쪽 값을 sort 배열에 추가
			gotoXY(55 + (i * 6), 25);		setColor(13);		printf("[ %d ] ", data[i]);
			gotoXY(55 + (j * 6), 25);		setColor(12);		printf("[ %d ] ", data[j]);
			getch();
			gotoXY(55 + (k * 6), sy);		setColor(13);		printf("[ %d ] ", sort[k]); // 출력
			gotoXY(55 + (i * 6), 25);		setColor(7);		printf("[ %d ] ", data[i]);
			gotoXY(55 + (j * 6), 25);		setColor(7);		printf("[ %d ] ", data[j]);
			j++;
			getch();
		}
		k++;
	}
	// 남아 있는 값들을 일괄 복사 
	// l <= mid && m <= right  .
	// 나눴을때.. 먼저 끝나는거 잇을거아님... 나머지 리스트 값들을 전부 새로운 리스트로 복사함.
	if (i > mid) {      // 왼쪽 인덱스가 mid보다 클 때
		for (a = j; a <= right; a++) {   // a = mid+1로 저장.  중간값이... right이랑 같아질 때까지 a++
			gotoXY(55 + (a * 6), 25);		setColor(12);		printf("[ %d ] ", data[a]);
			sort[k] = data[a];    // sort에다가 data의 a 인덱스번째를 저장
			getch();
			gotoXY(55 + (k * 6), sy);		setColor(13);		printf("[ %d ] ", sort[k]);	
			k++;
			getch();
			gotoXY(55 + (a * 6), 25);		setColor(7);		printf("[ %d ] ", data[a]);
		}
	}
	// 남아 있는 값들을 일괄 복사
	else {			// 그 외 뭐... mid보다 작을 때?
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

	// 배열 sorted[](임시 배열)의 리스트를 배열 list[]로 재복사
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
	pivot = i;  // 가장 왼쪽
	i = i + 1;

	if (left >= right) return;

	while (i<=j) { // 교차할때까지 반복
		gotoXY(55 + (left * 6), 24);			setColor(13);		printf("■■");
		gotoXY(55 + (left *6), 25);			setColor(13);		printf("[ %d ] ", data[pivot]);
		while (i <= right && data[i] <= data[pivot]) {  // 같거나 작으면 종료        false가 되면 종룐데. pivot 값이 i보다 작아지면 종료임
			gotoXY(55 + (i * 6),25);	setColor(14);		 printf("[ %d ] ", data[i]);
			getch();
			gotoXY(55 + (i * 6), 25);	setColor(7);		 printf("[ %d ] ", data[i]);
			i++;
		} // 끝까지 돌면서 pivot보다 작은 값을 만날때까지 i++  큰 숫자를 왼쪽부터 찾습니다.   // 크거나 같으면 종료
		gotoXY(55 + (i * 6), 25);	setColor(14);		 printf("[ %d ] ", data[i]);
		getch();
		while (j > left && data[j] >= data[pivot]) {				/// pivot값이 i보다 커지면 종료임.
			gotoXY(55 + (j * 6), 25);	setColor(3);		 printf("[ %d ] ", data[j]);
			getch();
			gotoXY(55 + (j * 6), 25);	setColor(7);		 printf("[ %d ] ", data[j]);
			j--;
		}
		gotoXY(55 + (i * 6), 25);	setColor(14);		 printf("[ %d ] ", data[i]);
		gotoXY(55 + (j * 6), 25);	setColor(3);		 printf("[ %d ] ", data[j]);
		getch();
		if (i > j) { // 큰 숫자가 오른쪽, 작은 숫자가 왼쪽에 있는 상태일 때..! 즉 i>j 일때!   교환하다가 엇갈린 경우임!
			temp = data[j];     // pivot보다 작은 값을 임시저장해주고
			data[j] = data[left];   // 원래 위치에는 pivot값을 삽입
			data[left] = temp;    // 맨 앞 값을 pivot보다 작은 값으로 변경해준다!
			gotoXY(55 + (left * 6), 25);	setColor(3);		 printf("[ %d ] ", data[left]);
			gotoXY(55 + (j * 6), 25);		setColor(13);		 printf("[ %d ] ", data[j]);

			gotoXY(55 + (left * 6), 24);								printf("    ");
			gotoXY(55 + (j * 6), 24);			setColor(13);			printf("■■");
			getch();
			gotoXY(55 + (left * 6), 25);	setColor(7);		 printf("[ %d ] ", data[left]);
			gotoXY(55 + (j * 6), 25);		setColor(7);		 printf("[ %d ] ", data[j]);
			gotoXY(55 + (i * 6), 25);	setColor(7);		 printf("[ %d ] ", data[i]);
			gotoXY(55 + (j * 6), 24);								printf("    ");
		}
		else {     // 
			temp = data[j];  // 7번째에 6 2번째에 8....              
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
	
	quickPartition(data, left, j - 1);  // left~ 피벗 바로 앞 정렬
	quickPartition(data, j+1, right); // 피벗 바로 뒤~right 정렬    즉 다음 피벗값은 pivot의 다음 인덱스이자, 뒤 배열의 첫번째 요소!
}

void quickSort() {
	cls;	int x = 10;		int y = 10;		int temp;		int plus = 45;	int left = 0;		int right = 7;
	gotoXY(x + 38, y - 5);	setColor(13);		printf("퀵 정렬(Quick sort) 알고리즘");
	gotoXY(x, y);			setColor(7);		printf("‘찰스 앤터니 리처드 호어(Charles Antony Richard Hoare)’가 개발한 정렬 알고리즘");
	gotoXY(x, y + 2);							printf("퀵 정렬은 불안정 정렬 에 속하며, 다른 원소와의 비교만으로 정렬을 수행하는 비교 정렬 에 속한다.");
	gotoXY(x, y + 4);							printf("분할 정복 알고리즘의 하나로, 평균적으로 매우 빠른 수행 속도를 자랑하는 정렬 방법");
	gotoXY(x, y + 6);							printf("피벗을 사용하여 리스트를 비균등하게 분할한다.");

	int data[8];

	gotoXY(x + plus, y + 15);					printf("[    ][    ][    ][    ][    ][    ][    ][    ]");
	gotoXY(x + plus, y + 10);					printf("띄어쓰기로 구분해서 숫자 입력 >> ");
	scanf("%d %d %d %d %d %d %d %d", &data[0], &data[1], &data[2], &data[3], &data[4], &data[5], &data[6], &data[7]);
	gotoXY(x + plus, y + 15);					printf("                                                      ");
	gotoXY(x + plus, y + 15);					printf("[ %d ] [ %d ] [ %d ] [ %d ] [ %d ] [ %d ] [ %d ] [ %d ]", data[0], data[1], data[2], data[3], data[4], data[5], data[6], data[7]);
	quickPartition(data, left, right);

	return 0;
} // 퀵 정렬

void heapSorting(int data[], int size) {
	for (int i = 1; i < size; i++) {
		int child = i;
		// 트리 구조를 힙구조로 바꾼다 (위가 가장 큰 값이 오도록)
		do {
			int root = (child - 1) / 2;   // 부모의 위치. 특정 위치 -1 /2 하면 부모의 위치다
			if (data[root] < data[child]) {
				int temp = data[root];
				data[root] = data[child];
				data[child] = temp;
			}
			child = root;   // 자식이 부모가 됨
		} while (child != 0);
	}
	
	for (int i = size - 1; i >= 0; i--) {
		int temp = data[0];
		data[0] = data[i];  // 맨 마지막 값이랑 교환
		data[i] = temp;  // 가장 큰 값을 계속해서 뒤로 보냄
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
	gotoXY(x + 38, y - 5);	setColor(13);		printf("히프 정렬(Heap sort) 알고리즘");
	gotoXY(x, y);			setColor(7);		printf("항상 가장 큰 원소가 루트 노드가 되고, 삭제 연산을 수행하면");
	gotoXY(x, y + 2);							printf(" 항상 루트 노드의 원소를 삭제하여 반환하는 특징이 있다. ");
	gotoXY(x, y + 4);							printf("그러므로, 최소 히프에 대해서 원소 개수만큼 삭제 연산을 수행하면");
	gotoXY(x, y + 6);							printf("오름차순으로 정렬된 원소를 얻을 수 있다. 정렬할 n개의 원소를 가진 최대 히프를 구성한다.");

	int data[8];

	gotoXY(x + plus, y + 15);					printf("[    ][    ][    ][    ][    ][    ][    ][    ]");
	gotoXY(x + plus, y + 10);					printf("띄어쓰기로 구분해서 숫자 입력 >> ");
	scanf("%d %d %d %d %d %d %d %d", &data[0], &data[1], &data[2], &data[3], &data[4], &data[5], &data[6], &data[7]);
	gotoXY(x + plus, y + 15);					printf("                                                      ");
	gotoXY(x + plus, y + 15);					printf("[ %d ] [ %d ] [ %d ] [ %d ] [ %d ] [ %d ] [ %d ] [ %d ]", data[0], data[1], data[2], data[3], data[4], data[5], data[6], data[7]);
	heapSorting(data, NUM);
	return 0;
} // 힙 정렬
int getMaxBucket(int data[], int size) {
	int max_val = 0;
	for (int i = 0; i < size; i++) {
		if (max_val < data[i])
			max_val = data[i];
	}
	int max_bucket = 1; // 자리수
	while (max_val / 10 > 0) {
		max_val /= 10;  // 계속 10으로 나눔
		max_bucket += 1;   // 자리수는 나눌때마다 올림
	}
	return max_bucket;
}
void radixSort() { 
	cls;	int x = 10;		int y = 10;		int k;		int plus = 45;	int i; int d; int f = 1;
	gotoXY(x + 38, y - 5);	setColor(13);		printf("기수 정렬(Radix Sort)");
	gotoXY(x, y);			setColor(7);		printf("정수나 문자열과 같은 키를 가진 원소들을 정렬하는 데 사용된다.");
	gotoXY(x, y + 2);							printf("기수 정렬은 자릿수를 이용하여 정렬을 수행하는 비교적 간단한 알고리즘이다. ");
	gotoXY(x, y + 4);							printf("일반적으로 정수의 정렬에 사용되며, 특히 정수의 자릿수가 비교적 작을 때 효과적이다.");
	gotoXY(x, y + 6);							printf("하지만 키의 크기가 크고 자릿수가 많은 경우 메모리 소비가 커질 수 있다.");

	int data[8];

	gotoXY(x + plus, y + 15);					printf("[    ][    ][    ][    ][    ][    ][    ][    ]");
	gotoXY(x + plus, y + 10);					printf("띄어쓰기로 구분해서 숫자 입력 >> ");
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
} // 기수 정렬

void DFS_adjList(graphType *g, int v) {
	graphNode* w;
	top = NULL;
	push(v);
	g->visited[v] = 1;
	getch();
	gotoXY(75, 22);		setColor(7); printf(" %c",v+65);
	
	// 스택이 공백이 아닌 동안 깊이 우선 탐색 반복
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
	gotoXY(x + 38, y - 5);	setColor(13);		printf("깊이 우선 탐색(DFS, Depth-First Search) 알고리즘");
	gotoXY(x, y);			setColor(7);		printf("그래프나 트리와 같은 자료 구조에서 특정 노드를 시작으로 깊이를 우선하여 탐색한다.");
	gotoXY(x, y + 2);							printf("스택(Stack)이나 재귀 함수를 통해 구현된다.");
	gotoXY(x, y + 4);							printf("그래프의 모든 정점을 방문하고, 특히 더 이상 갈 곳이 없을 때까지 그 경로를 따라가며 깊이를 우선적으로 탐색");
	gotoXY(x, y + 6);							printf("그래프의 깊은 부분을 탐색하는 데에 적합하며, 주로 경로의 발견, 연결 요소의 개수 세기, 사이클 검출 등에 사용된다.");


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
	
	gotoXY(15, 18);		setColor(14); printf("<< G의 인접 리스트 >>");
	getch();
	print_adjList(G);


	getch();
	gotoXY(75, 18);		setColor(14); printf("<<깊이 우선 탐색 >>");

	DFS_adjList(G, 0);
	getch();
	return 0;
} // Depth-First Search, DFS   깊이 우선 탐색

void BFS_adjList(graphType* g, int v) {
	graphNode* w;
	LQueueType* Q;
	Q = createLinkedQueue();
	g->visited[v] = 1;
	getch();
	gotoXY(75, 22);		setColor(7); printf(" %c", v + 65);
	enLQueue(Q, v);
	// 큐가 공백이 아닌 동안 너비 우선 탐색 반복
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
	gotoXY(x + 38, y - 5);	setColor(13);		printf("BFS(너비 우선 탐색, Breadth-First Search) 알고리즘");
	gotoXY(x, y);			setColor(7);		printf("그래프나 트리 등의 자료 구조에서 시작 노드로부터 인접한 노드를 먼저 모두 탐색한 후,");
	gotoXY(x, y + 2);							printf(" 그 다음 단계에서는 해당 인접 노드의 인접 노드를 순차적으로 탐색한다.");
	gotoXY(x, y + 4);							printf(" 큐(Queue) 자료 구조를 사용하여 구현되며,");
	gotoXY(x, y + 6);							printf("최단 경로를 찾는 데에 주로 사용되며, 그래프에서의 최단 경로, 최단 거리, 최소 비용 등을 구하는 데에 적합하다.");

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

	gotoXY(15, 18);		setColor(14); printf("<< G의 인접 리스트 >>");
	getch();
	print_adjList(G);


	getch();
	gotoXY(75, 18);		setColor(14); printf("<<너비 우선 탐색 >>");

	BFS_adjList(G, 0);
	getch();
	return 0;
} // Breadth-Firsh Search, BFS  너비 우선 탐색

// 크루스칼
// 정점의 부모를 찾는 함수 (Union-Find의 Find 연산)
int findParent(int parent[], int vertex) {
	if (parent[vertex] == -1) {
		return vertex;
	}
	return findParent(parent, parent[vertex]);
}

// 두 정점을 합치는 함수 (Union-Find의 Union 연산)   
void unionVertices(int parent[], int x, int y) {
	int xSet = findParent(parent, x);
	int ySet = findParent(parent, y);
	parent[xSet] = ySet;
}

// 간선을 가중치 기준으로 비교하는 함수
int compareEdges(const void* a, const void* b) {
	return ((Edge*)a)->weight - ((Edge*)b)->weight;
}

// 초기 그래프의 간선을 출력하고 크루스칼 알고리즘을 호출하는 함수
void runKruskal(Edge edges[], int numVertices, int numEdges) {
	// 초기 그래프 출력
	printf("  초기 그래프의 간선:\n");
	for (int i = 0; i < numEdges; i++) {
		printf("  (%d - %d) 가중치: %d\n", edges[i].v1, edges[i].v2, edges[i].weight);
	}
	printf("\n");

	// 크루스칼 알고리즘 호출
	qsort(edges, numEdges, sizeof(Edge), compareEdges);

	int parent[50];
	for (int i = 0; i < numVertices; i++) {
		parent[i] = -1;
	}

	printf("  최소 비용 신장 트리의 간선:\n");
	for (int i = 0; i < numEdges; i++) {
		int v1 = edges[i].v1;
		int v2 = edges[i].v2;
		int weight = edges[i].weight;

		// 사이클을 형성하지 않으면 해당 간선을 선택
		if (findParent(parent, v1) != findParent(parent, v2)) {
			printf("  (%d - %d) 가중치: %d\n", v1, v2, weight);
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
	gotoXY(x + 38, y - 5);	setColor(13);		printf("크루스칼(Kruskal) 알고리즘");
	gotoXY(x, y);			setColor(7);		printf("그래프의 모든 정점을 최소 비용으로 연결하는 최소 신장 트리(Minimum Spanning Tree)를 찾는 알고리즘 중 하나이다.");
	gotoXY(x, y + 2);							printf("이 알고리즘은 간선의 가중치를 기반으로 동작하며, 가장 가중치가 작은 간선부터 선택하여 신장 트리를 구성한다.");
	gotoXY(x, y + 4);							printf("Union-Find(Disjoint Set) 자료구조가 주로 사용되어 각 정점이 어떤 집합에 속하는지를 관리한다.");
	gotoXY(x, y + 6);							printf("이를 통해 사이클을 검사하고 사이클이 형성되지 않도록 간선을 선택한다.");

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
	gotoXY(5, 0);		setColor(14); printf("<<Kuruskal 알고리즘 >>\n\n");
	// 초기 그래프 출력
	printInitialGraph(edges, numEdges);

	// 크루스칼 알고리즘 호출
	runKruskal(edges, numVertices, numEdges);

	return 0;

} // Kruskal's Algorithm
void Prim() {
	cls;	int x = 10;		int y = 10;			int plus = 45;			int i;			graphType* G;
	gotoXY(x + 38, y - 5);	setColor(13);		printf("프림(Prim) 알고리즘");
	gotoXY(x, y);			setColor(7);		printf("최소 신장 트리란 그래프 내의 모든 정점을 포함하면서 간선의 가중치의 합이 최소인 트리이다.");
	gotoXY(x, y + 2);							printf("프림은 그래프에서 최소 신장 트리(Minimum Spanning Tree)를 찾기 위한 탐욕 알고리즘 중 하나이다.");
	gotoXY(x, y + 4);							printf("우선순위 큐(또는 최소 힙)를 사용하여 현재 최소 신장 트리에 연결된 정점과 그에 대한 후보 간선들을 효율적으로 관리한다.");
	gotoXY(x, y + 6);							printf("간선의 수가 많을 때에도 효과적으로 동작하며, 시간 복잡도는 주로 간선의 수(E)와 정점의 수(V)에 의존한다.");

	getch();

	int INF = 555;  // 큰값으로 설정
	int graph[5][5] = {
		{INF, 2, INF, 6, INF},
		{2, INF, 3, 8, 5},
		{INF, 3, INF, INF, 7},
		{6, 8, INF, INF, 9},
		{INF, 5, 7, 9, INF}
	};

	int numVertices = 5;  // 정점의 수
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
	int parent[5];  // 부모 정점을 저장하는 배열
	int key[5];     // 현재 연결된 정점과 가중치를 저장하는 배열
	int mstSet[5]; // 최소 신장 트리에 포함된 정점을 나타내는 배열

	// 초기화
	for (int i = 0; i < numVertices; ++i) {
		key[i] = INF;
		mstSet[i] = 0;
	}

	key[0] = 0;      // 시작 정점 선택
	parent[0] = -1;  // 시작 정점은 부모가 없음

	for (int count = 0; count < numVertices - 1; ++count) {
		// 현재 key 배열에서 최소값을 찾아 u로 선택
		int u, min = INF;
		for (int v = 0; v < numVertices; ++v) {
			if (!mstSet[v] && key[v] < min) {
				min = key[v];
				u = v;
			}
		}

		mstSet[u] = 1;  // u를 최소 신장 트리에 추가

		// u의 인접 정점들에 대해 key 갱신
		for (int v = 0; v < numVertices; ++v) {
			if (graph[u][v] && !mstSet[v] && graph[u][v] < key[v]) {
				parent[v] = u;
				key[v] = graph[u][v];
			}
		}
	}
	printf("\n  Minimum Graph:\n");
	// 결과 출력
	for (int i = 1; i < numVertices; ++i) {
		printf("  Edge %d: %d -- %d, Weight: %d\n", i, parent[i], i, graph[i][parent[i]]);
	}
}

// 위상 정렬 수행
void topologicalSort(graphType *g){
	stackNode stack;
	top = NULL;

	// 진입 차수가 0인 정점을 스택에 추가
	for (int i = 0; i < 8; ++i) {
		if (g->visited[i] == 0) {
			push(i);
		}
	}

	// 위상 정렬 수행
	while (!isStackEmpty()) {
		int currentVertex = pop();
		printf("%d ", currentVertex);
		getch();
		// 현재 정점과 연결된 정점들의 진입 차수를 감소시키고,
		// 진입 차수가 0이 되면 스택에 추가
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
	gotoXY(x + 38, y - 5);	setColor(13);		printf("위상 정렬(Topological Sorting)");
	gotoXY(x, y);			setColor(7);		printf("방향 그래프(Directed Graph)에서 간선의 방향을 지키면서 모든 정점을 나열하는 알고리즘이다.");
	gotoXY(x, y + 2);							printf(". 이 알고리즘은 보통 작업들 간의 의존성이 있는 그래프에서 작업의 순서를 찾기 위해 사용된다.");
	gotoXY(x, y + 4);							printf("방향 그래프에서만 가능하며, 그래프에 사이클이 없어야 하고 여러 가지 위상 정렬이 존재할 수 있다.");
	gotoXY(x, y + 6);							printf("작업 스케줄링, 의존성 분석, 프로젝트 관리 등 다양한 분야에서 활용된다.");

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

	gotoXY(15, 18);		setColor(14); printf("<< G의 인접 리스트 >>");
	getch();
	print_adjList(G);


	getch();
	gotoXY(75, 18);		setColor(14); printf("<< Topological Sort: >>\n");
	gotoXY(75, 22);		setColor(7);
	topologicalSort(G);

	return 0;
} // 위상 정렬


//// 큐 /////////
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

///////////////// 스택
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


///////////// 그래프 //////////
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
		printf("그래프 정점 개수 초과");
		return;
	}
	g->n++;
}
void insertEdge(graphType* g, int u, int v) {
	graphNode* node;

	if (u >= g->n || v >= g->n) {
		printf("그래프에 없는 정점임");
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
		gotoXY(15, y);		setColor(7);		printf("정점 %c의 인접 리스트", i + 65);
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


// 탐욕, 그리디 알고리즘 

// 두 회의를 비교하여 정렬하기 위한 비교 함수
int compareMeetings(const void* a, const void* b) {
	return ((struct Meeting*)a)->end - ((struct Meeting*)b)->end;
}

// 그리디 알고리즘을 사용하여 최대로 선택할 수 있는 회의를 출력하는 함수
void printMaxMeetings(struct Meeting meetings[], int n) {
	// 회의를 끝나는 시간을 기준으로 정렬
	qsort(meetings, n, sizeof(struct Meeting), compareMeetings);

	printf("최대로 선택할 수 있는 회의:\n");

	// 첫 번째 회의는 항상 선택
	int i = 0;
	printf("회의 %d: 시작 시간 = %d, 끝나는 시간 = %d\n", meetings[i].id, meetings[i].start, meetings[i].end);

	// 선택한 회의의 끝나는 시간보다 뒤에 시작하는 회의를 선택
	for (int j = 1; j < n; j++) {
		if (meetings[j].start >= meetings[i].end) {
			printf("회의 %d: 시작 시간 = %d, 끝나는 시간 = %d\n", meetings[j].id, meetings[j].start, meetings[j].end);
			i = j;
		}
	}
}

void myGreed() {
	int n;
	setColor(7);

	printf("회의의 개수를 입력하세요: ");
	scanf_s("%d", &n);

	struct Meeting* meetings = (struct Meeting*)malloc(n * sizeof(struct Meeting));

	// 사용자로부터 회의 정보 입력 받기
	for (int i = 0; i < n; i++) {
		printf("회의 %d의 시작 시간을 입력하세요: ", i + 1);
		scanf_s("%d", &meetings[i].start);

		printf("회의 %d의 끝나는 시간을 입력하세요: ", i + 1);
		scanf_s("%d", &meetings[i].end);

		meetings[i].id = i + 1;  // 회의 번호 부여
	}

	printMaxMeetings(meetings, n);

	free(meetings);  // 동적으로 할당한 메모리 해제

	getchar();
	while (1) {
		if (keyControl() == SUBMIT) {
			main(); // main 함수 호출
		}
	}
}

void Greedy() {
	cls;	int x = 10;		int y = 10;			int plus = 45;			
	gotoXY(x + 38, y - 5);	setColor(13);		printf("그리디 알고리즘 (Greedy)");
	gotoXY(x, y);			setColor(7);		printf("Greedy 알고리즘은 각 단계에서 현재 상태에서 가장 좋아 보이는 선택을 하면서 문제를 해결하는 최적화 알고리즘이다.");
	gotoXY(x, y + 2);							printf("이 알고리즘은 각 단계에서 지역 최적해를 선택하며, 이러한 선택들이 모여 전역 최적해를 찾는다.");
	gotoXY(x, y + 4);							printf("최적 부분 구조, 탐욕적 선택 속성, 최소(또는 최대) 하위 문제 최적해로 전역 최적해 도출");
	gotoXY(x, y + 6);							printf("Greedy 알고리즘의 특징은 다음과 같고, 거스름돈 문제 해결 등에 주로 사용된다.");

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
// 이진 탐색 트리 전위 순회
void preorderTraversal(struct Node* root) {
	if (root != NULL) {
		printf("%d ", root->key);
		preorderTraversal(root->left);
		preorderTraversal(root->right);
	}
}

// 이진 탐색 트리 중위 순회
void inorderTraversal(struct Node* root) {
	if (root != NULL) {
		inorderTraversal(root->left);
		printf("%d ", root->key);
		inorderTraversal(root->right);
	}
}


// 이진 탐색 트리 후위 순회
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

	// 사용자로부터 원하는 원소 개수 입력
	printf("원소 개수를 입력하세요: ");
	scanf_s("%d", &size);

	// 사용자로부터 원소 입력 및 이진 탐색 트리에 삽입
	printf("원소를 입력하세요: ");
	for (int i = 0; i < size; ++i) {
		int element;
		scanf_s("%d", &element);
		root = insert(root, element);
	}

	// 전위 순회로 트리 출력
	printf("전위 순회 결과: ");
	preorderTraversal(root);
	printf("\n");

	// 중위 순회로 트리 출력
	printf("중위 순회 결과: ");
	inorderTraversal(root);
	printf("\n");

	// 후위 순회로 트리 출력
	printf("후위 순회 결과: ");
	postorderTraversal(root);
	printf("\n");

	// 메모리 해제
	free(root);

	getchar();
	while (1) {
		if (keyControl() == SUBMIT) {
			main(); // main 함수 호출
		}
	}
}

void binaryTree() {
	cls;	int x = 10;		int y = 10;			int plus = 45;			
	gotoXY(x + 38, y - 5);	setColor(13);		printf("이진 트리(Binary Tree)");
	gotoXY(x, y);			setColor(7);		printf("각 노드가 최대 두 개의 자식 노드를 가지는 트리 구조이다.");
	gotoXY(x, y + 2);							printf("이진 트리에서 각 노드는 두 개의 서브 트리를 가지며, 각 서브 트리는 왼쪽 서브 트리와 오른쪽 서브 트리로 나뉜다.");
	gotoXY(x, y + 4);							printf("이진 트리는 다양한 응용 분야에서 사용되며, 특히 정렬된 데이터의 저장 및 검색에 효과적으로 사용된다.");
	gotoXY(x, y + 6);							printf("루트, 부모, 자식, 리프, 서브트리 등의 요소가 존재한다.");

	getch();
	cls;
	myBinary();
}