<?hh //strict

namespace hhpack\getopt;

use LogicException;

final class StringOption extends ValueOption<string> implements Option<string>
{

    public function consume(ArgumentsConsumable<string> $consumer) : Pair <string, string>
    {
        list($name, $value) = $this->consumeArguments($consumer);
        return Pair { $name, $value };
    }

}
