<?hh //strict

namespace hhpack\getopt;

use LogicException;

<<__ConsistentConstruct>>
abstract class ValueOption<T> implements Option<T>
{

    use OptionBehavior<T>;

    public function __construct(
        string $name,
        string $shortName,
        string $longName,
        T $defaultValue,
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

    protected function consumeArguments(ArgumentsConsumer $consumer) : Pair <string, string>
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
