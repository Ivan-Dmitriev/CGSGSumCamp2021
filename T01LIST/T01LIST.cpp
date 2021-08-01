/* FILE NAME  : t01list.cpp
 * PROGRAMMER : ID3
 * LAST UPDATE: 17.07.2021
 * PURPOSE    : Making list program.
 */

#include <cstdio>
#include <iostream>

struct list
{
	struct entry {
		int Data;
		entry* Next;
		entry(int NewD, entry* NewN = nullptr) :
			Data(NewD), Next(NewN)
		{
		}
	} *Start;
	list(void) : Start(nullptr)
	{
	}
	~list(void)
	{
		while (Start != nullptr)
		{
			entry* old = Start;

			Start = Start->Next;
			delete old;
		}
	}
	void Add(int NewD)
	{
		Start = new entry(NewD, Start);
	}
	void AddBack(int NewD)
	{
		entry** ptr = &Start;

		if (*ptr != nullptr)
		{
			while ((*ptr)->Next != nullptr)
			{
				ptr = &(*ptr)->Next;
			}
			*ptr = new entry(NewD, nullptr);
		}
	}
	void Display(void)
	{
		entry* old = Start;

		while (old != nullptr)
		{
			std::cout << old->Data;
			old = old->Next;

		}

	}
};

/* END OF 't01list.cpp' FILE */
