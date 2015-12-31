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

final class OptionValue<T> implements Option<T>
{
    public function __construct(
        private ConsumeHandler<T> $consumeHandler,
        private T $defaultValue,
        private ValueType $required,
        private string $helpMessage
    )
    {
    }

    public function name() : string
    {
        return $this->consumeHandler->name();
    }

    public function isRequired() : bool
    {
        return $this->required === ValueType::Required;
    }

    public function isOptional() : bool
    {
        return !$this->isRequired();
    }

    public function defaultValue() : T
    {
        return $this->defaultValue;
    }

    public function isTakesValue() : bool
    {
        return $this->consumeHandler->isTakesValue();
    }

    public function flags() : ImmSet<string>
    {
        return $this->consumeHandler->flags();
    }

    public function options() : Iterator<Pair<string, Option<T>>>
    {
        foreach ($this->flags()->items() as $name) {
            yield Pair { $name, $this };
        }
    }

    public function helpMessage() : string
    {
        return $this->helpMessage;
    }

    public function toImmMap() : ImmMap<string, Option<T>>
    {
        return ImmMap::fromItems( $this->options() );
    }

    public function matches(string $name) : bool
    {
        return $this->consumeHandler->matches($name);
    }

    public function consume(ArgumentsConsumable<string> $consumer) : Pair <string, T>
    {
        return $this->consumeHandler->consume($consumer);
    }

}
