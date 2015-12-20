<?hh //strict

namespace hhpack\getopt;

interface Extractable<T>
{
    public function items() : Iterable<T>;
}
