<?hh //strict

namespace hhpack\getopt;

final class OptionParserBuilder implements ParserBuilder<Traversable<string>, ParsedResult>
{

    private Vector<Option<mixed>> $options;

    public function __construct()
    {
        $this->options = Vector {};
    }

    public function addOption(Option<mixed> $option) : this
    {
        $this->options->add($option);
        return $this;
    }

    public function optionCount() : int
    {
        return $this->options->count();
    }

    public function build() : Parser<Traversable<string>, ParsedResult>
    {
        return new OptionParser($this->options);
    }

}
