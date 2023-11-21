#include "Geometry.hpp"
#include <iostream>
#include <math.h>
#include <array>
#include <vector>
#include <random>
#include <typeinfo>
#include <algorithm>

void writePoint(const std::array<double, 3>& a) {       //actually simply print array
    for(double i : a){
        std::cout << i << " ";
    }
}


std::vector<geometricShape*> randomGeometryFigureGenerator(const int& amount) {
    double X, Y, Z, radius1, radius2, rotationZ, rotationY, rotationX;
    int ShapeType;
    std::vector<geometricShape*> ShapeSequence(amount);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> shapeGenerator(0, 2);
    std::uniform_real_distribution<double> pointGenerator(-10.0, 10.0);
    std::uniform_real_distribution<double> radiusGenerator(0.1, 5.0);
    std::uniform_real_distribution<double> stepGenerator(0.5, 5.0);
    std::uniform_real_distribution<double> rotationGenerator(0, 2 * M_PI);

    for (int i = 0; i < amount; ++i) {
        ShapeType = shapeGenerator(gen);
        radius1   = radiusGenerator(gen);
        X         = pointGenerator(gen);
        Y         = pointGenerator(gen);
        Z         = pointGenerator(gen);
        rotationZ = rotationGenerator(gen);
        rotationY = rotationGenerator(gen);
        rotationX = rotationGenerator(gen);
        switch(ShapeType) {
            case 0: //Circle
                ShapeSequence.at(i) = new Circle(X, Y, Z, radius1, rotationZ, rotationY, rotationX);
                break;
            case 1: //Ellipse
                radius2 = radiusGenerator(gen);
                ShapeSequence.at(i) = new Ellipse(X, Y, Z, radius1, radius2, rotationZ, rotationY, rotationX);
            default: //Helix
                radius2 = stepGenerator(gen);   //radius2 here is step
                ShapeSequence.at(i) = new Helix(X, Y, Z, radius1, radius2, rotationZ, rotationY, rotationX);
                break;
        }
    }
    return ShapeSequence;
}


void printPointsAndFirstDerivatives(const std::vector<geometricShape*>& ShapeSequence, const double& t = 0){
    std::array<double, 3> PointOrVector;
    for (geometricShape* iter : ShapeSequence){
        PointOrVector = iter->getPoint(t);
        std::cout << "Point: ";
        writePoint(PointOrVector);
        PointOrVector = iter->getFirstDerivativeVector(t);
        std::cout << " First Derivatives: ";
        writePoint(PointOrVector);
        std::cout << "\n";
    }
}

void printCircleRadii(const std::vector<geometricShape*>& ShapeSequence){
    std::cout << "List of Circle radii:\n";
    for (geometricShape* iter : ShapeSequence){
        std::cout << "radius = " << iter->getRadii().at(0) << "\n";
    }
}

std::vector<geometricShape*> findCirclesFromSequence(const std::vector<geometricShape*>& ShapeSequence) {
    std::vector<geometricShape*> Circles;
    std::string CircleTypeId = typeid(Circle).name();
    for (geometricShape* iter : ShapeSequence){
        if(typeid(*iter).name() == CircleTypeId)
            Circles.push_back(static_cast<geometricShape*>(iter));
    }
    return Circles;
}

bool CompareGeometricShapeCirclePtr(geometricShape* left, geometricShape* right){
    return *(static_cast<Circle*>(left)) < *(static_cast<Circle*>(right));
}

std::vector<geometricShape*> sortCirclesByRadius(std::vector<geometricShape*> Circles) {
    if (Circles.empty())
        return Circles;
    std::sort(Circles.begin(), Circles.end(), &CompareGeometricShapeCirclePtr);
    return Circles;
}

double sumCirclesRadii(const std::vector<geometricShape*>& Circles) {
    double sum = 0;
    for (geometricShape* iter : Circles) {
        sum += (*iter).getRadii().at(0);
    }
    return sum;
}

int main()
{
    int amount = 10;
    std::vector<geometricShape*> ShapeSequence = randomGeometryFigureGenerator(amount);
    std::cout << "ShapeSequence Points and First Derivatives at t = PI/4:\n";
    printPointsAndFirstDerivatives(ShapeSequence, M_PI / 4);

    std::vector<geometricShape*> CircleSequence = findCirclesFromSequence(ShapeSequence);
    std::vector<geometricShape*> SortedCircleSequence = sortCirclesByRadius(CircleSequence);
    std::cout << "\n";
    std::cout << "Only circles Points and First Derivatives at t = 0:\n";
    printPointsAndFirstDerivatives(CircleSequence);
    std::cout << "\nunsorted:\n";
    printCircleRadii(CircleSequence);           //not sure that this function is needed
    std::cout << "\nsorted:\n";
    printCircleRadii(SortedCircleSequence);           //not sure that this function is needed
    std::cout << "Circles radii sum: " << sumCirclesRadii(CircleSequence) << "\n";
    for (int i = 0; i < ShapeSequence.size(); ++i)
        delete ShapeSequence.at(i);
}