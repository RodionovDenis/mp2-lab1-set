// ����, ���, ���� "������ ����������������-2", �++, ���
//
// tset.cpp - Copyright (c) ������� �.�. 04.10.2001
//   ������������ ��� Microsoft Visual Studio 2008 �������� �.�. (19.04.2015)
//
// ��������� - ���������� ����� ������� ����

#include "tset.h"
#include <iostream>
#include <conio.h>

TSet::TSet(int mp) : BitField(mp), MaxPower(mp) {}

// ����������� �����������
TSet::TSet(const TSet &s) : BitField(s.BitField), MaxPower(s.MaxPower) {}

// ����������� �������������� ����
TSet::TSet(const TBitField &bf) : BitField(bf), MaxPower(bf.GetLength()) {}

TSet::operator TBitField()
{
	return BitField;
}

int TSet::GetMaxPower(void) const // �������� ����. �-�� ��-���
{
	return MaxPower;
}

int TSet::IsMember(const int Elem) const // ������� ���������?
{
	if (Elem < 0 || Elem > MaxPower - 1)
		throw "Data is not correct";
	return (BitField.GetBit(Elem)) ? 1 : 0;
}

void TSet::InsElem(const int Elem) // ��������� �������� ���������
{
	if (Elem < 0 || Elem > MaxPower - 1)
		throw "Data is not correct";
	BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // ���������� �������� ���������
{
	if (Elem < 0 || Elem > MaxPower - 1)
		throw "Data is not correct";
	BitField.ClrBit(Elem);
}

// ���������-������������� ��������

TSet& TSet::operator=(const TSet &s) // ������������
{
	if (this == &s)
		return *this;
	BitField = s.BitField;
	MaxPower = s.MaxPower;
	return *this;
}

int TSet::operator==(const TSet &s) const // ���������
{
	return (BitField == s.BitField) ? 1 : 0;
}

int TSet::operator!=(const TSet &s) const // ���������
{
	return ((*this) == s) ? 0 : 1;
}

TSet TSet::operator+(const TSet &s) // �����������
{
	int size = (MaxPower <= s.MaxPower) ? s.MaxPower : MaxPower;
	TBitField bild(size);
	bild = BitField | s.BitField;
	TSet set(bild);
	return set;
}

TSet TSet::operator+(const int Elem) // ����������� � ���������
{
	if (Elem < 0 || Elem > MaxPower - 1)
		throw "Data is not correct";
	BitField.SetBit(Elem);
	return *this;

}

TSet TSet::operator-(const int Elem) // �������� � ���������
{
	if (Elem < 0 || Elem > MaxPower - 1)
		throw "Data is not correct";
	BitField.ClrBit(Elem);
	return *this;
}

TSet TSet::operator*(const TSet &s) // �����������
{
	int size = (MaxPower <= s.MaxPower) ? s.MaxPower : MaxPower;
	TBitField bild(size);
	bild = BitField & s.BitField;
	TSet set(bild);
	return set;
}

TSet TSet::operator~(void) // ����������
{
	BitField = ~BitField;
	return *this;
}

// ���������� �����/������

istream &operator>>(istream &istr, TSet &s) // ����
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

ostream& operator<<(ostream &ostr, const TSet &s) // �����
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