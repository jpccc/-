#include"GrammarAnalyzerByJPC.h"
TreeNode* GrammarAnalyzer::ProgramHead() {
	TreeNode node = new TreeNode();//PheadK����
	node.setnodeKind(PheadK);
	match("PROGRAM")//���˳���Ϊƥ��ɹ��������Ż���Сд��
		if (CurrentToken->type == ID) {
			node->name[0] = CurrentToken->value;
	}
	match(CurrentToken->value);
}
void GrammarAnalyzer::match(string st) {
	if(CurrentWord)
}