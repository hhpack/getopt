<?hh //strict

namespace hhpack\getopt;

use LogicException;
use IteratorAggregate;

interface ArgumentsConsumable<T>
{
    public function current() : string;
    public function hasNext() : bool;
    public function next() : string;
    public function consume() : void;
}
