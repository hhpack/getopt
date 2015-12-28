<?hh //strict

namespace hhpack\getopt;

interface ConsumeHandler<T> extends Matcher
{
    public function name() : string;
    public function flags() : ImmSet<string>;
    public function matches(string $name) : bool;
    public function isTakesValue() : bool;
    public function consume(ArgumentsConsumable<string> $consumer) : Pair<string, T>;
}
