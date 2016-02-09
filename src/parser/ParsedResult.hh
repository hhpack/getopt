<?hh //strict

/**
 * This file is part of hhpack\getopt package.
 *
 * (c) Noritaka Horio <holy.shared.design@gmail.com>
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */

namespace hhpack\getopt\parser;

final class ParsedResult
{

    private ImmVector<string> $args;
    private ImmMap<string, mixed> $options;

    public function __construct(
        Traversable<string> $args,
        Traversable<Pair<string, mixed>> $options
    )
    {
        $this->args = ImmVector::fromItems($args);
        $this->options = ImmMap::fromItems($options);
    }

    public function arguments() : ImmVector<string>
    {
        return $this->args->immutable();
    }

    public function argumentCount() : int
    {
        return $this->args->count();
    }

    public function options() : ImmMap<string, mixed>
    {
        return $this->options->immutable();
    }

    public function optionCount() : int
    {
        return $this->options->count();
    }

    public function hasOption(string $name) : bool
    {
        return $this->options->containsKey($name);
    }

    public function getOption(string $name) : mixed
    {
        return $this->options->at($name);
    }

    public function map<Tu>((function(this):Tu) $mapper) : Tu
    {
        return $mapper($this);
    }

}
