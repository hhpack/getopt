<?hh //strict

namespace hhpack\getopt;

use LogicException;

final class OneArgumentConsumeHandler extends ArgumentConsumeHandler<string>
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
        $this->consumeType = ConsumeType::TakesValue;
    }

    public function consume(ArgumentsConsumable<string> $consumer) : Pair <string, string>
    {
        $name = $consumer->current();

        if (!$this->matches($name))  {
            throw new LogicException('Option name does not match');
        }

        if (!$consumer->hasNext()) {
            throw new LogicException('have not argument value');
        }

        $next = $consumer->next();
        $consumer->consume();

        if (preg_match('/^(-|--)/', $next) === 1) {
            throw new LogicException('have not argument value');
        }

        $consumer->consume();

        return Pair { $this->name, $next };
    }

}
