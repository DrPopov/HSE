#include <stdio.h>
#include <string.h>
#include <gmp.h>
#include "curve.h"
#include "parameters.h"
/**
 *
 *
 * План:
 *
 * Реализовать вычисление кратной точки
 * а) Найти параметры эллиптической кривой
 * б) Выработать точку P на кривой и случайное число k
 * в) Вычислить Q = kP
 * г) Проверка
 *   - Точка должна принадлежать кривой
 *   - Проверка условия
 *   k = k1 + k2 => k1P, k2P, (k1P + k2P) = kP
 *   - Пусть m порядок группы точек, тогда
 *   mP = 0(ноль группы)
 *   (m+1)P = P
 *   (m-1)P = P
 *
 *   - Две реализации
 *
 */



void tests(){

    struct Point E, P, P1, P2, P3;
    mpz_inits( E.X,  E.Y,  E.Z,
               P.X,  P.Y,  P.Z,
              P1.X, P1.Y, P1.Z,
              P2.X, P2.Y, P2.Z,
              P3.X, P3.Y, P3.Z);


    struct JacobiCurve curve;
    mpz_inits(curve.p, curve.X_base, curve.Y_base, curve.Z_base, curve.a, curve.d, curve.e, curve.q, curve.theta, curve.x, curve.y);


    printf("\nTest printing:");
    struct Point point1, point2, point3;
    mpz_inits(point1.X, point1.Y, point1.Z);
    mpz_set_ui(point1.X, 1);
    mpz_set_ui(point1.Y, 2);
    mpz_set_ui(point1.Z, 3);
    printProjectivePoint(&point1);

    printf("Test neutralPointInit:");
    neutralPointInit(&point2);
    printProjectivePoint(&point2);


    printf("Test customPointInit:");
    customPointInit(&point3, "3", "4", "5");
    printProjectivePoint(&point3);


    printf("Test basePointInit:");


    printf("Test affineCoordinatesConversion:");

    printf("Test printAffinePoint:");

    printf("Test pointFree");
    pointFree(&point1);
    pointFree(&point2);
    pointFree(&point3);

    printf("Test curveFree");
    curveFree(&curve);



}




int main() {
    //tests();
    return 0;
}


/**

    mpz_t a, b;
    mpz_t t; // this is the type of statement is needed to declare a variable
    mpz_init (t); // initialization of a variable
    mpz_init (a);
    mpz_init (b);
    mpz_set_ui (t, 2); // assignment of 2 to already initialized variable t
    mpz_set_ui (a, 3);
    mpz_set_ui (b, 4);
    mpz_set_str (t, "1234", 10); // string assignment
    mpz_add (t, a , b); // a + b is assigned to t, that is, t = a + b
    mpz_sub (t, a, b); // subtraction
    mpz_mul (t, a, b); // multiplication

    */