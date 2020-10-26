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
 * Вывод координат точки в аффинных координатах
 */
void printAffinePoint (const struct Point *point, const struct JacobiCurve *curve)
{
    struct Point res;
    mpz_inits( res.X, res.Y, res.Z);
    neutralPointInit (&res);

    affineCoordinatesConversion (&res, point, curve);
    gmp_printf("x = %Zd\ny = %Zd\n\n",  res.X, res.Y);
}

/*
 * Инициализация кривой в форме квадрики Якоби:
 * Y^2 = e * X^4 - 2 * d * X^2 * Z^2 + Z^4
 */
void JacobiCurveInit(struct JacobiCurve *curve){
    mpz_t tmp1, tmp2, tmp3, buf1, buf2, buf3;
    mpz_inits(tmp1, tmp2, tmp3, buf1,  buf2, buf3);

    mpz_set_str(curve->theta, theta_str, 10);
    mpz_set_str(curve->a,         a_str, 10);
    mpz_set_str(curve->x,    x_base_str, 10);
    mpz_set_str(curve->y,    y_base_str, 10);
    mpz_set_str(curve->p,         p_str, 10);
    mpz_set_str(curve->q,         q_str, 10);
    mpz_set_str(curve->e,           "0", 10);
    mpz_set_str(curve->d,           "0", 10);
    mpz_set_str(curve->X_base,      "0", 10);
    mpz_set_str(curve->Y_base,      "0", 10);
    mpz_set_str(curve->Z_base,      "0", 10);


    // e = (-(3 * theta^2 + 4 * a)) / 16
    mpz_set_str(buf3, "3", 10);                             // buf3 = 3
    mpz_powm(curve->e, curve->theta, 2, curve->p );         // e = theta^2

    // ------------------------------------------------------- e = 3 * theta^2
    mpz_mul(curve->e, buf3, curve->e);
    mpz_mod(curve->e, curve->e, curve->p);
    // ---------------
    // --------------------------------------------------------buf1 = 4 * a
    mpz_mod(tmp1, curve->a, curve->p);                      //tmp1 = a mod p
    mpz_mul(buf1, 4, tmp1);                                 // buf1 = 4 * a
    mpz_mod(buf1, buf1, curve->p);
    // ---------------
    mpz_mul(buf1, curve->e, buf1);
    mpz_mod(buf1, buf1, curve->p);                          // buf1 = 3 * theta^2 + 4 * a

    mpz_set_str(buf3, "-1", 10);                            // buf3 = -1
    mpz_mul(buf1, buf1, buf3);
    mpz_mod(buf1, buf1, curve->p);                          // buf1 = -(3 * theta^2 + 4 * a)

    mpz_set_str(buf3, "16", 10);                            // buf3 = 16
    mpz_invert(buf3, buf3, curve->p);                       // buf3 = 1 / 16
    mpz_mul(curve->e, buf3, buf1);
    mpz_mod(curve->e, curve->e, curve->p);                  // e = (-(3 * theta^2 + 4 * a)) / 16


    // d = 3 * theta / 4
    mpz_mod(tmp1, curve->theta, curve->p);












}


/*
 * Очистка памяти
 */
void pointFree (struct Point *point)
{
    mpz_clears(point->X, point->Y, point->Z);
}


/*
 * Очистка памяти
 */
void curveFree (struct JacobiCurve *curve)
{
    mpz_clears(curve->theta, curve->a, curve->e, curve->d, curve->x, curve->y, curve->p, curve->q, curve-> X_base, curve->Y_base, curve->Z_base);
}