<?hh //strict

namespace hhpack\getopt;

abstract class ArgumentConsumeHandler<T> implements ConsumeHandler<T>
{

    protected string $name;
    protected ImmVector<FlagMatcher> $flags;
    protected ConsumeType $consumeType = ConsumeType::TakesValue;

    public function name() : string
    {
        return $this->name;
    }

    public function flags() : ImmSet<string>
    {
        $nameHandler = ($flag) ==> $flag->name();
        return $this->flags->map($nameHandler)->toImmSet();
    }

    public function isTakesValue() : bool
    {
        return $this->consumeType === ConsumeType::TakesValue;
    }

    public function matches(string $name) : bool
    {
        $matched = false;

        foreach ($this->flags->items() as $flag) {
            if ($flag->matches($name)) {
                $matched = true;
                break;
            }
        }
        return $matched;
    }

}
