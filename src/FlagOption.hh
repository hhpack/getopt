<?hh //strict

namespace hhpack\getopt;

use LogicException;

final class FlagOption implements Option<bool>
{

    use OptionBehavior<bool>;

    public function __construct(
        string $name,
        string $shortName,
        string $longName
    )
    {
        $this->name = $name;
        $this->shortName = $shortName;
        $this->longName = $longName;
        $this->defaultValue = false;
        $this->required = ArgumentType::Optional;
    }

    public function isNoArgument() : bool
    {
        return true;
    }

    /**
     * -d
     * --debug
     */
    public function consume(ArgumentsConsumer $consumer) : Pair <string, bool>
    {
        $value = $consumer->current();

        if (!$this->matchesName($value))  {
            throw new LogicException('Option name does not match');
        }

        $consumer->consume();
        return Pair { $this->name(), true };
    }

}
