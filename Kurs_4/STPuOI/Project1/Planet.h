#ifndef PROJECT1_PLANET_H
#define PROJECT1_PLANET_H

#include <iostream>
#include <string>
#include <utility>

using namespace std;

/**
 * @brief Перечисление всех возможных цветов планеты
 *
 */
enum Colors{
    red,
    orange,
    yellow,
    green,
    blue,
    violet,
};

/**
 * @brief Класс, описывающий характеристики планет
 *
 */
class Planet {
private:
    int id{};
    string name;
    Colors color;
    int portals{};

public:
    /**
     * @brief Конструктор с параметрами
     *
     * @param id      Уникальный идентификатор планеты
     * @param name    Уникальное имя планеты
     * @param color   Цвет планеты
     * @param portals Количество порталов
     */
    Planet(int id, string name, Colors color, int portals);

    /**
     * @brief Конструктор по умолчанию
     */
    Planet();

    //! Get & set
    void set_id(int planet_id){id = planet_id;}
    void set_name(string  planet_name){name = planet_name;}
    void set_color(Colors planet_color){color = planet_color;}
    void set_portals(int planet_portals){portals = planet_portals;}

    int get_id()       const{ return id;}
    string get_name()  const{ return name;}
    Colors get_color() const{ return color;}
    int get_portals()  const{ return portals;}

};


#endif //PROJECT1_PLANET_H
