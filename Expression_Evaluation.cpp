#include<iostream>
#include<stack>
using namespace std;

int operatorPreference(char op);
int binaryOperation(int a, int b, char op);
void calculate(std::stack<int> & newValues, std::stack<char> & newOps);
bool evaluate(const char *expression, int &result);

int main() 
{
    int res;
    //const char * exp;
    //const char * exp = "-1 + 3";
    //const char * exp = "(1 + 3) * 2";
    //const char * exp = "(4 * 2) + 6";
    const char * exp = "4 + (12 / (1 + 2))";
    //const char * exp = "(1 + (12 * 2)";
    //const char * exp = "17 + 3 * 4";
    //const char * exp = "(6 / 0)";
    //const char * exp = "(1 + 3) / (2 + 0) * (8 - 3)";
    //const char* exp = "(1 + (12 + 3 * 2))";
    //const char* exp = "13 - -2";
    //const char* exp = "-1 + 3";
    evaluate(exp, res) ? cout<<"Result = "<<res<<endl : cout<<"Invalid Expression" ;
    return 0;
}

bool evaluate(const char *expression, int &result)
{
    int leftBrace, rightBrace;
    leftBrace = rightBrace = 0;
    
    //return value from this method
    bool retVal = false;
    
    //converting const char * to std::strinf to use c++ idioms
    std::string tokens = expression;
    
    //if expression is empty or null, return false
    if(expression == nullptr || expression == "")
        return false;
        
    // this condition is specially for the 1st token
    // if the expression starts with ),*, +, / 
    // then return false
    if(*expression == 41 || *expression == 42 || *expression == 43 || *expression == 47 )
        return false;

    // purpose of this while loop to check if any non-valid character
    // is present then dont iteratre, just return false  
    while(*expression != '\0')
    {
        //
        if(*expression != 32 &&  *expression < 40 || *expression > 58 || *expression == 44 || *expression == 46)
        {
            return false;
            break;
        }
        else
        {
            //counting left brace and right brace
            if(*expression == 40) leftBrace++;
            if(*expression == 41) rightBrace++;
            retVal = true;
        }
        expression++;
    }
    
    // if any extra brace is present then its invalid expression, return
    if(leftBrace != rightBrace)
        return false;
    
    int minus = 1; // crated for checking -ve number
    stack <int> values; //created stack to store numbers only
    stack <char> ops; // created stack to store operators and braces
    for(int i = 0; i < tokens.length(); i++)
    {
        //temporary variable to check -ve number 
        int x = i + 1; 
        
        //skip if space encountered
        if(tokens[i] == ' ') 
            continue;
            
        // checking for left brace i.e. (
        else if(tokens[i] == '(')
        {
            ops.push(tokens[i]);
        }
        
        //if there is -ve number example -5 so i am checking 2 consequitive token    
        else if(tokens[i] == '-' && isdigit(tokens[x])) 
        {
            minus = -1; // set -1 to minus so that it will used in next iteration
        }
        
        // check if the token is number or digit
        else if(isdigit(tokens[i])) 
        {
            int val = 0;
            while(i < tokens.length() && isdigit(tokens[i]))
            {
                val = (val*10) + (tokens[i]-'0'); //  
                i++;
            }
            val = minus * val; // this line is only for -ve number 
            values.push(val);
            i--;
            minus = 1; // reset the value for future iteration
        }
        
        // checking for left brace i.e. )
        else if(tokens[i] == ')')
        {
            //if right brace found, i am checking left brace ( 
            // to evaluate the expression inisde 2 brace 
            // example : (1 + 3 * 4)
            while(!ops.empty() && ops.top() != '(')
            {
                // till now numbers and operators are stored in stack ops and values 
                // as it is stack it will do LIFO so default operation will be done from right to left
                // but as per instructions, expression MUST be evaluated from left to right 
                // so i am creating new stack to store number and operators
                // parsing and calculation will happen from left to right
                // LOGIC START -- parsing from left to right 
                
                stack <int> newValues; // new stack to number
                stack <char> newOps; // new stack to store operator
                while (ops.top() != '(')
                {
                    newOps.push(ops.top());// get operator from old stack and push to new stack 
                    ops.pop();// remove operator from old stack
                    newValues.push(values.top()); // get number from old stack and push to new stack
                    values.pop();// remove number from old stack
                 }
                newValues.push(values.top());
                values.pop();
                while(!newOps.empty())
                {
                    calculate(newValues, newOps); 
                }
                // LOGIC END -- parsing from left to right
                
                // pushing result to original values stack again
                values.push(newValues.top());
            }
            if(!ops.empty())
                ops.pop(); // as previous operator already evaluated, so removing last previous operator
        }
        else
        {
            //insert operator into ops stack by checking condition that stack is not empty and operator preference
            while(!ops.empty() && operatorPreference(ops.top()) >= operatorPreference(tokens[i]))
            {
                // LOGIC START -- parsing from left to right
                stack <int> newValues;
                stack <char> newOps;
                while (!ops.empty())
                {
                    newOps.push(ops.top());
                    ops.pop();
                }
                while (!values.empty())
                {
                    newValues.push(values.top());
                    values.pop();
                }
                while(!newOps.empty())
                {
                    calculate (newValues, newOps);
                }
                // LOGIC END -- parsing from left to right 
                
                
                values.push(newValues.top());
            }
            
            //pushing binary operator i.e. + - * /
            ops.push(tokens[i]);
        }
    }
    
    // by this all expression insdie braces are evaluated, no more brace will be present in expression
    // example : 10 + 4 * 3
    // as i have to calculate from left to right i am performing the above method again
    // LOGIC START -- parsing from left to right 
    stack <int> newValues;  
    stack <char> newOps; 
    while (!ops.empty())
    {
        newOps.push(ops.top());
        ops.pop();
    }
    while (!values.empty())
    {
        newValues.push(values.top());
        values.pop();
    }
    while(!newOps.empty())
    {
        calculate (newValues, newOps);
    }
    // LOGIC END -- parsing from left to right 
    
    // final result 
    result = newValues.top();
    return retVal;
}

// this function is returning operator preference
int operatorPreference(char op)
{
    if(op == '+'||op == '-')
        return 1;
    if(op == '*'||op == '/')
        return 2;
    return 0;
}

// this function is doing mathematical cal according to operator provided
int binaryOperation(int a, int b, char op)
{
    if(op == '+')
        return a + b;
    else if(op == '-')
        return a - b;
    else if(op == '*')
        return a * b;
    else if(op == '/')
    {
        // sometime user is give input 0 as divider, so it will crash
        // i have handled exception 
        if(b == 0)
            throw runtime_error("The given number Can't divide by 0 \n");
        return a / b;
    }
    return 0;
}

void calculate (stack<int> & newValues, stack<char> & newOps)
{
    //simple logic to pop 2 number from values stack and 1 corespoding operator to do calculate
    
    // get 1st element
    int val1 = newValues.top();
    newValues.pop();
    
    // get 2nd element
    int val2 = newValues.top();
    newValues.pop();
    
    // get operator symbol
    char op = newOps.top();
    newOps.pop();
       
    // as this method may throw exception so i am calling inside try method    
    try 
    {
        newValues.push(binaryOperation(val1, val2, op));
    }
    catch(runtime_error& error)
    {
        cout << "Exception occurred : "<< error.what() << endl;
    }
}