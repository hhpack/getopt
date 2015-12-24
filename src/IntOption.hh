<?hh //strict

namespace hhpack\getopt;

final class IntOption extends ValueOption<int> implements Option<int>
{

    public function consume(ArgumentsConsumer $consumer) : Pair<string, int>
    {
        list($name, $value) = $this->consumeArguments($consumer);
        return Pair { $name, (int) $value };
    }

}
