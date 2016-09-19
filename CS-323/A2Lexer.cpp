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
