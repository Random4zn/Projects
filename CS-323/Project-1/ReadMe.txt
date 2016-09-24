/*****************************************************************
* PROJECT - A2 LEXICON PARSER
* ----------------------------------------------------------------
* Team Name : DeMorgan's_loss.
* Authors   : Can Dalgir, David Luong.
* Project   : 1
* Style     : Pragmatic / Pair Programming
* IDE       : Visual Studio 2012 Professional
* Language  : C++ / Visual C++
*
* Project Folder -> RoughLexer
*
* ----------------------------------------------------------------
* CONTACT INFORMATION
* ----------------------------------------------------------------
* Can Dalgir e-mail: cdalgir@csu.fullerton.edu
* David Luong e-mail: davidluong@csu.fullerton.edu
*
* ----------------------------------------------------------------
* DESCRIPTION
* ----------------------------------------------------------------
* This program is designed to handle the A2 programming language
* lexicon. The program is additionally designed to handle dynamic
* lexer ruleset(s) to avoid further programming language 
* transformation(s).
*
* ---------------------------------------------------------------- 
* A2 Lexicon Usage Guidelines
* ---------------------------------------------------------------- 
* The current A2 Lexicon program requires you to edit one of the
* three test case files 'TestCase_1.txt'..etc.. in order to test
* the A2 Lexigraphical analysis of the program.
*
* ---------------------------------------------------------------- 
* TEST CASE SUCCESS
* ----------------------------------------------------------------
* The current programs state of passing the test cases designed by
* the A2 Lexicon project '.pdf' file.
* 
* Test Case #1: prog main { print( "ASCII:", " A= ", 65, " Z= ", 90 ); }
* Parsing Rate             : 100%
* Syntatical Analysis Rate : 100%
* Completion Rate          : 100%
*
* Test Case #2: prog main { // Find the circumference of a circle.
*                 pi = 3.14;
*                 print( "Input radius> " );
*                 rx = input ( float );
*                 circum = 2 * pi * rx;
*                 print( "Circumf= ", circum );
*                }
* Parsing Rate             : 100%
* Syntatical Analysis Rate : 85%
* Completion Rate          : 92.5%
*
* Test Case #3: prog main { // Find the hypotenuse of a right triangle.
*                 print( "Input legs> " );
*                 a = input( int );
*                 b = input( int );
*                 print( "Hypotenuse= ", ( a * a + b * b ) ^ 0.5 );
*                }
*
* Parsing Rate             : 90%
* Syntatical Analysis Rate : 80%
* Completion Rate          : 85%
*
* Overall Completion Rate  : 92.6%
* ---------------------------------------------------------------- 
* BUGS
* ----------------------------------------------------------------
* Syntactical Errors:
* The current structure of the program strugles in the linear
* fashion of determining the correct output stack for 'id''+''id'
* structure.
* 
* Error Handling:
* Currently there is no feature to handle the errors rather than
* a try and catch statement for out-of-bounds check.
*
* ----------------------------------------------------------------
* CLASS | RuleSet_A2
* ----------------------------------------------------------------
* The designed class is exclusively for reading the A2 lexers
* ruleset(s) for programming the A2 lexer/parser.
* ----------------------------------------------------------------
*         |-ruleset
*         |---> A2_Lexer
*         |---> A2iD_
*         |---> A2Key_
*         |---> A2Op_
*
* ----------------------------------------------------------------
* CLASS | Parser_A2
* ----------------------------------------------------------------
* The designed class is exclusively for parsing the desired
* input from the user through a provided '.txt' file.
* ----------------------------------------------------------------
* CLASS | Parser_A2
*         |-parser_
*         |---> File_Text
*
******************************************************************/

