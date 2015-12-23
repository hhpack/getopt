<?hh //strict

namespace hhpack\getopt;

final class ArgumentParser implements Parser<Traversable<string>, ParsedResult>
{

    public function __construct(
        private OptionSet $options
    )
    {
    }

    public function parse(Traversable<string> $input = []) : ParsedResult
    {
        $arguments = Vector {};
        $options = Vector {};
        $options->addAll($this->options->defaultValues());

        $consumer = new ArgumentsConsumer($this->options, $input);

        while ($consumer->valid()) {
            $matches = [];
            $value = $consumer->current();

            if (preg_match('/^(-|--)(\w+)=?/', $value, $matches) !== 1) {
                $arguments->add($value);
                $consumer->consume();
                continue;
            }
            list($_, $_, $name) = $matches;

            $option = $this->options->get($name);
            $result = $option->consume($consumer);

            $options->add($result);
        }

        return new ParsedResult($arguments, $options);
    }

}
