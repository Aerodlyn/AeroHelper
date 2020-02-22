#include "Color.h"

/**
 * Interface for representing a color that will be passed to the color_converter CLI.
 *
 * @author  Patrick Jahnig (Aerodlyn)
 * @version 2020.02.15
 */

/**
 * Creates a new Color instance using the given RGBA values.
 *
 * @param r - The red component of the color
 * @param g - The green component of the color
 * @param b - The blue component of the color
 * @param a - The alpha component of the color
 */
Aerodlyn::Color::Color (const int r, const int g, const int b, const int a)
    : _a (a), _b (b), _g (g), _r (r)
{
    QString hex = QStringLiteral ("0x%1%2%3%4")
        .arg (toHex (r), 2, '0')
        .arg (toHex (g), 2, '0')
        .arg (toHex (b), 2, '0')
        .arg (toHex (a), 2, '0');

    _hex = hex;
}

/* Public methods */
/**
 * Returns the alpha component of this color.
 *
 * @return The alpha component of this color
 */
int Aerodlyn::Color::a ()
    { return _a; }

/**
 * Returns the blue component of this color.
 *
 * @return The blue component of this color
 */
int Aerodlyn::Color::b ()
    { return _b; }

/**
 * Returns the green component of this color.
 *
 * @return The green component of this color
 */
int Aerodlyn::Color::g ()
    { return _g; }

/**
 * Returns the red component of this color.
 *
 * @return The red component of this color
 */
int Aerodlyn::Color::r ()
    { return _r; }

/**
 * Returns the stored hexadecimal string representing this color
 *
 * @return The stored hexadecimal string
 */
QString Aerodlyn::Color::hex () const
    { return _hex; }

/* Private methods */
/**
 * Converts the given value (i.e. RGBA component) to a hexadecimal part.
 *
 * @param value - The value to convert into a hexadecimal part
 *
 * @return The given value converted into a hexadecimal part
 */
QString Aerodlyn::Color::toHex (const int value)
{
    const char hexValues [] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };
    QString result = QString ();

    int counter = value;
    while (counter > 0)
    {
        result.prepend (hexValues [counter % 16]);
        counter /= 16;
    }

    return result;
}
