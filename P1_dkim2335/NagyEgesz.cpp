/*
Deák Krisztián
Objektum Orientált Programozás
Projekt 1: Nagy Egész Osztály
Dátum: 2024/22/05
*/

#include "NagyEgesz.h"
#include <iostream>
#include <stdexcept>
#include <cstdlib>
using namespace std;

template <class T>
int sgn(T a)
{
    if (a < 0)
    {
        return -1;
    }
    if (a == 0)
    {
        return 0;
    }
    return 1;
}

void NagyEgesz::resize(int newSize) {

    if (newSize < 0) {
        throw invalid_argument("Helytelen meret");
    }

    if (newSize == 0)
    {
        resize(1);
        szamjegyek[0] = 0;
        elojel = 0;
        return;
    }

    if (newSize != (int)(newSize))
    {
        throw invalid_argument("Helytelen osztas");
    }

    if (szamjegyek == nullptr)
    {
        szamjegyek = new int[newSize](); 
        if (szamjegyek == nullptr)
        {
            throw bad_alloc();
        }
        n = newSize;
        return;
    }
    else
    {
        if (newSize == n) {
            return;
        }

        int* temp = new int[newSize]();
        if (temp == nullptr) {
            throw bad_alloc();
        }

        for (int i = 0; i < min(n, newSize); i++) {
            temp[i] = szamjegyek[i];
        }

        if (newSize > n)
        {
            for (int i = n; i < max(n, newSize); i++)
            {
                temp[i] = 0;
            }
        }

        delete[] szamjegyek;
        szamjegyek = temp;
        n = newSize;
    }


}

void NagyEgesz::moveRight(int m)
{
    if (m == 0)
    {
        return;
    }
    if (m < 0)
    {
        moveLeft(abs(m));
        return;
    }

    int newmax = n + m;
    int oldlength = n;
    resize(newmax);

    for (int i = oldlength-1; i >= 0; i--)
    {
        szamjegyek[i + m] = szamjegyek[i];
    }

    for (int i = 0; i < m; i++)
    {
        szamjegyek[i] = 0;
    }
    
}
// moveRight(2)
// n = 2
// newmax = 4
// 0 1
// 5 6
// 0 1 2 3
// 0 0 5 6

void NagyEgesz::moveLeft(int m)
{
    if (m < 0)
    {
        moveRight(abs(m));
        return;
    }
    if (m == 0)
    {
        return;
    }

    for (int i = 0; i < n-m; i++)
    {
        szamjegyek[i] = szamjegyek[m + i];
    }
    resize(n - m);
}

void NagyEgesz::cut()
{
    int i = 0;
    while (szamjegyek[i] == 0 && i < n)
    {
        i++;
    }
    moveLeft(i);
}

int NagyEgesz::getElojel()
{
    return elojel;
}

int NagyEgesz::getN()
{
    return n;
}

NagyEgesz::NagyEgesz() : szamjegyek(nullptr), n(1), elojel(0)
{
    resize(n);
    szamjegyek[0] = 0;
}

NagyEgesz::NagyEgesz(int e, int m, int* sz) : elojel(e), n(m), szamjegyek(nullptr)
{
    resize(n);
    for (int i = 0; i < n; ++i)
    {
        szamjegyek[i] = sz[i];
    }
}

NagyEgesz::NagyEgesz(const NagyEgesz& nagy) : elojel(nagy.elojel), n(nagy.n), szamjegyek(nullptr)
{
    resize(n);
    for (int i = 0; i < n; ++i)
    {
        szamjegyek[i] = nagy.szamjegyek[i];
    }
}

NagyEgesz::NagyEgesz(int szam)
{
    //cout << this->getN() << endl;
    n = 0;
    szamjegyek = nullptr;
    elojel = sgn(szam);
    int temp = abs(szam);
    int hossz = 1;
    while (temp > 9) {
        temp /= 10;
        hossz++;
    }
    if (hossz == 0) {
        hossz = 1; 
    }
    //cout << this->getN() << endl;
    resize(hossz);
    temp = abs(szam);
    for (int i = hossz - 1; i >= 0; --i) {
        szamjegyek[i] = temp % 10;
        temp /= 10;
    }
}

NagyEgesz::NagyEgesz(long szam) : elojel(sgn(szam)), n(0), szamjegyek(nullptr)
{
    long temp = abs(szam);
    int hossz = 0;
    while (temp > 0) {
        temp /= 10;
        hossz++;
    }
    if (hossz == 0) {
        hossz = 1;  // Handle zero case
    }
    resize(hossz);
    temp = abs(szam);
    for (int i = hossz - 1; i >= 0; --i) {
        szamjegyek[i] = temp % 10;
        temp /= 10;
    }
}

NagyEgesz::~NagyEgesz()
{
    delete[] szamjegyek;
}

ostream& operator<<(ostream& os, const NagyEgesz& ne)
{
    if (ne.elojel == 0)
    {
        os << "0";
        return os;
    }

    if (ne.elojel < 0)
    {
        os << "-";
    }

    for (int i = 0; i < ne.n; ++i)
    {
        os << ne.szamjegyek[i];
    }
    return os;
}

NagyEgesz& NagyEgesz::operator=(const NagyEgesz& nagy)
{
    if (this == &nagy)
        return *this;

    elojel = nagy.elojel;
    resize(nagy.n);
    for (int i = 0; i < n; ++i)
    {
        szamjegyek[i] = nagy.szamjegyek[i];
    }

    return *this;
}

NagyEgesz NagyEgesz::operator+(const NagyEgesz& nagy) const
{
    if (nagy == 0)
    {
        return *this;
    }
    if (*this == 0)
    {
        return nagy;
    }

    if ((this->elojel == 1 && nagy.elojel == -1) || (this->elojel == -1 && nagy.elojel == 1))
    {
        NagyEgesz temp1 = (* this).nabs();
        NagyEgesz temp2 = nagy.nabs();
        NagyEgesz eredmeny = (max(temp1, temp2) - min(temp1, temp2));
        if (eredmeny != 0)
        {
            (temp1 >= temp2) ? eredmeny.elojel = this->elojel : eredmeny.elojel = nagy.elojel;
        }
        else
        {
            eredmeny.elojel = 0;
        }
        return eredmeny;
    }

    if (this->elojel == 0) return nagy;
    if (nagy.elojel == 0) return *this;

    int ujElojel = 1;
    if (this->elojel == nagy.elojel)
    {
        ujElojel = this->elojel;
    }

    int maxHossz = max(this->n, nagy.n);
    NagyEgesz temp;
    temp.resize(maxHossz + 1);
    temp.elojel = ujElojel;

    int maradek = 0;
    for (int i = 0; i < maxHossz; ++i)
    {
        int szj = (i < this->n) ? this->szamjegyek[this->n - 1 - i] : 0;
        int nagySzj = (i < nagy.n) ? nagy.szamjegyek[nagy.n - 1 - i] : 0;
        int sum = szj + nagySzj + maradek;
        maradek = sum / 10;
        temp.szamjegyek[temp.n - 1 - i] = sum % 10;
    }

    if (maradek > 0)
    {
        temp.szamjegyek[0] = maradek;
    }
    else
    {
        temp.moveLeft(1);
    }

    temp.cut();
    return temp;
}

NagyEgesz NagyEgesz::operator-(const NagyEgesz& nagy) const
{
    NagyEgesz nulla(0);

    if (nagy == nulla)
    {
        return *this;
    }

    if (*this == nulla)
    {
        NagyEgesz temp = nagy;
        temp.elojel *= -1;
        return temp;
    }

    if (*this > nulla && nagy > nulla && *this < nagy)
    {
        NagyEgesz temp = nagy - (*this);
        temp.elojel = -1;
        return temp;  
    }

    if (*this < nulla && nagy > nulla)
    {
        NagyEgesz temp = (*this).nabs() + nagy.nabs();
        temp.elojel = -1;
        return temp;
    }

    if (*this > nulla && nagy < nulla)
    {
        NagyEgesz temp = (*this).nabs() + nagy.nabs();
        return temp;
    }

    if (*this < nulla && nagy < nulla)
    {
        NagyEgesz temp;
        if (*this < nagy)
        {
            temp = this->nabs() - nagy.nabs();
            temp.elojel = 1;
        }
        else
        {
            temp = nagy.nabs() - this->nabs();
            temp.elojel = -1;
        }
        return temp;
    }


    int ujElojel = this->elojel;

    int maxHossz = max(this->n, nagy.n);
    NagyEgesz temp;
    temp.resize(maxHossz);
    temp.elojel = ujElojel;

    if (*this < nagy)
    {
        temp.elojel = -1;
    }

    int borrow = 0;
    for (int i = 0; i < maxHossz; ++i)
    {
        int szj = (i < this->n) ? this->szamjegyek[this->n - 1 - i] : 0;
        int nagySzj = (i < nagy.n) ? nagy.szamjegyek[nagy.n - 1 - i] : 0;
        int kulonbseg = szj - nagySzj - borrow;
        if (kulonbseg < 0)
        {
            kulonbseg += 10;
            borrow = 1;
        }
        else
        {
            borrow = 0;
        }
        temp.szamjegyek[temp.n - 1 - i] = kulonbseg;
    }

    temp.cut();
    return temp;
}

NagyEgesz NagyEgesz::operator*(const NagyEgesz& nagy) const
{
    if (this->elojel == 0 || nagy.elojel == 0) return NagyEgesz();

    int ujElojel = this->elojel * nagy.elojel;

    int ujHossz = this->n + nagy.n;
    NagyEgesz temp;
    temp.resize(ujHossz);
    temp.elojel = ujElojel;

    for (int i = 0; i < this->n; ++i)
    {
        int maradek = 0;
        for (int j = 0; j < nagy.n; ++j)
        {
            int szj = this->szamjegyek[this->n - 1 - i];
            int nagySzj = nagy.szamjegyek[nagy.n - 1 - j];
            int p = szj * nagySzj + temp.szamjegyek[ujHossz - i - j - 1] + maradek;
            maradek = p / 10;
            temp.szamjegyek[ujHossz - i - j - 1] = p % 10;
        }
        temp.szamjegyek[ujHossz - i - nagy.n - 1] += maradek;
    }

    temp.cut();
    return temp;
}

NagyEgesz NagyEgesz::operator/(const NagyEgesz& nagy) const
{
    if (nagy == NagyEgesz(0))
    {
        throw invalid_argument("A nullával való osztást nem lehet elvégezni");
    }

    if (*this == NagyEgesz(0))
    {
        return NagyEgesz(0);
    }

    NagyEgesz osztando = this->nabs();
    NagyEgesz oszto = nagy.nabs();
    NagyEgesz eredmeny(0);
    NagyEgesz maradek(0);

    for (int i = 0; i < osztando.n; ++i)
    {
        // Hozzáadjuk az aktuális számjegyet
        maradek = maradek * NagyEgesz(10) + NagyEgesz(osztando.szamjegyek[i]);
        int osztas = 0;
        while (maradek >= oszto)
        {
            maradek = maradek - oszto;
            osztas++;
        }
        eredmeny = eredmeny * NagyEgesz(10) + NagyEgesz(osztas);
    }

    eredmeny.elojel = this->elojel * nagy.elojel;

    eredmeny.cut();
    return eredmeny;
}

NagyEgesz& NagyEgesz::operator+=(const NagyEgesz& nagy)
{
    *this = *this + nagy;
    return *this;
}

NagyEgesz& NagyEgesz::operator-=(const NagyEgesz& nagy)
{
    *this = *this - nagy;
    return *this;
}

NagyEgesz& NagyEgesz::operator*=(const NagyEgesz& nagy)
{
    *this = *this * nagy;
    return *this;
}

NagyEgesz& NagyEgesz::operator/=(const NagyEgesz& nagy)
{
    if (nagy == 0)
    {
        throw NullavalValoOsztas("A nullaval valo osztast nem lehet elvegezni");
        exit(1);
    }

    *this = *this / nagy;
    return *this;
}

bool NagyEgesz::operator==(const NagyEgesz& nagy) const {
    if (elojel != nagy.elojel || n != nagy.n) {
        return false;
    }
    for (int i = 0; i < n; ++i) {
        if (szamjegyek[i] != nagy.szamjegyek[i]) {
            return false;
        }
    }
    return true;
}

bool NagyEgesz::operator!=(const NagyEgesz& nagy) const {
    return !(*this == nagy);
}

bool NagyEgesz::operator<(const NagyEgesz& nagy) const {
    if (elojel != nagy.elojel) {
        return elojel < nagy.elojel;
    }
    if (n != nagy.n) {
        return n < nagy.n;
    }
    for (int i = 0; i < n; ++i) {
        if (szamjegyek[i] != nagy.szamjegyek[i]) {
            return szamjegyek[i] < nagy.szamjegyek[i];
        }
    }
    return false;
}

bool NagyEgesz::operator>(const NagyEgesz& nagy) const {
    return nagy < *this;
}

bool NagyEgesz::operator<=(const NagyEgesz& nagy) const {
    return !(*this > nagy);
}

bool NagyEgesz::operator>=(const NagyEgesz& nagy) const {
    return !(*this < nagy);
}

NagyEgesz NagyEgesz::operator++()
{
    NagyEgesz temp(1);
    *this += temp;
    return *this;
}

NagyEgesz NagyEgesz::operator++(int)
{
    NagyEgesz temp(*this);  
    ++(*this);              
    return temp;            
}

NagyEgesz NagyEgesz::operator--()
{
    NagyEgesz temp(1);
    *this -= temp;
    return *this;
}

NagyEgesz NagyEgesz::operator--(int)
{
    NagyEgesz temp(*this);
    --(*this);
    return temp;
}

NagyEgesz NagyEgesz::nmax(const NagyEgesz& nagy) const
{
    if (*this < nagy)
    {
        return nagy;
    }
    return *this;
}

NagyEgesz NagyEgesz::nmin(const NagyEgesz& nagy) const
{
    if (*this < nagy)
    {
        return *this;
    }
    return nagy;
}

NagyEgesz NagyEgesz::nabs() const
{
    NagyEgesz temp = *this;
    temp.elojel = 1;
    return temp;
}