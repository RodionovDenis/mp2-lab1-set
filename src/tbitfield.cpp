// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len) //конструктор
{
	if (len <= 0)
		throw "Data is not correct";
	BitLen = len;
	MemLen = (BitLen - 1) / (8 * sizeof(TELEM)) + 1; 
	pMem = new TELEM[MemLen]; 
	for (int i = 0; i < MemLen; i++) 
		pMem[i] = 0;
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	MemLen = bf.MemLen;
	BitLen = bf.BitLen;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++)
		pMem[i] = bf.pMem[i];
}

TBitField::~TBitField()
{
	delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	if (n < 0 || BitLen - 1 < n)
		throw "Data is not correct";
	return n / (sizeof(TELEM) * 8);
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	if (n < 0 || BitLen - 1 < n)
		throw "Data is not correct";
	int count = n % (sizeof(TELEM) * 8); 
	TELEM mask = 1;
	return mask << count;
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
	return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if (n < 0 || BitLen - 1 < n)
		throw "Data is not correct";
	int mem = (*this).GetMemIndex(n); //номер блока
	TELEM mask = (*this).GetMemMask(n);
	pMem[mem] |= mask;
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if (n < 0 || BitLen - 1 < n)
		throw "Data is not correct";
	int mem = (*this).GetMemIndex(n); //номер блока
	TELEM mask = (*this).GetMemMask(n);
	TELEM mask_negation = ~mask;
	pMem[mem] = pMem[mem] & mask_negation;
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if (n < 0 || BitLen - 1 < n)
		throw "Data is not correct";
	int mem = (*this).GetMemIndex(n); //номер блока
	int flag = n % (sizeof(TELEM) * 8);
	return (pMem[mem] >> flag) & 1;
}

// битовые операции

TBitField & TBitField::operator=(const TBitField &bf) // присваивание
{
	if (this == &bf)
		return *this;
	if (BitLen != bf.BitLen)
	{
		delete[] pMem;
		pMem = new TELEM[bf.MemLen];
	}
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	for (int i = 0; i < MemLen; i++)
		pMem[i] = bf.pMem[i];
	return *this;
}
int TBitField::operator==(const TBitField &bf) const // сравнение
{
	if (BitLen != bf.BitLen)
		return 0;
	for (int i = 0; i < BitLen; i++)
		if (GetBit(i) != bf.GetBit(i))
			return 0;
	return 1;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
	if ((*this) == bf)
		return 0;
	else
		return 1;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	if ((*this) == bf) 
		return *this;
	int flag = (BitLen >= bf.BitLen) ? 1 : 0;
	int count = flag ? bf.BitLen : BitLen;
	TBitField bit_copy = flag ? *this : bf;
	for (int i = 0; i < count; i++)
	{
		if (GetBit(i) | bf.GetBit(i)) 
			bit_copy.SetBit(i);
	}
	return bit_copy;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	if ((*this) == bf) 
		return *this;
	int count1 = (BitLen >= bf.BitLen) ? BitLen : bf.BitLen;
	int count2 = (BitLen >= bf.BitLen) ? bf.BitLen : BitLen;
	TBitField bit_copy(count1);
	for (int i = 0; i < count2; i++) 
		if (GetBit(i) & bf.GetBit(i))
			bit_copy.SetBit(i);
	return bit_copy;
}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField bit_copy = (*this);
	for (int i = 0; i < BitLen; i++) 
	{
		if (bit_copy.GetBit(i))
			bit_copy.ClrBit(i);
		else 
			bit_copy.SetBit(i);
	}
	return bit_copy;
}

//// ввод/вывод
//
istream &operator>>(istream &istr, TBitField &bf) // ввод
{
	int size = bf.GetLength();
	for (int i = 0; i < size; i++)
	{
		int value;
		istr >> value;
		if (value == 1)
			bf.SetBit(i);
		else if (value == 0)
			bf.ClrBit(i);
		else throw "Data is not correct";
	}
	return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	int size = bf.GetLength();
	for (int i = 0; i < size; i++)
	{
		ostr << bf.GetBit(i);
	}
	return ostr;
}