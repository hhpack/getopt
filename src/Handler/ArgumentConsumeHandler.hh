<?hh //strict

/**
 * This file is part of hhpack\getopt package.
 *
 * (c) Noritaka Horio <holy.shared.design@gmail.com>
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */

namespace HHPack\Getopt\Handler;

use HHPack\Getopt\Spec\{ ConsumeType, FlagMatcher };

abstract class ArgumentConsumeHandler<T> implements ConsumeHandler<T>
{

    protected string $name;
    protected ImmVector<FlagMatcher> $flags;
    protected ConsumeType $consumeType = ConsumeType::TakesValue;

    public function name() : string
    {
        return $this->name;
    }

    public function flags() : ImmSet<string>
    {
        $nameHandler = ($flag) ==> $flag->name();
        return $this->flags->map($nameHandler)->toImmSet();
    }

    public function isTakesValue() : bool
    {
        return $this->consumeType === ConsumeType::TakesValue;
    }

    public function matches(string $name) : bool
    {
        $matched = false;

        foreach ($this->flags->items() as $flag) {
            if ($flag->matches($name)) {
                $matched = true;
                break;
            }
        }
        return $matched;
    }

}
