// RoughLexer.cpp : Defines the entry point for the console application.
//
#include "RoughLexer.h"
#include "A2Lexer.h"
/*****************************************************************
* PROJECT - A2 LEXICON PARSER
* ----------------------------------------------------------------
* Team Name : DeMorgan's loss.
* Authors   : Can Dalgir, David Luong.
* Project   : 1
* Style     : Pragmatic
* ----------------------------------------------------------------
* DESCRIPTION
* ----------------------------------------------------------------
* This program is designed to handle the A2 programming language
* lexicon. The program is additionally designed to handle dynamic
* lexer ruleset(s) to avoid further programming language 
* transformation(s).
* 
* ----------------------------------------------------------------
* CLASS | RuleSet_A2
* ----------------------------------------------------------------
* The designed class is exclusively for reading the A2 lexers
* ruleset(s) for programming the A2 lexer/parser.
* ----------------------------------------------------------------
*         |-ruleset
*         |---> A2_Lexer
*         |---> A2iD_
*         |---> A2Key_
*         |---> A2Op_
*
* ----------------------------------------------------------------
* CLASS | Parser_A2
* ----------------------------------------------------------------
* The designed class is exclusively for parsing the desired
* input from the user through a provided '.txt' file.
* ----------------------------------------------------------------
* CLASS | Parser_A2
*         |-parser_
*         |---> File_Text
*
******************************************************************/
int main()
{
	/*----------------------------------------------------------------
	* CLASS | RuleSet_A2
	* ----------------------------------------------------------------
	* Decleration segment.
	*/
	RuleSet_A2 ruleset;
	vector<string> A2_Lexer = ruleset.ruleSet_(); 
	vector<string> A2iD_    = ruleset.parseID(A2_Lexer);
	vector<string> A2Key_   = ruleset.parseKey(A2_Lexer);
	vector<string> A2Op_    = ruleset.parseOp(A2_Lexer);

	/*----------------------------------------------------------------
	 * CLASS | Parser_A2
	 * ----------------------------------------------------------------
	 * Decleration segment.
     */
	Parser_A2 parser_;
	vector<string>File_Text_1 = parser_.read_Text("TestCase_1.txt");

	//FUNCTION CALL - Parser_A2Lexi
	parser_.Parser_A2Lexi(A2iD_, A2Key_, A2Op_, File_Text_1);
	cout << "Finished parsing Testcase_1..." << endl;
	parser_.cleanParser_();
	cin.ignore();

	vector<string>File_Text_2 = parser_.read_Text("TestCase_2.txt");
	parser_.Parser_A2Lexi(A2iD_, A2Key_, A2Op_, File_Text_2);
	cout << "Finished parsing Testcase_2..." << endl;
	parser_.cleanParser_();
	cin.ignore();

	vector<string>File_Text_3 = parser_.read_Text("TestCase_3.txt");
	parser_.Parser_A2Lexi(A2iD_, A2Key_, A2Op_, File_Text_3);
	cout << "Finished parsing Testcase_3..." << endl;
	parser_.cleanParser_();
	cin.ignore();

    //------------------------------------------------------------------------------
	//Halts the Visual Studio console for readability of the correct output.
	std::cin.ignore();
	std::cin.ignore();
	return 0;
}
