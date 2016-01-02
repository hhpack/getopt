<?hh //strict

/**
 * This file is part of hhpack\getopt package.
 *
 * (c) Noritaka Horio <holy.shared.design@gmail.com>
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */

namespace hhpack\getopt\handler;

use hhpack\getopt\spec\ConsumeType;
use hhpack\getopt\spec\FlagMatcher;
use hhpack\getopt\argv\ArgumentsConsumable;
use LogicException;

final class BoolConsumeHandler extends ArgumentConsumeHandler<bool>
{

    public function __construct(
        string $name,
        Traversable<string> $flags
    )
    {
        $this->name = $name;
        $this->flags = ImmVector::fromItems($flags)->map(($flag) ==> {
            return new FlagMatcher($flag);
        });
        $this->consumeType = ConsumeType::NoValue;
    }

    public function consume(ArgumentsConsumable<string> $consumer) : Pair <string, bool>
    {
        $value = $consumer->current();

        if (!$this->matches($value))  {
            throw new LogicException('Option name does not match');
        }

        $consumer->consume();

        return Pair { $this->name(), true };
    }

}
