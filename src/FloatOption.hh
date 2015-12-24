<?hh //strict

namespace hhpack\getopt;

final class FloatOption extends ValueOption<float> implements Option<float>
{

    public function consume(ArgumentsConsumer $consumer) : Pair<string, float>
    {
        list($name, $value) = $this->consumeArguments($consumer);
        return Pair { $name, (float) $value };
    }

}
