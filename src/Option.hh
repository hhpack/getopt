<?hh //strict

namespace hhpack\getopt;

interface Option<T>
{
    public function name() : string;
    public function names() : ImmSet<string>;
    public function options() : Iterator<Pair<string, Option<T>>>;
    public function shortName() : string;
    public function longName() : string;
    public function isRequired() : bool;
    public function isOptional() : bool;
    public function isNoArgument() : bool;
    public function defaultValue() : T;
    public function matchesName(string $name) : bool;
    public function consume(ArgumentsConsumer $consumer) : Pair <string, T>;
    public function toImmMap() : ImmMap<string, Option<T>>;
}
