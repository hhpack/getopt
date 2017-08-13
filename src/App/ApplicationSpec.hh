<?hh //strict

/**
 * This file is part of hhpack\getopt package.
 *
 * (c) Noritaka Horio <holy.shared.design@gmail.com>
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */

namespace HHPack\Getopt\App;

use HHPack\Getopt\Spec\{ Option, OptionSet, OptionCollection };
use HHPack\Getopt\Parser\{ Parser, OptionParser, ParsedResult };

final class ApplicationSpec implements ApplicationSpecDisplayable, Parser<ParsedResult>
{

    private string $usage = "  {app.name} [options]\n\n";
    private OptionCollection $options;

    public function __construct(
        private string $name,
        private string $version = '0.0.0'
    )
    {
        $this->options = new OptionSet();
    }

    public function name(string $name) : this
    {
        $this->name = $name;
        return $this;
    }

    public function version(string $version) : this
    {
        $this->version = $version;
        return $this;
    }

    public function usage(string $usage) : this
    {
        $this->usage = $usage;
        return $this;
    }

    public function options(Traversable<Option<mixed>> $options = []) : this
    {
        $this->options = new OptionSet($options);
        return $this;
    }

    public function parse(Traversable<string> $input = []) : ParsedResult
    {
        $parser = new OptionParser($this->options);
        return $parser->parse($input);
    }

    private function displayUsage() : void
    {
        $templateValues = [ '{app.name}', '{app.version}' ];
        $replaceVariables = [ $this->name, $this->version ];

        fwrite(STDOUT, "Usage:\n\n");
        fwrite(STDOUT, str_replace($templateValues, $replaceVariables, $this->usage));
    }

    public function displayHelp() : void
    {
        $this->displayUsage();
        $this->options->displayHelp();
    }

    public function displayVersion() : void
    {
        fwrite(STDOUT, sprintf("%s %s\n",
            $this->name, $this->version));
    }

}
