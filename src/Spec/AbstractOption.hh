<?hh //strict

/**
 * This file is part of hhpack\getopt package.
 *
 * (c) Noritaka Horio <holy.shared.design@gmail.com>
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */

namespace HHPack\Getopt\Spec;

abstract class AbstractOption implements Option
{

    protected ImmSet<string> $flags;
    protected string $helpMessage = '';
    protected int $numberOfArgs = 0;

    public function flags() : ImmSet<string>
    {
        return $this->flags;
    }

    public function options() : Iterator<Pair<string, Option>>
    {
        foreach ($this->flags->items() as $name) {
            yield Pair { $name, $this };
        }
    }

    public function isTakesValue() : bool
    {
        return $this->numberOfArgs > 0;
    }

    public function helpMessage() : string
    {
        return $this->helpMessage;
    }

    public function toImmMap() : ImmMap<string, Option>
    {
        return ImmMap::fromItems( $this->options() );
    }

    protected function matches(string $name) : bool
    {
        $matched = false;

        $flags = ImmVector::fromItems($this->flags)->map(($flag) ==> {
            return new FlagMatcher($flag);
        });

        foreach ($flags->items() as $flag) {
            if ($flag->matches($name)) {
                $matched = true;
                break;
            }
        }
        return $matched;
    }
}
