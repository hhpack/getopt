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


final class OneArgumentOption extends AbstractOption implements Option
{

    public function __construct(
        Traversable<string> $names,
        string $helpMessage = '',
        private OneArgmentAction $action = (($_) ==> {})
    )
    {
        $this->names = ImmSet::fromItems($names);
        $this->helpMessage = $helpMessage;
        $this->numberOfArgs = 1;
    }

    public function consume(ArgumentsConsumable<string> $consumer) : void
    {
        $name = $consumer->current();

        if (!$this->matches($name))  {
            throw new LogicException('Option name does not match');
        }

        if (!$consumer->hasNext()) {
            throw new LogicException('have not argument value');
        }

        $next = $consumer->next();
        $consumer->consume();

        if (preg_match('/^(-|--)/', $next) === 1) {
            throw new LogicException('have not argument value');
        }

        $consumer->consume();

        $action = $this->action;
        $action($next);
    }
}
