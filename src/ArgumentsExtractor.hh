<?hh //strict

namespace hhpack\getopt;

use RuntimeException;
use ConstCollection;

// The reason is unknown, because the error occurs at run time, you do not specify a ConstIndexAccess
// Declaration of hhpack\getopt\ArgumentsExtractor::at() must be compatible with that of ConstIndexAccess::at() in /home/vagrant/shared/getopt/src/ArgumentsExtractor.hh on line 9
// use ConstIndexAccess;

final class ArgumentsExtractor implements ConstCollection<string>
{

    private ImmVector<string> $argv;

    public function __construct(
        private OptionSet $options,
        Traversable<string> $argv
    )
    {
        $this->argv = $this->extract($argv);
    }

    public function items() : Iterable<string>
    {
        return $this->argv->items();
    }

    public function isEmpty() : bool
    {
        return $this->argv->isEmpty();
    }

    public function count() : int
    {
        return $this->argv->count();
    }

    public function at(int $k) : string
    {
        return $this->argv->at($k);
    }

    public function containsKey<Tu super int>(Tu $k) : bool
    {
        return $this->argv->containsKey($k);
    }

    public function get(int $k) : ?string
    {
        return $this->argv->get($k);
    }

    private function extract(Traversable<string> $argv) : ImmVector<string>
    {
        return $this->extractFlagSet($this->extractOptions($argv));
    }

    private function extractOptions(Traversable<string> $argv) : ImmVector<string>
    {
        $arguments = Vector {};

        foreach ($argv as $value) {
            $matches = [];

            if (preg_match('/^(-|--)(\w+)=(.+)$/', $value, $matches) !== 1) {
                $arguments->add($value);
                continue;
            }
            list($_, $prefix, $name, $value) = $matches;

            $arguments->addAll([ $prefix . $name, $value ]);
        }

        return $arguments->toImmVector();
    }

    private function extractFlagSet(Traversable<string> $argv) : ImmVector<string>
    {
        $arguments = Vector {};

        foreach ($argv as $value) {
            $matches = [];

            if (preg_match('/^-([A-Za-z]+)$/', $value, $matches) !== 1) {
                $arguments->add($value);
                continue;
            }
            list($_, $flags) = $matches;

            if (strlen($flags) <= 1) {
                $arguments->add('-' . $flags);
                continue;
            }

            $flagArguments = $this->extractFlagSetValue($flags);
            $arguments->addAll($flagArguments);
        }

        return $arguments->toImmVector();
    }

    private function extractFlagSetValue(string $flags) : ImmVector<string>
    {
        $arguments = Vector {};
        $remainFlags = $flags;

        while (strlen($remainFlags) > 0) {
            $flag = substr($remainFlags, 0, 1);

            if ($this->options->hasFlagOption($flag)) { //has options rule?
                $arguments->add('-' . $flag);
                $remainFlags = substr($remainFlags, 1);
                continue;
            } else if ($this->options->hasValueOption($flag)) { //has args?
                $value = substr($remainFlags, 1);
                $arguments->addAll([ '-' . $flag, $value ]);
                break;
            } else {
                throw new RuntimeException(sprintf('%s is not a valid option', $flag));
            }
        }

        return $arguments->toImmVector();
    }

}
