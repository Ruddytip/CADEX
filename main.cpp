#include <vector>    // Для std::vector
#include <memory>    // Для std::shared_ptr
#include <ctime>     // Для std::time
#include <iostream>  // Для std::cout
#include <algorithm> // Для std::copy_if, std::transform
#include <numeric>   // Для std::accumulate
#include "Curve.hpp" // Решение 1 задания

// Для личного удобства, просмотра кривых в Render.exe
void const pointsWriteToFile(const std::vector<std::shared_ptr<Curve>>& vec);

int main(){
    std::srand(std::time(0));
    // Решение 2 задания ======================================================
    std::vector<std::shared_ptr<Curve>> vec; // Контейнер для кривых
    const int count = 10; // Количество кривых
    for(auto i = 0; i < count; ++i){
        double radius_1 = rand() % 15; // Случайный радиус
        double radius_2 = rand() % 15; // Второй случайный радиус (для эллипса)
        double step = (rand() % 15) / 10.0; // Случайный шаг (для спирали)

        // int shape = rand() % 3; // Определяет, какая кривая будет создана
        int shape = 0; // Определяет, какая кривая будет создана
        if(shape == 0){ // Круг
            std::shared_ptr<Curve> ptr(new Circle(radius_1));
            vec.push_back(ptr);
        }else if(shape == 1){ // Эллипс
            std::shared_ptr<Curve> ptr(new Ellipse(radius_1, radius_2));
            vec.push_back(ptr);
        }else{ // Спираль
            std::shared_ptr<Curve> ptr(new Helix(radius_1, step));
            vec.push_back(ptr);
        }
    }
    // Не использую make_shard, так как начиная с C++17 утечка памяти при
    // использовании сырого указателя в конструкторе shared_ptr уже невозможна
    // ========================================================================

    // Решение 3 задания ======================================================
    const double t = pi / 4.0;
    int row = 0;
    for(const auto& it : vec){
        std::cout << std::endl << row++ << ": ";
        switch (it->getID()) {
        case 0: std::cout << "Circle" << std::endl; break;
        case 1: std::cout << "Ellipse" << std::endl; break;
        case 2: std::cout << "Helix" << std::endl; break;
        default: std::cout << "Unknown curve type!!!" << std::endl; break;
        }
        std::cout << "\tx: " << it->getPoint(t).x << std::endl;
        std::cout << "\ty: " << it->getPoint(t).y << std::endl;
        std::cout << "\tz: " << it->getPoint(t).z << std::endl;
        std::cout << "\tDerivative: " << it->getDerivative(t) << std::endl;
    }
    // ========================================================================

    // Решение 4 задания ======================================================
    // Копирование только кругов во временный вектор
    std::vector<std::shared_ptr<Curve>> buff(vec.size());
    auto it_b = std::copy_if(vec.begin(), vec.end(), buff.begin(), [](const std::shared_ptr<Curve>& ptr)->bool{
        return (ptr->getID() == 0);
    });
    buff.resize(std::distance(buff.begin(), it_b));

    // Преобразование типа из Curve в Circle
    std::vector<std::shared_ptr<Circle>> OnlyCircle(buff.size());
    std::transform(buff.begin(), buff.end(), OnlyCircle.begin(), [](std::shared_ptr<Curve> ptr){
        return std::shared_ptr<Circle>(dynamic_cast<Circle*>(ptr.get()));
    });
    buff.clear(); // Очистка временного буфера
    // ========================================================================

    // Решение 5 задания ======================================================
    std::cout << "\nBefore sort: ";
    for(const auto& it : OnlyCircle) std::cout << it->getRadius() << " "; std::cout << std::endl;
    std::sort(OnlyCircle.begin(), OnlyCircle.end(), [](std::shared_ptr<Circle> p1, std::shared_ptr<Circle> p2){
        return (p1->getRadius() < p2->getRadius());
    });
    std::cout << "After sort:  ";
    for(const auto& it : OnlyCircle) std::cout << it->getRadius() << " "; std::cout << std::endl;
    // ========================================================================

    // Решение 6 задания ======================================================
    auto sum_radius = std::accumulate(OnlyCircle.begin(), OnlyCircle.end(), 0, [](int accumulator, const std::shared_ptr<Circle>& ptr){
        return accumulator + ptr->getRadius();
    });
    std::cout << "\nSumm all circle radius: " << sum_radius << std::endl;
    // ========================================================================

    // Генерация файла "out.txt", используется для просмтора кривых в 3D пространстве
    // pointsWriteToFile(vec);
    // system("Render out.txt");
    return 0;
}