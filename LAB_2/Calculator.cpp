#include <iostream>
#include <stack>
#include <string>

using namespace std;

// Функция для определения приоритета операций
int getPriority(char op) 
{
    if (op == '*' || op == '/')
        return 2;
    else if (op == '+' || op == '-')
        return 1;
    else
        return 0; // Низкий приоритет для скобок
}

// Функция для выполнения операции между двумя числами
double applyOperation(double a, double b, char op) 
{
    switch (op) 
    {
    case '+':
        return a + b;
    case '-':
        return a - b;
    case '*':
        return a * b;
    case '/':
        if (b != 0) 
        {
            return a / b;
        }
        else 
        {
            cerr << "Ошибка: деление на ноль" << endl;
            exit(1);
        }
    default:
        cerr << "Ошибка: недопустимая операция" << endl;
        exit(1);
    }
}

double calculateExpression(const string& expression) 
{
    stack<double> values;
    stack<char> operators;

    for (size_t i = 0; i < expression.length(); ++i) 
    {
        char currentChar = expression[i];

        if (isdigit(currentChar)) 
        {
            // Если текущий символ - цифра, считываем число и добавляем его в стек значений
            string numStr;
            while (i < expression.length() && (isdigit(expression[i]) || expression[i] == '.')) 
            {
                numStr += expression[i];
                i++;
            }
            i--; // Возвращаемся назад, чтобы не пропустить следующий символ после числа
            values.push(stod(numStr));
        }
        else if (currentChar == '(') 
        {
            // Если текущий символ - открывающая скобка, добавляем её в стек операторов
            operators.push(currentChar);
        }
        else if (currentChar == ')') 
        {
            // Если текущий символ - закрывающая скобка, выполняем операции внутри скобок
            while (!operators.empty() && operators.top() != '(') 
            {
                char op = operators.top();
                operators.pop();

                if (values.size() < 2)
                {
                    cerr << "Ошибка: недостаточно операндов для операции" << endl;
                    exit(1);
                }

                double b = values.top();
                values.pop();
                double a = values.top();
                values.pop();

                double result = applyOperation(a, b, op);
                values.push(result);
            }

            if (!operators.empty() && operators.top() == '(') 
            {
                operators.pop(); // Убираем открывающую скобку из стека операторов
            }
            else
            {
                cerr << "Ошибка: неправильное расположение скобок" << endl;
                exit(1);
            }
        }
        else if (currentChar == '+' || currentChar == '-' || currentChar == '*' || currentChar == '/') 
        {
            // Если текущий символ - оператор, обрабатываем его с учетом приоритетов
            while (!operators.empty() && getPriority(operators.top()) >= getPriority(currentChar))
            {
                char op = operators.top();
                operators.pop();

                if (values.size() < 2) 
                {
                    cerr << "Ошибка: недостаточно операндов для операции" << endl;
                    exit(1);
                }

                double b = values.top();
                values.pop();
                double a = values.top();
                values.pop();

                double result = applyOperation(a, b, op);
                values.push(result);
            }

            operators.push(currentChar); // Добавляем текущий оператор в стек операторов
        }
        else if (currentChar == '=') 
        {
            // Если текущий символ - равно, выполняем оставшиеся операции в стеке операторов
            while (!operators.empty()) 
            {
                char op = operators.top();
                operators.pop();

                if (values.size() < 2) 
                {
                    cerr << "Ошибка: недостаточно операндов для операции" << endl;
                    exit(1);
                }

                double b = values.top();
                values.pop();
                double a = values.top();
                values.pop();

                double result = applyOperation(a, b, op);
                values.push(result);
            }
        }
        else if (currentChar != ' ' && currentChar != '\t') 
        {
            cerr << "Ошибка: недопустимый символ в выражении" << endl;
            exit(1);
        }
    }

    // После обработки всего выражения, результат должен быть на вершине стека значений
    if (values.size() != 1) 
    {
        cerr << "Ошибка: недостаточно операторов в выражении" << endl;
        exit(1);
    }

    return values.top();
}

int main() 
{
    setlocale(LC_ALL, "Russian");
    string expression;
    cout << "Введите математическое выражение (окончание '='): ";
    getline(cin, expression);

    double result = calculateExpression(expression);
    cout << "Результат: " << result << endl;

    return 0;
}
