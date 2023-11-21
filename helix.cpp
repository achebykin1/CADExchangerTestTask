#include "helix.hpp"
#include <stdexcept>
#include <math.h>
#include <iostream>

Helix::Helix() : CenterPoint(std::array<double, 3> {0, 0, 0}), radius(1), step(1), geometricShape(0, 0, 0) {}

Helix::Helix(const double& x, const double& y, const double& z, 
        const double& radius, const double& step, const double& rotationZ, const double& rotationY, const double& rotationX) : 
        CenterPoint(std::array<double, 3>{x, y, z}), 
        radius(radius), step(step), geometricShape(rotationZ, rotationY, rotationX)  
{
    if (radius <= 0)
        throw std::invalid_argument("Radius should be above zero");
            
}

Helix::Helix(std::array<double, 3> Center, 
        const double& radius, const double& step, const double& rotationZ, const double& rotationY, const double& rotationX) : 
        CenterPoint(Center), radius(radius), step(step), geometricShape(rotationZ, rotationY, rotationX)
{
    if (radius <= 0)
        throw std::invalid_argument("Radius should be above zero");   
}

Helix::Helix(Helix& copy) : CenterPoint(copy.CenterPoint), radius(copy.radius), step(copy.step), geometricShape(copy) {}

bool Helix::operator==(const Helix& right) const {
    return (this->radius == right.radius) && (this->step == right.step);
}

bool Helix::operator<(const Helix& right) const {
    if (this->radius < right.radius)
        return true;

    if (this->radius > right.radius)
        return false;
    return this->step < right.step;
}

bool Helix::operator>(const Helix& right) const {
    if (this->radius > right.radius)
        return true;

    if (this->radius < right.radius)
        return false;
    return this->step > right.step;
}

bool Helix::operator<=(const Helix& right) const {
    return !(*this > right);
}

bool Helix::operator>=(const Helix& right) const {
    return !(*this < right);
}
Helix& Helix::operator=(const Helix& right) {
    if(this == &right)
        return *this;
    CenterPoint = std::array<double, 3> (right.CenterPoint);
    radius = right.radius;
    step = right.step;
    this->setRotationZ(right.getRotationZ());
    this->setRotationY(right.getRotationY());
    this->setRotationX(right.getRotationX());
    return *this;
}

std::array<double, 3> Helix::getCenter() const {
    return CenterPoint;
}

std::vector<double> Helix::getRadii() const {
    std::vector<double> answer = {radius};
    return answer;
}

double Helix::getStep() const {
    return step;
}

std::array<double, 3> Helix::getPoint(const double& t) const {     
    std::array<double, 3> Point = {0, 0, 0};
    Point[0] = radius * cos(t);
    Point[1] = radius * sin(t);
    Point[2] = t * step / (2 * M_PI);
    Point = rotatePoint(Point);
    Point = translationGeometry(Point, CenterPoint);
    return Point;
}

std::array<double, 3> Helix::getFirstDerivativeVector(const double& t) const {
    std::array<double, 3> Point = {0, 0, 0};
    Point[0] = radius * -sin(t);
    Point[1] = radius *  cos(t);
    Point[2] = step / (2 * M_PI);
    Point = rotatePoint(Point);
    return Point;
}

void Helix::setCenter(const std::array<double, 3>& newCenter) {
    CenterPoint = newCenter;
}

void Helix::setRadii(const std::vector<double>& newRadiuses) {
    if (newRadiuses.size() != 1)
        throw std::invalid_argument("Wrong ammount of radii for Helix, vector should have one radius");
    if (newRadiuses.at(0) <= 0)
        throw std::invalid_argument("Radius should be above zero");
    radius = newRadiuses.at(0); 
}

void Helix::setStep(const double& newStep) {
    step = newStep;
}