/*
Deák Krisztián
Objektum Orientált Programozás
Projekt 1: Nagy Egész Osztály
Dátum: 2024/22/05
*/


#ifndef NagyEgesz_H
#define NagyEgesz_H

#include <iostream>

using namespace std;

class NagyEgesz
{
private:
	int elojel;
	int n;
	int* szamjegyek;

public:
	NagyEgesz();
	NagyEgesz(int, int, int*);
	NagyEgesz(const NagyEgesz&);
	NagyEgesz(int);
	NagyEgesz(long);
	~NagyEgesz();


	void resize(int);
	void moveRight(int);
	void moveLeft(int);
	void cut();

	int getElojel();
	int getN();

	NagyEgesz operator+(const NagyEgesz&) const;
	NagyEgesz operator-(const NagyEgesz&) const;
	NagyEgesz operator*(const NagyEgesz&) const;
	NagyEgesz operator/(const NagyEgesz&) const;

	NagyEgesz& operator=(const NagyEgesz& nagy);

	NagyEgesz& operator+=(const NagyEgesz&);
	NagyEgesz& operator-=(const NagyEgesz&);
	NagyEgesz& operator*=(const NagyEgesz&);
	NagyEgesz& operator/=(const NagyEgesz&);

	friend ostream& operator<<(ostream&, const NagyEgesz& );
	
	bool operator==(const NagyEgesz&) const;
	bool operator!=(const NagyEgesz&) const;
	bool operator<(const NagyEgesz&) const;
	bool operator>(const NagyEgesz&) const;
	bool operator<=(const NagyEgesz&) const;
	bool operator>=(const NagyEgesz&) const;
	
	NagyEgesz operator++();
	NagyEgesz operator++(int);

	NagyEgesz operator--();
	NagyEgesz operator--(int);

	NagyEgesz nmax(const NagyEgesz&) const;
	NagyEgesz nmin(const NagyEgesz&) const;
	NagyEgesz nabs() const;


public:

	class NullavalValoOsztas : exception
	{
	private:
		string msg;
	public:
		NullavalValoOsztas(string m) : msg(m) {}
		const char* what() const
		{
			return msg.c_str();
		}
	};

};


#endif // !NagyEgesz_H
