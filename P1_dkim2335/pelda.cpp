#include <iostream>
#include "NagyEgesz.h"

using namespace std;

int main()
{
	cout << " + - * /  operatorok: " << endl << endl;
	int ta[] = { 1,0 };
	NagyEgesz a(1, 2, ta);
	NagyEgesz b = -3;
	NagyEgesz nulla;
	cout << "a = " << a << endl;
	cout << "b = " << b << endl;

	cout << "a + b= " << a + b << endl;
	cout << "a - b= " << a - b << endl;
	cout << "a * b= " << a * b << endl;

	try
	{
		cout << "a / 5= " << a / 5 << endl;
		cout << "b / 3= " << b / 3 << endl;
		
	}
	catch ( NagyEgesz::NullavalValoOsztas err)
	{
		cout << err.what() << endl;
	}
	cout << endl;

	cout << " ++  --  operatorok:" << endl << endl;

	cout << "n  =" << nulla << endl;
	cout << "++n= " << ++nulla << endl;
	cout << "n++= " << nulla++ << endl;
	cout << "n  = " << nulla << endl;

	cout << endl;

	cout << "--n= " << --nulla << endl;
	cout << "n--= " << nulla-- << endl;
	cout << "n  = " << nulla << endl;

	cout << endl;

	cout << "Nagy tesztek (35 szamjegy): " << endl << endl;

	int nagytomb[] = { 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
	NagyEgesz nagy1(1, 35, nagytomb);
	NagyEgesz nagy2(-1, 35, nagytomb);

	cout << "nagy1= " << nagy1 << endl << "nagy2= " << nagy2 << endl;
	cout << "nagy1 + nagy2 = " << nagy1 + nagy2 << endl;
	cout << "nagy1 - nagy2 = " << nagy1 - nagy2 << endl;
	cout << "nagy1 * nagy2 = " << nagy1 * nagy2 << endl;
	cout << "nagy1 / nagy2 = " << nagy1 / nagy2 << endl;

	return 0;
}
