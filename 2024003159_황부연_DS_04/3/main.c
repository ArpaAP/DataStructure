#include <stdio.h>
#include <string.h>

int nfind(char* string, char* pat)
{
	int i = 0, j = 0, start = 0;
	int lasts = strlen(string) - 1;
	int lastp = strlen(pat) - 1;
	int endmatch = lastp;

	for (i = 0; endmatch <= lasts; endmatch++, start++) {
		if (string[endmatch] == pat[lastp])
			for (j = 0, i = start; j < lastp && string[i] == pat[j]; i++, j++);
		if (j == lastp)
			return start;
	}

	return -1;
}

int main(void)
{
	char string[100];
	char pat[100];

	printf("문자열을 입력하세요 : ");
	scanf_s("%s", string, 100);
	printf("비교할 패턴을 입력하세요 : ");
	scanf_s("%s", pat, 100);

	int result = nfind(string, pat);

	if (result == -1)
		printf("문자열에서 패턴을 찾을 수 없음..\n");
	else
		printf("문자열 %d 번째부터 패턴이 시작됨..\n", result);

	return 0;
}