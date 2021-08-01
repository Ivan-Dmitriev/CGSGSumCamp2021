/* FILE NAME  : t00PI.cpp
 * PROGRAMMER : ID3
 * LAST UPDATE: 18.07.2021
 * PURPOSE    : Pyphagorian drawing program.
 */

#include <iostream>

using namespace std;

int main( void )
{
        float first_number, step, number_of_values, current_number;
        char Buf[1000];

        cout << "Input first number:";
        cin >> first_number; 
        cout << "Input step:";
        cin >> step;
        cout << "Input number of values:";
        cin >> number_of_values;

        sprintf_s(Buf, "%f", first_number);
        cout.precision(7);
        //cout.width(10);
        
        /*
        cout << " ";
        for (float i = first_number; i < number_of_values * step + first_number; i += step)
                cout << i << " ";
        cout << endl;
        */

        for (float i = first_number; i < number_of_values * (float)step + first_number; i += step)
        {
          cout.precision(7);
          cout.width(10);
          cout << i << " ";
          for (float j = first_number + step; j < number_of_values * step + first_number; j += step)
          {
                  if (i == first_number)
                  {
                    cout.precision(7);
                    cout.width(10);
	            cout << j << " ";
                  }
                  //else if (j == (number_of_values * (step - 2) + first_number))
                  //  break;
                  else
                  {
                    cout.precision(7);
                    cout.width(10);
	            cout << i * j << " ";
                  }

                  //if (j == first_number + number_of_values * (step - 2))
          }
          cout << std::endl;
  }
  return 0;
}

/* END OF 't00pi.cpp' FILE */