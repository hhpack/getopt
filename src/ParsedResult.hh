<?hh //strict

namespace hhpack\getopt;

final class ParsedResult
{

    private ImmVector<string> $args;
    private ImmMap<string, mixed> $options;

    public function __construct(
        Traversable<string> $args,
        Traversable<Pair<string, mixed>> $options
    )
    {
        $this->args = ImmVector::fromItems($args);
        $this->options = ImmMap::fromItems($options);
    }

    public function argumentCount() : int
    {
        return $this->args->count();
    }

    public function optionCount() : int
    {
        return $this->options->count();
    }

    public function hasOption(string $name) : bool
    {
        return $this->options->containsKey($name);
    }

    public function getOption(string $name) : mixed
    {
        return $this->options->at($name);
    }

}
