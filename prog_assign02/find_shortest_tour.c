#pragma warning(disable:4996)
#include<stdio.h>
#include<math.h>
#define MAX 100

typedef struct dot {
	int index;
	int x;
	int y;
} Dot;

int N;
int tour[MAX];
double getTour(Dot spot[], int k, double min);
double sumDistance(int N, Dot data[]);
double distance(Dot data1, Dot data2);
void swap(Dot spot[], int i, int j);

int main() {
	FILE *fp = fopen("input.txt", "r");
	fscanf(fp, "%d", &N);
	Dot spot[MAX];
	for (int i = 0; i < N; i++) {
		spot[i].index = i;
		fscanf(fp, "%d %d", &spot[i].x, &spot[i].y);
	}
	double min1 = sumDistance(N, spot);

	printf("%lf\n", getTour(spot, 0, min1));
	printf("경로: [ ");
	for (int i = 0; i < N - 1; i++) printf("%d, ", tour[i]);
	printf("%d ]\n", tour[N - 1]);
	fclose(fp);
	getch();
	return 0;
}

double getTour(Dot spot[], int k, double min) {  //[0~k-1]까지는 순서가 정해져있고, [k~N-1]로 만들수 있는 투어의 거리 최솟값반환
	if (k == N) {
		return sumDistance(N, spot);
	}
	//else
	for (int i = k; i < N; i++) {
		swap(spot, k, i);
		double tmp = getTour(spot, k + 1, min);
		if (min> tmp) {
			min = tmp;
			if (k == N - 1) for (int i = 0; i < N; i++) tour[i] = spot[i].index;
		}
		swap(spot, k, i);
	}
	return min;
}

double sumDistance(int N, Dot data[]) //한 투어의 이동거리 구하기
{
	double sum = 0;
	for (int i = 0; i < N; i++) {
		if (i == N - 1) sum += distance(data[i], data[0]);
		else sum += distance(data[i], data[i + 1]);
	}
	return sum;
}

double distance(Dot data1, Dot data2) //두 좌표(data1, data2) 사이 거리 구하기
{
	return sqrt((data1.x - data2.x)*(data1.x - data2.x) + (data1.y - data2.y)*(data1.y - data2.y));
}

void swap(Dot spot[], int i, int j)
{
	Dot tmp = spot[i];
	spot[i] = spot[j];
	spot[j] = tmp;
}