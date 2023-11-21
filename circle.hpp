#include "geometricShape.hpp"
#include <array>
#include <vector>

class Circle : public geometricShape {
private:
    std::array<double, 3> CenterPoint;
    double radius;

public:
    Circle();
    Circle(const double& x, const double& y, const double& z, const double& radius, 
            const double& rotationZ = 0, const double& rotationY = 0, const double& rotationX = 0);

    Circle(std::array<double, 3> Center, const double& radius, const double& rotationZ = 0, const double& rotationY = 0, const double& rotationX = 0);
    Circle(Circle& copy);

    bool operator==(const Circle& right) const;
    bool operator<(const Circle& right) const;
    bool operator>(const Circle& right) const;
    bool operator<=(const Circle& right) const;
    bool operator>=(const Circle& right) const;

    Circle& operator=(const Circle& right);    

    std::array<double, 3> getCenter() const override;
    std::vector<double> getRadii() const override;

    void setCenter(const std::array<double, 3>&) override;
    void setRadii(const std::vector<double>&) override;

    std::array<double, 3> getPoint(const double&) const override;
    std::array<double, 3> getFirstDerivativeVector(const double&) const override;
};

