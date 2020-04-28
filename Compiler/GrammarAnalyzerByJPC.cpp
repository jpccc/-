#include"GrammarAnalyzerByJPC.h"
TreeNode* GrammarAnalyzer::ProgramHead() {
	TreeNode node = new TreeNode();//PheadK类型
	node.setnodeKind(PheadK);
	match("PROGRAM")//不退出即为匹配成功，后期优化大小写！
		if (CurrentToken->type == ID) {
			node->name[0] = CurrentToken->value;
	}
	match(CurrentToken->value);
}
void GrammarAnalyzer::match(string st) {
	if(CurrentWord)
}