#ifndef LAB1_CURVE_H
#define LAB1_CURVE_H
#include <gmp.h>
#include "parameters.h"

/**
 * Структура для хранения точек
 */
struct Point{
    mpz_t X, Y, Z;

};

// вывод координат точки в проективных координатах на экран
void printProjectivePoint (const struct Point *point);

// инициализация нейтрального элемента
void neutralPointInit (struct Point *point);

// инициализация точки с произвольными координатами
void customPointInit (struct Point *point, char *X, char *Y, char *Z);

/**
 * Структура для хранения параметров квадрики
 *
 * Y^2 = e*X^4 -2*d*X^2 * Z^2 + Z^4
 */
struct JacobiCurve{
    mpz_t X_base;       // первая координата порождающей точки в форме квадрики Якоби
    mpz_t Y_base;       // вторая координата порождающей точки в форме квадрики Якоби
    mpz_t Z_base;       // третья координата порождающей точки в форме квадрики Якоби
    mpz_t e;            // параметр e эллиптической кривой в форме квадрики Якоби
    mpz_t d;            // параметр d эллиптической кривой в форме квадрики Якоби
    mpz_t p;            // характеристика простого поля, над которым определятся эллиптическая кривая

    mpz_t a;           // параметр a эллиптической кривой в форме Вейерштрасса
    mpz_t x;           // первая координата порождающей точки в форме Вейерштрасса
    mpz_t y;           // вторая координата порождающей точки в форме Вейерштрасса
    mpz_t q;           // порядок циклической подгруппы группы точек эллиптической кривой
    mpz_t theta;       // (theta, 0) - точка второго порядка в форме Вейерштрасса
};

// инициализация порождающей точки
void basePointInit (struct Point *point, const struct JacobiCurve *curve);

// перевод в аффинные координаты из проективных
void affineCoordinatesConversion (struct Point *res, const struct Point *point, const struct JacobiCurve *curve);

// вывод координат точки в аффинных координатах на экран
void printAffinePoint (const struct Point *point, const struct JacobiCurve *curve);

// инициализация кривой в форме квадрики Якоби
void JacobiCurveInit (struct JacobiCurve *curve);

// сложение двух точек
void pointsAddition (struct Point *res, const struct Point *P1, const struct Point *P2, const struct JacobiCurve *curve);

// сравнение двух  точек на равенство
int pointsEquality (const struct Point *P1, const struct Point *P2, const struct JacobiCurve *curve);



// запись противоположной точки
void negativePoint (struct Point *res, const struct Point *point);

// алгоритм "Лесенка Монтгомери" для вычисления кратной точки
void montgomeryLadder (struct Point *res, const struct Point *point, const struct JacobiCurve *curve, const mpz_t power);

// проверка, лежит ли точка на кривой
int pointOnCurve (const struct JacobiCurve *curve, const struct Point *point);

// очистка памяти
void pointFree (struct Point *point);

// очистка памяти
void curveFree (struct JacobiCurve *curve);



#endif //LAB1_CURVE_H