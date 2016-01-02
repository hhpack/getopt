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
    use hhpack\getopt\spec\ValueType;

    type ArgOptionSpec<T> = (string, T, string);
    type ArgOptionParameters<T> = shape(
        'name' => string, // option name
        'flags' => Traversable<string>, // example -f, --file
        'defaultValue' => T, // option default value
        'required' => ValueType, // option type, optional or required option
        'helpMessage' => string
    );
}
