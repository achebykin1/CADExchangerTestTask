#include "circle.hpp"
#include <stdexcept>
#include <math.h>
#include <iostream>

Circle::Circle() : CenterPoint(std::array<double, 3> {0, 0, 0}), radius(1), geometricShape(0, 0, 0) {}

Circle::Circle(const double& x, const double& y, const double& z, 
        const double& radius, const double& rotationZ, const double& rotationY, const double& rotationX) : 
        CenterPoint(std::array<double, 3>{x, y, z}), 
        radius(radius), geometricShape(rotationZ, rotationY, rotationX)  
{
    if (radius <= 0)
        throw std::invalid_argument("Radius should be above zero");
            
}

Circle::Circle(std::array<double, 3> Center, 
        const double& radius, const double& rotationZ, const double& rotationY, const double& rotationX) : 
        CenterPoint(Center), 
        radius(radius), geometricShape(rotationZ, rotationY, rotationX)
{
    if (radius <= 0)
        throw std::invalid_argument("Radius should be above zero");   
}

Circle::Circle(Circle& copy) : CenterPoint(copy.CenterPoint), radius(copy.radius), geometricShape(copy) {}

bool Circle::operator==(const Circle& right) const {
    return this->radius == right.radius;
}

bool Circle::operator<(const Circle& right) const {
    return this->radius < right.radius;
}

bool Circle::operator>(const Circle& right) const {
    return this->radius > right.radius;
}

bool Circle::operator<=(const Circle& right) const {
    return !(*this > right);
}

bool Circle::operator>=(const Circle& right) const {
    return !(*this < right);
}

Circle& Circle::operator=(const Circle& right) {
    if(this == &right)
        return *this;
    CenterPoint = std::array<double, 3> (right.CenterPoint);
    radius = right.radius;
    this->setRotationZ(right.getRotationZ());
    this->setRotationY(right.getRotationY());
    this->setRotationX(right.getRotationX());
    return *this;
}

std::array<double, 3> Circle::getCenter() const {
    return CenterPoint;
}

std::vector<double> Circle::getRadii() const {
    std::vector<double> answer = {radius};
    return answer;
}

std::array<double, 3> Circle::getPoint(const double& t) const {     
    std::array<double, 3> Point = {0, 0, 0};
    Point[0] = radius * cos(t);
    Point[1] = radius * sin(t);
    Point = rotatePoint(Point);
    Point = translationGeometry(Point, CenterPoint);
    return Point;
}

std::array<double, 3> Circle::getFirstDerivativeVector(const double& t) const {
    std::array<double, 3> Point = {0, 0, 0};
    Point[0] = radius * -sin(t);
    Point[1] = radius *  cos(t);
    Point = rotatePoint(Point);
    return Point;
}

void Circle::setCenter(const std::array<double, 3>& newCenter) {
    CenterPoint = newCenter;
}

void Circle::setRadii(const std::vector<double>& newRadiuses) {
    if (newRadiuses.size() != 1)
        throw std::invalid_argument("Wrong ammount of radii for Circle, vector should have one radius");
    if (newRadiuses.at(0) <= 0)
        throw std::invalid_argument("Radius should be above zero");
    radius = newRadiuses.at(0); 
}