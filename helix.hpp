#include "geometricShape.hpp"
#include <array>
#include <vector>

class Helix : public geometricShape {
private:
    std::array<double, 3> CenterPoint;
    double radius;
    double step;
public:
    Helix();
    Helix(const double& x, const double& y, const double& z, const double& radius, 
            const double& step, const double& rotationZ = 0, const double& rotationY = 0, const double& rotationX = 0);
    
    Helix(std::array<double, 3> Center, const double& radius, const double& step, 
            const double& rotationZ = 0, const double& rotationY = 0, const double& rotationX = 0);
    Helix(Helix& copy);

    bool operator==(const Helix& right) const;
    bool operator<(const Helix& right) const;
    bool operator>(const Helix& right) const;
    bool operator<=(const Helix& right) const;
    bool operator>=(const Helix& right) const;

    Helix& operator=(const Helix& right); 

    std::array<double, 3> getCenter() const override;
    std::vector<double> getRadii() const override;
    double getStep() const;

    void setCenter(const std::array<double, 3>&) override;
    void setRadii(const std::vector<double>&) override;
    void setStep(const double&);

    std::array<double, 3> getPoint(const double&) const override;
    std::array<double, 3> getFirstDerivativeVector(const double&) const override;
};