#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <iostream>
#include <string>
#include <cmath>
#include <sstream>

using namespace std;

double strtd(string& str)
{
    istringstream iss(str);
    double num;
    iss >> num;
    return num;
}

double strtd(string&& str)
{
    istringstream iss(str);
    double num;
    iss >> num;
    return num;
}

string dts(double num)
{
    stringstream ss;
    string str;
    ss << num;
    ss >> str;
    return str;
}

int character(char & s)
{
    if(s >= '0' && s <= '9')
    {
        return 0;
    }
    else if(s == '+' || s == '-' || s == '*' || s == '/' || s == '^')
    {
        return 1;
    }
    else if(s == '(' || s == ')' || s == '.')
    {
        return 2;
    }
    else
    {
        return 3;
    }
}

bool filter(string & s)
{
    int a = 0;
    for(int i = 0; i < s.size(); ++i)
    {
        if(character(s[i]) != 3)
        {
            if(character(s[i]) == 1 && ((i == 0 && s[i] != '-') || i == s.size() || (character(s[i+1]) != 0 && s[i+1] != '(') || (character(s[i-1]) != 0 && s[i-1] != ')' && s[i] != '-')))
            {
                cerr << "Error: Operational symbol is wrong" << endl;
                return false;
            }
            
            else if(s[i] == '.' && (i == 0 || i == s.size() || character(s[i+1]) != 0 || character(s[i-1]) != 0))
            {
                cerr << "Error: Decimal point is wrong" << endl;
                return false;
            }

            else if(s[i] == '/' && s[i+1] == '0')
            {
                cerr << "Error: Divisor = 0" << endl;
                return false;
            }

            else if(s[i] == '(')
            {
                if(s[i+1] != ')' )
                {
                    a = a+1;
                }
                else
                {
                    cerr << "Error: Empty brackets" << endl;
                    return false;
                }
            }

            else if(s[i] == ')' )
            {
                a = a-1;
            }
        }

        else
        {
            cerr << "Error: Exceptional character" << endl;
            return false;
        }

        if (a < 0)
        {
            cerr << "Error: Unusual brackets position" << endl;
            return false;
        }
    }

    if( a != 0)
    {
        cerr << "Error: Invalid brackets" << endl;
        return false;
    }
    return true;
}

class ExpressionTree
{
public:
    ExpressionTree() : root{nullptr}
    {}

    void makeEmpty()
    {
        makeEmpty(root);
    }

    ~ExpressionTree()
    {
        makeEmpty();
    }

    void insert(const string & s)
    {
        insert(s, root);
    }

    string calculate()
    {
        calculate(root);
        return root -> element;
    }

private:
    struct ExpressionNode
    {
        string element;
        ExpressionNode *left;
        ExpressionNode *right;

        ExpressionNode(const string & theElement, ExpressionNode *lt, ExpressionNode *rt) : element{theElement}, left{lt}, right{rt} {}
        ExpressionNode(string && theElement, ExpressionNode *lt, ExpressionNode *rt) : element{move(theElement)}, left{lt}, right{rt} {}
    };

    ExpressionNode *root;

    void insert(const string & s, ExpressionNode *&t)
    {
        if(t == nullptr)
            t = new ExpressionNode{s, nullptr, nullptr};
        else if(isPre(s) <= isPre(t -> element) && t->right != nullptr && (isPre(s) != 2 ||  isPre(t -> element) != 2))
        {
            insert(s, t -> left);
            t -> left -> left = t -> left -> right;
            t -> left -> right = t;
            t = t -> left;
            t -> right -> left = t -> left;
            t -> left = nullptr;
        }

        else if(isPre(s) <= isPre(t -> element) && t -> right == nullptr && (isPre(s) != 2 || isPre(t -> element) != 2))
        {
            insert(s, t -> right);
            t -> right -> right = t;
            t = t -> right;
            t -> right -> right = nullptr;
        }

        else if(isPre(s) == 2 && isPre(t -> element) == 2)
        {
            insert(s, t -> left);
        }

        else if(isPre(s) > isPre(t -> element) && t -> right != nullptr)
        {
            insert(s, t -> left);
        }

        else if(isPre(s) > isPre(t -> element) && t -> right == nullptr)
        {
            insert(s, t -> right);
        }
    }

    int isPre(string s)
    {
        if(s == "+" || s == "-")
        {
            return 0;
        }
        else if(s == "*" || s == "/") 
        {
            return 1;
        }
        else if(s == "^") 
        {
            return 2;
        }
        else 
        {
            return 3;
        }
    }

    void calculate(ExpressionNode *t)
    {
        if(character((t -> element)[0]) == 1 && t -> element.size() == 1 && !(t -> element == "/" && strtd(t -> left -> element) == 0))
        {
            calculate(t -> left);
            calculate(t -> right);
            t -> element = getvalue(t);
        }
        else if(t -> element == "/" && strtd(t -> left -> element) == 0)
        {
            cerr << "Error: Divisor = 0" << endl;
            t -> element = " ";
        }   
    }

    string getvalue(ExpressionNode *&t)
    {
        if(t -> left -> element == " " || t -> right -> element == " ")
        {
            return " ";
        }
        else if(t -> element == "+")
        {
            return dts(strtd(t -> right -> element) + strtd(t -> left -> element));
        }
        else if(t -> element == "-")
        {
            return dts(strtd(t -> right -> element) - strtd(t -> left -> element));
        }
        else if(t -> element == "*")
        {
            return dts(strtd(t -> right -> element) * strtd(t -> left -> element));
        }
        else if(t -> element == "/")
        {
            return dts(strtd(t -> right -> element) / strtd(t -> left -> element));
        }
        else if(t -> element == "^")
        {
            return dts(pow(strtd(t -> right -> element), strtd(t -> left -> element)));
        }
        else
            return " ";
    }

    void makeEmpty(ExpressionNode *&t)
    {
        if(t != nullptr)
        {
            makeEmpty(t -> left);
            makeEmpty(t -> right);
            delete t;
        }
        t = nullptr;
    }  
}; 

#endif