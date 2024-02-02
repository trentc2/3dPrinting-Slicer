#include "myvector.h"
#include <math.h>
#include <QVector3D>
#include <ostream>

MyVector::MyVector(float xx, float yy, float zz)
{
    xPoint = xx;
    yPoint = yy;
    zPoint = zz;
}

MyVector::MyVector()
{
    xPoint = 0;
    yPoint = 0;
    zPoint = 0;
}


QVector3D MyVector::to_qvector()
{
    return QVector3D(xPoint, yPoint, zPoint);
}

MyVector::~MyVector()
{
}

void MyVector::set_x(float x)
{
    xPoint = x;
}

float MyVector::get_x() const
{
    return xPoint;
}

void MyVector::set_y(float y)
{
    yPoint = y;
}

float MyVector::get_y() const
{
    return yPoint;
}

void MyVector::set_z(float z)
{
    zPoint = z;
}

float MyVector::get_z() const
{
    return zPoint;
}

void MyVector::normalize()
{
    double mag{magnitude()};
    if(mag != 0)
    {
        xPoint = xPoint/mag;
        yPoint = yPoint/mag;
        zPoint = zPoint/mag;
    }

}

float MyVector::dot(const MyVector &v2)const
{
    return v2.get_x()*xPoint + v2.get_y()*yPoint + v2.get_z()*zPoint;
}

MyVector cross(MyVector &v1, MyVector &v2)
{
    float i{v1.get_y()*v2.get_z() - v1.get_z()*v2.get_y()};
    float j{v1.get_z()*v2.get_x() - v1.get_x()*v2.get_z()};
    float k{v1.get_x()*v2.get_y() - v1.get_y()*v2.get_x()};
    return MyVector(i, j, k);
}

double MyVector::magnitude()
{
    return sqrt( pow(xPoint, 2) + pow(yPoint, 2) + pow(zPoint, 2));
}

double MyVector::distance_between(MyVector &v1, MyVector &v2)
{
    MyVector temp{v1-v2};
    return temp.magnitude();
}

MyVector operator+(const MyVector &v1, const MyVector &v2)
{
    float x{v1.get_x()+v2.get_x()};
    float y{v1.get_y()+v2.get_y()};
    float z{v1.get_z()+v2.get_z()};
    return MyVector(x, y, z);
}

MyVector operator*(const MyVector &v1, const MyVector &v2)
{
    float x{v1.get_x() * v2.get_x()};
    float y{v1.get_y() * v2.get_y()};
    float z{v1.get_z() * v2.get_z()};
    return MyVector(x, y, z);
}

MyVector operator-(const MyVector &v1, const MyVector &v2)
{
    float x{v1.get_x()-v2.get_x()};
    float y{v1.get_y()-v2.get_y()};
    float z{v1.get_z()-v2.get_z()};
    return MyVector(x, y, z);
}

MyVector operator*(const MyVector &v1, const int &number)
{
    return MyVector(v1.get_x()*number, v1.get_y()*number, v1.get_z()*number);
}

MyVector operator*(const MyVector &v1, const float &number)
{
    return MyVector(v1.get_x()*number, v1.get_y()*number, v1.get_z()*number);
}

MyVector operator*(const MyVector &v1, const double &number)
{
    return MyVector(v1.get_x()*number, v1.get_y()*number, v1.get_z()*number);
}

MyVector operator*(const int &number, const MyVector &v1)
{
    return MyVector(v1.get_x()*number, v1.get_y()*number, v1.get_z()*number);
}

MyVector operator*(const float &number, const MyVector &v1)
{
    return MyVector(v1.get_x()*number, v1.get_y()*number, v1.get_z()*number);
}

MyVector operator*(const double &number, const MyVector &v1)
{
    return MyVector(v1.get_x()*number, v1.get_y()*number, v1.get_z()*number);
}

MyVector operator/(const MyVector &v1, const float &number)
{
    return MyVector(v1.get_x()/number, v1.get_y()/number, v1.get_z()/number);
}

MyVector & MyVector::operator+=(const MyVector &v1)
{
    this->set_x(this->get_x()+v1.get_x());
    this->set_y(this->get_y()+v1.get_y());
    this->set_z(this->get_z()+v1.get_z());
    return *this;
}

MyVector & MyVector::operator/=(const int &digit)
{
    this->set_x(this->get_x() / digit);
    this->set_y(this->get_y() / digit);
    this->set_z(this->get_z() / digit);
    return *this;
}

MyVector & MyVector::operator/=(const float &digit)
{
    this->set_x(this->get_x() / digit);
    this->set_y(this->get_y() / digit);
    this->set_z(this->get_z() / digit);
    return *this;
}

MyVector & MyVector::operator/=(const double &digit)
{
    this->set_x(this->get_x() / digit);
    this->set_y(this->get_y() / digit);
    this->set_z(this->get_z() / digit);
    return *this;
}

MyVector & MyVector::operator-=(const MyVector &v)
{
    this->set_x(this->get_x()-v.get_x());
    this->set_y(this->get_y()-v.get_y());
    this->set_z(this->get_z()-v.get_z());
    return *this;
}

bool operator==(const MyVector &v1, const MyVector &v2)
{
    if( (v1.get_x() == v2.get_x()) && (v1.get_y() == v2.get_y()) && (v1.get_z() == v1.get_z()) )
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool operator!=(const MyVector &v1, const MyVector &v2)
{
    if( (v1.get_x() == v2.get_x()) && (v1.get_y() == v2.get_y()) && (v1.get_z() == v1.get_z()) )
    {
        return false;
    }
    else
    {
        return true;
    }
}
