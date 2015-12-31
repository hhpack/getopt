<?hh //strict

/**
 * This file is part of hhpack\getopt package.
 *
 * (c) Noritaka Horio <holy.shared.design@gmail.com>
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */

namespace hhpack\getopt;

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
        $args = Vector {};
        $options = Vector {};
        $options->addAll($this->options->defaultValues());

        $consumer = new ArgumentsConsumer($this->options, $input);

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

}
