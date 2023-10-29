#include <iostream>
#include <iomanip>
#include <stack>
#include "ArgumentManager.h"
#include <fstream>
using namespace std;
 
int prec(char c) {
  if (c == '/' || c == '*')
    return 2;
  else if (c == '+' || c == '-')
    return 1;
  else
    return 0;
}

string getPostfix(string s) {
  stack<char> st;
  string postfix;
 
  for (int i=0; i<s.length(); i++) {
    if (s[i] >= '0' && s[i] <= '9')
      postfix += s[i];

    else if (s[i] == '(')
      st.push('(');

    else if (s[i] == ')') {
      while (st.top() != '(') {
        postfix += st.top();
        st.pop();
      }
      st.pop();
    }

    else {
      while (!st.empty() && prec(s[i]) <= prec(st.top())) {
          postfix += st.top();
          st.pop();
      }
      st.push(s[i]);
    }
  }

  while (!st.empty()) {
    postfix += st.top();
    st.pop();
  }
 
  return postfix;
}

int evaluatePostfix(string s) {
  stack<int> st;

  for (int i=0; i<s.length(); i++) {
    if (s[i] >= '0' && s[i] <= '9')
      st.push(s[i] - '0');
    else {
      int val1 = st.top(); st.pop();
      int val2 = st.top(); st.pop();
      switch (s[i]) {
        case '+': st.push(val2 + val1); break;
        case '-': st.push(val2 - val1); break;
        case '*': st.push(val2 * val1); break;
        case '/': st.push(val2 / val1); break;
      }
    }
  }
  return st.top();
}

int main(int argc, char *argv[]) {
  // x*(8*9-(0+(9/3*2)*2*3)*2+9)=4
	ArgumentManager am(argc,argv);
	ifstream input(am.get("input"));
	ofstream out(am.get("output"));
	
	/*
		get substring without x, find pos of x, get substr of answer

	*/ 
  string exp = "(8*9-(0+(9/3*2)*2*3)*2+9)";
  char opr = '/';
  int temp = 4;
  double x = 0;
  bool front = false;
  
  string postfix = getPostfix(exp);
  cout << postfix << endl;
  int result = evaluatePostfix(postfix);
  cout<< result << endl;

  if (opr == '+')
    x = (double)temp - (double)result;
  else if (opr == '-') {
    if (front)
      x = (double)temp + (double)result;
    else
      x = (double)result - (double)temp;
  }
  else if (opr == '*')
    x = (double)temp / (double)result;
  else {
    if (front)
      x = (double)temp * (double)result;
    else
      x = (double)result / (double)temp;
  }

  cout <<setprecision(3)<<x<<endl;
  
  return 0;
}