#include "RoughLexer.h"


/*****************************************************************
* CLASS | RuleSet_A2
* ----------------------------------------------------------------
* The designed class is exclusively for reading the A2 lexers
* ruleset(s) for programming the A2 lexer/parser.
* ----------------------------------------------------------------
*
* public -> This section provides accesible functions to the 
*           ruleset only.
*
* private -> This section is designed to hold variables that
*            can only be access for the A2 lexer ruleset.
* -
******************************************************************/
class RuleSet_A2
{
	public:

		/*****************************************************************
		* VECTOR<STRING>| parseID
		* ----------------------------------------------------------------
		* This vector function is designed to parse the ID of the A2
		* lexer ruleset(s). The parseID's are the first initial number
		* structures to determine the key's attached id.
		*
		* RETURNS: Parsed ID Vector.
		******************************************************************/
		vector<string> parseID(vector<string> parseStack);

		/*****************************************************************
		* VECTOR<STRING>| parseKey
		* ----------------------------------------------------------------
		* This vector function is designed to parse the Key of the A2
		* lexer ruleset(s). Key's are generally keywords to describe the
		* A2 lexers input character(s) set(s).
		*
		* RETURNS: Parsed Key Vector.
		******************************************************************/
		vector<string> parseKey(vector<string> parseStack);

		/*****************************************************************
		* VECTOR<STRING>| parseOp
		* ----------------------------------------------------------------
		* This vector function is designed to parse the what the key
		* of the A2 ruleset members look like. Key's are generally keywords
		* to describe the A2 lexers input character(s) set(s).
		* Ex: 10 kwdprog = "prog"
		*
		* + '10' is the ID.
		* + 'kwdprog' is the key.
		* + 'prog' is the Op(short for operation.)
		*
		* RETURNS: Parsed Operation Vector.
		******************************************************************/
		vector<string> parseOp(vector<string> parseStack);

		/*****************************************************************
		* VECTOR<STRING>| ruleSet_
		* ----------------------------------------------------------------
		* This vector function is designed to read in the A2 Lexicon 
		* ruleset and stores them into the desired vector structure. 
		* RETURNS: A2 Lexicon ruleset.
		******************************************************************/
		vector<string> ruleSet_();

	private:

		std::vector<std::string> A2RuleSet; //A2 Lexicon Ruleset vector.
		                                    //Holds all the required ruleset(s).

};

/*****************************************************************
* CLASS | Parser_A2
* ----------------------------------------------------------------
* The designed class is exclusively for parsing the desired
* input from the user through a provided '.txt' file.
* 
* NOTE: The parser is dynamic and currently is following the
*       A2 Lexicon ruleset(s).
* ----------------------------------------------------------------
*
* public -> This section provides accesible functions to the
*           parser only.
*
* private -> This section is designed to hold variables that
*            can only be access for the parser ruleset.
* -
******************************************************************/
class Parser_A2
{
	public:

		/*****************************************************************
		* VECTOR<STRING>| read_Text
		* ----------------------------------------------------------------
		* This function is designed to read the given '.txt' file with
		* A2 Lexicon parameters to be checked and executed for
		* correct A2 Lexicon ruleset(s).
		*
		* + string File_Name : The name of the '.txt' file that will be 
		*                      queue'd for parsing with A2 Lexicon
		*                      ruleset.
		*
		* RETURNS: Detailed vector<string> stack that has additional '.txt'
		*          file information.
		******************************************************************/
		vector<string> read_Text(string File_Name);

		/*****************************************************************
		* STRING| int_check
		* ----------------------------------------------------------------
		* This function is designed to distinguish between an integer and
		* a float.
		*
		* + string line_ : The substring where the parsing for the int
		*                  float will be executed at.
		*
		* + int _pos     : The position variable where the integer or the
		*                  float has been verified.
		*
		* RETURNS: Parsed Integer or Float with a hardcoded flag.
		******************************************************************/
		string int_check(string line_, int _pos);

		/*****************************************************************
		* STRING| next_token
		* ----------------------------------------------------------------
		* This function is designed to execute the initial parsing process
		* process. The process will accomidate the A2 Lexicon ruleset(s)
		* and parse accordingly.
		*
		* + vector<string> _id        : The id parameter from A2 Lexicon 
		*                               ruleset(s).
		* + vector<string> _key       : The key parameter from A2 Lexicon
		*                               ruleset(s).
		* + vector<string> _operation : The operation parameter from A2 
		*                               Lexicon ruleset(s).
		* + string _line              : The substring that will be
		*                               initially checked for token(s).
		* + string _line_num          : The line number(s) collected
		*                               from the text file stack.
		*
		* RETURNS: Nothing.
		******************************************************************/
		void next_token(vector<string> _id, vector<string> _key, vector<string> _operation, string _line, string _line_num);

		/*****************************************************************
		* STRING| Parser_A2Lexi
		* ----------------------------------------------------------------
		* This function is designed to create the initial parsing process
		* process. The process will accomidate the A2 Lexicon ruleset(s)
		* and parse accordingly.
		*
		* + vector<string> _id        : The id parameter from A2 Lexicon
		*                               ruleset(s).
		* + vector<string> _key       : The key parameter from A2 Lexicon
		*                               ruleset(s).
		* + vector<string> _operation : The operation parameter from A2
		*                               Lexicon ruleset(s).
		* + string _line              : The substring that will be
		*                               initially checked for token(s).
		* + string _line_num          : The line number(s) collected
		*                               from the text file stack.
		*
		* RETURNS: Nothing.
		******************************************************************/
		void Parser_A2Lexi(vector<string> _id, vector<string> _key, vector<string> _operation, vector<string> Text_File);

	private:

		vector<string> Text_File;
		vector<string> id_string;
		int number_of_lines = 0;
};
