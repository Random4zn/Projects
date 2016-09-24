/*****************************************************************
* PROJECT - A2 LEXICON PARSER
* ----------------------------------------------------------------
* Team Name : DeMorgan's loss.
* Authors   : Can Dalgir, David Luong.
* Project   : 1
* Style     : Pragmatic
* ----------------------------------------------------------------
* DESCRIPTION
* ----------------------------------------------------------------
* This program is designed to handle the A2 programming language
* lexicon. The program is additionally designed to handle dynamic
* lexer ruleset(s) to avoid further programming language 
* transformation(s).
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
* Floating Point Errors:
* There is a duplication of index 
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
