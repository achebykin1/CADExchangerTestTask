#include "ellipse.hpp"
#include <stdexcept>
#include <math.h>
#include <iostream>

Ellipse::Ellipse() : CenterPoint(std::array<double, 3> {0, 0, 0}), radii(std::array<double, 2> {1, 1}), geometricShape(0, 0, 0) {}

Ellipse::Ellipse(const double& x, const double& y, const double& z, const double& r1, const double& r2,     //(x, y, z, radius1, radius2)
        const double& rotationZ, const double& rotationY, const double& rotationX) :
        CenterPoint(std::array<double, 3>{x, y, z}), radii(std::array<double, 2>{r1, r2}), 
        geometricShape(rotationZ, rotationY, rotationX)
{
    if(radii[0] <= 0 || radii[1] <= 0)
        throw std::invalid_argument("Radii should be above zero");
}

Ellipse::Ellipse(const double& x, const double& y, const double& z, std::array<double, 2> radii,            //(x, y, z, radii)
        const double& rotationZ, const double& rotationY, const double& rotationX) :
        CenterPoint(std::array<double, 3>{x, y, z}), radii(radii), 
        geometricShape(rotationZ, rotationY, rotationX)
{
    if(radii[0] <= 0 || radii[1] <= 0)
        throw std::invalid_argument("Radii should be above zero");
}

Ellipse::Ellipse(std::array<double, 3> Center, const double& r1, const double& r2,                          //(point, radius1, radius2)
        const double& rotationZ, const double& rotationY, const double& rotationX) :
        CenterPoint(Center), radii(std::array<double, 2>{r1, r2}), 
        geometricShape(rotationZ, rotationY, rotationX)
{
    if(radii[0] <= 0 || radii[1] <= 0)
        throw std::invalid_argument("Radii should be above zero");
}

Ellipse::Ellipse(std::array<double, 3> Center, std::array<double, 2> radii,                                 //(point, radii)
        const double& rotationZ, const double& rotationY, const double& rotationX) :
        CenterPoint(Center), radii(radii), 
        geometricShape(rotationZ, rotationY, rotationX)
{
    if(radii[0] <= 0 || radii[1] <= 0)
        throw std::invalid_argument("Radii should be above zero");
}

Ellipse::Ellipse(Ellipse& copy) :
        CenterPoint(copy.CenterPoint), radii(copy.radii), geometricShape(copy) {}

bool Ellipse::operator==(const Ellipse& right) const {
    return (this->radii.at(0) == right.radii.at(0)) && (this->radii.at(1) == right.radii.at(1));
}

bool Ellipse::operator<(const Ellipse& right) const {
    if (this->radii.at(0) < right.radii.at(0))
        return true;
        
    if (this->radii.at(0) > right.radii.at(0))
        return false;
    return this->radii.at(1) < right.radii.at(1);
}

bool Ellipse::operator>(const Ellipse& right) const {
    if (this->radii.at(0) > right.radii.at(0))
        return true;
        
    if (this->radii.at(0) < right.radii.at(0))
        return false;
    return this->radii.at(1) > right.radii.at(1);
}

bool Ellipse::operator<=(const Ellipse& right) const {
    return !(*this > right);
}

bool Ellipse::operator>=(const Ellipse& right) const {
    return !(*this < right);
}

Ellipse& Ellipse::operator=(const Ellipse& right) {
    if(this == &right)
        return *this;
    CenterPoint = std::array<double, 3> (right.CenterPoint);
    radii = std::array<double, 2> (right.radii);
    this->setRotationZ(right.getRotationZ());
    this->setRotationY(right.getRotationY());
    this->setRotationX(right.getRotationX());
    return *this;
}

std::array<double, 3> Ellipse::getCenter() const {
    return CenterPoint;
}

std::vector<double> Ellipse::getRadii() const {
    std::vector<double> answer = {radii.at(0), radii.at(1)};
    return answer;
}

std::array<double, 3> Ellipse::getPoint(const double& t) const {     
    std::array<double, 3> Point = {0, 0, 0};
    Point[0] = radii.at(0) * cos(t);
    Point[1] = radii.at(1) * sin(t);
    Point = geometricShape::rotatePoint(Point);
    Point = geometricShape::translationGeometry(Point, CenterPoint);
    return Point;
}

std::array<double, 3> Ellipse::getFirstDerivativeVector(const double& t) const {
    std::array<double, 3> Point = {0, 0, 0};
    Point[0] = radii.at(0) * -sin(t);
    Point[1] = radii.at(1) *  cos(t);
    Point = geometricShape::rotatePoint(Point);
    return Point;
}

void Ellipse::setCenter(const std::array<double, 3>& newCenter) {
    CenterPoint = newCenter;
}

void Ellipse::setRadii(const std::vector<double>& newRadiuses) {
    if (newRadiuses.size() != 2)
        throw std::invalid_argument("Wrong ammount of radii for Ellipse, vector should have two radius");
    if (newRadiuses.at(0) <= 0 || newRadiuses.at(1) <= 0)
        throw std::invalid_argument("Radii should be above zero");
    radii.at(0) = newRadiuses.at(0);
    radii.at(1) = newRadiuses.at(1);
}
