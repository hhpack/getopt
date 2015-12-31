<?hh //strict

/**
 * This file is part of hhpack\getopt package.
 *
 * (c) Noritaka Horio <holy.shared.design@gmail.com>
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */

namespace hhpack\getopt;

/**
 * bool_option(shape(
 *   'name' => 'debug',
 *   'flags' => [ '-d', '--debug' ],
 *   'defaultValue' => false
 * ));
 */
function bool_option(BoolOptionParameters $parameters) : Option<bool> {
    $consumeHandler = new BoolConsumeHandler(
        $parameters['name'],
        $parameters['flags']
    );
    return new OptionValue(
        $consumeHandler,
        $parameters['defaultValue'],
        ValueType::Optional,
        $parameters['helpMessage']
    ); 
}

/**
 * string_option(shape(
 *   'name' => 'name',
 *   'flags' => [ '-n', '--name' ],
 *   'defaultValue' => 'foo',
 *   'required' => ValueType::Optional
 * ));
 */
function string_option(StringOptionParameters $parameters) : Option<string> {
    $consumeHandler = new StringConsumeHandler(
        $parameters['name'],
        $parameters['flags']
    );
    return new OptionValue(
        $consumeHandler,
        $parameters['defaultValue'],
        $parameters['required'],
        $parameters['helpMessage']
    ); 
}

/**
 * int_option(shape(
 *   'name' => 'limit',
 *   'flags' => [ '-l', '--limit' ],
 *   'defaultValue' => 100,
 *   'required' => ValueType::Optional
 * ));
 */
function int_option(IntOptionParameters $parameters) : Option<int> {
    $consumeHandler = new IntConsumeHandler(
        $parameters['name'],
        $parameters['flags']
    );
    return new OptionValue(
        $consumeHandler,
        $parameters['defaultValue'],
        $parameters['required'],
        $parameters['helpMessage']
    ); 
}

/**
 * float_option(shape(
 *   'name' => 'limit',
 *   'flags' => [ '-l', '--limit' ],
 *   'defaultValue' => 95.0,
 *   'required' => ValueType::Optional
 * ));
 */
function float_option(FloatOptionParameters $parameters) : Option<float> {
    $consumeHandler = new FloatConsumeHandler(
        $parameters['name'],
        $parameters['flags']
    );
    return new OptionValue(
        $consumeHandler,
        $parameters['defaultValue'],
        $parameters['required'],
        $parameters['helpMessage']
    ); 
}
