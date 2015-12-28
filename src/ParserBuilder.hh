<?hh //strict

namespace hhpack\getopt;

interface ParserBuilder<Ti, To>
{
    public function build() : Parser<Ti, To>;
}
