// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"
#include <iostream>
#include <conio.h>

TSet::TSet(int mp) : BitField(mp), MaxPower(mp) {}

// конструктор копирования
TSet::TSet(const TSet &s) : BitField(s.BitField), MaxPower(s.MaxPower) {}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : BitField(bf), MaxPower(bf.GetLength()) {}

TSet::operator TBitField()
{
	return BitField;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
	return MaxPower;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
	if (Elem < 0 || Elem > MaxPower - 1)
		throw "Data is not correct";
	return (BitField.GetBit(Elem)) ? 1 : 0;
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
	if (Elem < 0 || Elem > MaxPower - 1)
		throw "Data is not correct";
	BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
	if (Elem < 0 || Elem > MaxPower - 1)
		throw "Data is not correct";
	BitField.ClrBit(Elem);
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet &s) // присваивание
{
	if (this == &s)
		return *this;
	BitField = s.BitField;
	MaxPower = s.MaxPower;
	return *this;
}

int TSet::operator==(const TSet &s) const // сравнение
{
	return (BitField == s.BitField) ? 1 : 0;
}

int TSet::operator!=(const TSet &s) const // сравнение
{
	return ((*this) == s) ? 0 : 1;
}

TSet TSet::operator+(const TSet &s) // объединение
{
	int size = (MaxPower <= s.MaxPower) ? s.MaxPower : MaxPower;
	TBitField bild(size);
	bild = BitField | s.BitField;
	TSet set(bild);
	return set;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
	if (Elem < 0 || Elem > MaxPower - 1)
		throw "Data is not correct";
	BitField.SetBit(Elem);
	return *this;

}

TSet TSet::operator-(const int Elem) // разность с элементом
{
	if (Elem < 0 || Elem > MaxPower - 1)
		throw "Data is not correct";
	BitField.ClrBit(Elem);
	return *this;
}

TSet TSet::operator*(const TSet &s) // пересечение
{
	int size = (MaxPower <= s.MaxPower) ? s.MaxPower : MaxPower;
	TBitField bild(size);
	bild = BitField & s.BitField;
	TSet set(bild);
	return set;
}

TSet TSet::operator~(void) // дополнение
{
	BitField = ~BitField;
	return *this;
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
	int temp = 1;
	while (temp)
	{
		cin >> temp;
		s.InsElem(temp);
		if (temp = _getch() == 13)
			temp = 0;
	}
	return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
	ostr << "{";
	for (int i = 0; i < s.MaxPower; i++)
	{
		if (s.IsMember(i))
		{
			ostr << i;
			if (i != s.MaxPower - 1)
				ostr << ",";
		}

	}
	ostr << "}";
	return ostr;
}