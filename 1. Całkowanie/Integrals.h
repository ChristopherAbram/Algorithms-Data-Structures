/***
* Integrals.h - implementacja algorytm�w ca�ek oznaczonych - trzy metody
*		(c) Krzysztof Abram
*		
*		Ten plik definiuje podstawowe funkcje licz�ce ca�k� oznaczon�
*		na przedziale domkni�tym [a,b], w kt�rym funkcja jest ci�g�a i ograniczona.
*
*		[Public]
***/

/* �rednica podzia�u przedzia�u - dla funkcji int_rectangle */
#define _dx_rec		0.0001
/* �rednica podzia�u przedzia�u - dla funkcji int_trapeze */
#define _dx_trap	0.0001
/* Ilo�� punkt�w losowych dla Monte-Carlo */
#define _n_per_mc	1000000

/* int_rectangle - liczenie ca�ki metod� ma�ych prostok�t�w :
 * f - funkcja rzeczywista argumentu rzeczywistego ( podca�kowa ),
 * a - granica dolna ca�kowania,
 * b - granica g�rna ca�kowania,
 * return : ca�ka oznaczona w przedziale [a,b] funkcji f(x)
 */
long double int_rectangle( double (*f)( double ), double a, double b ){
	double _int = 0, _x, _tmp;
	/* Decyduje o znaku ca�ki - gdy wynika to z podanego przedzia�u ca�kowania */
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

/* int_trapeze - liczenie ca�ki metod� ma�ych trapez�w :
* f - funkcja rzeczywista argumentu rzeczywistego ( podca�kowa ),
* a - granica dolna ca�kowania,
* b - granica g�rna ca�kowania,
* return : ca�ka oznaczona w przedziale [a,b] funkcji f(x)
*/
long double int_trapeze( double(*f)(double), double a, double b ){
	double _int = 0, _x, _tmp; 
	double _b, _e; // Zmienne pomocnicze - przechowuj� warto�ci funkcji f ( _b - na pocz�tku przedzia�u cz�ciowego, _e - na ko�cu przedzia�u cz�ciowego )
	int sign = 1; // Decyduje o znaku ca�ki - gdy wynika to z podanego przedzia�u ca�kowania

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

/* int_mc - liczenie ca�ki metod� Monte-Carlo :
* f - funkcja rzeczywista argumentu rzeczywistego ( podca�kowa ),
* a - granica dolna ca�kowania,
* b - granica g�rna ca�kowania,
* return : ca�ka oznaczona w przedziale [a,b] funkcji f(x)
*/
long double int_mc(double(*f)(double), double a, double b){
	double _int = 0, _tmp;
	int sign = 1; // Decyduje o znaku ca�ki - gdy wynika to z podanego przedzia�u ca�kowania
	__int64 n = 0; // n-te losowanie
	__int64 N; // ilo�� punkt�w losowych

	if (b < a){
		_tmp = a;
		a = b;
		b = _tmp;
		sign = -1;
	}

	srand(time(NULL));
	N = _n_per_mc * (__int64)(fabs(b - a)); // ilo�� punkt�w losowych zale�na od wielko�ci przedzia�u
	for (; n < N; n++){
		_int += f( a + (double)rand()/(double)(RAND_MAX) * (b - a) );
	}
	_int = (b - a) * _int / N;
	return (sign * _int);
}// end int_mc