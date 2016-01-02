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

    public function argumentCount() : int
    {
        return $this->args->count();
    }

    public function arguments() : Iterable<string>
    {
        return $this->args->items();
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

}
