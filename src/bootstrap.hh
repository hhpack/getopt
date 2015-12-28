<?hh //strict

namespace hhpack\getopt
{
    type OptionParameters<T> = shape(
        'name' => string, // option name
        'flags' => Traversable<string>, // example -f, --file
        'defaultValue' => T, // option default value
        'required' => ValueType, // option type, optional or required option,
        'consumeType' => ConsumeType
    );

    type BoolOptionParameters = shape(
        'name' => string, // option name
        'flags' => Traversable<string>, // example -f, --file
        'defaultValue' => bool // option default value
    );

    type OneArgOptionParameters<T> = shape(
        'name' => string, // option name
        'flags' => Traversable<string>, // example -f, --file
        'defaultValue' => T, // option default value
        'required' => ValueType // option type, optional or required option
    );
    type StringOptionParameters = OneArgOptionParameters<string>;
    type IntOptionParameters = OneArgOptionParameters<int>;
    type FloatOptionParameters = OneArgOptionParameters<float>;
    type CallbackOptionParameters<T> = shape(
        'name' => string, // option name
        'flags' => Traversable<string>, // example -f, --file
        'defaultValue' => T, // option default value
        'required' => ValueType, // option type, optional or required option,
        'consumeType' => ConsumeType,
        'callback' => (function(ArgumentsConsumable<string>):T)
    );
}
