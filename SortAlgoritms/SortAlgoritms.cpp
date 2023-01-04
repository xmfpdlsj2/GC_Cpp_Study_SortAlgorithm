// 정렬 알고리즘들과 각 시간복잡도(Big O) 비교

#include <iostream>

using Comparion = bool (*)(int, int);

void Sort(int[], int, Comparion);

int* Clone(int*, int);


void PrintArray(int[], int);
void Swap(int&, int&);
void SequentialSort(int[], int);
void SelectionSort(int[], int);
void BubbleSort(int[], int);
void InsertSort(int[], int);
void MergeSort(int[], int[], int, int);
void Merge(int[], int[], int, int, int);
void QuickSort(int[], int, int);

int main()
{
	//const int NUM_ARRAY = 10;
	//int scores[NUM_ARRAY]{ 20, 10, 40, 15, 30, 70, 60, 80, 90, 50 };

	//auto startTime = std::chrono::system_clock::now();
	//Sort(scores, NUM_ARRAY, Ascending);
	//auto endTime = std::chrono::system_clock::now();

	//auto duration = endTime - startTime;
	//std::cout << "Sort : " << duration.count() << "ms" << std::endl;

	//for (int i = 0; i < NUM_ARRAY; i++)
	//{
	//	std::cout << scores[i] << std::endl;
	//}

	// 복잡도를 위한 예제 (36강)
	//const int COUNT = 10;
	//int array[COUNT]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

	//int* newArray{};

	//newArray = Clone(array, COUNT);
	//for (int i = 0; i < 10; i++)
	//{
	//	std::cout << newArray[i] << std::endl;
	//}
	//delete[] newArray;
	//newArray = nullptr;

	// 정렬을 빠르게 만들어보는 예제 (36-37강)
	const int NUM_ARRAY = 10;
	int scores[NUM_ARRAY]{ 20, 10, 40, 15, 30, 70, 60, 80, 90, 50 };
	int tempScores[NUM_ARRAY]{};

	//SequentialSort(scores, NUM_ARRAY);
	//SelectionSort(scores, NUM_ARRAY);
	//BubbleSort(scores, NUM_ARRAY);
	//InsertSort(scores, NUM_ARRAY);

	//MergeSort(scores, tempScores, 0, NUM_ARRAY - 1);
	QuickSort(scores, 0, NUM_ARRAY - 1);

	PrintArray(scores, NUM_ARRAY);
}

bool Ascending(int x, int y)
{
	return x > y;
}

bool Decending(int x, int y)
{
	return x < y;
}

void Sort(int numbers[], int count, Comparion f)
{
	int temp{};

	for (int i = 0; i < count; i++)
	{
		for (int j = 0; j < count; j++)
		{
			if (f(numbers[i], numbers[j]))
			{
				temp = numbers[i];
				numbers[i] = numbers[j];
				numbers[j] = temp;
			}
		}
	}
}

// 복잡도를 위한 예제 (36강)
int* Clone(int* origin, int num)
{
	int* copy{ new int[num] };
	if (copy)
	{
		for (int i = 0; i < num; i++)
		{
			copy[i] = origin[i];
		}
	}
	return copy;
}

// 정렬을 빠르게 만들어보는 예제 (36-37강)
void PrintArray(int input[], int size)
{
	for (int i = 0; i < size; i++)
	{
		std::cout << input[i] << " ";
	}
	std::cout << std::endl;
}

void Swap(int& x, int& y)
{
	int temp{ x };
	x = y;
	y = temp;
}

// 순차 정렬
//Time Complexity = O(n^2)
//Space Complexity = O(n)
void SequentialSort(int input[], int size)
{
	for (int i = 0; i < size - 1; ++i)
	{
		for (int j = 0; j < size; ++i)
		{
			if (input[i] > input[j])
			{
				Swap(input[i], input[j]);
			}
		}
	}
}

// 선택 정렬
//Time Complexity = O(n^2)
//Space Complexity = O(n)
void SelectionSort(int input[], int size)
{
	for (int i = 0; i < size; i++)
	{
		int minIndex{ i };
		for (int j = i; j < size; j++)
		{
			if (input[j] < input[minIndex])
			{
				minIndex = j;
			}
		}
		if (minIndex != i)
		{
			Swap(input[i], input[minIndex]);
		}
	}
}

// 버블 정렬
//Time Complexity = O(n^2)
//Space Complexity = O(n)
void BubbleSort(int input[], int size)
{
	for (int i = 0; i < (size - 1); i++)
	{
		for (int j = 0; j < (size - 1 - i); j++)
		{
			if (input[j] > input[j + 1])
			{
				Swap(input[j], input[j + 1]);
			}
		}
	}
}

// 삽입 정렬
//Time Complexity = O(n^2)
//Space Complexity = O(n)
void InsertSort(int input[], int size)
{
	for (int i = 1; i < size; i++)
	{
		int j = i;
		int target{ input[j] };
		while (j-- >= 0 && target < input[j])
		{
			input[j + 1] = input[j];
			input[j] = target;
		}
	}
}

// Divide & Conquer
// Divide
//Time Complexity = O(n log n)
//Space Complexity = O(n)
void MergeSort(int input[], int tempArray[], int start, int end)
{
	// base case
	if (start >= end)
	{
		return;
	}

	// recursive case
	int half = (start + end) / 2;

	MergeSort(input, tempArray, start, half);
	MergeSort(input, tempArray, half + 1, end);

	Merge(input, tempArray, start, half, end);
}

// Conquer
void Merge(int input[], int temp[], int start, int half, int end)
{
	int i{ start }, j{ half + 1 }, k{ 0 };
	while (i <= half && j <= end)
	{
		if (input[i] < input[j])
		{
			temp[k++] = input[i++];
		}
		else
		{
			temp[k++] = input[j++];
		}
	}

	// 남은 블럭 병합
	while (i <= half)
	{
		temp[k++] = input[i++];
	}
	while (j <= end)
	{
		temp[k++] = input[j++];
	}

	// 원래 배열로 복사
	k = 0;
	for (int i = start; i <= end; ++i)
	{
		input[i] = temp[k++];
	}
}

// Quick Sort
// Time Complexity = O(n log n)
// Space Complexity = O(n)
void QuickSort(int input[], int left, int right)
{
	int i{ left }, j{ right }, pivot{ input[(left + right) / 2] };

	do
	{
		while (input[i] < pivot)
		{
			i++;
		}
		while (input[j] > pivot)
		{
			j--;
		}

		if (i <= j) // 크로스가 일어나면 안됨.
		{
			Swap(input[i], input[j]);
			i++;
			j--;
		}
	} while (i <= j);

	// recursive case + 조건문 추가로 basecase 없게.
	if (left < j)
	{
		QuickSort(input, left, j);
	}
	if (i < right)
	{
		QuickSort(input, i, right);
	}
}