#include "A2Lexer.h"

//Reads in the A2 Lexicon ruleset and puts it into A2RuleSet variable. 
//Returns error if unable to open text file with rules. 
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


//Finds non alphabet characters and parses them.
vector<string> RuleSet_A2::parseID(vector<string> parseStack)
{
	string tempP_ = "";
	string iD_ = "";
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

//parses alphabet and equal signs
vector<string> RuleSet_A2::parseKey(vector<string> parseStack)
{
	string tempP_ = "";
	string Key_ = "";
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

//parses operators functions 
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

//A2 Parser
vector<string> Parser_A2::read_Text(string File_Name)
{
	//Reads in the A2 Lexicon ruleset and puts it into A2RuleSet variable. 
	//Returns error if unable to open text file with rules. 
	string dummyline = "";
	string text_ = "";
	ifstream dummyfile("DummyText.txt");
	if (dummyfile.is_open())
	{
		while (getline(dummyfile, dummyline))
		{
			++number_of_lines;

			string temp_ = "Line " + to_string(number_of_lines) + ": ";
			//IF STATEMENT - This section is designed to remove any comments
			//               written by the user. This is due to the fact that
			//               we are allowed to treat comments as whitespace up to newline char;
			//
			// FURTHER TESTING NEEDED ( )
			size_t comment_ = dummyline.find("//");
			if (comment_ != string::npos)
			{
				dummyline.erase(comment_, dummyline.length());
			}
			//Line Vector: Overall structure of the program stack.
			Text_File.push_back(temp_ + dummyline);
		}
		dummyfile.close();
	}
	else cout << "Unable to open file";

	return Text_File;
}

string Parser_A2::int_check(string line_)
{
	string temp_digit = "";
	for (int i = 0; i < line_.length(); i++)
	{
		//TRY BLOCK
		try
		{
			if (isdigit(line_[i]) && (line_[i] != ';'))
			{
				temp_digit += line_[i];
			}//END OF INTEGERCHECK-IF-STATEMENT
		}//END OF TRY
		catch (int Error) { cout << "Error code: " << Error << endl; }
	}

	return temp_digit;
}

string Parser_A2::float_check(string line_)
{
	bool floatFlag    = false;
	string temp_digit = "";
	//FloatLoop
	for (int j = 0; j < line_.length(); j++)
	{
		size_t found_Float = line_.find(".");
		if (found_Float != string::npos)
		{
			floatFlag = true;
			//Modify for more then one of the keyword.
			//Next_Token() function would go here.
			//TRY BLOCK
			try
			{
				if (isdigit(line_[j]) && (line_[j] != ';'))
				{
					if (floatFlag)
					{
						for (int l = j; l < line_.length(); l++)
						{
							j = l;
							if (line_[l] == ';') { break; } //end of line count
							if (line_[l] == ' ') { break; } //space count
							temp_digit += line_[l];
						}
					}
				}
			}
			catch (int Error)
			{
				cout << "Error code: " << Error << endl;
			}
		}
	}

	return temp_digit;
}

string Parser_A2::token_match(vector<string> _id, vector<string> _key, vector<string> _operation, string _line, string _line_num)
{
	string temp_string = "";
	string delim_check = "";

	string float_digit = "";
	string int_digit = "";

	float _float_check = 0.0;
	vector<string> _float;
	vector<float> _out_float;

	_line.erase(remove_if(_line.begin(), _line.end(), isspace), _line.end());
	for (int i = 0; i < _line.length(); i++)
	{
		temp_string += _line[i];
		delim_check  = _line[i];

		float_digit = float_check(temp_string);
		int_digit   = int_check(temp_string);

		cout << float_digit << endl;

		//working on diz.
		if (!(float_digit.empty()))
			_float.push_back(float_digit);

		//Unpaired Delimiters Check
		for (int index = 0; index < 6; index++)
		{
			if (delim_check == _operation[index])
			{
				cout << "(Tok: id= " << _id[index] << "line= " << _line_num << " " << "str= " << "\"" << _operation[index] << "\"" << ")" << endl;
				temp_string.clear();
				delim_check.clear();
				break;
			}
		}

		//Keyword Check
		for (int index = 6; index < 20; index++)
		{
			if (temp_string == _operation[index])
			{
				cout << "(Tok: id= " << _id[index] << "line= " << _line_num << " " << "str= " << "\"" << _operation[index] << "\"" << ")" << endl;
				temp_string.clear();
				delim_check.clear();
				break;
			}
		}

		//Paired Delimiters Check
		for (int index = 21; index < 30; index++)
		{
			if (delim_check == _operation[index])
			{
				cout << "(Tok: id= " << _id[index] << "line= " << _line_num << " " << "str= " << "\"" << _operation[index] << "\"" << ")" << endl;
				temp_string.clear();
				delim_check.clear();
				break;
			}
		}

		//Other Punctuation Check
		for (int index = 30; index < 40; index++)
		{
			if (delim_check == _operation[index])
			{
				if ((!float_digit.empty()) && (delim_check != "."))
				{
					cout << "(Tok: id= " << _id[index] << "line= " << _line_num << " " << "str= " << "\"" << _operation[index] << "\"" << ")" << endl;
				}
				else if ((float_digit.empty()) && (delim_check == "."))
				{
					cout << "(Tok: id= " << _id[index] << "line= " << _line_num << " " << "str= " << "\"" << _operation[index] << "\"" << ")" << endl;
				}

				if (float_digit.empty())
				{
					temp_string.clear();
					delim_check.clear();
					break;
				}

			}
		}
	}

	return temp_string;
}

void Parser_A2::Parser_A2Lexi(vector<string> _id, vector<string> _key, vector<string> _operation, vector<string> Text_File)
{
	string Textword_ = "";
	string Textline_ = "";
	string temp_ = "";

	int line_ = 0;
	int floatcount_ = 0;
	bool intFlag = false;
	bool signFlag = false;
	bool floatFlag = false;

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

		token_match(_id, _key, _operation, Text_File[i], to_string(line_));
	}
}
