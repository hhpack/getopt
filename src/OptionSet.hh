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

use LogicException;
use ConstCollection;

final class OptionSet implements OptionCollection
{

    private ImmMap<string, Option<mixed>> $options;

    public function __construct(
        Traversable<Option<mixed>> $options = []
    )
    {
        $namedOptions = Map {};

        foreach ($options as $option) {
            $namedOptions->setAll( $option->toImmMap() );
        }

        $this->options = $namedOptions->toImmMap();
    }

    /**
     * $options->contains('-c');
     * $options->contains('-c', '--config');
     */
    public function contains(...) : bool
    {
        $included = false;
        $optionNames = $this->optionNames();

        foreach (func_get_args() as $name) {
            if (!$optionNames->contains($name)) {
                continue;
            }
            $included = true;
            break;
        }

        return $included;
    }

    /**
     * $options->get('-c');
     * $options->get('--config');
     */
    public function get(string $name) : Option<mixed>
    {
        if (!$this->options->containsKey($name)) {
            throw new LogicException('have not option ' . $name);
        }
        return $this->options->at($name);
    }

    public function hasNoValue(string $name) : bool
    {
        return $this->noValues()->containsKey($name);
    }

    <<__Memoize>>
    public function noValues() : ImmMap<string, Option<mixed>>
    {
        $result = Map {};
        $selector = ($option) ==> !$option->isTakesValue();
        $options = $this->options->filter($selector)->values();

        foreach ($options as $option) {
            $result->addAll( $option->options() );
        }
        return $result->toImmMap();
    }

    public function hasOneValue(string $name) : bool
    {
        return $this->oneValues()->containsKey($name);
    }

    public function defaultValues() : ImmVector<Pair<string, mixed>>
    {
        $defaultValues = Map {};

        foreach ($this->options->lazy() as $name => $option) {
            if ($defaultValues->containsKey($option->name())) {
                continue;
            }
            $defaultValues->set($option->name(), Pair { $option->name(), $option->defaultValue() });
        }

        return $defaultValues->toImmVector();
    }

    public function isEmpty() : bool
    {
        return $this->options->isEmpty();
    }

    public function count() : int
    {
        return $this->options->count();
    }

    public function items() : Iterable<Option<mixed>>
    {
        $options = Map {};

        foreach ($this->options->values() as $name => $option) {
            if ($options->containsKey($option->name())) {
                continue;
            }
            $options->set($option->name(), $option);
        }

        return $options->values()->items();
    }

    <<__Memoize>>
    public function oneValues() : ImmMap<string, Option<mixed>>
    {
        $result = Map {};
        $selector = ($option) ==> $option->isTakesValue();
        $options = $this->options->filter($selector)->values();

        foreach ($options as $option) {
            $result->addAll( $option->options() );
        }
        return $result->toImmMap();
    }

    <<__Memoize>>
    private function optionNames() : ImmSet<string>
    {
        $optionNames = Set {};

        foreach ($this->options->values() as $option) {
            $optionNames->addAll($option->flags());
        }

        return $optionNames->toImmSet();
    }

    public function displayHelp() : void
    {
        fwrite(STDOUT, "Options:\n");

        foreach ($this->items() as $option) {
            $flags = $option->flags()->toValuesArray();
            $helpMessage = $option->helpMessage();

            fwrite(STDOUT, sprintf(
                "  %s %s\n",
                implode(', ', $flags),
                $helpMessage
            ));
        }
    }

}
