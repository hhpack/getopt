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
        private OptionCollection $options = new OptionSet()
    )
    {
    }

    public function parse(Traversable<string> $input = []) : Traversable<string>
    {
        list($argv, $notFlags) = $this->prepareArgs($input);

        $args = Vector::fromItems($notFlags);

        $extractedArgv = $this->extractArgv($argv);
        $consumer = new ArgumentsConsumer($extractedArgv);

        while ($consumer->valid()) {
            $matches = [];
            $value = $consumer->current();

            if (preg_match('/^(-{1,2}[^-]+)$/', $value, $matches) !== 1) {
                $args->add($value);
                $consumer->consume();
                continue;
            }
            list($_, $name) = $matches;

            $option = $this->options->get($name);
            $option->consume($consumer);
        }

        return $args;
    }

    private function prepareArgs(Traversable<string> $argv = []) : (Traversable<string>, Traversable<string>)
    {
        $arguments = ImmSet::fromItems($argv);

        $notFlags = $arguments->skipWhile(($value) ==> $value !== '--');

        $args = $arguments->slice(0, $arguments->count() - $notFlags->count());

        if (!$notFlags->isEmpty()) {
            $notFlags = $notFlags->slice(1, $notFlags->count() - 1); // Remove --
        }

        return tuple($args, $notFlags);
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
