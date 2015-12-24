<?hh //strict

namespace hhpack\getopt;

final class IntOption extends ValueOption<int> implements Option<int>
{

    public function consume(ArgumentsConsumable<string> $consumer) : Pair<string, int>
    {
        list($name, $value) = $this->consumeArguments($consumer);
        return Pair { $name, (int) $value };
    }

}
