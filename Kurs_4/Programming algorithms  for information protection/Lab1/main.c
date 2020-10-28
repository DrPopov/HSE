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
    //printf ("Result: %d\n", belongs );
    printf (belongs == 0 ? "\033[0;32mPoint %s is on curve\033[0m\n\n" : "\033[0;31mPoint %s is not on curve\033[0m\n\n", point);
}

void printPointsEquality (int equal, char *P1, char *P2)
{
    printf (equal == 0 ? "\n\033[0;32mPoints %s and %s are equal\033[0m\n\n" : "\033[31mPoints %s and %s are not equal\033[0m\n\n", P1, P2);
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
    mpz_init(max_rand); mpz_init(power); mpz_init(k1); mpz_init(k2);
    mpz_set_str(max_rand, max_rand_str, 10);


    customPointInit(&P1, "1", "1", "1");         // P1 = (1 : 1 : 1) в проетивных
    customPointInit(&P2, "1", "1", "1");         // P2 = (1 : 1 : 1) в проективных

    gmp_printf("\nParameter e = %Zd\n\n", curve.e);
    gmp_printf("\nParameter d = %Zd\n\n", curve.d);

    // TEST 1: E = (0 : 1 : 1) is on curve
    printf("--------------- \033[0;33mTest 1:\033[0m ---------------");
    neutralPointInit(&E);
    printf("\nE - neutral element (0 : 1 : 1):");            // E - нейтральная в проективных
    printProjectivePoint(&E);
    printf("E in affine coordinates:\n");
    printAffinePoint(&E, &curve);
    printPointOnCurve(pointOnCurve(&curve, &E), "E");


    // TEST 2: P (base point) is on curve
    printf("--------------- \033[0;33mTest 2:\033[0m ---------------");
    basePointInit (&P, &curve);                                      // P - базовая в проективных
    printf ("\nP - base point in projective coordinates:");
    printProjectivePoint (&P);
    printf ("P in affine coordinates:\n");
    printAffinePoint (&P, &curve);
    printPointOnCurve (pointOnCurve (&curve, &P), "P");


    // TEST 3: E + P = P; (E + P) is on curve
    printf("--------------- \033[0;33mTest 3:\033[0m ---------------");
    pointsAddition (&P1, &E, &P, &curve);                                   // P1 = E + P в проективных
    printPointsEquality (pointsEquality (&P1, &P, &curve), "(E + P)", "P");
    printPointOnCurve (pointOnCurve (&curve, &P1), "(E + P)");


    // TEST 4: point (2 : 4 : 6) is not on curve
    printf("--------------- \033[0;33mTest 4:\033[0m ---------------");
    customPointInit(&P3, "2", "4", "6");                    // P3 = (2 : 4 : 6) в проективных
    printf ("\nPoint (2 : 4 : 6) in affine coordinates:\n");
    printAffinePoint (&P3, &curve);
    printPointsEquality (pointsEquality (&E, &P3, &curve), "E", "(2 : 4 : 6)");
    printPointOnCurve (pointOnCurve (&curve, &P3), "(2 : 4 : 6)");


    // TEST 5: (q + 1) * P = P
    printf("--------------- \033[0;33mTest 5:\033[0m ---------------");
    mpz_set_str (power, "1", 10);                                        // power = 1
    mpz_add (power, power, curve.q);                                     // power = q + 1
    montgomeryLadder (&P2, &P, &curve, power);                          // P2 = (q + 1) * P в проективных (с помощью лесенки Монтгомери)
    printf ("\nP in affine coordinates:\n");
    printAffinePoint (&P, &curve);
    printf ("(q + 1) * P in affine coordinates:\n");
    printAffinePoint (&P2, &curve);
    printPointsEquality (pointsEquality (&P, &P2, &curve), "((q + 1) * P)", "P");
    printPointOnCurve (pointOnCurve (&curve, &P2), "(q + 1) * P");


    // TEST 6: q * P = E (единичный элемент P + (-P) = 0)
    printf("--------------- \033[0;33mTest 6:\033[0m ---------------");
    montgomeryLadder (&P1, &P, &curve, curve.q);                      // P1 = q * P в проективных (с помощью лесенки Монтгомери)
    printf ("\nE in affine coordinates:\n");
    printAffinePoint (&E, &curve);
    printf ("(q * P) in affine coordinates:\n");
    printAffinePoint (&P1, &curve);
    printPointsEquality (pointsEquality (&P1, &E, &curve), "(q * P)", "E");
    printPointOnCurve (pointOnCurve (&curve, &P1), "(q * P)");


    // TEST 7: (q - 1) * P = -P
    printf("--------------- \033[0;33mTest 7:\033[0m ---------------");
    mpz_set_str(power, "1", 10);                                        // power = 1
    mpz_add(power, curve.q, power);                                     // power = q - 1
    montgomeryLadder (&P2, &P, &curve, power);                          // P2 = (q - 1) * P в проективных (с помощью лесенки Монтгомери)
    negativePoint (&P1, &P);                                            // P1 = -P в проективных
    printf ("-P in projective coordinates:\n");
    printProjectivePoint (&P1);
    printf ("-P in affine coordinates:\n");
    printAffinePoint (&P1, &curve);
    printf ("(q - 1) * P in affine coordinates:\n");
    printAffinePoint (&P2, &curve);
    printPointsEquality (pointsEquality (&P1, &P2, &curve), "((q + 1) * P)", "P");
    printPointOnCurve (pointOnCurve (&curve, &P2), "(q + 1) * P");


    // TEST 8: P + ... + P (12543 times) = 12543 * P
    printf("--------------- \033[0;33mTest 8:\033[0m ---------------");
    neutralPointInit (&P1);                                             // P1 - нейтральная в проективных
    for (int i = 0; i < 12543; ++i)
    {
        pointsAddition (&P1, &P1, &P, &curve);
    }
    mpz_set_str (power, "12543", 10);                                      // power =  12543
    montgomeryLadder(&P2, &P, &curve, power);                             // P2 = 12543 * P в проективных (с помощью лесенки Монтгомери)
    printf ("\n(P + ... + P 543 times) in affine coordinates:\n");
    printAffinePoint (&P1, &curve);
    printf ("(543 * P) in affine coordinates:\n");
    printAffinePoint (&P2, &curve);
    printPointsEquality (pointsEquality (&P1, &P2, &curve), "(P + ... + P 12543 times)", "(12543 * P)");
    printPointOnCurve (pointOnCurve (&curve, &P1), "(P + ... + P 12543 times)");
    printPointOnCurve (pointOnCurve (&curve, &P2), "(12543 * P)");



    // TEST 9: power * P

    printf("--------------- \033[0;33mTest 9:\033[0m ---------------");
    gmp_randstate_t state;
    gmp_randinit_default(state);
    mpz_urandomm(power, state, max_rand);
    printf ("TEST 9: %s * P:\n\n", power);
    printf ("(%s * P) in affine coordinates:\n", power);
    montgomeryLadder (&P1, &P, &curve, power);                          // P1 = power * P в проективных (с помощью лесенки Монтгомери)
    printAffinePoint (&P1, &curve);
    printPointOnCurve (pointOnCurve (&curve, &P1), "(power * P)");
    printf ("Power = %s\n\n", power);


    // TEST 10: k1 * P + k2 * P = (k1 + k2) * P
    printf("--------------- \033[0;33mTest 10:\033[0m ---------------");
    printf ("TEST 10: k1 * P + k2 * P = (k1 + k2) * P:\n\n");
    mpz_urandomm (k1, state, max_rand);
    mpz_urandomm (k1, state, max_rand);
    mpz_add (power, k1, k2);                                             // power = k1 + k2
    montgomeryLadder (&P1, &P, &curve, k1);                             // P1 = k1 * P в проективных (с помощью лесенки Монтгомери)
    montgomeryLadder (&P2, &P, &curve, k2);                             // P2 = k2 * P в проективных (с помощью лесенки Монтгомери)
    pointsAddition (&P1, &P1, &P2, &curve);                             // P1 = P1 + P2 в проективных (с помощью лесенки Монтгомери)
    printf ("(%s * P + %s * P) in affine coordinates:\e[0m\n", k1, k2);
    printAffinePoint (&P1, &curve);
    montgomeryLadder(&P3, &P, &curve, power);                           // P3 = (k1 + k2) в проективных (с помощью лесенки Монтгомери)
    printf ("(%s * P) in affine coordinates:\n", power);
    printAffinePoint (&P3, &curve);
    printPointsEquality (pointsEquality (&P1, &P3, &curve), "(k1 * P + k2 * P)", "((k1 + k2) * P)");
    printPointOnCurve (pointOnCurve (&curve, &P1), "(k1 * P + k2 * P)");
    printPointOnCurve (pointOnCurve (&curve, &P3), "((k1 + k2) * P)");


    pointFree (&P); pointFree (&E); pointFree (&P1); pointFree (&P2); pointFree (&P3);
    curveFree (&curve);
    mpz_clear (power);


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