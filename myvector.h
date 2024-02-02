#ifndef MYVECTOR_H
#define MYVECTOR_H

#include <QtCore>
#include <QVector3D>

class MyVector
{

public:
    MyVector(float xx, float yy, float zz);
    MyVector();
    ~MyVector();

    float xPoint{0};
    float yPoint{0};
    float zPoint{0};

    void set_x(float x);
    float get_x() const;
    void set_y(float x);
    float get_y() const;
    void set_z(float x);
    float get_z() const;
    void normalize();

    QVector3D to_qvector();

    float dot(const MyVector &v2)const;
    MyVector cross(MyVector &v1, MyVector &v2);
    double magnitude();
    static double distance_between(MyVector &v1, MyVector &v2);

    friend MyVector operator+(const MyVector &v1, const MyVector &v2);
    friend MyVector operator*(const MyVector &v1, const MyVector &v2);
    friend MyVector operator-(const MyVector &v1, const MyVector &v2);
    friend MyVector operator*(const MyVector &v1, const int &number);
    friend MyVector operator*(const MyVector &v1, const float &number);
    friend MyVector operator*(const MyVector &v1, const double &number);
    friend MyVector operator/(const MyVector &v1, const float &number);
    friend MyVector operator*(const int &number, const MyVector &v1);
    friend MyVector operator*(const float &number, const MyVector &v1);
    friend MyVector operator*(const double &number, const MyVector &v1);
    MyVector & operator+=(const MyVector &v1);
    MyVector & operator/=(const int &digit);
    MyVector & operator/=(const float &digit);
    MyVector & operator/=(const double &digit);
    MyVector & operator-=(const MyVector &v);

    friend bool operator==(const MyVector &v1, const MyVector &v2);
    friend bool operator!=(const MyVector &v1, const MyVector &v2);
    friend std::ostream& operator<<(std::ostream& os, const MyVector &v1);


private:

protected:

};

#endif // MYVECTOR_H
