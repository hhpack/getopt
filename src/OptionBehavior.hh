<?hh //strict

namespace hhpack\getopt;

trait OptionBehavior<T>
{
    require implements Option<T>;

    private string $name;
    private string $shortName;
    private string $longName;
    private bool $required = false;
    private T $defaultValue;

    public function name() : string
    {
        return $this->name;
    }

    public function shortName() : string
    {
        return $this->shortName;
    }

    public function longName() : string
    {
        return $this->longName;
    }

    public function isRequired() : bool
    {
        return $this->required;
    }

    public function isOptional() : bool
    {
        return !$this->isRequired();
    }

    public function defaultValue() : T
    {
        return $this->defaultValue;
    }

    public function names() : ImmSet<string>
    {
        return ImmSet { $this->shortName(), $this->longName() };
    }

    public function options() : Iterator<Pair<string, Option<T>>>
    {
        yield Pair { $this->shortName(), $this };
        yield Pair { $this->longName(), $this };
    }

    public function toImmMap() : ImmMap<string, Option<T>>
    {
        return ImmMap {
            $this->shortName() => $this,
            $this->longName() => $this
        };
    }

    public function matchesName(string $name) : bool
    {
        $pattern = '/^(-' . $this->shortName() . '|--' . $this->longName() . '$)/';
        return preg_match($pattern, $name) === 1;
    }

}
