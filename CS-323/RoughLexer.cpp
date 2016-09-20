// RoughLexer.cpp : Defines the entry point for the console application.
//
#include "RoughLexer.h"
#include "A2Lexer.h"

int main()
{
	RuleSet_A2 ruleset;
	vector<string> A2_Lexer = ruleset.ruleSet_();
	// Calls the parsing functions and translators. 
	vector<string> A2iD_  = ruleset.parseID(A2_Lexer);
	vector<string> A2Key_ = ruleset.parseKey(A2_Lexer);
	vector<string> A2Op_  = ruleset.parseOp(A2_Lexer);

	Parser_A2 parser_;
	vector<string>File_Text = parser_.read_Text("DummyText.txt");
	parser_.Parser_A2Lexi(A2iD_, A2Key_, A2Op_, File_Text);

	for (int i = 0; i < File_Text.size(); i++)
	{
		//cout << File_Text[i] << endl;
	}

//------------------------------------------------------------------------------
	

	std::cin.ignore();
	std::cin.ignore();

	return 0;
}
