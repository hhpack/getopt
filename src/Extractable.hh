<?hh //strict

namespace hhpack\getopt;

interface Extractable<Ti, To>
{
    public function extract(Ti $input) : To;
}
