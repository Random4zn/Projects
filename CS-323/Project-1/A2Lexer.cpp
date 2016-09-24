#include "A2Lexer.h"
/*****************************************************************
* PROJECT - A2 LEXICON PARSER
* ----------------------------------------------------------------
* Team Name : DeMorgan's loss.
* Authors   : Can Dalgir, David Luong.
* Project   : 1
* Style     : Pragmatic / Pair Programming.
* ----------------------------------------------------------------*/


/*****************************************************************
* CLASS | RuleSet_A2
* ----------------------------------------------------------------
* The designed class is exclusively for reading the A2 lexers
* ruleset(s) for programming the A2 lexer/parser.
* ----------------------------------------------------------------
* NOTE: The RuleSet_A2 is region wrapped using #pragma provided
*       by visual studio 2012.
******************************************************************/
#pragma region Region_Class_RuleSet_A2

/*****************************************************************
* VECTOR<STRING>| ruleSet_
* ----------------------------------------------------------------
* This vector function is designed to read in the A2 Lexicon
* ruleset and stores them into the desired vector structure.
*
* RETURNS: A2 Lexicon ruleset.
******************************************************************/
vector<string> RuleSet_A2::ruleSet_()
{
	string keyline = "";
	ifstream keyfile("A2LexiconKey.txt");
	if (keyfile.is_open())
	{
		while (getline(keyfile, keyline))
		{
			if (keyline.at(0) != '/')
			{
				A2RuleSet.push_back(keyline);
			}
		}
		keyfile.close();
	}
	else cout << "Unable to open file";

	return A2RuleSet;
}


/*****************************************************************
* VECTOR<STRING>| parseID
* ----------------------------------------------------------------
* This vector function is designed to parse the ID of the A2
* lexer ruleset(s). The parseID's are the first initial number
* structures to determine the key's attached id.
*
* RETURNS: Parsed ID Vector.
******************************************************************/
vector<string> RuleSet_A2::parseID(vector<string> parseStack)
{
	string tempP_ = "";
	string iD_    = "";
	vector<string> idParsed;

	for (int i = 0; i < parseStack.size(); i++)
	{
		tempP_ = parseStack[i];
		for (int k = 0; k < tempP_.length(); k++)
		{
			if (isalpha(tempP_[k])) { break; }
			else { iD_ += tempP_[k]; }
		}

		idParsed.push_back(iD_);
		iD_.clear();
	}
	return idParsed;
}

/*****************************************************************
* VECTOR<STRING>| parseKey
* ----------------------------------------------------------------
* This vector function is designed to parse the Key of the A2
* lexer ruleset(s). Key's are generally keywords to describe the
* A2 lexers input character(s) set(s).
*
* RETURNS: Parsed Key Vector.
******************************************************************/
vector<string> RuleSet_A2::parseKey(vector<string> parseStack)
{
	string tempP_ = "";
	string Key_   = "";
	vector<string> keyParsed;

	for (int i = 0; i < parseStack.size(); i++)
	{
		tempP_ = parseStack[i];
		for (int k = 0; k < tempP_.length(); k++)
		{
			if (isalpha(tempP_[k]))
			{
				Key_ += tempP_[k];
			}

			if (tempP_[k] == '=')
			{
				Key_ += tempP_[k];
				break;
			}
		}

		keyParsed.push_back(Key_);
		Key_.clear();
	}

	return keyParsed;
}

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
vector<string> RuleSet_A2::parseOp(vector<string> parseStack)
{
	string tempP_ = "";
	string Key_ = "";
	vector<string> keyParsed;

	for (int i = 0; i < parseStack.size(); i++)
	{
		tempP_ = parseStack[i];
		for (int k = 0; k < tempP_.length(); k++)
		{
			if (tempP_[k] == '=')
			{
				for (int z = (k + 1); z < tempP_.length(); z++)
				{
					if ((tempP_[z] != 34) && (tempP_[z] != 39) && (tempP_[z] != ' '))
					{
						Key_ += tempP_[z];
					}
				}
			}
		}

		keyParsed.push_back(Key_);
		Key_.clear();
	}

	return keyParsed;
}

#pragma endregion Region_Class_RuleSet_A2

/*****************************************************************
* CLASS | Parser_A2
* ----------------------------------------------------------------
* The designed class is exclusively for parsing the desired
* input from the user through a provided '.txt' file.
*
* NOTE: The parser is dynamic and currently is following the
*       A2 Lexicon ruleset(s).
* ----------------------------------------------------------------
* NOTE: The RuleSet_A2 is region wrapped using #pragma provided
*       by visual studio 2012.
******************************************************************/
#pragma region Region_Class_Parser_A2

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
vector<string> Parser_A2::read_Text(string File_Name)
{
	cout << File_Name << endl;
	string _line     = "";
	string text_     = "";
	ifstream file_(File_Name);
	if (file_.is_open())
	{
		while (getline(file_, _line))
		{
			++number_of_lines;

			string temp_ = "Line " + to_string(number_of_lines) + ": ";
			//IF STATEMENT - This section is designed to remove any comments
			//               written by the user. This is due to the fact that
			//               comments are treated as whitespace up to newline char.
			//
			size_t comment_ = _line.find("//");
			if (comment_ != string::npos)
			{
				_line.erase(comment_, _line.length());
			}
			//Line Vector: Overall structure of the program stack.
			Text_File.push_back(temp_ + _line);
		}
		file_.close();
	}
	else cout << "Unable to open file";

	return Text_File;
}

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
string Parser_A2::int_check(string line_, int _pos)
{
	string temp_digit = "";

	for (int i = (_pos + 1); i < line_.length(); i++)
	{
		//TRY BLOCK
		try
		{
			if (isdigit(line_[i]))
			{
				temp_digit += line_[i];
			}//END OF INTEGERCHECK-IF-STATEMENT
			else
			{
				break;
			}
			if (isdigit(line_[i]))
			{
				size_t found_Float = line_.find(".");
				//search for period with limit.
				if (found_Float != string::npos)
				{
					for (int k = found_Float; k < line_.size(); k++)
					{
						if (line_[k] != ';')
						{
							temp_digit += line_[k];
						}
					}
					temp_digit += "_float_";
					break;
				}
				else
				{
					temp_digit += "_int_";
				}
			}
		}//END OF TRY
		catch (int Error) { cout << "Error code: " << Error << endl; }
	}

	return temp_digit;
}

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
void Parser_A2::next_token(vector<string> _id, vector<string> _key, vector<string> _operation, string _line, string _line_num)
{
	string temp_string = "";
	string temp_id     = "";
	string temp_s      = "";
	string delim_check = "";
	string int_digit   = "";

	//FOR LOOP - The main for loop designed to handle
	//           token collecting and check for
	//           A2 Lexicon ruleset structures.
	for (int i = 0; i < _line.length(); i++)
	{
		//IF STATEMENT - Avoids whitespace to reduce token
		//               input.
		if (_line[i] != ' ')
		{
			temp_string += _line[i];
			delim_check  = _line[i];
		}

		/*----------------------------------------------------------------
		* REGION | Region_String_Check
		* ----------------------------------------------------------------
		* The region is designed to check for structures that are allowed
		* in the 'String' ruleset structure for an A2 Lexicon.
		******************************************************************/
		if (_line[i] == '"')
		{
			for (int index = (i + 1); index < _line.length(); index++)
			{
				if (_line[index] == '"')
				{
					i = index;
					break;
				}
				temp_s += _line[index];
			}
		}
		if (!(temp_s.empty()))
		{
			cout << "(Tok: id= " << _id[3] << "line= " << _line_num << " " << "str= " << "\"" << temp_s << "\"" << ")" << endl;
			temp_s.clear();
		}

		/*----------------------------------------------------------------
		* REGION | Region_Unpaired_Delimiters_Check
		* ----------------------------------------------------------------
		* The region is designed to check for structures that are allowed
		* in the 'Unpaired Delimiters' ruleset structure for an A2 Lexicon.
		******************************************************************/
		for (int index = 4; index < 6; index++)
		{
			if (delim_check == _operation[index])
			{
				cout << "(Tok: id= " << _id[index] << "line= " << _line_num << " " << "str= " << "\"" << _operation[index] << "\"" << ")" << endl;
				delim_check.clear();
			}
		}

		/*----------------------------------------------------------------
		* REGION | Region_Keywords_Check
		* ----------------------------------------------------------------
		* The region is designed to check for structures that are allowed
		* in the 'Keywords' ruleset structure for an A2 Lexicon.
		******************************************************************/
		for (int index = 6; index < 20; index++)
		{

			if (temp_string == _operation[index])
			{
				cout << "(Tok: id= " << _id[index] << "line= " << _line_num << " " << "str= " << "\"" << _operation[index] << "\"" << ")" << endl;
				temp_string.clear();
			}
		}

		/*----------------------------------------------------------------
		* REGION | Region_Paired_Delimeters_Check
		* ----------------------------------------------------------------
		* The region is designed to check for structures that are allowed
		* in the 'Paired Delimeters' ruleset structure for an A2 Lexicon.
		******************************************************************/
		for (int index = 21; index < 29; index++)
		{
			if (delim_check == _operation[index])
			{
				cout << "(Tok: id= " << _id[index] << "line= " << _line_num << " " << "str= " << "\"" << _operation[index] << "\"" << ")" << endl;
				temp_string.clear();
				delim_check.clear();
			}
		}

		string temp_du = "";
		/*----------------------------------------------------------------
		* REGION | Region_Other_Punctuation_Check
		* ----------------------------------------------------------------
		* The region is designed to check for structures that are allowed
		* in the 'Other Punctuation' ruleset structure for an A2 Lexicon.
		******************************************************************/
        #pragma region Region_Other_Punctuation_Check
		for (int index = 29; index < 40; index++)
		{
			if (delim_check == _operation[index])
			{
				/*----------------------------------------------------------------
				* REGION | Region_Id_Check
				* ----------------------------------------------------------------
				* The region is designed to check for structures that are allowed
				* in the ruleset structure for an A2 Lexicon.
				******************************************************************/
                #pragma region Region_Id_Check
				if (delim_check == "=")
				{

					//Creates the ID -
					for (int f = 0; f < i; f++)
					{
						if (isalpha(_line[f]))
						{
							temp_id += _line[f];
						}
					}

					//Displays The ID-
					if (!(temp_id.empty()))
					{
						//Still need to edit out the semi-colon stuff.
						cout << "(Tok: id= " << _id[0] << "line= " << _line_num << " " << "str= " << "\"" << temp_id << "\"" << ")" << endl;
						cout << "(Tok: id= " << _id[index] << "line= " << _line_num << " " << "str= " << "\"" << _operation[index] << "\"" << ")" << endl;
						if (!(temp_id.empty()))
						{
							id_string.push_back(temp_id);
						}
					}


					/*----------------------------------------------------------------
					 * REGION | Region_Float_and_Int_Check
					 * ----------------------------------------------------------------
					 * The region is designed to check for numerical structures
					 * that will provide the correct data determination weather be
					 * an integer of a float.
					 ******************************************************************/
					#pragma region Region_Float_and_Int_Check
					temp_du = int_check(_line, i);
					size_t found_Float = temp_du.find("_float_");
					size_t found_Int   = temp_du.find("_int_");
					//search for period with limit.
					if(found_Float != string::npos)
					{
						string temp_f = "_float_";
						temp_du.erase(found_Float, temp_f.length());
						if (!(temp_du.empty()))
						{
							//Still need to edit out the semi-colon stuff.
							cout << "(Tok: id= " << _id[2] << "line= " << _line_num << " " << "str= " << "\"" << temp_du << "\"" << " float=" << temp_du << ")" << endl;
							temp_du.clear();
						}

					}
					else if(found_Int != string::npos)
					{
						string temp_i = "_int_";
						temp_du.erase(found_Int, temp_i.length());
						if (!(temp_du.empty()))
						{
							cout << "(Tok: id= " << _id[1] << "line= " << _line_num << " " << "str= " << "\"" << temp_du << "\"" << " int=" << temp_du << ")" << endl;
							temp_du.clear();
						}

					}
                    #pragma endregion Region_Float_and_Int_Check
				}
				#pragma endregion Region_Id_Check

				//IF STATEMENT - Designed to output additional delimiter(s).
				if (delim_check != "=")
				{ cout << "(Tok: id= " << _id[index] << "line= " << _line_num << " " << "str= " << "\"" << _operation[index] << "\"" << ")" << endl; }

				//Queue's ID position
				string temp_sc = "";
				for (int outer_ = i; outer_ < _line.length(); outer_++)
				{
					if (isalpha(_line[outer_]))
					{
						temp_sc += _line[outer_];
						for (int inner_ = 0; inner_ < id_string.size(); inner_++)
						{
							if (temp_sc == id_string[inner_])
							{
								cout << "(Tok: id= " << _id[0] << "line= " << _line_num << " " << "str= " << "\"" << temp_sc << "\"" << ")" << endl;
								temp_sc.clear();
								break;
							}
						}

						if (temp_sc.empty())
						{ break; }
					}
				}

				//String and vector clearing.
				//Memory management.
				temp_id.clear();
				temp_string.clear();
				delim_check.clear();
			}
		}
        #pragma endregion Region_Other_Punctuation_Check

		/*----------------------------------------------------------------
		* REGION | Region_Float_and_Int_Check
		* ----------------------------------------------------------------
		* The region is designed to check for numerical structures
		* that will provide the correct data determination weather be
		* an integer of a float.
		******************************************************************/
		if (isdigit(_line[i]))
		{
			#pragma region Region_Float_and_Int_Check_2
			temp_du.clear();
			temp_du = int_check(_line, (i-1));
			size_t found_Float = temp_du.find("_float_");
			size_t found_Int   = temp_du.find("_int_");
			//search for period with limit.
			if (found_Float != string::npos)
			{
				string temp_f = "_float_";
				temp_du.erase(found_Float, temp_f.length());
				if (!(temp_du.empty()))
				{
					//Still need to edit out the semi-colon stuff.
					cout << "(Tok: id= " << _id[2] << "line= " << _line_num << " " << "str= " << "\"" << temp_du << "\"" << " float=" << temp_du << ")" << endl;
					temp_du.clear();
				}

			}
			else if (found_Int != string::npos)
			{
				string temp_i = "_int_";
				temp_du.erase(found_Int, temp_i.length());
				if (!(temp_du.empty()))
				{
					cout << "(Tok: id= " << _id[1] << "line= " << _line_num << " " << "str= " << "\"" << temp_du << "\"" << " int=" << temp_du << ")" << endl;
					temp_du.clear();
				}

			}
			#pragma endregion Region_Float_and_Int_Check_2
		}

	}
}

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
void Parser_A2::Parser_A2Lexi(vector<string> _id, vector<string> _key, vector<string> _operation, vector<string> Text_File)
{
	string Textword_ = "";
	string Textline_ = "";
	string temp_     = "";
	int line_        = 0;

	for (int i = 0; i < Text_File.size(); i++)
	{
		//Getting the line number and getting rid of the "Line String"
		++line_;
		string key_ = "Line " + to_string(line_) + ": ";
		size_t L_ine = Text_File[i].find(key_);
		if (L_ine != string::npos)
		{
			Text_File[i] = Text_File[i];
			Text_File[i].erase(L_ine, key_.length());
		}

		next_token(_id, _key, _operation, Text_File[i], to_string(line_));
	}
}
#pragma endregion Region_Class_Parser_A2
