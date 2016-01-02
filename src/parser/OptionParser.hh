<?hh //strict

/**
 * This file is part of hhpack\getopt package.
 *
 * (c) Noritaka Horio <holy.shared.design@gmail.com>
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */

namespace hhpack\getopt\parser;

use hhpack\getopt\spec\Option;
use hhpack\getopt\spec\OptionSet;
use hhpack\getopt\spec\OptionCollection;
use hhpack\getopt\argv\ArgumentsConsumer;
use hhpack\getopt\argv\ArgumentsExtractor;

final class OptionParser implements Parser<Traversable<string>, ParsedResult>
{

    private OptionCollection $options;

    public function __construct(
        Traversable<Option<mixed>> $options = []
    )
    {
        $this->options = new OptionSet($options);
    }

    public function parse(Traversable<string> $input = []) : ParsedResult
    {
        list($argv, $notFlags) = $this->prepareArgs($input);

        $args = Vector::fromItems($notFlags);
        $options = Vector::fromItems( $this->options->defaultValues() );

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
            $result = $option->consume($consumer);

            $options->add($result);
        }

        return new ParsedResult($args, $options);
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

        $this->options->validate($extractedArgv);

        return $extractedArgv;
    }

}