/***
* Integrals.h - implementacja algorytmów ca³ek oznaczonych - trzy metody
*		(c) Krzysztof Abram
*		
*		Ten plik definiuje podstawowe funkcje licz¹ce ca³kê oznaczon¹
*		na przedziale domkniêtym [a,b], w którym funkcja jest ci¹g³a i ograniczona.
*
*		[Public]
***/

/* Œrednica podzia³u przedzia³u - dla funkcji int_rectangle */
#define _dx_rec		0.0001
/* Œrednica podzia³u przedzia³u - dla funkcji int_trapeze */
#define _dx_trap	0.0001
/* Iloœæ punktów losowych dla Monte-Carlo */
#define _n_per_mc	1000000

/* int_rectangle - liczenie ca³ki metod¹ ma³ych prostok¹tów :
 * f - funkcja rzeczywista argumentu rzeczywistego ( podca³kowa ),
 * a - granica dolna ca³kowania,
 * b - granica górna ca³kowania,
 * return : ca³ka oznaczona w przedziale [a,b] funkcji f(x)
 */
long double int_rectangle( double (*f)( double ), double a, double b ){
	double _int = 0, _x, _tmp;
	/* Decyduje o znaku ca³ki - gdy wynika to z podanego przedzia³u ca³kowania */
	int sign = 1;

	if (b < a){
		_tmp = a;
		a = b;
		b = _tmp;
		sign = -1;
	}
	_x = a;
	for (; _x <= b; _x += _dx_rec ) 
		_int += _dx_rec * f( _x );
	return ( sign * _int );
}// end int_rectangle

/* int_trapeze - liczenie ca³ki metod¹ ma³ych trapezów :
* f - funkcja rzeczywista argumentu rzeczywistego ( podca³kowa ),
* a - granica dolna ca³kowania,
* b - granica górna ca³kowania,
* return : ca³ka oznaczona w przedziale [a,b] funkcji f(x)
*/
long double int_trapeze( double(*f)(double), double a, double b ){
	double _int = 0, _x, _tmp; 
	double _b, _e; // Zmienne pomocnicze - przechowuj¹ wartoœci funkcji f ( _b - na pocz¹tku przedzia³u czêœciowego, _e - na koñcu przedzia³u czêœciowego )
	int sign = 1; // Decyduje o znaku ca³ki - gdy wynika to z podanego przedzia³u ca³kowania

	if (b < a){
		_tmp = a;
		a = b;
		b = _tmp;
		sign = -1;
	}

	_x = a;
	_b = f( _x );
	for (; _x <= b; _x += _dx_trap){
		_e = f(_x + _dx_trap);
		_int += _dx_trap * ( _b + _e ) / 2;
		_b = _e;
	}

	return (sign * _int);
}// end int_trapeze

/* int_mc - liczenie ca³ki metod¹ Monte-Carlo :
* f - funkcja rzeczywista argumentu rzeczywistego ( podca³kowa ),
* a - granica dolna ca³kowania,
* b - granica górna ca³kowania,
* return : ca³ka oznaczona w przedziale [a,b] funkcji f(x)
*/
long double int_mc(double(*f)(double), double a, double b){
	double _int = 0, _tmp;
	int sign = 1; // Decyduje o znaku ca³ki - gdy wynika to z podanego przedzia³u ca³kowania
	__int64 n = 0; // n-te losowanie
	__int64 N; // iloœæ punktów losowych

	if (b < a){
		_tmp = a;
		a = b;
		b = _tmp;
		sign = -1;
	}

	srand(time(NULL));
	N = _n_per_mc * (__int64)(fabs(b - a)); // iloœæ punktów losowych zale¿na od wielkoœci przedzia³u
	for (; n < N; n++){
		_int += f( a + (double)rand()/(double)(RAND_MAX) * (b - a) );
	}
	_int = (b - a) * _int / N;
	return (sign * _int);
}// end int_mc