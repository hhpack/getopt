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

use HHPack\Getopt\App\{ ArgumentParser };
use HHPack\Getopt\Spec\{ Option, NoArgumentOption, OneArgumentOption, NoArgmentAction, OneArgmentAction };
use HHPack\Getopt\Parser\{ Parser, OptionParser };

function app(string $name, string $version = '0.0.0') : ArgumentParser
{
    return new ArgumentParser($name, $version);
}

/**
 * Create a option parser
 */
function optparser(Traversable<Option> $options = []) : OptionParser
{
    return OptionParser::fromOptions($options);
}

/**
 * Create a no argument option
 *
 *   on(['-h', '--help'], 'message', () ==> { ... }])
 *
 */
function on(
    Traversable<string> $prefixes,
    string $help,
    NoArgmentAction $action): NoArgumentOption
{
    return new NoArgumentOption($prefixes, $help, $action);
}

/**
 * Create a one argument option
 *
 *   take_on(['--name'], 'message', ($name) ==> { ... }])
 *
 */
function take_on(
    Traversable<string> $prefixes,
    string $help,
    OneArgmentAction $action): OneArgumentOption
{
    return new OneArgumentOption($prefixes, $help, $action);
}
