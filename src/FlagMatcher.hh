<?hh //strict

namespace hhpack\getopt;

final class FlagMatcher implements Matcher
{

    public function __construct(
        private string $name
    )
    {
    }

    public function name() : string
    {
        return $this->name;
    }

    public function matches(string $name) : bool
    {
        $pattern = '/^(' . $this->name() . ')$/';
        return preg_match($pattern, $name) === 1;
    }

}
