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

std::string LibComp(std::vector<std::string> stackP);
std::string NextToken(std::string Tok_);
std::vector<std::string> parseID(std::vector<std::string> parseStack);

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

std::string LibComp(std::vector<std::string> stackP)
{
	std::string temp_ = "";
	if (!stackP.empty())
	{
		for (int i = 0; i < stackP.size(); i++)
		{
			temp_ = NextToken(stackP[i]);
		}
	}


	//return "(Tok: id= <ID#> line= <line> str= “<token>” [int= <int> | float= <float>])";
	return temp_;
}

std::string NextToken(std::string Tok_)
{
	std::vector<std::string> Prag_;
	//Train the Prag_;

	if (!Prag_.empty())
	{
		for (int i = 0; i < Prag_.size(); i++)
		{
			if ((Tok_ == Prag_[i]) && (Prag_[i] == "print"))
			{
				return "ID:10, Print";
			}
		}
	}
	return "0";
}

int main()
{
	std::string testS = "'print\( \"Hypotenuse = \", ( a * a + b * b ) ^ 0.5 )\;'";
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


	std::vector<std::string> A2iD_ = parseID(A2RuleSet);

	for (int i = 0; i < A2iD_.size(); i++)
	{
		cout << A2iD_[i] << endl;
	}

	std::string Tok_ = LibComp(stackP);

	std::cin.ignore();
	std::cin.ignore();

	return 0;
}
