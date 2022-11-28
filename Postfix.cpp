#include <iostream>
#include <stack>
#include <string.h>
using namespace std;

class Expression
{
public:
    template <size_t n>
    Expression(const char (&a)[n])
    {
        int size = n;
        mystack.push('#');
        // a[7] is '\0', we should exclude this char
        for (int i = size - 2; i >= 0; i--)
        {
            if (a[i] == ' ')
                continue;
            mystack.push(a[i]);
        }
    }
    char NextToken()
    {
        char top = mystack.top();
        mystack.pop();
        return top;
    }
    int size() const { return mystack.size(); }
    void reverse()
    {
        stack<char> re;
        re.push('#');
        for (char x = NextToken(); x != '#'; x = NextToken())
        {
            if (x == '(')
            {
                x = ')';
            }
            else if (x == ')')
            {
                x = '(';
            }
            re.push(x);
        }
        mystack = re;
    }

private:
    stack<char> mystack;
};

int isp(char a)
{
    if (a == '!')
        return 1;
    else if (a == '*' || a == '/' || a == '%')
        return 2;
    else if (a == '+' || a == '-')
        return 3;
    else if (a == '<' || a == '>')
        return 4;
    else if (a == '#' || a == '(')
        return 8;
    return -1;
}

int icp(char a)
{
    if (a == '(')
        return 0;
    else if (a == '!')
        return 1;
    else if (a == '*' || a == '/' || a == '%')
        return 2;
    else if (a == '+' || a == '-')
        return 3;
    else if (a == '<' || a == '>')
        return 4;
    return -1;
}

void Prefix(Expression e)
{
    // reverse the expression
    e.reverse();

    stack<char> s;
    stack<char> output;
    s.push('#');
    output.push('#');
    for (char x = e.NextToken(); x != '#'; x = e.NextToken())
    {
        if ((x >= 'a' && x <= 'z') || (x >= 'A' && x >= 'Z') || (x >= '0' && x <= '9'))
        {
            output.push(x);
        }
        else if (x == ')')
        { // unstack untill '('
            for (; s.top() != '('; s.pop())
            {
                output.push(s.top());
            }
            s.pop(); // unstack '('
        }
        else
        { // x is an operator
            for (; isp(s.top()) < icp(x); s.pop())
            {
                output.push(s.top());
            }
            s.push(x);
        }
    }
    // end of expression; empty the stack
    for (; s.top() != '#'; s.pop())
    {
        output.push(s.top());
    }
    // print the expression
    for (; output.top() != '#'; output.pop())
    {
        cout << output.top() << " ";
    }
    cout << endl;
}

int main()
{
    Expression e1("A*B/C");
    Prefix(e1);
    Expression e2("A / B - C + D * E - A * C");
    Prefix(e2);
    Expression e3("A * (B + C) / D - G");
    Prefix(e3);
}
