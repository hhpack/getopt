<?hh //strict

/**
 * This file is part of hhpack\getopt package.
 *
 * (c) Noritaka Horio <holy.shared.design@gmail.com>
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */

namespace HHPack\Getopt\Parser;

use HHPack\Getopt\Spec\{ Option, OptionSet, OptionCollection, HelpDisplayable };
use HHPack\Getopt\Argv\{ ArgumentsConsumer, ArgumentsExtractor };

final class OptionParser implements Parser, HelpDisplayable
{

    public function __construct(
        private OptionCollection $options = new OptionSet(),
        private bool $stopAtNonOption = false
    )
    {
    }

    public function parse(Traversable<string> $input = []) : ImmVector<string>
    {
        if ($this->stopAtNonOption) {
            return $this->parseUntilNonOption($input);
        } else {
            return $this->parseAll($input);
        }
    }

    private function parseAll(Traversable<string> $input = []) : ImmVector<string>
    {
        $args = Vector {};

        $extractedArgv = $this->extractArgv($input);
        $consumer = new ArgumentsConsumer($extractedArgv);

        while ($consumer->valid()) {
            $matches = [];
            $value = $consumer->current();

            if (preg_match('/^(--)$/', $value, $matches) === 1) {
                $consumer->consume();
                break;
            } else if (preg_match('/^(-{1,2}[^-]+)$/', $value, $matches) !== 1) {
                $args->add($value);
                $consumer->consume();
                continue;
            }
            list($_, $name) = $matches;

            $option = $this->options->get($name);
            $option->consume($consumer);
        }

        return $consumer->applyTo($args)->immutable();
    }

    private function parseUntilNonOption(Traversable<string> $input = []) : ImmVector<string>
    {
        $args = Vector {};

        $extractedArgv = $this->extractArgv($input);
        $consumer = new ArgumentsConsumer($extractedArgv);

        while ($consumer->valid()) {
            $matches = [];
            $value = $consumer->current();

            if (preg_match('/^(--)$/', $value, $matches) === 1) {
                break;
            }

            if (preg_match('/^(-{1,2}[^-]+)$/', $value, $matches) !== 1) {
                break;
            }

            list($_, $name) = $matches;

            $option = $this->options->get($name);
            $option->consume($consumer);
        }

        return $consumer->applyTo($args)->immutable();
    }

    private function extractArgv(Traversable<string> $argv) : ImmVector<string>
    {
        $extractor = ArgumentsExtractor::fromOptions($this->options);
        $extractedArgv = $extractor->extract($argv);

        return $extractedArgv;
    }

    public function displayHelp() : void
    {
        $this->options->displayHelp();
    }

    public static function fromOptions(Traversable<Option> $options = []) : this
    {
        $options = new OptionSet($options);
        return new static($options);
    }

}
