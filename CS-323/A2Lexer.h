#include "RoughLexer.h"

class RuleSet_A2
{
	public:
		vector<string> parseID(vector<string> parseStack);
		vector<string> parseKey(vector<string> parseStack);
		vector<string> parseOp(vector<string> parseStack);
		vector<string> ruleSet_();

	private:
		std::vector<std::string> A2RuleSet;

};

class Parser_A2
{
	public:
		vector<string> read_Text(string File_Name);
		void Parser_A2Lexi(vector<string> _id, vector<string> _key, vector<string> _operation, vector<string> Text_File);
		string token_match(vector<string> _id, vector<string> _key, vector<string> _operation, string _line, string _line_num);

		string int_check(string line_);
		string float_check(string line_);
		void next_token();

	private:
		vector<string> Text_File;
		int number_of_lines = 0;
};
