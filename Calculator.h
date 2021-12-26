#pragma once
#include <iostream>
#include <cmath>

using namespace std;

const double pi = acos(-1);
const double e = 2.71;

class num_stack
{
private:
	class node
	{
	public:
		node* next = nullptr;
		double value;
		node(double value, node* next = nullptr)
		{
			this->value = value;
			this->next = next;
		}
	};
public:
	int Size = 0;
	node* top = nullptr;


	void push(double value)
	{
		top = new node(value, top);
		Size++;
	}


	void pop()
	{
		node* temp = top;
		top = top->next;
		Size--;
	}

	double at(int index)
	{
		node* current = top;
		for (int i = 0; i < index; i++)
		{
			current = current->next;
		}
		return current->value;
	}

	int size()
	{
		return Size;
	}

	void clear()
	{
		while (size()) pop();
	}

	bool isEmpty()
	{
		return size() == 0;
	}

};


class sym_stack
{
private:
	class node
	{
	public:
		node* next = nullptr;
		char type;
		node(char type, node* next = nullptr)
		{
			this->next = next;
			this->type = type;
		}
	};
public:
	int Size = 0;
	node* top = nullptr;


	void push(char type)
	{
		top = new node(type, top);
		Size++;
	}

	void pop()
	{
		node* temp = top;
		top = top->next;
		Size--;
	}


	int size()
	{
		return Size;
	}


	int at(int index)
	{
		node* current = top;
		for (int i = 0; i < index; i++)
		{
			current = current->next;
		}
		return current->type;
	}

	void clear()
	{
		while (size()) pop();
	}

	bool isEmpty()
	{
		return size() == 0;
	}

};

class calculator
{
public:
	double Sin(double x)
	{
		return (round(sin(x) * 10000000) / 10000000);
	}


	double Cos(double x)
	{
		return (round(cos(x) * 10000000) / 10000000);
	}


	double ctg(double x)
	{
		double a = Cos(x);
		double b = Sin(x);
		return (a / b);
	}


	struct Lekasema {
		char type;
		double value;
	};


	num_stack stack_num;
	sym_stack stack_sym;

	int Rang(char ch)
	{
		if ((ch == 'c') || (ch == 't') || (ch == 's') || (ch == 'g') || (ch == 'e') || (ch == 'l') || (ch == 'n')) return 4;
		if (ch == '^') return 3;
		if ((ch == '*') || (ch == '/')) return 2;
		if ((ch == '+') || (ch == '-')) return 1;
		if ((ch == '(') || (ch == ')')) return 0;
		else
			return -1;
	}

	string infixToPostfix(string s) {

		string result;
		string sum;
		sym_stack st;

		for (int i = 0; i < s.length(); i++) {
			char c = s[i];

			if (c == ' ')
				continue;
			else if ((c >= '0' && c <= '9') || (c == 'l') || (c == 'o') || (c == 'g') || (c == 'n') || (c == 't') || (c == 'a') || (c == 's') || (c == 'c') || (c == 'i') || (c == 'p') || (c == 'e'))
			{
				sum = sum + c;
				if ((sum == "cos") || (sum == "sin") || (sum == "tan") || (sum == "ctg") || (sum == "lon") || (sum == "log"))
				{
					result += sum;
					sum = "";
				}
				if (i == s.length() - 1)
					result += sum;
			}

			else if (c == '(')
				st.push('(');

			else if (c == ')') {
				while (st.at(0) != '(')
				{
					result += st.at(0);
					st.pop();
				}
				st.pop();
				result += sum;
				sum = "";
			}

			else {
				if (c != '0' && c != '1' && c != '2' && c != '3' && c != '4' && c != '5' && c != '6' && c != '7' && c != '8' && c != '9' && ((s[i - 1] >= '0' && s[i - 1] <= '9') || (s[i - 1] == NULL)))
				{
					result += sum;
					sum = "";
				}
				while (!st.isEmpty() && Rang(s[i]) <= Rang(st.at(0))) {
					result += st.at(0);
					st.pop();
				}
				if (c != '0' && c != '1' && c != '2' && c != '3' && c != '4' && c != '5' && c != '6' && c != '7' && c != '8' && c != '9')
					st.push(c);
			}
		}

		while (!st.isEmpty()) {
			result += st.at(0);
			st.pop();
		}

		return result;

	}


	double string_to_double(string str)
	{
		double numdouble = 0;
		int degree = 1, minus = 0;
		size_t i;
		for (i = 0; i < str.size() && str[i] != ','; i++)
		{
			if (str[i] == '-')
			{
				minus = 1;
				continue;
			}
			numdouble = numdouble * pow(10, i - minus) + (double)str[i] - 48;
		}
		if (i < str.size()) if (str[i] == ',')
		{
			for (++i; i < str.size(); i++, degree++)
			{
				numdouble = numdouble + ((double)str[i] - 48) * pow(10, -degree);
			}
			if (minus) numdouble *= -1;
		}
		return numdouble;
	}


	int read_string(string str)
	{
		num_stack stack_1;
		sym_stack stack_2;
		char ch, func[3];
		string temp_value, result;
		Lekasema item;
		bool flag = 1;
		int i, open_parenthesis_count = 0, close_parenthesis_count=0;

		cout << "Hello! This is caculator!\nHelp on using the calculator:\n1.To use Pi enter 'p'.\n2.to use E enter 'exp (1)'.\n3.To use ln enter lon.\nTo use sqrt enter (x)^(1/2).\nTo use unary minus enter (-x).\nEnter the expression:" << str << endl;
		for (i = 0; i < str.length(); i++)
		{
			ch = str[i];
			if (ch == '\n') break;
			if (ch == ' ')
			{
				continue;
			}
			if (ch == 's' || ch == 'c' || ch == 't' || ch == 'l' || ch == 'o' || ch == 'g' || ch == 'n' || ch == 'a')
			{
				for (int j = 0; j < 3; j++)
				{
					ch = str[i + j];
					func[j] = ch;
				}
				i += 2;
				if (func[0] == 's' && func[1] == 'i' && func[2] == 'n')
				{
					item.type = 's';
					item.value = 0;
					stack_2.push(item.type);
					flag = 0;
					continue;
				}
				if (func[0] == 'c' && func[1] == 'o' && func[2] == 's')
				{
					item.type = 'c';
					item.value = 0;
					stack_2.push(item.type);
					flag = 0;
					continue;
				}
				if (func[0] == 't' && func[1] == 'a' && func[2] == 'n')
				{
					item.type = 't';
					item.value = 0;
					stack_2.push(item.type);
					flag = 0;
					continue;
				}
				if (func[0] == 'c' && func[1] == 't' && func[2] == 'g')
				{
					item.type = 'g';
					item.value = 0;
					stack_2.push(item.type);
					flag = 0;
					continue;
				}
				if (func[0] == 'l' && func[1] == 'o' && func[2] == 'g')
				{
					item.type = 'l';
					item.value = 0;
					stack_2.push(item.type);
					flag = 0;
					continue;
				}
				if (func[0] == 'l' && func[1] == 'o' && func[2] == 'n')
				{
					item.type = 'n';
					item.value = 0;
					stack_2.push(item.type);
					flag = 0;
					continue;
				}
				if (func[0] == 'a' && func[1] == 'c' && func[2] == 's')
				{
					item.type = 'a';
					item.value = 0;
					stack_2.push(item.type);
					flag = 0;
					continue;
				}
			}
			if (ch == 'p')
			{
				item.type = '0';
				item.value = pi;
				stack_1.push(item.value);
				flag = 0;
				continue;
			}
			if (ch == 'e')
			{
				item.type = '0';
				item.value = e;
				stack_1.push(item.value);
				flag = 0;
				continue;
			}
			if (ch >= '0' && ch <= '9' || ch == '-' && flag == 1)
			{
				double value;
				while (str[i] >= '0' && str[i] <='9')
				{
					ch = str[i];
					temp_value += ch;
					i++;
				}
				i--;
				value = string_to_double(temp_value);
				temp_value = "";
				item.type = '0';
				item.value = value;
				stack_1.push(item.value);
				flag = 0;
				continue;
			}
			if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^')
			{
				if (stack_2.size() == 0)
				{
					item.type = ch;
					item.value = 0;
					stack_2.push(item.type);
					continue;
				}
				if (stack_2.size() != 0 && Rang(ch) > Rang(stack_2.at(0)))
				{
					item.type = ch;
					item.value = 0;
					stack_2.push(item.type);
					continue;
				}
				if (stack_2.size() != 0 && Rang(ch) <= Rang(stack_2.at(0)))
				{
					if (Maths(stack_1, stack_2) == false)
					{
						system("pause");
						return 0;
					}
					stack_1 = stack_num;
					stack_2 = stack_sym;
					continue;
				}
			}
			if (ch == '(')
			{
				open_parenthesis_count++;
				item.type = ch;
				item.value = 0;
				stack_2.push(item.type);
				continue;
			}
			if (ch == ')')
			{
				close_parenthesis_count++;
				while (stack_2.at(0) != '(')
				{
					if (Maths(stack_1, stack_2) == false)
					{
						system("pause");
						return 0;
					}
					else
					{
						stack_1 = stack_num;
						stack_2 = stack_sym;
						continue;
					}
				}
				stack_2.pop();
				continue;
			}
			else {
				cout << "Error! Unable to recognize the number or symbol! Re-run programm and write your example again!\n" << endl;
				system("pause");
				return 0;
			}
		}
		if (open_parenthesis_count != close_parenthesis_count)
		{
			cout << "The number of opening and closing parentheses does not match" << endl;
			system("pause");
			return 1;
		}
		while (stack_2.size() != 0)
		{
			if (Maths(stack_1, stack_2) == false)
			{
				system("pause");
				return 0;
			}
			else
			{
				stack_1 = stack_num;
				stack_2 = stack_sym;
				continue;
			}
		}
		result = infixToPostfix(str);
		postfix_output(result);
		result_output(stack_1);
	}

	bool Maths(num_stack stack_1, sym_stack stack_2)
	{
		Lekasema item;
		double a, b, c;
		a = stack_1.at(0);
		stack_1.pop();
		switch (stack_2.at(0))
		{
		case '+':
			b = stack_1.at(0);
			stack_2.pop();
			c = a + b;
			item.type = '0';
			item.value = c;
			stack_1.pop();
			stack_1.push(item.value);
			break;
		case '-':
			b = stack_1.at(0);
			stack_2.pop();
			c = b - a;
			item.type = '0';
			item.value = c;
			stack_1.pop();
			stack_1.push(item.value);
			break;
		case '*':
			b = stack_1.at(0);
			stack_2.pop();
			c = a * b;
			item.type = '0';
			item.value = c;
			stack_1.pop();
			stack_1.push(item.value);
			break;
		case '/':
			b = stack_1.at(0);
			if (a == 0)
			{
				cerr << "Error! Cannot be divided by 0!\n";
				return false;
			}
			stack_2.pop();
			c = b / a;
			item.type = '0';
			item.value = c;
			stack_1.pop();
			stack_1.push(item.value);
			break;
		case '^':
			b = stack_1.at(0);
			stack_2.pop();
			c = pow(b, a);
			item.type = '0';
			item.value = c;
			stack_1.pop();
			stack_1.push(item.value);
			break;
		case 'c':
			c = Cos(a);
			stack_2.pop();
			item.type = '0';
			item.value = c;
			if (stack_1.Size != 0)
				stack_1.pop();
			stack_1.push(item.value);
			break;
		case 's':
			c = Sin(a);
			stack_2.pop();
			item.type = '0';
			item.value = c;
			if(stack_1.Size!=0)
				stack_1.pop();
			stack_1.push(item.value);
			break;
		case 't':
			if (Cos(a) == 0)
			{
				cerr << "Error! Tan is not correct!";
				return false;
			}
			c = tan(a);
			stack_2.pop();
			item.type = '0';
			item.value = c;
			if (stack_1.Size != 0)
				stack_1.pop();
			stack_1.push(item.value);
			break;
		case 'g':
			if (Sin(a) == 0)
			{
				cerr << "Error! ctg is not correct!";
				return false;
			}
			c = ctg(a);
			stack_2.pop();
			item.type = '0';
			item.value = c;
			if (stack_1.Size != 0)
				stack_1.pop();
			stack_1.push(item.value);
			break;
		case 'a':
			c = acos(a);
			stack_2.pop();
			item.type = '0';
			item.value = c;
			if (stack_1.Size != 0)
				stack_1.pop();
			stack_1.push(item.value);
			break;
		case 'l':
			c = log(a);
			stack_2.pop();
			item.type = '0';
			item.value = c;
			if(stack_1.Size != 0)
				stack_1.pop();
			stack_1.push(item.value);
			break;
		case 'n':
			c = log10(a);
			stack_2.pop();
			item.type = '0';
			item.value = c;
			if(stack_1.Size != 0)
				stack_1.pop();
			stack_1.push(item.value);
			break;
		default:
			cerr << "Error! Unable to recognize the number or symbol! Re-run programm and write your example again!\n";
			return false;
			break;
		}

		stack_num = stack_1;
		stack_sym = stack_2;

		return true;
	}

	void postfix_output(string result)
	{
		cout << result << endl;
	}

	void result_output(num_stack stack_1)
	{
		cout << "Answer: " << stack_1.at(stack_1.size() - 1) << endl;
	}

};