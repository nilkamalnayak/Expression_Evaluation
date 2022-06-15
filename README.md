# Expression_Evaluation
**C++ Program that evaluates simple expression **

**Description:-**
The main purpose of this application is to evaluate simple expression.
At the same time it will handle all scenarios including +ve as well -ve test scenarios.
The evaluates() function takes input as expression string and result. once evaluation will be done, it updates the result variable and returns true.
If there will be any non-valid character presents or common error occurs, it will handle and return false.

so before doing expression evaluation i have checked few -ve test scenario.

**Example :**

**Sample Expression :** (1 + 2) * 4 + (8 / 2) * 3 + (6 - 4) **)**                                                               

In the above example, if you see, there is 1 extra right paranthesis is present in last.
instead of evaluating (which requires memory allocation and calling functions) the expression  from begining to till last and in last it will find as non-valid character.
So here i am using a while loop to check that condition without doing evaluation which saves memory as well as time.

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
