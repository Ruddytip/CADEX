#pragma once

// Число Пи
const double pi = 3.141592653589793;

template<typename Type>
struct Point{
    Type x, y, z;
};

class Curve{
private:
    int type_id;
public:
    Curve(const int& _id);
    virtual Point<double> getPoint(const double& t) const = 0;
    virtual double getDerivative(const double& t) const = 0;
    // Метод для личного удобста, записывает точки в файл,
    // для последующей визуализации с помощью Render.exe
    virtual void pointWtriteToFile(const char* str) const = 0;
    // Нужен для определения кривой
    virtual int getID() const;
};

class Circle : public Curve{
private:
    double radius;
public:
    Circle(const double& _radius);
    virtual ~Circle();
    virtual Point<double> getPoint(const double& t) const override;
    virtual double getDerivative(const double& t) const override;
    virtual void pointWtriteToFile(const char* str) const override;
    virtual double getRadius() const;
};

class Ellipse : public Curve{
private:
    double radius_min;
    double radius_max;
public:
    Ellipse(const double& _min, const double& _max);
    virtual ~Ellipse();
    virtual Point<double> getPoint(const double& t) const override;
    virtual double getDerivative(const double& t) const override;
    virtual void pointWtriteToFile(const char* str) const override;
};

class Helix : public Curve{
private:
    double radius, step;
public:
    Helix(const double& _radius, const double& _step);
    virtual ~Helix();
    virtual Point<double> getPoint(const double& t) const override;
    virtual double getDerivative(const double& t) const override;
    virtual void pointWtriteToFile(const char* str) const override;
};
