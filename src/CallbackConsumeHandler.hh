<?hh //strict

namespace hhpack\getopt;

final class CallbackConsumeHandler<T> extends ArgumentConsumeHandler<T>
{

    public function __construct(
        string $name,
        Traversable<string> $flags,
        ConsumeType $consumeType,
        private (function(ArgumentsConsumable<string>):T) $callback
    )
    {
        $this->name = $name;
        $this->flags = ImmVector::fromItems($flags)->map(($flag) ==> {
            return new FlagMatcher($flag);
        });
        $this->consumeType = $consumeType;
    }

    public function consume(ArgumentsConsumable<string> $consumer) : Pair <string, T>
    {
        $callback = $this->callback;
        return Pair { $this->name() , $callback($consumer) };
    }

}
