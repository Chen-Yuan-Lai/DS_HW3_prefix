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
            mystack.push(a[i]);
        }
    }
    char NextToken()
    {
        char top = mystack.top();
        mystack.pop();
        return top;
    }
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
    else if (a == '*' || a == '/' || a = '%')
        return 2;
    else if (a == '+' || a == '-')
        return 3;
    else if (a == '<' || a == '<=' || a == '>=' || a == '>')
        return 4;
    else if (a == '==' || a == !=)
        return 5;
    else if (a == '&&')
        return 6;
    else if (a == '||')
        return 7;
    else if (a == '#' || a == '(')
        return 8;
}

int icp(char a)
{
    if (a == ')')
        return 0;
    else if (a == '!')
        return 1;
    else if (a == '*' || a == '/' || a = '%')
        return 2;
    else if (a == '+' || a == '-')
        return 3;
    else if (a == '<' || a == '<=' || a == '>=' || a == '>')
        return 4;
    else if (a == '==' || a == !=)
        return 5;
    else if (a == '&&')
        return 6;
    else if (a == '||')
        return 7;
}

void Posfix(Expression e)
{
    // reverse the expression
    e = e.reverse();

    stack<char> s;
    for (char x = e.NextToken(); x != '#'; x = e.NextToken())
    {
        if (x != '!' ||
            x != '*' ||
            x != '/' ||
            x != '%' ||
            x != '+' ||
            x != '-' ||
            x != '<' ||
            x != '<=' ||
            x != '>=' ||
            x != '>' ||
            x != '==' ||
            x != '!=' ||
            x != '&&' ||
            x != '||')
        {
            cout << x;
        }
        else if (x == ')')
        { // unstack untill '('
            for (; s.top() != '('; s.pop())
            {
                cout << s.top();
            }
            s.pop(); // unstack '('
        }
        else
        { // x is an operator
            for (; isp(s.top()) <= icp(x); s.pop())
            {
                cout << s.top();
            }
            s.push(x)
        }
    }
    // end of expression; empty the stack
    for (; !s.empty(); s.pop())
        cout << s.top();
    cout << endl;
}

int main()
{
    Expression e("A*B+C/D");
    e.reverse();

    while (1)
    {
        char token = e.NextToken();
        if (token == '#')
        {
            break;
        }
        cout << token << " ";
    }
    cout << endl;
}