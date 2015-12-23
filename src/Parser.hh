<?hh //strict

namespace hhpack\getopt;

interface Parser<Ti, To>
{
    public function parse(Ti $input) : To;
}
