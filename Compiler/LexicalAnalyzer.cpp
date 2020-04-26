#include"LexicalAnalyzer.h"
void LexicalAnalyzer::testId(string input) {
	int state = 0;
	int curIndex = 0;
	char curChar = input[curIndex];
	cout << "curchar=" << curChar << endl;
	enum {error=-1};
	int matrix[3][2] = { 1,error,2,2,2,2 };
	cout << "matrix:"<<matrix[1][0] << " " << matrix[1][1] << endl;
	while (curChar!='#'&&state != error ) {
		if ((curChar >= 'a' && curChar <= 'z') || (curChar >= 'A' && curChar <= 'Z')) {
			state = matrix[state][0];
		}
		else if (curChar >= '0' && curChar <= '9') {
			state = matrix[state][1];
		}
		else
		{
			state = error;
		}
		curChar = input[++curIndex];
	}
	if (state == 2 || state == 3) {
		cout << "识别成功" << endl;
	}
	else
	{
		cout << "识别错误" << endl;
	}
}