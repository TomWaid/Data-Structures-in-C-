//#include "stdafx.h"
#include <cmath>
#include <cstdio>
#include <iostream>
#include <cctype>
#include <fstream>
#include <iomanip>
#include <string>
#include <sstream>
#include <ostream>
#include <map>
#include <cassert>
#include "ArgumentManager.h"










// I did not attemp the division part and do not get passed for test case 3






using namespace std;

struct Node
{
	long long num = 0;
	string str;
	Node *prev = 0;
	Node *next = 0;
};
class DoubleLinkedList
{
public:
	DoubleLinkedList() {}
	 
	~DoubleLinkedList()
	{
		 
		clear();
	}

	void clear()
	{
		while (head != nullptr)
		{
			Node *deleteme = head;
			head = head->next;
			delete deleteme;
		}
	}

	 
	DoubleLinkedList(DoubleLinkedList const &list)
	{
		 
	}

	DoubleLinkedList &operator=(DoubleLinkedList const &other)
	{
		 
		clear();

		Node *temp = other.head;
		while (temp != nullptr)
		{
			push_back(temp->str);
			temp = temp->next;
		}
		return *this;
	}

	void push_front(string parted)
	{
		Node *temp = new Node();
		temp->str = parted;
		stringstream ss(parted);
		ss >> temp->num;
		if (head == 0)
		{
			head = temp;
			tail = temp;
		}
		else
		{
			head->prev = temp;
			temp->next = head;
			head = temp;
		}
	}

	void push_back(string parted)
	{
		Node *temp = new Node();
		temp->str = parted;
		stringstream ss(parted);
		ss >> temp->num;
		if (head == 0)
		{
			head = temp;
			tail = temp;
		}
		else
		{
			tail->next = temp;
			temp->prev = tail;
			tail = temp;
		}
	}

	void print(ostream &out) const
	{
		Node *temp = head;
		while (temp != nullptr)
		{
		 	out << temp->str;
			temp = temp->next;
		}
	}

	Node at(int index) const
	{
		int i = 0;
		Node *temp = head;
		while (i != index)
		{
			temp = temp->next;
			i++;
		}
		return *temp;
	}

	int size() const
	{
		int count = 0;
		Node *temp = head;
		while (temp != 0)
		{
			temp = temp->next;
			count++;
		}
		return count;
	}

	void swap(DoubleLinkedList &other)
	{
		Node *temp = head;
		head = other.head;
		other.head = temp;
	}

private:
	Node * head = 0;
	Node *tail = 0;
};

template <class Type>
class stackType
{
private:
	int maxStackSize;
	int stackTop;
	Type *list;

public:
	void initializeStack();
	bool isFullStack() const;
	bool isEmptyStack() const;
	void push(const Type &);
	void pop();
	Type top() const;
	stackType(int = 20);
	~stackType();
};
template <class Type>
void stackType<Type>::initializeStack()
{
	stackTop = 0;
}  
template <class Type>
bool stackType<Type>::isFullStack() const
{
	return (stackTop == maxStackSize);
}  
template <class Type>
bool stackType<Type>::isEmptyStack() const
{
	return (stackTop == 0);
}  
template <class Type>
void stackType<Type>::push(const Type &newItem)
{
	if (!isFullStack())
	{
		list[stackTop] = newItem;
		stackTop++;
	}
	else
		cout << "\n\tStack is full";
}
 
template <class Type>
void stackType<Type>::pop()
{
	if (!isEmptyStack())
		stackTop--;
	else
		cout << "\n\tStack is empty";
}  
template <class Type>
Type stackType<Type>::top() const
{

	assert(stackTop != 0);
	return list[stackTop - 1];

}  
template <class Type>
stackType<Type>::stackType(int stackSize)
{
	if (stackSize <= 0)
	{
		cout << "Size not valid";
		stackSize = 10;
	}  
	else
		maxStackSize = stackSize;
	stackTop = 0;
	list = new Type[maxStackSize];

}  
template <class Type>
stackType<Type>::~stackType()
{
	delete[] list;
} 









class LargeNum
{
public:
	LargeNum() {}
	~LargeNum()
	{
		 
	}

	LargeNum(int digits)
		: digits(digits)
	{}

	LargeNum(string expression, int digits)
		: digits(digits)
	{
		if (expression[0] == '-')
		{
			isNegative = true;
			expression.erase(expression.begin());
		}
		noleadzeros(expression);
		int startIndex = expression.size() - digits;
		while (startIndex > 0)
		{
			data.push_front(expression.substr(startIndex, digits));
			startIndex -= digits;
		}
		if (startIndex <= 0)
		{
			data.push_front(expression.substr(0, startIndex + digits));
		}
	}
	LargeNum(LargeNum const &other)
	{
		 
		isNegative = other.isNegative;
		data = other.data;
		digits = other.digits;
	}
	LargeNum &operator=(LargeNum const &other)
	{
		 
		isNegative = other.isNegative;
		data = other.data;
		digits = other.digits;
		return *this;
	}

	 
	LargeNum operator+(LargeNum &other)
	{
		return add(LargeNum(*this), LargeNum(other));
	}
	LargeNum operator-(LargeNum &other)
	{
		return sub(LargeNum(*this), LargeNum(other));
	}

	LargeNum operator*(LargeNum const &other)
	{
		LargeNum const & LargeNumA = *this;
		LargeNum const & LargeNumB = other;
		LargeNum result(digits);

		int indexA = LargeNumA.data.size() - 1;
		long long count = 0;
		while (indexA > -1)
		{
			LargeNum tempresult(digits);
			for (int i = 0; i < count; i++)
			{
				tempresult.data.push_front("000");
			}
			count++;
			int indexB = LargeNumB.data.size() - 1;
			int rollover = 0;
			while (indexB > -1)
			{
				long long num = (LargeNumA.data.at(indexA).num * LargeNumB.data.at(indexB).num) + rollover;
				indexB--;
				rollover = num / pow(10, digits);
				num = num % (int)pow(10, digits);
				string str = numtostring(num);
				if (rollover > 0 || indexB > -1)
				{
					padzeros(str);
				}
				tempresult.data.push_front(str);
			}
			if (rollover > 0)
			{
				string str = numtostring(rollover);
				tempresult.data.push_front(str);
			}
			result = add(result, tempresult);
			indexA--;
		}

		if (LargeNumA.isNegative || LargeNumB.isNegative)
		{
			result.isNegative = true;
		}
		if (LargeNumA.isNegative && LargeNumB.isNegative)
		{
			result.isNegative = false;
		}
		return result;
	}

	void print(ostream &out) const
	{
		if (isNegative)
		{
			out << "-";
		}
		data.print(out);
	}
	 
	void swap(LargeNum &other)
	{
		std::swap(isNegative, other.isNegative);
		data.swap(other.data);
	}

private:
	LargeNum add(LargeNum LargeNumA, LargeNum LargeNumB)
	{
		LargeNum result(digits);

		 
		if (!LargeNumA.isNegative && LargeNumB.isNegative)
		{
			 
			LargeNumA.isNegative = false;
			LargeNumB.isNegative = false;
			return sub(LargeNumA, LargeNumB);
		}
		if (LargeNumA.isNegative && !LargeNumB.isNegative)
		{
			 
			LargeNumA.isNegative = false;
			LargeNumB.isNegative = false;
			return sub(LargeNumB, LargeNumA);
		}
		if (LargeNumA.isNegative && LargeNumB.isNegative)
		{
			 
			result.isNegative = true;
		}

		int rollover = 0;
		int indexA = LargeNumA.data.size() - 1;
		int indexB = LargeNumB.data.size() - 1;

		 
		while (indexA > -1 || indexB > -1)
		{
			int a = 0;
			int b = 0;

			if (indexA > -1)
			{
				a = LargeNumA.data.at(indexA).num;
				indexA--;
			}
			if (indexB > -1)
			{
				b = LargeNumB.data.at(indexB).num;
				indexB--;
			}

			long long num = a + b + rollover;
			rollover = num / pow(10, digits);
			num = num % (int)pow(10, digits);

			string str;
			stringstream ss;
			ss << num;
			ss >> str;
			 
			if (rollover > 0 || indexA > -1 || indexB > -1)
			{
				padzeros(str);
			}

			result.data.push_front(str);
		}
		 
		if (rollover > 0)
		{
			string str;
			stringstream ss;
			ss << rollover;
			ss >> str;
			result.data.push_front(str);
		}
		return result;
	}
	LargeNum sub(LargeNum LargeNumA, LargeNum LargeNumB)
	{  
		if (!LargeNumA.isNegative && LargeNumB.isNegative)
		{
			 
			LargeNumA.isNegative = false;
			LargeNumB.isNegative = false;
			return add(LargeNumA, LargeNumB);
		}
		if (LargeNumA.isNegative && !LargeNumB.isNegative)
		{
			 
			LargeNumA.isNegative = true;
			LargeNumB.isNegative = true;
			return add(LargeNumA, LargeNumB);
		}
		if (LargeNumA.isNegative && LargeNumB.isNegative)
		{
			 
			LargeNumA.isNegative = false;
			LargeNumB.isNegative = false;
			return sub(LargeNumB, LargeNumA);
		}

		 
		LargeNum LargeNumL;
		LargeNum LargeNumS;
		LargeNum LargeNum9;

		int nodesA = LargeNumA.data.size() - 1;
		int nodesB = LargeNumB.data.size() - 1;
		int charsA = LargeNumA.data.at(0).str.size();
		int charsB = LargeNumB.data.at(0).str.size();
		int const EQUAL = 0;
		int const BIG_A = 1;
		int const BIG_B = 2;
		int which = EQUAL;
		if (nodesA > nodesB)
		{
			which = BIG_A;
		}
		if (nodesA < nodesB)
		{
			which = BIG_B;
		}
		if (nodesA == nodesB)
		{
			if (charsA > charsB)
			{
				which = BIG_A;
			}
			else
			{
				which = BIG_B;
			}
		}

		int nodes = 0;
		int chars = 0;
		if (which == BIG_A)
		{
			 
			LargeNumL = LargeNumA;
			LargeNumS = LargeNumB;
			nodes = (LargeNumA.data.size() - 1);
			chars = LargeNumA.data.at(0).str.size();
			LargeNum9.digits = LargeNumA.digits;
		}
		else
		{
			 
			LargeNumL = LargeNumB;
			LargeNumS = LargeNumA;
			nodes = (LargeNumB.data.size() - 1);
			chars = LargeNumB.data.at(0).str.size();
			LargeNum9.digits = LargeNumB.digits;
		}

		 
		while (nodes > 0)
		{
			nodes--;
			LargeNum9.data.push_front(string(LargeNum9.digits, '9'));
		}
		LargeNum9.data.push_front(string(chars, '9'));


 

		LargeNum step1 = sub_nocarry(LargeNum9, LargeNumL);
		 

		LargeNum step2 = add(step1, LargeNumS);
		 

		int nodesY = step2.data.size() - 1;
		int nodes9 = LargeNum9.data.size() - 1;
		int charsY = step2.data.at(0).str.size();
		int chars9 = LargeNum9.data.at(0).str.size();

		if (nodesY > nodes9 || charsY > chars9)
		{
			 
			LargeNum temp(LargeNumA.digits);
			 
			for (int i = 1; i < step2.data.size() - 1; i++)
			{
				 
				temp.data.push_back(step2.data.at(i).str);
			}
			if (nodesY == nodes9)
			{
				 
				int num = step2.data.at(0).num;
				num = num % (int)pow(10, chars9);
				if (nodesY > 0)
				{
					 
					if (num > 0)
					{
						temp.data.push_front(numtostring(num));
					}
					 
					temp.data.push_back(numtostring(step2.data.at(step2.data.size() - 1).num + 1));
				}
				else
				{
					 
					temp.data.push_back(numtostring(num + 1));
				}
			}
			else
			{
				 
				temp.data.push_back(numtostring(step2.data.at(step2.data.size() - 1).num + 1));
			}

			return temp;
		}
		else
		{
			 

			LargeNum step3 = sub_nocarry(LargeNum9, step2);
			 
			if (which == BIG_A)
			{
				step3.isNegative = false;
			}
			else
			{
				if (step3.data.size() == 1 && step3.data.at(0).num == 0)
				{
					step3.isNegative = false;
				}
				else
				{
					step3.isNegative = true;
				}
			}

			return step3;
		}
	}

	LargeNum sub_nocarry(LargeNum LargeNumA, LargeNum LargeNumB)
	{
		 
		if (!LargeNumA.isNegative && LargeNumB.isNegative)
		{
			 
			LargeNumA.isNegative = false;
			LargeNumB.isNegative = false;
			return add(LargeNumA, LargeNumB);
		}
		if (LargeNumA.isNegative && !LargeNumB.isNegative)
		{
			 
			LargeNumA.isNegative = true;
			LargeNumB.isNegative = true;
			return add(LargeNumA, LargeNumB);
		}
		if (LargeNumA.isNegative && LargeNumB.isNegative)
		{
			 
			LargeNumA.isNegative = false;
			LargeNumB.isNegative = false;
			return sub_nocarry(LargeNumB, LargeNumA);
		}

		LargeNum result(digits);

		int rollover = 0;
		int indexA = LargeNumA.data.size() - 1;
		int indexB = LargeNumB.data.size() - 1;

		while (indexA > -1 || indexB > -1)
		{
			 
			int a = 0;
			int b = 0;

			if (indexA > -1)
			{
				a = LargeNumA.data.at(indexA).num;
				indexA--;
			}
			if (indexB > -1)
			{
				b = LargeNumB.data.at(indexB).num;
				indexB--;
			}

			long long num = a - b + rollover;
			rollover = num / pow(10, digits);
			num = num % (int)pow(10, digits);

			string str = numtostring(num);

			 
			if (rollover > 0 || indexA > -1 || indexB > -1)
			{
				padzeros(str);
			}

			if (num > 0 || indexA > -1 || indexB > -1)
			{
				result.data.push_front(str);
			}
		}
		if (result.data.size() == 0)
		{
			result.data.push_front("0");
		}

		return result;
	}

	void padzeros(string & str) const
	{
		 
		string pad(digits - str.size(), '0');
		str = pad + str;
	}
	string numtostring(long long num) const
	{
		string str;
		stringstream ss;
		ss << num;
		ss >> str;
		return str;
	}
	void noleadzeros(string & str)
	{
		while (str.size() > 1)
		{
			if (str[0] == '0')
			{
				str.erase(str.begin());
			}
			else
			{
				break;
			}
		}
	}

	bool isNegative = false;
	DoubleLinkedList data;
	int digits;
};








class infixToPostfix
{
	string infix;
	string postfix;
	DoubleLinkedList data;

public:
	void showPostfix();
	bool isOperator(const char c);
	int precedence(const char op1, const char op2);
	 
	void getInfix(string infixString)
	{
		infix = infixString;
	}

	void showInfix()
	{
		cout << infix;
	}

	void evaluatePostfix(int digits)
	{
		string str;
		stringstream ss(postfix);
		stackType<LargeNum> myStack;
		while (ss.good())
		{
			ss >> str;
			if (str.size() == 0)
			{
				continue;
			}
			if (str.size() == 1 && isOperator(str[0]))
			{
				char op = str[0];
				LargeNum operand2 = myStack.top();
				myStack.pop();
				LargeNum operand1 = myStack.top();
				myStack.pop();

				if (op == '+')
				{
					myStack.push(operand1 + operand2);
				}
				else if (op == '-')
				{
					myStack.push(operand1 - operand2);
				}
				else if (op == '*')
				{
					myStack.push(operand1 * operand2);
				}
			}
			else
			{
				myStack.push(LargeNum(str, digits));
			}
		}
		cout << "=";
		myStack.top().print(cout);
		cout << endl;
	}
};

bool infixToPostfix::isOperator(const char c)
{
	if ((c == '+') || (c == '-') || (c == '*') || (c == '/'))
		return true;
	else
		return false;
}

int infixToPostfix::precedence(const char op1, const char op2)
{
	int pre1 = 0, pre2 = 0;  
	if ((op1 == '^') || (op2 == '^'))
		cout << "Exponents were not included.";
	if ((op1 == '+') || (op1 == '-'))  
		pre1 = 0;
	else if ((op1 == '*') || (op1 == '/') || (op1 == '%'))
		pre1 = 1;                      
	if ((op2 == '+') || (op2 == '-'))  
		pre2 = 0;
	else if ((op2 == '*') || (op2 == '/') || (op2 == '%'))
		pre2 = 1; 

				  
	if (pre1 == pre2)  
		return 0;
	else if (pre1 > pre2)  
		return 1;
	else  
		return -1;
}

 
void infixToPostfix::showPostfix()
{
	stackType<char> myStack;  
	string pfx = "";
	infix.append(")");  
	infix.insert(0,1,'(');  
	unsigned int i = 0;
	if ((infix[i]) == '-')
		infix[i] = '~';
	do
	{  
		if (isOperator(infix[i]) && infix[i + 1] == '-')
		{
			infix[i + 1] = '~';
		}
		else if (isOperator(infix[i]) && infix[i + 1] == '+')
		{
			infix.erase(infix.begin() + i + 1);
		}
		else if (isOperator(infix[i]))
		{  
			pfx += ' ';
			if (!myStack.isEmptyStack() && isOperator(myStack.top()))
			{  
				if (precedence(infix[i], myStack.top()) == 0)
				{  
					pfx = pfx + myStack.top(); 
					myStack.pop();              
				}
				else if (precedence(infix[i], myStack.top()) == 1)
				{
					myStack.push(infix[i]); 
					i++;
				}
				else
				{
					pfx = pfx + myStack.top(); 
					myStack.pop();
				}
			}
			else
			{
				myStack.push(infix[i]);  
				i++;
			}
		}
		else if (infix[i] == ')')
		{
			while (!myStack.isEmptyStack() && myStack.top() != '(')
			{  
				pfx += ' ';
				pfx = pfx + myStack.top();
				myStack.pop();
			}
			myStack.pop();  
			i++;
		}
		else if (infix[i] == '(')
		{
			myStack.push(infix[i]);  
			if (infix[i + 1] == '-')
			{
				infix.erase(infix.begin() + i + 1);
				pfx += '-';
			}
			else if (infix[i + 1] == '+')
			{
				infix.erase(infix.begin() + i + 1);
				pfx += '+';
			}
			i++;
		}  
		else
		{
			if (infix[i] == '~')
			{
				pfx += '-';
			}
			else
			{
				pfx = pfx + infix[i];  
			}
			i++;
		}
	} while (i < infix.length());
	 
	postfix = pfx;
}

 
int count_lines(string &filename, int digits)
{
	std::ifstream ifs(filename.c_str());

	int counter = 0;
	while (!ifs.eof())
	{
		string line;
		ifs >> line;
		counter++;
	}
	return counter;
}
bool assessString(string& line)
{
	int lparen = 0;
	int rparen = 0;

	char last = '\0';
	for (int i = 0; i < line.length(); last = line[i], i++)
	{
		// count parenthesis
		if (line[i] == '(')
		{
			lparen++;
			continue;
		}
		if (line[i] == ')')
		{
			rparen++;
			continue;
		}

		// accept numbers
		if (line[i] >= '0' && line[i] <= '9') continue;

		// reject duplicate minus sign
		if (line[i] == last) return false;

		// accept addition
		if (line[i] == '+') continue;
		// accept subtraction
		if (line[i] == '-') continue;
		// accept multiplication
		if (line[i] == '*') continue;

		// reject division
		// reject anything else
		return false;
	}

	return lparen == rparen;
}


 
int main(  int argc, char *argv[]  )
{
	  if (argc < 2)
	{
		
		return 1;
	}
	 ArgumentManager am(argc, argv);
	 std::string filename = am.get("input");
	
	
	
	 
	 ifstream infile(filename, ios::in);
	int digits = 3;

	infixToPostfix InfixExp;
	string infix;
	if (!infile)
	{
		cout << "Cannot open input file. Program terminates!!!" << endl;
		return 1;
	}
	while (getline(infile, infix))
	{
	 if (infix.empty() || infix.at(0) == '\n') { continue; }
		if (assessString(infix) == false)
		{
			continue;
		}
		 
		InfixExp.getInfix(infix);
		 
		InfixExp.showInfix();
		 
		InfixExp.showPostfix();
		InfixExp.evaluatePostfix(digits);
		 
		 
	}
	infile.close();

	return 0;
}
