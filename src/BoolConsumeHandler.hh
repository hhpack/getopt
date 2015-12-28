<?hh //strict

namespace hhpack\getopt;

use LogicException;

final class BoolConsumeHandler extends ArgumentConsumeHandler<bool>
{

    public function __construct(
        string $name,
        Traversable<string> $flags
    )
    {
        $this->name = $name;
        $this->flags = ImmVector::fromItems($flags)->map(($flag) ==> {
            return new FlagMatcher($flag);
        });
        $this->consumeType = ConsumeType::NoValue;
    }

    public function consume(ArgumentsConsumable<string> $consumer) : Pair <string, bool>
    {
        $value = $consumer->current();

        if (!$this->matches($value))  {
            throw new LogicException('Option name does not match');
        }

        $consumer->consume();

        return Pair { $this->name(), true };
    }

}
