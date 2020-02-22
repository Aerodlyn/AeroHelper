#ifndef COLOR_H
#define COLOR_H

#include <QMetaType>
#include <QString>
#include <QStringLiteral>

namespace Aerodlyn
{
    /**
     * Interface for representing a color that will be passed to the color_converter CLI.
     *
     * @author  Patrick Jahnig (Aerodlyn)
     * @version 2020.02.15
     */
    class Color
    {
        private: // Fields
            int     _a;
            int     _b;
            int     _g;
            int     _r;

            QString _hex;

        public: // Constructors/Deconstructors
            /**
             * Creates a new Color instance using the given RGBA values.
             *
             * @param r - The red component of the color
             * @param g - The green component of the color
             * @param b - The blue component of the color
             * @param a - The alpha component of the color
             */
            Color (const int r = 0, const int g = 0, const int b = 0, const int a = 255);

        public: // Methods
            /**
             * Returns the alpha component of this color.
             *
             * @return The alpha component of this color
             */
            int a ();

            /**
             * Returns the blue component of this color.
             *
             * @return The blue component of this color
             */
            int b ();

            /**
             * Returns the green component of this color.
             *
             * @return The green component of this color
             */
            int g ();

            /**
             * Returns the red component of this color.
             *
             * @return The red component of this color
             */
            int r ();

            /**
             * Returns the stored hexadecimal string representing this color
             *
             * @return The stored hexadecimal string
             */
            QString hex () const;

        private: // Methods
            /**
             * Converts the given value (i.e. RGBA component) to a hexadecimal part.
             *
             * @param value - The value to convert into a hexadecimal part
             *
             * @return The given value converted into a hexadecimal part
             */
            QString toHex (const int value);
    };
}

Q_DECLARE_METATYPE (Aerodlyn::Color)

#endif
