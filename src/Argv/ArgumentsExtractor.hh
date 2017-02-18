<?hh //strict

/**
 * This file is part of hhpack\getopt package.
 *
 * (c) Noritaka Horio <holy.shared.design@gmail.com>
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */

namespace HHPack\Getopt\Argv;

use HHPack\Getopt\Spec\OptionCollection;
use RuntimeException;
use ConstCollection;

final class ArgumentsExtractor
{

    public function __construct(
        private OptionCollection $options
    )
    {
    }

    public function extract(Traversable<string> $argv) : ImmVector<string>
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
            $shortName = '-' . $flag;

            if ($this->options->hasNoValue($shortName)) { //has options rule?
                $arguments->add($shortName);
                $remainFlags = substr($remainFlags, 1);
                continue;
            } else if ($this->options->hasOneValue($shortName)) { //has args?
                $value = substr($remainFlags, 1);
                $arguments->addAll([ $shortName, $value ]);
                break;
            } else {
                throw new RuntimeException(sprintf('%s is not a valid option', $flag));
            }
        }

        return $arguments->toImmVector();
    }

    public static function fromOptions(OptionCollection $options) : this
    {
        return new static($options);
    }

}
