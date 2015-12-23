<?hh //strict

namespace hhpack\getopt;

use LogicException;

final class OptionSet
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

        foreach ($names as $name) {
            if (!$this->options->containsKey($name)) {
                continue;
            }
            $option = $this->options->at($name);
            break;
        }

        if ($option === null) {
            throw new LogicException('have not option ' . implode(', ', $names));
        }

        return $option;
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

    public function defaultValues() : ImmVector<Pair<string, mixed>>
    {
        $defaultValues = Map {};

        foreach ($this->valueOptions()->lazy() as $name => $option) {
            if ($option instanceof FlagOption) {
                continue;
            }
            if ($defaultValues->containsKey($option->name())) {
                continue;
            }
            $defaultValues->set($option->name(), Pair { $option->name(), $option->defaultValue() });
        }

        return $defaultValues->toImmVector();
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

}
