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

string Parser_A2::int_check(string line_, int _pos)
{
	string temp_digit = "";
	for (int i = (_pos+1); i < line_.length(); i++)
	{
		//TRY BLOCK
		try
		{
			if (isdigit(line_[i]) && (line_[i] != ';'))
			{
				temp_digit += line_[i];
			}//END OF INTEGERCHECK-IF-STATEMENT
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

string Parser_A2::token_match(vector<string> _id, vector<string> _key, vector<string> _operation, string _line, string _line_num)
{
	string temp_string = "";
	string temp_id = "";
	string temp_s = "";
	string delim_check = "";
	string int_digit = "";
	vector<string> id_string;


	_line.erase(remove_if(_line.begin(), _line.end(), isspace), _line.end());
	for (int i = 0; i < _line.length(); i++)
	{
		temp_string += _line[i];
		delim_check  = _line[i];
		
		//String Check
		if (_line[i] == '"')
		{
			for (int index = (i+1); index < _line.length(); index++)
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
			temp_string.clear();
			delim_check.clear();
		}

		//Unpaired Delimiters Check
		for (int index = 4; index < 6; index++)
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
		
		for (int index = 0; index < id_string.size(); index++)
		{
			if (temp_string == id_string[index])
			{
				cout << "(Tok: id= " << _id[0] << "line= " << _line_num << " " << "str= " << "\"" << id_string[index] << "\"" << ")" << endl;
				temp_string.clear();
				delim_check.clear();
				break;
			}
		}

		string temp_du = "";
		//Other Punctuation Check
		for (int index = 30; index < 40; index++)
		{
			if (delim_check == _operation[index])
			{
				//Checkerino Peporino
				if (delim_check == "=")
				{
					for (int f = 0; f < i; f++)
					{
						if (isalpha(_line[f]))
						{
							temp_id += _line[f];
						}
					}

					if (!(temp_id.empty()))
					{
						//Still need to edit out the semi-colon stuff.
						cout << "(Tok: id= " << _id[0]  << "line= " << _line_num << " " << "str= " << "\"" << temp_id << "\"" << ")" << endl;
						cout << "(Tok: id= " << _id[33] << "line= " << _line_num << " " << "str= " << "\"" << delim_check << "\"" << ")" << endl;
						if (!(temp_id.empty()))
						{
							id_string.push_back(temp_id);
						}
						temp_id.clear();
						temp_string.clear();
						delim_check.clear();
					}

					//FLOAT AND INT CHECK
					temp_du = int_check(_line, i);
					size_t found_Float = temp_du.find("_float_");
					size_t found_Int = temp_du.find("_int_");
					//search for period with limit.
					if (found_Float != string::npos)
					{
						string temp_f = "_float_";
						temp_du.erase(found_Float, temp_f.length());
						if (!(temp_du.empty()))
						{
							//Still need to edit out the semi-colon stuff.
							cout << "(Tok: id= " << _id[2] << "line= " << _line_num << " " << "str= " << "\"" << temp_du << "\"" << " float=" << temp_du << ")" << endl;
							temp_string.clear();
							delim_check.clear();
						}
					}
					//search for period with limit.
					else if (found_Int != string::npos)
					{
						string temp_i = "_int_";
						temp_du.erase(found_Int, temp_i.length());
						if (!(temp_du.empty()))
						{
							//Still need to edit out the semi-colon stuff.
							cout << "(Tok: id= " << _id[1] << "line= " << _line_num << " " << "str= " << "\"" << temp_du << "\"" << " int=" << temp_du << ")" << endl;
							temp_string.clear();
							delim_check.clear();
						}
					}

				}

				break;
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
