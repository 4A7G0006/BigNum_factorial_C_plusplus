#define _CRT_SECURE_NO_DEPRECATE
#include <iostream>
#include <cstring>
using namespace std;
void reupdate(char *update, char *str) {   //update;
	bool work = false;
	while ((*str) == '0') {
		str++;
		work = true;
	}
	if (work) {
		while ((*str) != '\0') {
			(*update) = (*str);
			update++;
			str++;
		}
		(*update) = '\0';
	}
}
char* Decrement(char *multiped) {     //step-1;
	int len = strlen(multiped) - 1;
	while (multiped[len] == '0')
		len--;
	multiped[len] = (multiped[len] - 1);
	while (multiped[++len] == '0')
		multiped[len] = '9';
	reupdate(multiped, multiped);

	return multiped;
}
void Multiply(char *answer, char *Multiplied) {
	char **tp, *tempsave;
	int next, num, index;

	if (strlen(Multiplied) != 0) {
		cout << answer << "*" << Multiplied << endl;
		tp = new char*[strlen(Multiplied)];

		for (int i = strlen(Multiplied) - 1; i >= 0; i--) {

			tp[i] = new char[(strlen(answer) * 2 + 1)];
			memset(tp[i], '-', strlen(answer) * 2 + 1);
			next = 0;
			num = 0;
			index = strlen(Multiplied) - 1 - i;
			for (int j = strlen(answer) - 1; j >= 0; j--) {
				num = ((int)Multiplied[i] - 48)*((int)answer[j] - 48) + next;
				next = num / 10;
				tp[i][index] = (char)((num % 10) + 48);
				index++;
			}
			if (next > 0)
				tp[i][index] = (char)(next + 48);

		}
		tempsave = new char[(strlen(answer) * 2 + 1)];
		memset(tempsave, '\0', strlen(answer) * 2 + 1);
		num = 0;

		for (unsigned int i = 0; i < strlen(answer) * 2 + 1; i++) {
			for (unsigned int j = 0; j < strlen(Multiplied); j++) {
				if (tp[j][i] >= '0' && tp[j][i] <= '9') {
					num = num + (((int)tp[j][i]) - 48);
				}
			}
			tempsave[i] = (char)((num % 10) + 48);

			num = num / 10;
		}
		tempsave[strlen(answer) * 2] = '\0';

		for (index = strlen(tempsave) - 1; index >= 0; index--)
			answer[(strlen(tempsave) - 1) - index] = tempsave[index];

		answer[index] = '\0';
		reupdate(answer, answer);
		delete[]tempsave;
		for (unsigned i = 0; i < strlen(Multiplied); i++)
			delete[]tp[i];
		Multiply(answer, Decrement(Multiplied));
	}
}
int main(int argc, char *argv[]) {
	char *strpt, *multiped;
	bool error;
	unsigned int i;
	strpt = new char[20000];
	multiped = new char[20000];
	memset(strpt, '\0', 20000);
	memset(multiped, '\0', 20000);
	while (cin >> strpt) {
		i = 0;
		error = false;
		while (i < strlen(strpt)) {
			if (strpt[i]<'0' || strpt[i]>'9') {
				error = true;
				break;
			}
			i++;
		}
		if (error) {
			cout << "error" << endl;
		}
		else {
			reupdate(strpt, strpt);
			strcpy(multiped, strpt);
			Multiply(strpt, Decrement(multiped));
			cout << "answer:" << endl << strpt << endl;
			//cout <<"共"<< strlen(strpt) << "位數" << endl;
			memset(strpt, '\0', 20000);
			memset(multiped, '\0', 20000);
		}
	}
}
