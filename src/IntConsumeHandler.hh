<?hh //strict

namespace hhpack\getopt;

final class IntConsumeHandler implements ConsumeHandler<int>
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

    public function consume(ArgumentsConsumable<string> $consumer) : Pair <string, int>
    {
        $result = $this->handler->consume($consumer);
        list($name, $value) = $result;
        return Pair { $this->handler->name(), (int) $value };
    }

}
