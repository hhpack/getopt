<?hh //strict

namespace hhpack\getopt;

interface Option<T> extends Matcher
{
    public function name() : string;
    public function flags() : ImmSet<string>;
    public function options() : Iterator<Pair<string, Option<T>>>;
    public function isRequired() : bool;
    public function isOptional() : bool;
    public function isTakesValue() : bool;
    public function defaultValue() : T;
    public function consume(ArgumentsConsumable<string> $consumer) : Pair <string, T>;
    public function toImmMap() : ImmMap<string, Option<T>>;
}
