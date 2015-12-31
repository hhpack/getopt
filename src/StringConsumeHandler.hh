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

final class StringConsumeHandler implements ConsumeHandler<string>
{

    private OneArgumentConsumeHandler $handler;

    public function __construct(
        string $name,
        Traversable<string> $flags
    )
    {
        $this->handler = new OneArgumentConsumeHandler($name, $flags);
    }

    public function name() : string
    {
        return $this->handler->name();
    }

    public function flags() : ImmSet<string>
    {
        return $this->handler->flags();
    }

    public function isTakesValue() : bool
    {
        return $this->handler->isTakesValue();
    }

    public function matches(string $name) : bool
    {
        return $this->handler->matches($name);
    }

    public function consume(ArgumentsConsumable<string> $consumer) : Pair <string, string>
    {
        return $this->handler->consume($consumer);
    }

}
