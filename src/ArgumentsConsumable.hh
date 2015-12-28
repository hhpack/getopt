<?hh //strict

namespace hhpack\getopt;

interface ArgumentsConsumable<T>
{
    public function valid() : bool;
    public function current() : string;
    public function hasNext() : bool;
    public function next() : string;
    public function consume() : void;
}
