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

	printf("���ڿ��� �Է��ϼ��� : ");
	scanf_s("%s", string, 100);
	printf("���� ������ �Է��ϼ��� : ");
	scanf_s("%s", pat, 100);

	int result = nfind(string, pat);

	if (result == -1)
		printf("���ڿ����� ������ ã�� �� ����..\n");
	else
		printf("���ڿ� %d ��°���� ������ ���۵�..\n", result);

	return 0;
}