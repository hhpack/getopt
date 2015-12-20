<?hh //strict

namespace hhpack\getopt;

use LogicException;

final class ArgumentOptions
{

    private ImmMap<string, Option<mixed>> $options;

    public function __construct(
        Traversable<Option<mixed>> $options = []
    )
    {
        $namedOptions = Map {};

        foreach ($options as $option) {
            $namedOptions->add(Pair { $option->name(), $option });
        }
        $this->options = $namedOptions->toImmMap();
    }

    /**
     * $options->hasOption('c');
     * $options->hasOption('c', 'config');
     */
    public function hasOption(...) : bool
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
     * $options->get('c');
     * $options->get('c', 'config');
     */
    public function get(...) : Option<mixed>
    {
        $option = null;
        $names = func_get_args();
        $options = $this->options();

        foreach ($names as $name) {
            if (!$options->containsKey($name)) {
                continue;
            }
            $option = $options->at($name);
            break;
        }

        if ($option === null) {
            throw new LogicException('have not option ' . implode(', ', $names));
        }

        return $option;
    }

    public function validate(array<string> $argv = []) : void
    {
        $options = $this->options();

        foreach ($argv as $arg) {
            $matches = [];

            if (preg_match('/^(-|--)(\w+)=?/', $arg, $matches) !== 1) {
                continue;
            }

            $name = array_pop($matches);

            if ($options->containsKey($name)) {
                continue;
            }
            throw new LogicException('have not option ' . $name);
        }
    }

    public function hasFlagOption(string $name) : bool
    {
        return $this->flagOptions()->containsKey($name);
    }

    <<__Memoize>>
    private function flagOptions() : ImmMap<string, Option<bool>>
    {
        $options = Map {};

        foreach ($this->options->values() as $option) {
            if (!($option instanceof FlagOption)) {
                continue;
            }
            $options->addAll( $option->options() );
        }

        return $options->toImmMap();
    }

    public function hasValueOption(string $name) : bool
    {
        return $this->valueOptions()->containsKey($name);
    }

    <<__Memoize>>
    private function valueOptions() : ImmMap<string, Option<mixed>>
    {
        $options = Map {};

        foreach ($this->options->values() as $option) {
            if ($option instanceof FlagOption) {
                continue;
            }
            $options->addAll( $option->options() );
        }

        return $options->toImmMap();
    }

    <<__Memoize>>
    private function optionNames() : ImmSet<string>
    {
        $optionNames = Set {};

        foreach ($this->options->values() as $option) {
            $optionNames->addAll($option->names());
        }

        return $optionNames->toImmSet();
    }

    <<__Memoize>>
    private function options() : ImmMap<string, Option<mixed>>
    {
        $namedOptions = Map {};

        foreach ($this->options->values() as $option) {
            foreach ($option->names() as $name) {
                $namedOptions->set($name, $option);
            }
        }

        return $namedOptions->toImmMap();
    }

}
