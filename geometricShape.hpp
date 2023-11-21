#include <array>
#include <vector>

#pragma once

class geometricShape {
private:
    void RotateToXCoordinate(std::array<double, 3>*) const;
    void RotateToYCoordinate(std::array<double, 3>*) const;
    void RotateToZCoordinate(std::array<double, 3>*) const;
    
    double RotationZ, RotationY, RotationX;


public:
    geometricShape(const double& RotationZ = 0, const double& RotationY = 0, const double& RotationX = 0);
    geometricShape(geometricShape& copy);

    std::array<double, 3> rotatePoint(const std::array<double, 3>&) const;
    std::array<double, 3> translationGeometry(const std::array<double, 3>&, const std::array<double, 3>&) const;
    void setRotationZ(const double&);
    void setRotationY(const double&);
    void setRotationX(const double&);
    double getRotationZ() const;
    double getRotationY() const;
    double getRotationX() const;

    virtual std::array<double, 3> getCenter() const = 0;
    virtual std::vector<double> getRadii() const = 0;
    virtual void setCenter(const std::array<double, 3>&) = 0;
    virtual void setRadii(const std::vector<double>&) = 0;
    virtual std::array<double, 3> getPoint(const double&) const = 0;
    virtual std::array<double, 3> getFirstDerivativeVector(const double&) const = 0;
};