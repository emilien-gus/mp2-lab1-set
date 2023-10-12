// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

TSet::TSet(int mp) : BitField(mp), MaxPower(mp)
{
}

// конструктор копирования
TSet::TSet(const TSet &s) : BitField(s.BitField), MaxPower(s.MaxPower)
{
}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : BitField(bf), MaxPower(bf.GetLength())
{
}

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
    if (Elem < 0 || Elem >= MaxPower)
        throw "ERROR_IS_MEMBER_OUT_OF_RANGE";

    return BitField.GetBit(Elem);
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
    if (Elem < 0 || Elem >= MaxPower)
        throw "ERROR_INS_ELEMENT_OUT_OF_RANGE";
    BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
    if (Elem < 0 || Elem >= MaxPower)
        throw "ERROR_DEL_ELEMENT_OUT_OF_RANGE";
    BitField.ClrBit(Elem);
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet &s) // присваивание
{
    if (this == &s)
        return *this;
    MaxPower = s.MaxPower;
    BitField = s.BitField;
    return *this;
}

int TSet::operator==(const TSet &s) const // сравнение
{
    if (MaxPower != s.MaxPower)
        return 0;
    if (BitField != s.BitField)
        return 0;
    return 1;
}

int TSet::operator!=(const TSet &s) const // сравнение
{
    return !(*this == s);
}

TSet TSet::operator+(const TSet &s) // объединение
{
    TSet buf(max(MaxPower, s.GetMaxPower()));
    buf.BitField = BitField | s.BitField;
    return buf;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
    if (Elem < 0 || Elem >= MaxPower)
        throw "ERROR_PLUS_OPERATOR";
    TSet buf(*this);
    buf.BitField.SetBit(Elem);
    return buf;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
    if (Elem < 0 || Elem >= MaxPower)
        throw "ERROR_MINUS_OPERATOR";
    TSet buf(*this);
    buf.BitField.ClrBit(Elem);
    return buf;
}

TSet TSet::operator*(const TSet &s) // пересечение
{
    TSet buf(max(MaxPower, s.GetMaxPower()));
    buf.BitField = BitField & s.BitField;
    return buf;
}

TSet TSet::operator~(void) // дополнение
{
    TSet buf(*this);
    buf.BitField = ~buf.BitField;
    return buf;
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
    TELEM buf;
    istr >> buf;
    if (buf < 0 || buf >= s.GetMaxPower())
        throw "ERROR_IN_CIN_NUMBER_IS_OUT_OF_RANGE";
    s.InsElem(buf);
    return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
    for (int i = 0; i < s.GetMaxPower(); ++i)
        if (s.IsMember(i))
            ostr << i << " ";
    return ostr;
}
