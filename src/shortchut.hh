<?hh //strict

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
    return new OptionValue($consumeHandler, $parameters['defaultValue'], ValueType::Optional); 
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
    return new OptionValue($consumeHandler, $parameters['defaultValue'], $parameters['required']); 
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
    return new OptionValue($consumeHandler, $parameters['defaultValue'], $parameters['required']); 
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
    return new OptionValue($consumeHandler, $parameters['defaultValue'], $parameters['required']); 
}

/**
 * callback_option(shape(
 *   'name' => 'limit',
 *   'flags' => [ '-l', '--limit' ],
 *   'defaultValue' => 95.0,
 *   'required' => ValueType::Optional,
 *   'consumeType' => ArgumentType::Optional,
 *   'callback' => ($consumer) ==> {
 *
 *   }
 * ));
 */
function callback_option(CallbackOptionParameters<mixed> $parameters) : Option<mixed> {
    $consumeHandler = new CallbackConsumeHandler(
        $parameters['name'],
        $parameters['flags'],
        $parameters['consumeType'],
        $parameters['callback']
    );
    return new OptionValue($consumeHandler, $parameters['defaultValue'], $parameters['required']); 
}
