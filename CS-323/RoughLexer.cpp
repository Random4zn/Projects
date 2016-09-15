// RoughLexer.cpp : Defines the entry point for the console application.
//

#include <string>
#include <vector>
#include <iomanip>
#include <iostream>

std::string LibComp(std::vector<std::string> stackP);
std::string NextToken(std::string Tok_);

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

	for (int i = 0; i <= testS.length(); i++)
	{
		if (testS[i] != ' ')
		{
			testW += testS[i];
		}
		else
		{
			std::cout << testW << std::endl;
			stackP.push_back(testW);
			testW.clear();
		}
	}

	std::string Tok_ = LibComp(stackP);

	std::cout << Tok_ << std::endl;

	//while (!eof())
	//{
	//Generate line
	//Grab line string
	//Split the string
	//DFS //finite state machine
	//Generate output
	//}

	std::cin.ignore();
	std::cin.ignore();

	return 0;
}

