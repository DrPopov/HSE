#include "curve.h"
#include <gmp.h>
//#include "parameters.h"


/**
 * Вывод координат точки в проективных координатах на экран
 */
void printProjectivePoint (const struct Point *point)
{
    gmp_printf("\nX = %Zd\nY = %Zd\nZ = %Zd\n\n", point->X, point->Y, point->Z);
}

/**
 *  Инициализация нейтрального элемента в проективных координатах 0 = (0, 1, 1)
 */
void neutralPointInit (struct Point *point){
    mpz_inits(point->X, point->Y, point->Z);
    mpz_set_str(point->X, "0", 10);
    mpz_set_str(point->Y, "1", 10);
    mpz_set_str(point->Z, "1", 10);
}

/**
 * Инициализация точки с произвольными координатами
 */
void customPointInit (struct Point *point, char *X, char *Y, char *Z) {
    mpz_inits(point->X, point->Y, point->Z);
    mpz_set_str(point->X, X, 10);
    mpz_set_str(point->Y, Y, 10);
    mpz_set_str(point->Z, Z, 10);
}

/**
 *  Инициализация порождающей точки
 */
void basePointInit (struct Point *point, const struct JacobiCurve *curve){
    neutralPointInit(point);
    mpz_set(point->X, curve->X_base);
    mpz_set(point->Y, curve->Y_base);
    mpz_set(point->Z, curve->Z_base);

}

/*
 * Перевод в аффинные координаты из проективных:
 *      x = X / Z
 *      y = X / Z^2
 *      z = 0
 */
void affineCoordinatesConversion (struct Point *res, const struct Point *point, const struct JacobiCurve *curve){
    mpz_t tmp1, tmp2, x, y, z;
    mpz_inits(tmp1,tmp2,  x, y, z);

    // x = X / Z  1/z(mod n) * x(mod n)
    mpz_invert(x, point->Z, curve->p);                  // x = 1 / Z
    mpz_mod(tmp1, x, curve->p);                         // x mod p
    mpz_mod(tmp2, point->X, curve->p);                 // X mod p
    mpz_mul(tmp1, tmp1, tmp2);                          // x * X
    mpz_mod(x, tmp1, curve->p);                         // x * X mod p
    //mpz_cdiv_qr(x, 0, x, point->X);


    // y = Y / Z^2
    mpz_invert(y, point->Z, curve->p);                   // y = 1 / Z
    mpz_powm(y, y, 2, curve->p);                         // y = 1 / Z^2

    //????
    // BN_mod_inverse (y, point->Z, curve->p, tmp);
    //N_mod_mul (y, y, y, curve->p, tmp);
    mpz_mod(tmp1, y, curve->p);
    mpz_mod(tmp2, point->Y, curve->p);
    mpz_mul(tmp1, tmp1, tmp2);
    mpz_mod(y, tmp1, curve->p);                          // y = Y / Z^2


    // z = 0
    mpz_set_str(z, "0", 10);                           // z = 0


    mpz_set(res->X, x);
    mpz_set(res->Y, y);
    mpz_set(res->Z, z);


    // Clear
    mpz_clears(x, y, z, tmp1, tmp2);

}

/*
 * Вывод координат точки в аффинных координатах на экран
 */
void printAffinePoint (const struct Point *point, const struct JacobiCurve *curve)
{
    struct Point res;
    mpz_inits( res.X, res.Y, res.Z);
    neutralPointInit (&res);

    affineCoordinatesConversion (&res, point, curve);
    gmp_printf("x = %Zd\ny = %Zd\n\n",  res.X, res.Y);
}