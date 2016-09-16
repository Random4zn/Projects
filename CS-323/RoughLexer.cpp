// RoughLexer.cpp : Defines the entry point for the console application.
//

#include <string>
#include <vector>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <ctype.h>
using namespace std;

std::vector<std::string> parseID(std::vector<std::string> parseStack);
std::vector<std::string> parseKey(std::vector<std::string> parseStack);
std::vector<std::string> parseOp(std::vector<std::string> parseStack);

std::vector<std::string> parseID(std::vector<std::string> parseStack)
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

std::vector<std::string> parseKey(std::vector<std::string> parseStack)
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


std::vector<std::string> parseOp(std::vector<std::string> parseStack)
{
	string tempP_ = "";
	string Key_   = "";
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
	std::string testS = "'print(\"Hypotenuse = \", ( a * a + b * b ) ^ 0.5 )\;'";
	std::string testW = "";
	std::vector<std::string> stackP;
	std::vector<std::string> A2RuleSet;

	for (int i = 0; i <= testS.length(); i++)
	{
		if (testS[i] != ' ')
		{
			testW += testS[i];
		}
		else
		{
			stackP.push_back(testW);
			testW.clear();
		}
	}

	string line;
	ifstream myfile("A2LexiconKey.txt");
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			A2RuleSet.push_back(line);
		}
		myfile.close();
	}
	else cout << "Unable to open file";

	std::vector<std::string> A2iD_  = parseID(A2RuleSet);
	std::vector<std::string> A2Key_ = parseKey(A2RuleSet);
	std::vector<std::string> A2Op_  = parseOp(A2RuleSet);

	/* for (int i = 0; i < A2iD_.size(); i++)
	{
		cout << A2iD_[i] << endl;
	} */

	/*for (int i = 0; i < A2Key_.size(); i++)
	{
		cout << A2Key_[i] << endl;
	}*/

	/*for (int i = 0; i < A2Op_.size(); i++)
	{
		cout << A2Op_[i] << endl;
	}*/

	for (int i = 0; i < A2Op_.size(); i++)
	{
		size_t found = testS.find(A2Op_[i]);
		if (found != string::npos)
		{
			cout << A2iD_[i] << "" << A2Key_[i] << " "<< A2Op_[i] << endl;
		}
	}



	std::cin.ignore();
	std::cin.ignore();

	return 0;
}
