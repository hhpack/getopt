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
use HHPack\Getopt\Spec\{ Option, NoArgumentOption, OneArgumentOption, NoArgmentAction, OneArgmentAction };
use HHPack\Getopt\Parser\{ Parser, OptionParser };

function app(string $name, string $version = '0.0.0') : ApplicationSpec
{
    return new ApplicationSpec($name, $version);
}

function optparser(Traversable<Option> $options = []) : Parser
{
    return OptionParser::fromOptions($options);
}

function on(
    Traversable<string> $prefixes,
    string $help,
    NoArgmentAction $action): NoArgumentOption
{
    return new NoArgumentOption($prefixes, $help, $action);
}

function take_on(
    Traversable<string> $prefixes,
    string $help,
    OneArgmentAction $action): OneArgumentOption
{
    return new OneArgumentOption($prefixes, $help, $action);
}
