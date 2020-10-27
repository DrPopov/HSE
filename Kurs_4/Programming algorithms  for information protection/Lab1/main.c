#include <stdio.h>
//#include <string.h>
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

void printPointOnCurve (int belongs, char *point)
{
    printf (belongs == 0 ? "Point %s is on curve\n\n" : "Point %s is not on curve\n\n", point);
}

void printPointsEquality (int equal, char *P1, char *P2)
{
    printf (equal == 0 ? "\e[36mPoints %s and %s are equal\e[0m\n\n" : "\e[31mPoints %s and %s are not equal\e[0m\n\n", P1, P2);
}

void tests(){

    printf("Start testing!");

    struct JacobiCurve curve;
    mpz_init(curve.p); mpz_init(curve.X_base); mpz_init(curve.Y_base); mpz_init(curve.Z_base); mpz_init(curve.a); mpz_init(curve.d); mpz_init(curve.e); mpz_init(curve.q); mpz_init(curve.theta); mpz_init(curve.x); mpz_init(curve.y);


    printf("\nTest JacobiCurveInit:");
    JacobiCurveInit(&curve);


    struct Point E, P, P1, P2, P3;
    mpz_init( E.X); mpz_init( E.Y); mpz_init( E.Z);
    mpz_init( P.X); mpz_init( P.Y); mpz_init( P.Z);
    mpz_init( P1.X); mpz_init( P1.Y); mpz_init( P1.Z);
    mpz_init( P2.X); mpz_init( P2.Y); mpz_init( P2.Z);
    mpz_init( P3.X); mpz_init( P3.Y); mpz_init( P3.Z);


    mpz_t power, k1, k2, max_rand;
    mpz_init(max_rand);
    mpz_set_str(max_rand, max_rand_str, 10);


    customPointInit(&P1, "1", "1", "1");         // P1 = (1 : 1 : 1) в проетивных
    customPointInit(&P2, "1", "1", "1");         // P2 = (1 : 1 : 1) в проективных

    gmp_printf("\nParameter e = %Zd\n\n", curve.e);
    gmp_printf("\nParameter d = %Zd\n\n", curve.d);

    // TEST 1: E = (0 : 1 : 1) is on curve
    printf("--------------- Test 1: ---------------");
    neutralPointInit(&E);
    printf("\nE - neutral element (0 : 1 : 1):");
    printProjectivePoint(&E);
    printf("E in affine coordinates:");
    printAffinePoint(&E, &curve);
    //pointOnCurve(&curve, &E);
    printPointOnCurve(pointOnCurve(&curve, &E), "E");

    /**

    printf("\nTest printing:");
    struct Point point1, point2, point3, res;
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
    basePointInit(&point1, &curve);


    printf("Test affineCoordinatesConversion:");

    printf("Test printAffinePoint:");
    printAffinePoint(&point1, &curve);


    printf("Test pointsAddition");
    pointsAddition(&res, &point1, &point2, &curve);

    printf("Test pointsEquality");
    pointsEquality(&point1, &point2, &curve);

    printf("Test pointFree");
    pointFree(&point1);
    pointFree(&point2);
    pointFree(&point3);

    printf("Test curveFree");
    curveFree(&curve);

     */



}




int main() {
    tests();
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