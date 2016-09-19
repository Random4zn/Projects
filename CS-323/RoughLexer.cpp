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

	for (int i = 0; i < A2_Lexer.size(); i++)
	{
		//cout << A2_Lexer[i] << endl;
	}

//------------------------------------------------------------------------------
	string Textword_ = "";
	string Textline_ = "";
	vector<std::string> dummyText;

	int at_Line = 0;
	int number_of_lines = 0;

	//Reads in the A2 Lexicon ruleset and puts it into A2RuleSet variable. 
	//Returns error if unable to open text file with rules. 
	string dummyline  = "";
	string text_ = "";
	ifstream dummyfile("DummyText.txt");
	if (dummyfile.is_open())
	{
		while (getline(dummyfile, dummyline))
		{
			++number_of_lines;
			string temp_ = "Line " + to_string(number_of_lines) + ": ";
			remove_if(dummyline.begin(), dummyline.end(), isspace);

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
			dummyText.push_back(temp_ + dummyline);

		}
		dummyfile.close();
	}
	else cout << "Unable to open file";

	for (int i = 0; i < dummyText.size(); i++)
	{
		//cout << dummyText[i] << endl;
	}
	vector<int>line_track;
	for (int i = 0; i < number_of_lines; i++)
	{
		line_track.push_back((i+1));
	}


	int line_ = 0;
	bool intFlag   = false;
	bool signFlag  = false;
	bool floatFlag = false;
	string temp_digit = "";
	for (int i = 0; i < dummyText.size(); i++)
	{
		//Getting the line number and getting rid of the "Line String"
		++line_;
		string key_  = "Line " + to_string(line_) + ": ";
		size_t L_ine = dummyText[i].find(key_);
		if (L_ine != string::npos)
		{
			//-----------------------++++
			//Parsing of the string 
			string temp_ = dummyText[i];
			int floatcount_ = 0;
			temp_.erase(L_ine, key_.length());
			for (int j = 0; j < temp_.length(); j++)
		    {
				if (temp_[j] == ';') { break; } //end of line count

				size_t found_Float = temp_.find(".");
				if (found_Float != string::npos)
				{
					floatFlag = true;
					//Modify for more then one of the keyword.
					//Next_Token() function would go here.
					//TRY BLOCK
					try
					{
						if (isdigit(temp_[j]) && (temp_[j] != ';'))
						{
							if (floatFlag)
							{
								for (int l = j; l < temp_.length(); l++)
								{
									if (temp_[l] == ';') { break; } //end of line count
									if (temp_[l] == ' ') { break; } //space count

									++floatcount_;
									temp_digit += temp_[l];
									j = l;
								}
							}

						}
					}
					catch (int Error)
					{
						cout << "Bob" << endl;
					}
				}
				
				//Modify for more then one of the keyword.
				//Next_Token() function would go here.
				//TRY BLOCK
				if (!floatFlag)
				{
					try
					{
						if (isdigit(temp_[j]) && (temp_[j] != ';'))
						{
							intFlag = true;
							temp_digit += temp_[j];
							//No out of bounds
							//Checks to see if there is a sign in leading number.
							//OPTIMIZE THIS LATER ()
							if ((j - 1) >= 0)
							{
								if (temp_[(j - 1)] == '-')
								{
									signFlag = true;
									//sign would go here
									//cout << temp_[(j - 1)] << endl;

								}
							}

						}
					}
					catch (int error)
					{
						cout << "Error code: " << error << endl;
					}
				}

				size_t found = temp_.find(A2Op_[j]);
				//cout << A2Op_[j] << endl;
				if (found != string::npos)
				{
					//cout << "(Tok: id= " << A2iD_[j] << "line= " << line_ << " " << "str= " << "\"" << A2Op_[j] << "\"" << ")" << endl;
				}
			}
		}

		if ((intFlag) && !(floatFlag))
		{
			cout << "(Tok: id= " << A2iD_[0] << "line= " << line_ << " " << "str= " << "\"" << temp_digit << "\"" << ")" << endl;
			temp_digit.clear();
			intFlag = false;
		}
		else if (!(intFlag) && (floatFlag))
		{
			cout << "(Tok: id= " << A2iD_[1] << "line= " << line_ << " " << "str= " << "\"" << temp_digit << "\"" << ")" << endl;
			temp_digit.clear();
			intFlag = false;
			floatFlag = false;
		}

	}


	std::cin.ignore();
	std::cin.ignore();

	return 0;
}
