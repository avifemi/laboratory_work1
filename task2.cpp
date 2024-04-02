#include <iostream>
#include <cstring>

using namespace std;

class logical_values_array
{
private:
    unsigned int _value; //0 принимаем за false, а !0 за true
public:
    unsigned int get_value(); //accessor или же просто геттер(метод get)
    logical_values_array(); //конструктор без принимабщих параметров
    logical_values_array(unsigned int value); //конструктор
    logical_values_array& operator=(unsigned int value);
    logical_values_array& inversion_value(); //инверсия
    logical_values_array& conjunction_value(logical_values_array ob); //конъюкция
    logical_values_array& disjunction_value(logical_values_array ob); //дизъюнкция
    logical_values_array& implication_value(logical_values_array ob); //импликация
    logical_values_array& coimplication_value(logical_values_array ob); //коимпликация
    logical_values_array& addition_modulo_2_value(logical_values_array ob); //сложение по модулю 2
    logical_values_array& equivalence_value(logical_values_array ob); //эквивалентность
    logical_values_array& Pier_arrow_value(logical_values_array ob); //стрелка Пирса
    logical_values_array& Schaeffers_stroke_value(logical_values_array ob); //штрих Шеффера
    static bool equals(unsigned int a, unsigned int b); //я принимаю это как полную экв. типа 1!=45, 1=1, 45=45
    char* perevod2cc();
    char get_bit(unsigned int position);
};

unsigned int logical_values_array::get_value()
{
    return _value;
}

logical_values_array::logical_values_array()
{
    _value = 0;
}

logical_values_array::logical_values_array(unsigned int value)
{
    _value = value;
}

logical_values_array& logical_values_array::operator=(unsigned int value)
{
    _value = value;
    
    return *this;
}

logical_values_array& logical_values_array::inversion_value()
{
    if(_value == 0)
    {
        _value = 1;
    }
    
    else
    {
        _value = 0;
    }
    
    return *this;
}

logical_values_array& logical_values_array::conjunction_value(logical_values_array ob)
{
    if((_value >= 1) && (ob._value >= 1))
    {
        _value = 1;
    }
    
    else
    {
        _value = ob._value * _value;
    }
    
    return *this;
}

logical_values_array& logical_values_array::disjunction_value(logical_values_array ob)
{
    if(_value == 0 && ob._value == 0)
    {
        _value = 0;
    }
    
    else
    {
        _value = 1;
    }
    
    return *this;
}

logical_values_array& logical_values_array::implication_value(logical_values_array ob)
{
    logical_values_array ob1(_value);
    ob1.inversion_value();
    ob1.disjunction_value(ob);
    _value = ob1._value;
    
    return *this;
}

logical_values_array& logical_values_array::coimplication_value(logical_values_array ob)
{
    logical_values_array ob1(_value);
    ob1.implication_value(ob);
    _value = ob1._value;
    if(_value == 0)
    {
        _value = 1;
    }
    
    else
    {
        _value = 0;
    }
    
    return *this;
}

logical_values_array& logical_values_array::addition_modulo_2_value(logical_values_array ob)
{
    //формула: (X1∨ X2) ∧ (¬X1∨ ¬X2)
    logical_values_array a(_value);
    logical_values_array a1(_value);
    
    a.disjunction_value(ob); //левая скобка
    a1.inversion_value();
    ob.inversion_value();
    a1.disjunction_value(ob); //правая скобка
    a1.conjunction_value(a);
    _value = a1._value;
    
    return *this;
}

logical_values_array& logical_values_array::equivalence_value(logical_values_array ob)
{
    //формула (X1∨¬X2) ∧ (¬X1∨X2)
    logical_values_array a(_value);
    logical_values_array a1(_value);
    ob.inversion_value();
    a.disjunction_value(ob); //левая скобка
    a1.inversion_value();
    ob.inversion_value(); //вернули x2 в исходное состояние
    a1.disjunction_value(ob); //правая скобка
    a.conjunction_value(a1);
    _value = a._value;
    
    return *this;
}

logical_values_array& logical_values_array::Pier_arrow_value(logical_values_array ob)
{
    //формула ¬X1 ∧ ¬X2
    logical_values_array a(_value);
    a.inversion_value();
    ob.inversion_value();
    a.conjunction_value(ob);
    _value = a._value;
    
    return *this;
}

logical_values_array& logical_values_array::Schaeffers_stroke_value(logical_values_array ob)
{
    //формула ¬X1 ∨ ¬X2
    logical_values_array a(_value);
    a.inversion_value();
    ob.inversion_value();
    a.disjunction_value(ob);
    _value = a._value;
    
    return *this;
}

bool logical_values_array::equals(unsigned int a, unsigned int b)
{
    if(a == b)
    {
        return true;
    }
    
    else
    {
        return false;
    }
}

char* logical_values_array::perevod2cc()
{
    unsigned int a;
    char* mas = new char[sizeof(unsigned int) +1]; //создаем массив для хранения числа в 2сс в виде строки
    char*ptr = mas + sizeof(unsigned int); //создаем указатель на предпоследнюю ячейку в массиве(тк число будет справа на лево)
    mas[sizeof(unsigned int) + 1] = '\0'; //строка оканчивается \0, поэтому сразу ставим в этом массиве
    
    while(_value != 0)
    {
        a = _value & 0x00000001; //извлекаем последний бит
        *ptr = '0' + a; //бит преобразуеи в символ и записываем в ячейку, куда указывает *ptr
        ptr--;
        _value = _value >> 1; //подвинули на один бит
    }
    
    return ++ptr;
}

char logical_values_array::get_bit(unsigned int position)
{
    char* ptr;
    logical_values_array ob(_value);
    ptr = ob.perevod2cc();
    if(position > strlen(ptr))
    {
        return ptr[strlen(ptr) - 1];
    }
    
    else
    {
        return ptr[position];
    }
}

int main()
{
    logical_values_array ob(10);
    logical_values_array ob1;
    
    //ob.perevod2cc();
    
    std::cout<<ob.perevod2cc();
}