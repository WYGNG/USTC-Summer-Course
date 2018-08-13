#include <iostream>
#include <cstdlib>
#include <thread>
#include <time.h>
#include <windows.h>
#define M 10
#define MAX 20
int mutex = 1;
int EMPTY = M;
int FULL = 0;
int a[M+1] = { 0 };
using namespace std;
void consumer(int *n1) {
	if (*n1 > MAX) {
		cout << "运行次数已达到最大限制，消费者进程结束\n" << endl;
		return;
	}
	if (FULL == 0) {
		printf("无产品可消费，消费者休眠随机时间\n");
		srand((unsigned)time(NULL));
		Sleep(rand()%3000);
		return consumer(n1);
	}
	while (FULL>0&&EMPTY<M) {
		if (mutex == 1) {
			mutex = 0;
			int i = 1;
			while (a[i] != 0 )
				i++;
			printf("消费者打印数组a中第%d号的数据，输出为%d,并重新归零\n", i - 1, a[i - 1]);
			a[i - 1] = { 0 };
			FULL -= 1;
			EMPTY += 1;
			printf("消费者进程运行一次，消费一件产品，EMPTY区目前为%d，FULL区目前为%d，消费了数组a中第%d号数据\n", EMPTY, FULL,i-1);
			mutex = 1;
			*n1++;
			srand((unsigned)time(NULL));
			Sleep(rand() % 3000);
			return consumer(n1);
		}
		else {
			printf("缓冲区被其他进程占用，消费者休眠随机时间\n");
			srand((unsigned)time(NULL));
			Sleep(rand() % 3000);
			return consumer(n1);
		}
	}
	return;
}
void producer(int *n2) {
	if (*n2 > MAX) {
		cout << "运行次数已达到最大限制，生产者进程结束\n" << endl;
		return;
	}
	if (FULL == M) {
		printf("产品货架已满，生产者休眠随机时间\n");
		srand((unsigned)time(NULL));
		Sleep(rand() % 3000);
		return producer(n2);
	}
	while (EMPTY>0&&FULL<M) {
		if (mutex == 1) {
			mutex = 0;
			EMPTY -= 1;
			FULL += 1;
			int i = 1;
			while (a[i] != 0)
				i++;
			a[i] = i;
			printf("生产者向a中第%d号写入数据%d\n", i, a[i]);
			printf("生产者进程运行一次，生产一件产品，EMPTY区目前为%d，FULL区目前为%d,向数组a第%d号写入数据\n", EMPTY, FULL,i);
			mutex = 1;
			*n2++;
			srand((unsigned)time(NULL));
			Sleep(rand() % 3000);
			return producer(n2);
		}
		else {
			printf("缓冲区被其他进程占用，生产者休眠随机时间\n");
			srand((unsigned)time(NULL));
			Sleep(rand() % 3000);
			return producer(n2);
		}
	}
	return;
}
int main() {
	cout << "主函数开始运行\n" << endl;
	int count1 = 0, count2 = 0;
	int *c1 = &count1, *c2 = &count2;
	thread CONSUMER(consumer,c1);
	thread PRODUCER(producer,c2);
	PRODUCER.join();
	CONSUMER.join();
	cout << "主函数运行结束\n" << endl;
	return 0;
}