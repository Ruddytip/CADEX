#include "Curve.hpp"
#include <cmath>   // Для std::cos, std::sin
#include <vector>  // Для std::vector
#include <fstream> // Для std::ofstream
#include <memory>  // Для std::shard_ptr

Curve::Curve(const int& _id)
: type_id(_id) {}

int Curve::getID() const {
    return type_id;
}

Circle::Circle(const double& _radius)
: Curve(0), radius(_radius){
    radius = radius < 0 ? 0 : radius;
}

Circle::~Circle() {}

Point<double> Circle::getPoint(const double& t) const {
    Point<double> out;
    out.x = radius * cos(t);
    out.y = radius * sin(t);
    out.z = 0.0;
    return out;
}

double Circle::getDerivative(const double& t) const {
    return -(cos(t) / sin(t));
}

void Circle::pointWtriteToFile(const char* str) const {
    std::ofstream out("out.txt", std::ios::app);
    if(!out.is_open()) return;
    for(double t = 0.0; t < 2 * pi; t+=0.001){
        out << getPoint(t).x << " ";
        out << getPoint(t).z << " ";
        out << getPoint(t).y << "\n";
    }
    out.close();
}

double Circle::getRadius() const {
    return radius;
}

Ellipse::Ellipse(const double& _min, const double& _max)
: Curve(1), radius_min(_min), radius_max(_max){
    radius_min = radius_min < 0 ? 0 : radius_min;
    radius_max = radius_max < 0 ? 0 : radius_max;
}

Ellipse::~Ellipse() {}

Point<double> Ellipse::getPoint(const double& t) const {
    Point<double> out;
    out.x = radius_min * std::cos(t);
    out.y = radius_max * std::sin(t);
    out.z = 0.0;
    return out;
}

double Ellipse::getDerivative(const double& t) const {
    return -((cos(t) * radius_min) / (sin(t) * radius_max));
}

void Ellipse::pointWtriteToFile(const char* str) const {
    std::ofstream out("out.txt", std::ios::app);
    if(!out.is_open()) return;
    for(double t = 0.0; t < 2 * pi; t+=0.001){
        out << getPoint(t).x << " ";
        out << getPoint(t).z << " ";
        out << getPoint(t).y << "\n";
    }
    out.close();
}

Helix::Helix(const double& _radius, const double& _step)
: Curve(2), radius(_radius), step(_step) {}

Helix::~Helix() {}

Point<double> Helix::getPoint(const double& t) const {
    Point<double> out;
    out.x = radius * cos(t);
    out.y = radius * sin(t);
    out.z = t * step;
    return out;
}

double Helix::getDerivative(const double& t) const {
    return 0.0;
}

void Helix::pointWtriteToFile(const char* str) const {
    std::ofstream out("out.txt", std::ios::app);
    if(!out.is_open()) return;
    for(double t = 0.0; t < 4 * pi; t+=0.001){
        out << getPoint(t).x << " ";
        out << getPoint(t).z << " ";
        out << getPoint(t).y << "\n";
    }
    out.close();
}

void const pointsWriteToFile(const std::vector<std::shared_ptr<Curve>>& vec){
    std::ofstream out("out.txt", std::ios::trunc);
    if(!out.is_open()) return;
    for(const auto it : vec) it->pointWtriteToFile("out.txt");
    out.close();
}
