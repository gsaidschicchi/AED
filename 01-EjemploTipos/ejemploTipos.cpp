
#include <string>
#include <cassert>

using namespace std::literals;

int main()
{
    // Boolean
    assert(false == !true);
    assert(true == true && true);
    assert(true == false || true);
    assert(true == true ^ false);

    // String (c++)
    assert("Hola Mundo"s == "Ho"s + "la"s + " "s + "Mun"s + "do"s);
    assert(10 == "Hola Mundo"s.length());
    assert('H' == "Hola Mundo"s.at(0));
    assert('H' == "Hola Mundo"s[0]);
    assert("Hola" == "Hola Mundo"s.substr(0, 4));

    // Desplazamiento de bits
    assert(10 == (5 << 1));  // Desplazo el 1 un bit a la izquierda 0101 << 0001 -> 1010b = 10d
    assert(10 == (20 >> 1)); // Desplazo el 1 un bit a la derecha 0001 >> 10100 -> 01010b = 10d

    // Char
    assert('a' == 97);
    assert('a' + 1 == 98);
    assert('a' + 1 == 'b');
    assert(97 + 1 == 'b');
    assert('d' - 'Z' == 10);

    // Unsigned
    assert(3 == 2 + 1);
    assert(0 == 0);
    assert(10 > 0);
    assert(10 == 5 * 2);

    // Integer
    assert(2u == 1u + 1u);
    assert(0u == 1u - 1u);
    assert(4u == 2u * 2u);
    assert(1u == 5u / 5u);
    assert(1u == 5u % 2u);
    assert(5u > 2u);
    assert(2u < 5u);

    // Double
    assert(2.0 == 1.0 + 1.0);
    assert(0.1 == 1.0 / 10.0);
    assert(1 == 1.0);
    assert(2.0 == 1 + 1.0);
    assert(2 == 1 + 1.0);
    assert(49.9 <= 50.0);
    assert(127.0 * 127.0 <= 16129.0);

    /**
     * Son los enumerados en la sección anterior realmente todos los tipos que usamos en clase?
     *
     * No, no son todos los tipos que usamos en clase.
     *
     * Algunos ejemplos pueden ser:
     *  - Tipos de datos void
     *  - Tipos de datos de punteros
     *  - Tipos de datos de structs
     *  - Tipos de datos de clases
     */

    /**
     * Para cada tipo de dato, agregue una notación literal alternativa, si la tiene.
     *
     * Boolean: No tiene notación literal alternativa.
     * Unsigned: No tiene notación literal alternativa.
     * Double: No tiene notación literal alternativa.
     * Char: No tiene notación literal alternativa.
     *
     * Integer: Se le puede agregar la notación literal "u" al final del número.
     * String: Se le puede agregar la notación literal "s" al final de la cadena.
     */

    /**
     * Intente probar que la suma de diez veces un décimo (0.1) es uno (1.0). ¿Qué está ocurriendo?
     *
     * Lo que esta ocurriendo es un problema de redondeo, ya que las computadoras utilizan IEEE 754
     * para representar los números de punto flotante, y en este caso, el número 0.1 no puede ser
     * representado exactamente en binario.
     *
     * Por lo tanto, la suma de diez veces 0.1 no es exactamente 1.0, sino que es un número muy
     * cercano a 1.0.
     *
     */
    assert(1.0 != 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1);

    return 0;
}
