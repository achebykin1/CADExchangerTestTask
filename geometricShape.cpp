#include "geometricShape.hpp"
#include <math.h>
#include <iostream>
#include <array>

geometricShape::geometricShape(const double& RotationZ, const double& RotationY, const double& RotationX) : 
        RotationZ(RotationZ), RotationY(RotationY), RotationX(RotationX) {}

geometricShape::geometricShape(geometricShape& copy) : 
        RotationZ(copy.RotationZ), RotationY(copy.RotationY), RotationX(copy.RotationX) {}

void geometricShape::RotateToZCoordinate(std::array<double, 3>* Point) const {

    /*
        (x)               (x')      (cos(RotationZ) * x' - sin(RotationZ) * y')
        (y)  =  R^_z *    (y')  =   (sin(RotationZ) * x' + cos(RotationZ) * y')        //R^_z - Матрица поворота для аффиного поворота по оси Оz
        (z)               (z')      (                   z'                    )
    
        (x')                                                (x)
        (y')  - вектор в системе координат до поворота      (y)   - вектор в системе координат после поворота
        (z')                                                (z)
    */
    double x = Point->at(0), y = Point->at(1);
    Point->at(0) = cos(RotationZ) * x - sin(RotationZ) * y;
    Point->at(1) = sin(RotationZ) * x + cos(RotationZ) * y;
} 

void geometricShape::RotateToYCoordinate(std::array<double, 3>* Point) const {
    /*
        (x)               (x')      ( cos(-RotationY) * x' + sin(-RotationY) * z')
        (y)  =  R^_y *    (y')  =   (                   y'                       )        //R^_y - Матрица поворота для аффиного поворота по оси Оy
        (z)               (z')      (-sin(-RotationY) * x' + cos(-RotationY) * z')
    
        (x')                                                (x)
        (y')  - вектор в системе координат до поворота      (y)   - вектор в системе координат после поворота
        (z')                                                (z)
    */
    double x = Point->at(0), z = Point->at(2);
    Point->at(0) =  cos(-RotationY) * x + sin(-RotationY) * z;
    Point->at(2) = -sin(-RotationY) * x + cos(-RotationY) * z;
}

void geometricShape::RotateToXCoordinate(std::array<double, 3>* Point) const {
    /*
        (x)               (x')      (                  x'                     )
        (y)  =  R^_x *    (y')  =   (cos(RotationX) * y' - sin(RotationX) * z')        //R^_x - Матрица поворота для аффиного поворота по оси Ох
        (z)               (z')      (sin(RotationX) * y' + cos(RotationX) * z')
    
        (x')                                                (x)
        (y')  - вектор в системе координат до поворота      (y)   - вектор в системе координат после поворота
        (z')                                                (z)
    */
    double y = Point->at(1), z = Point->at(2);
    Point->at(1) = cos(RotationX) * y - sin(RotationX) * z;
    Point->at(2) = sin(RotationX) * y + cos(RotationX) * z;
}

std::array<double, 3> geometricShape::rotatePoint(const std::array<double, 3>& Point) const {       //Порядок поворота важен!!!
    std::array<double, 3> RotatedPoint = Point;                                                     //В моём случае с начало фигуру поворочивают
    if (RotationZ != 0)                                                                             //Относительно оси Oz, потом Oy, потом Ox
        RotateToZCoordinate(&RotatedPoint);
    if (RotationY != 0)
        RotateToYCoordinate(&RotatedPoint);
    if (RotationX != 0)
        RotateToXCoordinate(&RotatedPoint);
    for (int i = 0; i < 3; ++i){
        if(abs(RotatedPoint[i]) <= pow(10, -8))
            RotatedPoint[i] = 0;
    }
    return RotatedPoint;
}

std::array<double, 3> geometricShape::translationGeometry(const std::array<double, 3>& Point, 
        const std::array<double, 3>& CenterPoint) const 
{
    std::array<double, 3> TranslatedPoint = Point;
    TranslatedPoint[0] = TranslatedPoint[0] + CenterPoint.at(0);
    TranslatedPoint[1] = TranslatedPoint[1] + CenterPoint.at(1);
    TranslatedPoint[2] = TranslatedPoint[2] + CenterPoint.at(2);
    return TranslatedPoint;
}

void geometricShape::setRotationZ(const double& newRotation) {
    RotationZ = newRotation;
}

void geometricShape::setRotationY(const double& newRotation) {
    RotationY = newRotation;
}

void geometricShape::setRotationX(const double& newRotation) {
    RotationX = newRotation;
}

double geometricShape::getRotationZ() const {
    return RotationZ;
}

double geometricShape::getRotationY() const {
    return RotationY;
}

double geometricShape::getRotationX() const {
    return RotationX;
}