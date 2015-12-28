<?hh //strict

namespace hhpack\getopt;

interface Matcher
{
    public function matches(string $name) : bool;
}
