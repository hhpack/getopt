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

}
