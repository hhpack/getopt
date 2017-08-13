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

use LogicException;
use RuntimeException;
use ConstCollection;

final class OptionSet implements OptionCollection
{

    private ImmMap<string, Option> $options;

    public function __construct(
        Traversable<Option> $options = []
    )
    {
        $mappedOptions = Map {};

        foreach ($options as $option) {
            $mappedOptions->setAll( $option->toImmMap() );
        }
        $this->options = $mappedOptions->toImmMap();
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
    public function get(string $name) : Option
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
    public function noValues() : ImmMap<string, Option>
    {
        $selector = ($option) ==> !$option->isTakesValue();
        return $this->options->filter($selector);
    }

    public function hasOneValue(string $name) : bool
    {
        return $this->oneValues()->containsKey($name);
    }

    public function isEmpty() : bool
    {
        return $this->options->isEmpty();
    }

    public function count() : int
    {
        return $this->options->count();
    }

    public function items() : Iterable<Option>
    {
        return $this->options->values();
    }

    <<__Memoize>>
    public function oneValues() : ImmMap<string, Option>
    {
        $selector = ($option) ==> $option->isTakesValue();
        return $this->options->filter($selector);
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
