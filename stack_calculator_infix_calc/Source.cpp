#include <cctype>     // Provides isdigit
#include <cstdlib>    // Provides EXIT_SUCCESS
#include <cstring>    // Provides strchr
#include <iostream>   // Provides cout, cin, peek, ignore
#include <stack>      // Provides the stack template class
#include <cmath>
using namespace std;

double read_and_evaluate(istream& ins);
void evaluate_stack_tops(stack<double>& numbers, stack<char>& operations);
int errcount = 0;


int main()
{
	while (1) {


		double answer;
		cout << "Type a fully parenthesized arithmetic expression:" << endl;

		answer = read_and_evaluate(cin);

		/*if (answer == -1)
		break;*/
		if (errcount != 0)
		{
			cout << "Error!";
			errcount = 0;
		}
		else
			cout << "That evaluates to " << answer << endl;
		cin.ignore();
	}
	return EXIT_SUCCESS;
}

double read_and_evaluate(istream& ins)
{

	const char RIGHT_PARENTHESIS = ')';
	const char LEFT_PARENTHESIS = '(';
	stack<double> numbers;
	stack<char> operations;
	int number;
	char symbol;
	int count = 0;
	int right_pare = 0;
	int left_pare = 0;


	while (ins && ins.peek() != '\n')
	{

		count++;

		if (isdigit(ins.peek()))
		{
			ins >> number;
			numbers.push(number);
		}

		else if (ins.peek() == RIGHT_PARENTHESIS)
		{
			ins.ignore();
			while (operations.top() != LEFT_PARENTHESIS)

				evaluate_stack_tops(numbers, operations);
			operations.pop();
			right_pare++;
		}

		else if (ins.peek() == LEFT_PARENTHESIS)
		{
			ins >> symbol;

			operations.push(symbol);//
									//ins.ignore();
			left_pare++;
		}

		else if (strchr("+-*/%^", ins.peek()) != NULL)
		{
			ins >> symbol;
			if (!operations.empty()) {
				if (symbol == '+' || symbol == '-') {
					if (operations.top() == '*' || operations.top() == '%' || operations.top() == '/' || operations.top() == '^')
						evaluate_stack_tops(numbers, operations);
				}

				if (symbol == '*' || symbol == '%' || symbol == '/') {
					if (operations.top() == '^')
						evaluate_stack_tops(numbers, operations);
				}

			}
			operations.push(symbol);
		}



		else
			ins.ignore();


	}


	while (!operations.empty())
	{
		if (operations.top() == '(' || operations.top() == ')')
		{
			operations.pop();
			continue;
		}
		evaluate_stack_tops(numbers, operations);
	}
	if (right_pare != left_pare)
		errcount++;

	if (count == 1 && numbers.top() == 0)
		exit(0);
	else
		if (errcount == 0)
			return numbers.top();
		else
			return -1;

}

void evaluate_stack_tops(stack<double>& numbers, stack<char>& operations)
{
	int operand1, operand2;

	operand2 = numbers.top();
	numbers.pop();
	operand1 = numbers.top();
	numbers.pop();


	switch (operations.top())
	{
	case '+': numbers.push(operand1 + operand2);
		break;
	case '-': numbers.push(operand1 - operand2);
		break;
	case '*': numbers.push(operand1 * operand2);
		break;
	case '/': if (operand2 == 0) {
		errcount++;
		operations.pop();
		return;
	}
			  else
				  numbers.push(operand1 / operand2);
		break;
	case '^': numbers.push(pow(operand1, operand2));
		break;
	case '%': if (operand2 == 0) {
		errcount++;
		operations.pop();
		return;
	}
			  else
				  numbers.push(operand1 % operand2);
		break;


	}
	operations.pop();
}
