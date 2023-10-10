// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len)
{
	if (len < 0)
		throw "NEGATIVE_NUMBER_OF_BITFIELD";
	BitLen = len;
	MemLen = (len - 1) / (sizeof(TELEM) * 8) + 1;
	pMem = new TELEM[MemLen];
	
	for (int i = 0; i < MemLen; ++i) 
		pMem[i] = 0;
}

TBitField::TBitField(const TBitField& bf) // конструктор копирования
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; ++i)
		pMem[i] = bf.pMem[i];
}

TBitField::~TBitField()
{
	delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	if (n < 0 || n > BitLen)
		throw "WRONG_BORDERS";
	return n / (sizeof(TELEM) * 8);
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	if (n < 0 || n > BitLen)
		throw "WRONG_BORDERS";

	return 1u << 32 - n % 32;

}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
	return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	pMem[GetMemIndex(n)] |= GetMemMask(n);
}

void TBitField::ClrBit(const int n) // очистить бит
{
	pMem[GetMemIndex(n)] &= ~(GetMemMask(n));
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if ((pMem[GetMemIndex(n)] | GetMemMask(n)) == pMem[GetMemIndex(n)])
		return 1;
	return 0;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField& bf) // присваивание
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; ++i)
		pMem[i] = bf.pMem[i];

	return *this;
}

int TBitField::operator==(const TBitField& bf) const // сравнение
{
	if (bf.BitLen != BitLen)
		return false;
	
	if (bf.MemLen != MemLen)
		return false;

	for (int i = 0; i < MemLen; ++i) {
		if (pMem[i] != bf.pMem[i])
			return 0;
	}
	return 1;

}

int TBitField::operator!=(const TBitField& bf) const // сравнение
{
	return !(bf == *this);
}

TBitField TBitField::operator|(const TBitField& bf) // операция "или"
{
	const int mn = min(BitLen, bf.BitLen);
	TBitField tmp(1);
	if (BitLen < bf.BitLen)
		tmp = bf;
	else
		tmp = *this;
	for (int i = 0; i < mn; ++i) {
		if (GetBit(i) | bf.GetBit(i))
			tmp.SetBit(i);
	}
	return tmp;
}

TBitField TBitField::operator&(const TBitField& bf) // операция "и"
{
	const int mn = min(BitLen, bf.BitLen);
	TBitField tmp(max(BitLen, bf.BitLen));
	for (int i = 0; i < mn; ++i) {
		if (GetBit(i) && bf.GetBit(i))
			tmp.SetBit(i);
	}
	return tmp;
}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField tmp(BitLen);
	for (int i = 0; i < BitLen; ++i) {
		if (!GetBit(i))
			tmp.SetBit(i);
	}
	return tmp;
}

// ввод/вывод

istream& operator>>(istream& istr, TBitField& bf) // ввод
{
	for (int i = 0; i < bf.GetLength(); ++i)
	{
		int buf;
		istr >> buf;
		if (buf)
			bf.SetBit(i);
	}
	return istr;
}

ostream& operator<<(ostream& ostr, const TBitField& bf) // вывод
{
	for (int i = 0; i < bf.BitLen; ++i)
		ostr << bf.GetBit(i);
	ostr << "\n";

	return ostr;
}
