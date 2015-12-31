<?hh //strict

/**
 * This file is part of hhpack\getopt package.
 *
 * (c) Noritaka Horio <holy.shared.design@gmail.com>
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */

namespace hhpack\getopt
{
    type BoolOptionParameters = shape(
        'name' => string, // option name
        'flags' => Traversable<string>, // example -f, --file
        'defaultValue' => bool, // option default value
        'helpMessage' => string
    );

    type OneArgOptionParameters<T> = shape(
        'name' => string, // option name
        'flags' => Traversable<string>, // example -f, --file
        'defaultValue' => T, // option default value
        'required' => ValueType, // option type, optional or required option
        'helpMessage' => string
    );
    type StringOptionParameters = OneArgOptionParameters<string>;
    type IntOptionParameters = OneArgOptionParameters<int>;
    type FloatOptionParameters = OneArgOptionParameters<float>;
}
