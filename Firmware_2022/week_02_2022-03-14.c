/*
* ===============================
	�߿��� �� ����̽� ����̹�
	2022-03-14 C��� ����
* ===============================
*/


#include <stdio.h>

int d() {
	static int n = 0;
	int x;
	int y = 0;

	n++;
	printf("n=%d\n", n);
}

int main() {

	char* c1 = "abcde";
	char* c2 = "abcde";
	//  "abcde" �� �ؽ�Ʈ ������ �����  (���)
	//	 c1�� stack�� ����� ��

	/*
		c1 c2�� ������ ������?  ( => �ּ� ���� ����)

		 &c1 : 0x005dfd48 {0x00bf7b38 "abcde"}
		 &c2 : 0x005dfd3c {0x00bf7b38 "abcde"}
	*/

	/*
		"abcde"�� �ϳ��� ����� ���� ��? ( = c1�� c2�� ���� �����ұ�?)

		 c1 : 0x00797b38 | c2 : 0x00797b38
	*/


	char* c3;

	c3 = c1;
	c3[2] = 'X';

	char c4[5];
	char c5[6] = "abcde";

	char c6[6] = "abcde";

	for (int i = 0; i < 1 ; i++)
	{
		d();
	}
}