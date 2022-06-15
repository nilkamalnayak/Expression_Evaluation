# Expression_Evaluation
**C++ Program that evaluates simple expression **

**Description:-**
initially i am going throug -ve scenarios where if any non valid character will be present then directly it will return as false.
like in below example, there is 1 extra right paranthesis is presetn in last token.
so before doing memory allocation and do evaluation, its better than i ll direct called a while loop which will find out extra right paranthesis and treat this expression as invalid

**Sample Expression :** (1 + 2) * 4 + (8 / 2) * 3 + (6 - 4) )

**Test Case Scenario:**
1. if the expression is null ptr or not
2. As the result of expression in integer which is mentioned in prototype of function below, i have taken integer (instead taking long int)
       bool evaluate(const char *expression, int &result)
3. the 1st character in expression can not be +, *, /, ) and treated as non=valid character.
4. if the expression contains empty string.
5. is there any negative number is present i.e. -5, -43 etc..
6. it should throw exception if any number divide by 0 and handled properly.
7. left paranthesis ( and right paranthesis ) should be balanced.
8. pop and push operation done after checking size.
9. check for non valid characters i.e. except +, -, *, /,(,)
10. ignore whitespace
11. evaluation takes place left to right (no BODAMS rule applied)

**Example:**

    //const char * exp = "-1 + 3";
    //const char * exp = "(1 + 3) * 2";
    //const char * exp = "(4 * 2) + 6";
    //const char * exp = "4 + (12 / (1 + 2))";
    //const char * exp = "(1 + (12 * 2)";
    //const char * exp = "17 + 3 * 4";
    //const char * exp = "(6 / 0)";
    //const char * exp = "(1 + 3) / (2 + 0) * (8 - 3)";
    //const char* exp = "(1 + (12 + 3 * 2))";
    //const char* exp = "13 - -2";
    //const char* exp = "-1 + 3";



**NOTE :** the below scenario is not working. it is crashing.

**Known Issue : **//const char* exp = "1 + 2 ) + ( 5"
