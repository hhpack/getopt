<?hh //strict

namespace hhpack\getopt;

final class FloatConsumeHandler implements ConsumeHandler<float>
{

    private OneArgumentConsumeHandler $handler;

    public function __construct(
        string $name,
        Traversable<string> $flags
    )
    {
        $this->handler = new OneArgumentConsumeHandler($name, $flags);
    }

    public function name() : string
    {
        return $this->handler->name();
    }

    public function flags() : ImmSet<string>
    {
        return $this->handler->flags();
    }

    public function isTakesValue() : bool
    {
        return $this->handler->isTakesValue();
    }

    public function matches(string $name) : bool
    {
        return $this->handler->matches($name);
    }

    public function consume(ArgumentsConsumable<string> $consumer) : Pair <string, float>
    {
        $result = $this->handler->consume($consumer);
        list($name, $value) = $result;
        return Pair { $this->handler->name(), (float) $value };
    }

}
