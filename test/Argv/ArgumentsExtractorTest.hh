<?hh //strict

namespace HHPack\Getopt\Test\Argv;

use HHPack\Getopt\Argv\{ ArgumentsExtractor };
use HHPack\Getopt\Spec\{ OptionSet, NoArgumentOption, OneArgumentOption };
use HHPack\Getopt\Test\Mock\{ OptionContainerMock };
use HackPack\HackUnit\Contract\Assert;

final class ArgumentsExtractorTest
{
    <<Test>>
    public function shortOption(Assert $assert) : void
    {
        $options = new OptionContainerMock([], [ '-n', '--name' ]);

        $extractor = new ArgumentsExtractor($options);
        $argv = $extractor->extract([ '-nfoo' ]);

        $assert->string($argv->at(0))->is('-n');
        $assert->string($argv->at(1))->is('foo');
    }

    <<Test>>
    public function shortEqOption(Assert $assert) : void
    {
        $options = new OptionContainerMock([], [ '-n', '--name' ]);

        $extractor = new ArgumentsExtractor($options);
        $argv = $extractor->extract([ '-n=foo' ]);

        $assert->string($argv->at(0))->is('-n');
        $assert->string($argv->at(1))->is('foo');
    }

    <<Test>>
    public function longOption(Assert $assert) : void
    {
        $options = new OptionContainerMock([], [ '-n', '--name' ]);

        $extractor = new ArgumentsExtractor($options);
        $argv = $extractor->extract([ '--name=foo' ]);

        $assert->string($argv->at(0))->is('--name');
        $assert->string($argv->at(1))->is('foo');
    }

    <<Test>>
    public function flagsOption(Assert $assert) : void
    {
        $options = new OptionContainerMock(['-d', '--debug', '-V', '--verbose'], []);

        $extractor = new ArgumentsExtractor($options);
        $argv = $extractor->extract([ '-dV' ]);

        $assert->string($argv->at(0))->is('-d');
        $assert->string($argv->at(1))->is('-V');
    }

    <<Test>>
    public function flagLongOption(Assert $assert) : void
    {
        $options = new OptionContainerMock(['-N', '--no-name'], []);

        $extractor = new ArgumentsExtractor($options);
        $argv = $extractor->extract([ '--no-name' ]);

        $assert->string($argv->at(0))->is('--no-name');
    }

    <<Test>>
    public function longWithSepalateOption(Assert $assert) : void
    {
        $options = new OptionContainerMock(['-N', '--long-name'], []);

        $extractor = new ArgumentsExtractor($options);
        $argv = $extractor->extract([ '--long-name', 'foo' ]);

        $assert->string($argv->at(0))->is('--long-name');
        $assert->string($argv->at(1))->is('foo');
    }
}
