#include <iostream>
#include <cmath>
using namespace std;

class complex_numbers
{
private:
    double Re; //Re - действительная часть
    double Im; //Im - мнимая часть
public:
    complex_numbers(); //конструктор без параметров
    complex_numbers(double Re, double Im); //конструктор
    complex_numbers& operator =(complex_numbers const& first_num);
    complex_numbers& operator +=(complex_numbers const& first_num);
    complex_numbers& operator +(complex_numbers const& first_num);
    complex_numbers& operator -(complex_numbers const& first_num);
    complex_numbers& operator *(complex_numbers const& first_num);
    complex_numbers& operator /(complex_numbers const& first_num);
    void arg_complex_numbers();
    double mod_complex_numbers();
    void show();
};

void complex_numbers::arg_complex_numbers()
{
    std::cout<< atan(Im/Re) << "+2πn, где n ∈ Z";
}

void complex_numbers::show()
{
    if(Im >= 0)
    {
        std::cout << "Комплексное число = " << Re << "+" << Im << "i" << endl;
    }
    else
    {
        std::cout << "Комплексное число = " << Re << Im << "i" << endl;
    }
}
    
double complex_numbers::mod_complex_numbers()
{
        return sqrt((Re*Re) + (Im*Im));
}
    
complex_numbers::complex_numbers(double Re1, double Im1)
{
    Re = Re1;
    Im = Im1;
}

complex_numbers::complex_numbers()
{
    Re = 0.0;
    Im = 0.0;
}

complex_numbers& complex_numbers::operator=(complex_numbers const& first_num)
{
    Re = first_num.Re;
    Im = first_num.Im;

    return *this;
}

complex_numbers& complex_numbers::operator+=(complex_numbers const& first_num)
{
    Re += first_num.Re;
    Im += first_num.Im;

    return *this;
}

complex_numbers& complex_numbers::operator+(complex_numbers const& first_num)
{
    Re += first_num.Re;
    Im += first_num.Im;

    return *this;
}

complex_numbers& complex_numbers::operator-(complex_numbers const& first_num)
{
    Re -= first_num.Re;
    Im -= first_num.Im;
    
    return *this;
}

complex_numbers& complex_numbers::operator *(complex_numbers const& first_num)
{
    double Im1, Re1;
    Im1 = Im;
    Re1 = Re;
    Im = Re1 * first_num.Im + Im1 * first_num.Re;
    Re = Re1 * first_num.Re - Im1 * first_num.Im;
    
    return *this;
}

complex_numbers& complex_numbers::operator /(complex_numbers const& first_num)
{
    double Zn;
    double Re1 = first_num.Re;
    Re1 = Re1 * (-1);
    complex_numbers ob3(Re1, first_num.Im);
    complex_numbers ob(Re, Im);
    Zn = first_num.Re * ob3.Re + ((-1)*first_num.Im *ob3.Im);
    ob = ob * ob3;
    Re = ob.Re / Zn;
    Im = ob.Im / Zn;
    
    return *this;
}

int main()
{
    double Dlina;
    complex_numbers ob(2.0, 3.0);
    complex_numbers ob1(-5.0, 7.0);
    complex_numbers ob2;
    //ob1.show();
    //Dlina = ob.mod_complex_numbers();
    //std::cout << Dlina;
    ob.arg_complex_numbers();
    
}
