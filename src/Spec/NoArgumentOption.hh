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

use HHPack\Getopt\Argv\ArgumentsConsumable;
use LogicException;

final class NoArgumentOption extends AbstractOption implements Option
{

    public function __construct(
        Traversable<string> $names,
        string $helpMessage = '',
        private NoArgmentAction $action = (() ==> {})
    )
    {
        $this->names = ImmSet::fromItems($names);
        $this->helpMessage = $helpMessage;
        $this->numberOfArgs = 0;
    }

    /**
     * Return option name for display
     *
     * examples:
     *   -h, --help
     *   --version
     */
    public function helpLabel() : string
    {
        $names = $this->names()->toValuesArray();
        return implode(', ', $names);
    }

    public function consume(ArgumentsConsumable<string> $consumer) : void
    {
        $value = $consumer->current();

        if (!$this->matches($value))  {
            throw new LogicException('Option name does not match');
        }

        $consumer->consume();

        $action = $this->action;
        $action();
    }
}
