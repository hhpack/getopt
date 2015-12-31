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

interface ConsumeHandler<T> extends Matcher
{
    public function name() : string;
    public function flags() : ImmSet<string>;
    public function matches(string $name) : bool;
    public function isTakesValue() : bool;
    public function consume(ArgumentsConsumable<string> $consumer) : Pair<string, T>;
}
