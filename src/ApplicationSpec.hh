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

final class ApplicationSpec implements ApplicationSpecDisplayable
{

    private OptionCollection $options;

    public function __construct(
        private string $name,
        private string $version,
        Traversable<Option<mixed>> $options = []
    )
    {
        $this->options = new OptionSet($options);
    }

    public function name() : string
    {
        return $this->name;
    }

    public function version() : string
    {
        return $this->version;
    }

    public function options() : OptionCollection
    {
        return $this->options;
    }

    private function displayUsage() : void
    {
        fwrite(STDOUT, sprintf("Usage: %s [options]\n", $this->name()));
        fwrite(STDOUT, PHP_EOL);
    }

    public function displayHelp() : void
    {
        $this->displayUsage();
        $this->options->displayHelp();
    }

    public function displayVersion() : void
    {
        fwrite(STDOUT, sprintf("%s %s\n",
            $this->name(), $this->version()));
    }

}
