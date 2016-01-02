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
use RuntimeException;
use ConstCollection;

final class OptionSet implements OptionCollection
{

    private ImmMap<string, Option<mixed>> $namedOptions;
    private ImmMap<string, Option<mixed>> $flagedOptions;

    public function __construct(
        Traversable<Option<mixed>> $options = []
    )
    {
        $namedOptions = Map {};
        $flagedOptions = Map {};

        foreach ($options as $option) {
            $namedOptions->add( Pair { $option->name(), $option }); 
            $flagedOptions->setAll( $option->toImmMap() );
        }

        $this->namedOptions = $namedOptions->toImmMap();
        $this->flagedOptions = $flagedOptions->toImmMap();
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
        if (!$this->flagedOptions->containsKey($name)) {
            throw new LogicException('have not option ' . $name);
        }
        return $this->flagedOptions->at($name);
    }

    public function hasNoValue(string $name) : bool
    {
        return $this->noValues()->containsKey($name);
    }

    <<__Memoize>>
    public function noValues() : ImmMap<string, Option<mixed>>
    {
        $selector = ($option) ==> !$option->isTakesValue();
        return $this->flagedOptions->filter($selector);
    }

    public function hasOneValue(string $name) : bool
    {
        return $this->oneValues()->containsKey($name);
    }

    public function validate(Traversable<string> $args) : void
    {
        $messages = [];
        $notSpecifiedOptions = $this->detectNotSpecifiedOptions($args);

        if ($notSpecifiedOptions->isEmpty()) {
            return;
        }

        foreach ($notSpecifiedOptions->items() as $item) {
            list($_, $option) = $item;
            $flagValue = implode(', ', $option->flags()->toArray());
            $messages[] = $flagValue . ' ' . $option->helpMessage();
        }

        throw new RequiredException(sprintf("Required option has not been specified.\n\n%s", implode(PHP_EOL, $messages)));
    }

    private function detectNotSpecifiedOptions(Traversable<string> $arguments) : ImmMap<string, Option<mixed>>
    {
        $required = ($option) ==> $option->isRequired();
        $requiredValues = $this->flagedOptions->filter($required)->toMap();

        foreach ($arguments as $argument) {
            if (!$requiredValues->containsKey($argument)) {
                continue;
            }
            $option = $requiredValues->at($argument);

            foreach ($option->flags() as $flag) {
                $requiredValues->remove($flag);
            }
        }

        $result = Map {};

        foreach ($requiredValues->lazy() as $key => $option) {
            $result->set($option->name(), $option);
        }

        return $result->toImmMap();
    }

    public function defaultValues() : ImmVector<Pair<string, mixed>>
    {
        $defaultValues = Vector {};

        foreach ($this->namedOptions->lazy() as $name => $option) {
            $defaultValues->add(Pair { $option->name(), $option->defaultValue() });
        }

        return $defaultValues->toImmVector();
    }

    public function isEmpty() : bool
    {
        return $this->namedOptions->isEmpty();
    }

    public function count() : int
    {
        return $this->namedOptions->count();
    }

    public function items() : Iterable<Option<mixed>>
    {
        return $this->namedOptions->values();
    }

    <<__Memoize>>
    public function oneValues() : ImmMap<string, Option<mixed>>
    {
        $selector = ($option) ==> $option->isTakesValue();
        return $this->flagedOptions->filter($selector);
    }

    <<__Memoize>>
    private function optionNames() : ImmSet<string>
    {
        $optionNames = Set {};

        foreach ($this->namedOptions->values() as $option) {
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
