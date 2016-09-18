// RoughLexer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <vector>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <ctype.h>
#include <cctype>
#include <algorithm>
using namespace std;

std::vector<std::string> parseID(std::vector<std::string> parseStack);
std::vector<std::string> parseKey(std::vector<std::string> parseStack);
std::vector<std::string> parseOp(std::vector<std::string> parseStack);

//Finds non alphabet characters and parses them.
std::vector<std::string> parseID(std::vector<std::string> parseStack)
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
std::vector<std::string> parseKey(std::vector<std::string> parseStack)
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
std::vector<std::string> parseOp(std::vector<std::string> parseStack)
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

int main()
{
	std::vector<std::string> A2RuleSet;

	//Reads in the A2 Lexicon ruleset and puts it into A2RuleSet variable. 
	//Returns error if unable to open text file with rules. 
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

	// Calls the parsing functions and translators. 
	std::vector<std::string> A2iD_ = parseID(A2RuleSet);
	std::vector<std::string> A2Key_ = parseKey(A2RuleSet);
	std::vector<std::string> A2Op_ = parseOp(A2RuleSet);

//------------------------------------------------------------------------------
	std::string Textword_ = "";
	std::string Textline_ = "";
	std::vector<std::string> dummyText;

	int at_Line = 0;
	int number_of_lines = 0;

	//Reads in the A2 Lexicon ruleset and puts it into A2RuleSet variable. 
	//Returns error if unable to open text file with rules. 
	string dummyline = "";
	ifstream dummyfile("DummyText.txt");
	if (dummyfile.is_open())
	{
		while (getline(dummyfile, dummyline))
		{
			++number_of_lines;
			string temp_ = "Line " + to_string(number_of_lines) + ": ";
			remove_if(dummyline.begin(), dummyline.end(), isspace);
			dummyText.push_back(temp_ + dummyline);
		}
		dummyfile.close();
	}
	else cout << "Unable to open file";

	for (int i = 0; i < dummyText.size(); i++)
	{

	}

	int line_ = 0;
	for (int i = 0; i < dummyText.size(); i++)
	{
		++line_;
		string key_  = "Line " + to_string(line_) + ": ";
		size_t L_ine = dummyText[i].find(key_);
		if (L_ine != string::npos)
		{
			//-----------------------++++
			string temp_ = dummyText[i];
			temp_.erase(L_ine, key_.length());
			for (int j = 0; j < A2Op_.size(); j++)
		    {
				//Modify for more then one of the keyword.
				size_t found = temp_.find(A2Op_[j]);
				if (found != string::npos)
				{
					cout << "(Tok: id= " << A2iD_[j] << "line= " << line_ << " " << A2Key_[j] << "str= " << "\"" << A2Op_[j] << "\"" << ")" << endl;
				}
			}
		}

	}


	std::cin.ignore();
	std::cin.ignore();

	return 0;
}
