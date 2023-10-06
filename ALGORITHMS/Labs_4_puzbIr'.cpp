#include <iostream>

int main()
{
    setlocale(LC_ALL, "Russian");
    int N;
    int temp; // Временная переменная для сохранения элемента
    int min = INT_MIN;
    std::cout << "Введите кол-во элементов последовательности: ";
    std::cin >> N;
    int* arr = new int [N];
    for (int i = 0; i < N; i++)
    {
        std::cout << "Введите " << i + 1 << "-й элемент: ";
        std::cin >> arr[i];
    }
    int numb;
    std::cout << "Введите номер сортировки(нужен просто номер): ";
    std::cin >> numb;
    switch (numb)
    {
    case 4: // Тут всё просто, начинаем с левого конца, и попрано смотрим числа, если справа старше, то они меняются, нет, идём дальше. Так N раз пока все не встанут на свои места Сложность O(N^2)
        for (int i = 0; i < N - 1; i++) 
        {
            for (int j = 0; j < N - i - 1; j++) 
            {
                if (arr[j] > arr[j + 1]) 
                {
                    temp = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = temp;
                }
            }
        }
        std::cout << "Была выыедена последовательность, после сортировки пузырьком:" << std::endl;
        break;
    case 5: // Тут подразумевается, что мы смотрим числа слева направо, находим первый элемент, который соответсвует условию цикла, и переносим его сразу на своё место. Сложность O(N^2)
        for (int i = 1; i < N; i++) 
        {
            for (int j = i; j > 0 && arr[j - 1] > arr[j]; j--) 
            {
                temp = arr[j - 1];
                arr[j - 1] = arr[j];
                arr[j] = temp;
            }
        }
        std::cout << "Была выыедена последовательность, после сортировки вставками:" << std::endl;
        break;
    case 6: // N-1 шагов, в которых N сравнений и 1 обмен, что соответсвует сложности O(N^2)
        for (int i = 0; i < N; i++)
        {
            min = i;
            for (int j = i + 1; j < N; j++)
            {
                if (arr[j] < arr[min])
                {
                    min = j;
                }
            }
            temp = arr[i];
            arr[i] = arr[min];
            arr[min] = temp;
        }
        break;
        std::cout << "Была выыедена последовательность, после сортировки выбором:" << std::endl;
     case 7:
        int j, step, i;
        for (step = N / 2; step > 0; step /= 2)
        {
            for (i = step; i < N; i++)
                {
                    temp = arr[i];
                    for (j = i; j >= step; j -= step)
                    {
                        if (temp < arr[j - step])
                        {
                            arr[j] = arr[j - step];
                        }
                        else
                        {
                            break;
                        }
                    }
                    arr[j] = temp;
                }
        }
        break;
        std::cout << "Была выведена последовательность, после Shell sort:" << std::endl;
    default:
        std::cout << "Что-то пошло не так ;(" << "\n";
        exit(0);
    }
 

    for (int i = 0; i < N; i++)
    {
        std::cout << arr[i] << " ";
    }
}

