#include "geometricShape.hpp"
#include <array>
#include <vector>

class Ellipse : public geometricShape {
private:
    std::array<double, 3> CenterPoint;
    std::array<double, 2> radii;

public:
    Ellipse();
    Ellipse(const double& x, const double& y, const double& z, const double& r1, const double& r2, 
            const double& rotationZ = 0, const double& rotationY = 0, const double& rotationX = 0);
    
    Ellipse(const double& x, const double& y, const double& z, std::array<double, 2> radii, 
            const double& rotationZ = 0, const double& rotationY = 0, const double& rotationX = 0);
    
    Ellipse(std::array<double, 3> Center, const double& r1, const double& r2, 
        const double& rotationZ = 0, const double& rotationY = 0, const double& rotationX = 0);

    Ellipse(std::array<double, 3> Ceneter, std::array<double, 2> radii, 
        const double& rotationZ = 0, const double& rotationY = 0, const double& rotationX = 0);
        
    Ellipse(Ellipse& copy);

    bool operator==(const Ellipse& right) const;
    bool operator<(const Ellipse& right) const;
    bool operator>(const Ellipse& right) const;
    bool operator<=(const Ellipse& right) const;
    bool operator>=(const Ellipse& right) const;

    Ellipse& operator=(const Ellipse& right); 

    std::array<double, 3> getCenter() const override;
    std::vector<double> getRadii() const override;

    void setCenter(const std::array<double, 3>&) override;
    void setRadii(const std::vector<double>&) override;

    std::array<double, 3> getPoint(const double&) const override;
    std::array<double, 3> getFirstDerivativeVector(const double&) const override;
};