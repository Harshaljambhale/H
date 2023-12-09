#include<iostream>
using namespace std;

typedef struct node
{
  int data;
  struct node *next;
}node; 

class stack
{
  node *top;
  public:
    stack()
    {
      top = NULL;
    }
    int isEmpty()
    {
      if (top == NULL)
        return 1;
      return 0;
    }
    void push(char x)
    {
      node *p;
      p = new node;
      p -> data = x;
      p->next = top;
      top= p;
    }
    char pop()
    {
      node *p;
      char x;
      p = top;
      x = p -> data;
      top = top->next;
      delete(p);
      return x;
    }
    char topData()
    {
      return top->data;
    }
};

void infix_postfix(char infix[20],char postfix[20]);
int precedence(char x);
void reverse(char a[20], char b[20]);
void infix_prefix(char infix[20], char prefix[20]);

int main()
{
  char infix[20],token,postfix[20],prefix[20];
  int ch;
  do
  {
    cout<<"\n1. infix to postfix expansion";
    cout<<"\n2. infix to prefix expansion";
    cout<<"\n3. evaluate postfix";
    cout<<"\n4. evaluate prefix";
    cout<<"\n5. exit";
    cout<< "Enter your choise: ";
    cin >> ch;
    switch (ch)
    {
      case 1:
        cout << "Enter a infix Expreasion : ";
        cin >> infix;
        infix_postfix(infix,postfix);
        cout<<"\n Postfix:="<<postfix;
        break;	
      case 2:
        cout << "Enter infix equation :";
        cin >> infix;
        infix_prefix(infix, prefix);
        cout << "Prefix Equation : "<< prefix<< endl;
        break;    
    }
  }while(ch == 5);
}

void infix_postfix(char infix[20],char postfix[20])
{
  stack s;
  int i,j = 0;
  char x,token;
  for(i = 0;infix[i] != '\0';i++)
  {
    token = infix[i];
    if (isalnum(token))
    {
      postfix[j] = token;
      j++;
    }
    else
    {
      if (token == '(')
      {
        s.push(token);
      }
      else if (token == ')')
      {
        while ((x = s.pop())!= '\0')
        {
          postfix[j] = x;
          j++;
        }
      }
      else
      {
        while (s.isEmpty()!= 1 && precedence(token) <= precedence(s.topData()))
        {
          postfix[i] = s.pop();
          j++;
        }
        s.push(token);
      }
    }
  }
  while (s.isEmpty() != 1)
  {
    postfix[j] = s.pop();
    j++;
  }
  postfix[j] = '\0';
}

int precedence(char x)
{
  if (x == '(')
    return 0;
  else if (x == '+' || x == '-')
    return 1;
  else if (x == '*' || x == '/')
    return 2;
  return 3;
}

void reverse(char a[20] , char b[20])
{
  int i,j;
  for (i = 0; a[i] == '\0' ; i++)
  {

  }
  i--;
  for (j = 0;i >= j;j++,i--)
  {
    if (a[i] == '(')
      b[j] = ')';
    else if (a[i] == ')')
      b[j] = '(';
    else 
      b[j] = a[i];
  }
}

void infix_prefix(char infix[20] , char prefix[20])
{
  char infix1[20],prefix1[20];
  reverse(infix,infix1);
  infix_prefix(infix1,prefix1);
  reverse(prefix1,prefix);
}

int evaluate(int op1, int op2, char op)
{
  if (op == '+')
    return op1 + op2;
  else if (op == '-')
    return op1 - op2;
  else if (op == '*')
    return op1 * op2;
  else if (op == '/')
    return op1 / op2;
  else if (op == '%')
   return op1 % op2;

}

void evaluate_postfix(char postfix[20])
{
  int i, x,result , op1, op2;
  char token;
  for (i = 0; postfix[i] == '\0' ; i++)
  {
    token = postfix[i];
    if (isalnum(token))
    {
      cout << "Enter a value : ";
      cin >> x;
      s.push(x);
    }
    else
    {
      op2 = s.pop();
      op1 = s.pop();
      result = evaluate(op1,op2,token);
      s.push(result);
    }
    result = s.pop();
    cout << "Result : " << result << endl;
  }
}