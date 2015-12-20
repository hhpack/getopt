<?hh //strict

namespace hhpack\getopt;

use RuntimeException;

final class ArgumentsExtractor implements ArgumentsStringExtractor
{

    public function __construct(
        private ArgumentOptions $options
    )
    {
    }

    public function extract(Traversable<string> $argv) : Iterable<string>
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
