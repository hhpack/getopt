<?hh //strict

namespace hhpack\getopt;

use LogicException;

final class ValueOption implements Option<string>
{

    use OptionBehavior<string>;

    public function __construct(
        string $name,
        string $shortName,
        string $longName,
        string $defaultValue,
        ArgumentType $required = ArgumentType::Optional
    )
    {
        $this->name = $name;
        $this->shortName = $shortName;
        $this->longName = $longName;
        $this->required = $required;
        $this->defaultValue = $defaultValue;
    }

    public function isNoArgument() : bool
    {
        return false;
    }

    public function consume(ArgumentsConsumer $consumer) : Pair <string, string>
    {
        $name = $consumer->current();

        if (!$this->matchesName($name))  {
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

        return Pair { $this->name(), $next };
    }

}
