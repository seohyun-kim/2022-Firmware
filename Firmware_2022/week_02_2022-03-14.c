/*
* ===============================
	펌웨어 및 디바이스 드라이버
	2022-03-14 C언어 복습
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
	//  "abcde" 는 텍스트 영역에 저장됨  (상수)
	//	 c1은 stack에 만들어 짐

	/*
		c1 c2가 만들어는 졌을까?  ( => 주소 값을 봐라)

		 &c1 : 0x005dfd48 {0x00bf7b38 "abcde"}
		 &c2 : 0x005dfd3c {0x00bf7b38 "abcde"}
	*/

	/*
		"abcde"가 하나만 만들어 졌을 까? ( = c1과 c2의 값은 동일할까?)

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