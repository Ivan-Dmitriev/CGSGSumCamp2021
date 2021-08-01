/* FILE NAME  : t04list.cpp
 * PROGRAMMER : ID3
 * LAST UPDATE: 19.07.2021
 * PURPOSE    : Linear single-connected list making program.
 */

#include <commondf.h>

#include <iostream>
#include <list>
#include <cstdio>
#include <cassert>

/* Debug memory allocation support */ 
#ifndef NDEBUG 
# define _CRTDBG_MAP_ALLOC
# include <crtdbg.h>
# define SetDbgMemHooks() \
  _CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_CHECK_ALWAYS_DF | \
  _CRTDBG_ALLOC_MEM_DF | _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG))

static class __Dummy 
{ 
public: 
  /* Class constructor */
  __Dummy( VOID ) 
  { 
    SetDbgMemHooks(); 
  } /* End of '__Dummy' constructor */
} __ooppss;
#endif /* _DEBUG */ 

#ifdef _DEBUG 
# ifdef _CRTDBG_MAP_ALLOC 
#   define new new(_NORMAL_BLOCK, __FILE__, __LINE__) 
# endif /* _CRTDBG_MAP_ALLOC */ 
#endif /* _DEBUG */

namespace id3
{
  /* Linear single-connected list handle class */
  template<typename Type>
    class list
    {
    private:
      int priv_length;
      struct entry
      {
        Type Data;
        entry* Next;
        entry (Type NewD, entry* NewN = nullptr) : Data(NewD), Next(NewN)
        {
        }
      } *Start;
    public:
      const int *length_ = &priv_length;

      /* Constructor of list class function.
       * ARGUMENTS: None.
       * RETURNS: None.  
       */
      list( void ) : Start(nullptr)
      {
        priv_length = 0;
      } /* End of default constructor */

      /* Destructor of list class function.
       * ARGUMENTS: None.
       * RETURNS: None.
       */
      ~list( void )
      {
        while (Start != nullptr)
        {
          entry* old = Start;

          Start = Start->Next;
          delete old;
        }
      } /* End of default destructor */

      /* Push one element to the beginning of the list function.
       * ARGUMENTS: 
       *   - Data to be add:
       *       Type NewD;
       * RETURNS: (list &) link on list.
       */
      list & PushFront( Type NewD )
      {
        Start = new entry(NewD, Start);
        priv_length++;
        return *this;
      } /* End of 'PushFront' function */

      /* Push one element to the end of the list function.
       * ARGUMENTS: 
       *   - Data to be add:
       *       Type NewD;
       * RETURNS: (list &) link on list.
       */
      list & PushBack( Type NewD )
      {
        entry** ptr = &Start;

        while (*ptr != nullptr)
          ptr = &(*ptr)->Next;

        *ptr = new entry(NewD, nullptr);
        priv_length++;
        return *this;
      } /* End of 'PushBack' function */
      
      /* Pop one element of the beginning of the list function.
       * ARGUMENTS: 
       *   - Link on deleted data:
       *       Type & DelVal;
       * RETURNS: (INT) TRUE if success, FALSE otherwise.
       */
      INT PopFront( Type & DelVal )
      { 
        if (Start == nullptr)
        {
          DelVal = 0;
          return false;
        }
        entry* old = Start;
        Type deleted = old->Data;
        Start = Start->Next;
        delete old;
        priv_length--;
        DelVal = deleted;
        return true;
      } /* End of 'PopFront' function */

      /* Pop one element from the end of the list function.
       * ARGUMENTS: 
       *   - Link on deleted data:
       *       Type & DelVal;
       * RETURNS: (INT) TRUE if success, FALSE otherwise.
       */
      INT PopBack( Type & DelVal )
      { 
        if (Start == nullptr)
        {
          DelVal = 0;
          return false;
        }
        entry* ptr = Start;

        if (ptr->Next == nullptr && ptr != nullptr)
        {
          entry* old = ptr;
        
          Start = nullptr;

          Type deleted_ = old->Data;
          delete old;
          priv_length--;
          DelVal = deleted_;

          return TRUE;
        }
        while (ptr != nullptr)
        {
          if (ptr->Next->Next == nullptr)
            break;
          ptr = ptr->Next;
        }

        if (ptr == nullptr || ptr->Next == nullptr)
        {
          DelVal = 0;
          return false;
        }
        entry* old = ptr->Next;
        
        ptr->Next = nullptr;

        Type deleted = old->Data;
        delete old;
        priv_length--;
        DelVal = deleted;

        return true;
      } /* End of 'PopBack' function */

      /* Copy constructor of the list function.
       * ARGUMENTS: 
       *   - List to copy from:
       *       const list &NewL;
       * RETURNS: (list) created list.
       */
      list( list &NewL )
      {
        Type x;
        
        while (Start != nullptr)
          PopFront(x);
        if (Start == nullptr)
          Start = new entry(0, Start);

        entry **CopiedPtr = &Start;
        entry **PtrForCopy = &NewL.Start;

        while (*PtrForCopy != nullptr)
        {
          *CopiedPtr = new entry((*PtrForCopy)->Data, nullptr);

          CopiedPtr = &(*CopiedPtr)->Next;
          PtrForCopy = &(*PtrForCopy)->Next;
        }

        /*
        while (CopiedPtr != nullptr)
        {
          PushBack(ptr->Data);
          ptr = ptr->Next;
        }
        */
      } /* End of copy constructor */

      /* Get element from list by index function.
       * ARGUMENTS: 
       *   - Data to be add:
       *       int i;
       * RETURNS: (Type) element by index.
       */
      Type & operator[]( int index )
      {
        //static Type x = (Type)((VOID *)0);
        entry *ptr = Start;

        while ((index-- > 0) && (ptr != nullptr))
          ptr = ptr->Next;

        //if (ptr == nullptr)
        //  this->Clear();
        assert(ptr != nullptr);

        /*
        if (index < 0 || index >= priv_length)
          return Start->Data;
        */

        return ptr->Data;
      }
      /* Display all elements of the list function.
       * ARGUMENTS: None.
       * RETURNS: None.  
       */
      void Display( void )
      {
        entry* old = Start;

        if (Start == nullptr)
        {
          std::cout << "List is empty" << std::endl;
          return;
        }
        while (old != nullptr)
        {
          std::cout << old->Data << " ";
          old = old->Next;
        }
        std::cout << std::endl;
      } /* End of 'Display' function */

      /* Clear list function.
       * ARGUMENTS: None.
       * RETURNS: None.
       */
      void Clear( void )
      {
        priv_length = 0;
        while (Start != nullptr)
        {
          entry* old = Start;

          Start = Start->Next;
          delete old;
        }
      } /* End of 'Clear' function */
      list & operator=( const list &list2 )
      {
        //this->Clear();
        entry *ptr = list2.Start;

        while (ptr != nullptr)
        {
          PushBack(ptr->Data);
          ptr = ptr->Next;
        }
         
        return *this;
      }
      list & operator<<( char *Text ) 
      {
        entry *ptr = Start;

        while (ptr != nullptr)
        {
          std::cout << ptr->Data << " ";
          ptr = ptr->Next;
        }
        return *this;
      }
    };
}

INT main( void )
{
  id3::list<double> L;
  double del_x;
  double &x = del_x;
  char buf[100];

  std::list<double> s;
  //SetDbgMemHooks();
  //L.PushFront(10);
  //L.PushFront(30);
  //L.PushFront(47);
  /*
  L.PushBack(3).PushBack(100).PushFront(30).Display();
  L.PopBack(del_x);
  L.Display();
  L.Clear();
  L.Display();
  sprintf_s(buf, "Deleted: %f", del_x);
  std::cout << buf;
  for (int i = 0; i < 100; i++)
    L.PushBack((rand() - (double)RAND_MAX / 2) / 102.0);
  L.PushBack(3);
  L.Display();
  L.Display();
  sprintf_s(buf, "Deleted: %f", del_x);
  std::cout << buf;
  for (int i = 0; i < 1000; i++)
    L.PushBack((rand() - (double)RAND_MAX / 2) / 102.0);
  */
  //std::cout << *L.length_;
  L.PushBack(30).PushBack(47);

  //L << " ";

  L[1] = 303030;
  L[0] = 12;

  //std::cout << L[0];

  id3::list<double> L2(L);
  L2 = L;
  
  //L.Display();
  for (int i = 0; i < 10000; i++)
  {
    L.PopFront(del_x);
    //sprintf_s(buf, "Deleted: %f", del_x);
    //std::cout << buf << std::endl;
  }

  //L.Display();
  std::cout << *L.length_;

  return 0;
}

/* END OF 't04list.cpp' FILE */