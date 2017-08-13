<?hh //strict

/**
 * This file is part of hhpack\getopt package.
 *
 * (c) Noritaka Horio <holy.shared.design@gmail.com>
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */

namespace HHPack\Getopt;

use HHPack\Getopt\App\ApplicationSpec;
use HHPack\Getopt\Spec\{ Option, ValueType, OptionValue };
use HHPack\Getopt\Parser\{ Parser, OptionParser, ParsedResult };
use HHPack\Getopt\Handler\{ BoolConsumeHandler, IntConsumeHandler, FloatConsumeHandler, StringConsumeHandler };
use LogicException;

function app(string $name, string $version = '0.0.0') : ApplicationSpec
{
    return new ApplicationSpec($name, $version);
}

function optparser(Traversable<Option<mixed>> $options = []) : Parser<ParsedResult>
{
    return OptionParser::fromOptions($options);
}

/**
 * -d|--debug  - flag
 * -n|--name=? - optional
 * -n|--name=+ - required
 */
function parse_spec(string $spec) : (Traversable<string>, ValueType) {
    $matches = [];

    if (preg_match('/^(-[^-=\|]+)?\|?(--[^-=]+)?(=[\+\?])?$/', $spec, $matches) !== 1) {
        throw new LogicException(sprintf("Invalid option specification, spec = %s", $spec));
    }

    if (count($matches) <= 3) {
        $matches[] = null;
    }

    list($_, $shortName, $longName, $valueType) = $matches;

    $flags = ImmSet::fromItems([ $shortName, $longName ])
        ->map(($flag) ==> $flag === null ? '' : $flag)
        ->filter(($flag) ==> $flag !== "");

    $type = ValueType::Optional;

    if ($valueType !== null) {
        $type = ValueType::assert(substr($valueType, 1));
    }

    return tuple( $flags, $type );
}

function bool_option(string $name, string $spec, bool $defaultValue, string $helpMessage) : Option<bool> {
    list($flags, $valueType) = parse_spec($spec);

    $handler = new BoolConsumeHandler($name, $flags);

    return new OptionValue(
        $handler,
        $defaultValue,
        $valueType,
        $helpMessage
    );
}

function string_option(string $name, string $spec, string $defaultValue, string $helpMessage) : Option<string> {
    list($flags, $valueType) = parse_spec($spec);

    $handler = new StringConsumeHandler($name, $flags);

    return new OptionValue(
        $handler,
        $defaultValue,
        $valueType,
        $helpMessage
    );
}

function int_option(string $name, string $spec, int $defaultValue, string $helpMessage) : Option<int> {
    list($flags, $valueType) = parse_spec($spec);

    $handler = new IntConsumeHandler($name, $flags);

    return new OptionValue(
        $handler,
        $defaultValue,
        $valueType,
        $helpMessage
    );
}

function float_option(string $name, string $spec, float $defaultValue, string $helpMessage) : Option<float> {
    list($flags, $valueType) = parse_spec($spec);

    $handler = new FloatConsumeHandler($name, $flags);

    return new OptionValue(
        $handler,
        $defaultValue,
        $valueType,
        $helpMessage
    );
}
