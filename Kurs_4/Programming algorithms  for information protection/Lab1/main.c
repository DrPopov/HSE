#include <stdio.h>
#include <time.h>
#include <gmp.h>
#include "curve.h"
#include "parameters.h"


void printPointOnCurve (int belongs, char *point)
{
    printf (belongs == 0 ? "\033[0;32mPoint %s is on curve\033[0m\n\n" : "\033[0;31mPoint %s is not on curve\033[0m\n\n", point);
}

void printPointsEquality (int equal, char *P1, char *P2)
{
    printf (equal == 0 ? "\n\033[0;32mPoints %s and %s are equal\033[0m\n\n" : "\033[31mPoints %s and %s are not equal\033[0m\n\n", P1, P2);
}

void tests(){

    printf("Start testing!");

    struct JacobiCurve curve;
    mpz_inits(curve.p, curve.X_base, curve.Y_base, curve.Z_base, curve.a, curve.d, curve.e, curve.q, curve.theta, curve.x, curve.y, NULL);


    JacobiCurveInit(&curve);




    struct Point E, P, P1, P2, P3;
    mpz_inits( E.X, E.Y, E.Z,
               P.X, P.Y, P.Z,
               P1.X, P1.Y, P1.Z,
               P2.X, P2.Y, P2.Z,
               P3.X, P3.Y, P3.Z, NULL);


    mpz_t power, k1, k2, max_rand;
    mpz_inits(max_rand, power, k1, k2, NULL);
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



    // TEST 3: q * P = E (единичный элемент P + (-P) = 0)
    printf("--------------- \033[0;33mTest 3: q * P = E (neutral element P + (-P) = 0): \033[0m ---------------");
    montgomeryLadder (&P1, &P, &curve, curve.q);                      // P1 = q * P в проективных (с помощью лесенки Монтгомери)
    printf ("\nE in affine coordinates:\n");
    printAffinePoint (&E, &curve);
    printf ("(q * P) in affine coordinates:\n");
    printAffinePoint (&P1, &curve);
    printPointsEquality (pointsEquality (&P1, &E, &curve), "(q * P)", "E");
    printPointOnCurve (pointOnCurve (&curve, &P1), "(q * P)");


    // TEST 4: (q + 1) * P = P
    printf("--------------- \033[0;33mTest 4: (q + 1) * P = P \033[0m ---------------");
    mpz_set_str (power, "1", 10);                                        // power = 1
    mpz_add (power, power, curve.q);                                     // power = q + 1
    montgomeryLadder (&P2, &P, &curve, power);                          // P2 = (q + 1) * P в проективных (с помощью лесенки Монтгомери)
    printf ("\nP in affine coordinates:\n");
    printAffinePoint (&P, &curve);
    printf ("(q + 1) * P in affine coordinates:\n");
    printAffinePoint (&P2, &curve);
    printPointsEquality (pointsEquality (&P, &P2, &curve), "((q + 1) * P)", "P");
    printPointOnCurve (pointOnCurve (&curve, &P2), "(q + 1) * P");



    // TEST 5: (q - 1) * P = -P
    printf("--------------- \033[0;33mTest 5: (q - 1) * P = -P: \033[0m ---------------");
    mpz_set_str(power, "1", 10);                                        // power = 1
    mpz_sub(power, curve.q, power);                                     // power = q - 1
    mpz_mod(power, power, curve.p);
    montgomeryLadder (&P2, &P, &curve, power);                          // P2 = (q - 1) * P в проективных (с помощью лесенки Монтгомери)
    negativePoint (&P1, &P);                                            // P1 = -P в проективных
    printf ("\n-P in projective coordinates:\n");
    printProjectivePoint (&P1);
    printf ("-P in affine coordinates:\n");
    printAffinePoint (&P1, &curve);
    printf ("(q - 1) * P in affine coordinates:\n");
    printAffinePoint (&P2, &curve);
    printPointsEquality (pointsEquality (&P1, &P2, &curve), "((q + 1) * P)", "P");
    printPointOnCurve (pointOnCurve (&curve, &P2), "(q + 1) * P");




    // TEST 6: k1 * P + k2 * P = (k1 + k2) * P
    printf("--------------- \033[0;33mTest 6: k1 * P + k2 * P = (k1 + k2) * P:\033[0m ---------------");
    gmp_randstate_t state;
    gmp_randinit_mt (state);
    time_t t1 = time(NULL);
    gmp_randseed_ui(state, t1);
    mpz_urandomm (k1, state, max_rand);
    mpz_urandomm (k2, state, max_rand);
    gmp_randclear(state);

    mpz_add (power, k1, k2);                                             // power = k1 + k2
    montgomeryLadder (&P1, &P, &curve, k1);                             // P1 = k1 * P в проективных (с помощью лесенки Монтгомери)
    montgomeryLadder (&P2, &P, &curve, k2);                             // P2 = k2 * P в проективных (с помощью лесенки Монтгомери)
    pointsAddition (&P1, &P1, &P2, &curve);                             // P1 = P1 + P2 в проективных (с помощью лесенки Монтгомери)
    gmp_printf("\n(%Zd * P + %Zd * P) in affine coordinates:\e[0m\n", k1, k2);
    printAffinePoint (&P1, &curve);
    montgomeryLadder(&P3, &P, &curve, power);                           // P3 = (k1 + k2) в проективных (с помощью лесенки Монтгомери)
    gmp_printf ("(%Zd * P) in affine coordinates:\n", power);
    printAffinePoint (&P3, &curve);
    printPointsEquality (pointsEquality (&P1, &P3, &curve), "(k1 * P + k2 * P)", "((k1 + k2) * P)");
    printPointOnCurve (pointOnCurve (&curve, &P1), "(k1 * P + k2 * P)");
    printPointOnCurve (pointOnCurve (&curve, &P3), "((k1 + k2) * P)");


    pointFree (&P); pointFree (&E); pointFree (&P1); pointFree (&P2); pointFree (&P3);
    //curveFree (&curve);
    mpz_clear (power);



}


int main() {

    tests();

    return 0;
}
