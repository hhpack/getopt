<?hh //strict

namespace HHPack\Getopt\Test\Argv;

use HHPack\Getopt\Spec\OptionSet;
use HHPack\Getopt\Spec\OptionValue;
use HHPack\Getopt\Spec\ValueType;
use HHPack\Getopt\Spec\NamedMatcher;
use HHPack\Getopt\Argv\ArgumentsExtractor;
use HHPack\Getopt\Handler\StringConsumeHandler;
use HHPack\Getopt\Handler\BoolConsumeHandler;
use HackPack\HackUnit\Contract\Assert;

final class ArgumentsExtractorTest
{
    <<Test>>
    public function shortOption(Assert $assert) : void
    {
        $args = [ '-nfoo' ];
        $options = new OptionSet([
            new OptionValue(
                new StringConsumeHandler('name', [ '-n', '--name' ]),
                'bar',
                ValueType::Optional
            )
        ]);
        $extractor = new ArgumentsExtractor($options);

        $argv = $extractor->extract($args);

        $assert->string($argv->at(0))->is('-n');
        $assert->string($argv->at(1))->is('foo');
    }

    <<Test>>
    public function shortEqOption(Assert $assert) : void
    {
        $args = [ '-n=foo' ];
        $options = new OptionSet([
            new OptionValue(
                new StringConsumeHandler('name', [ '-n', '--name' ]),
                'foo',
                ValueType::Optional
            )
        ]);
        $extractor = new ArgumentsExtractor($options);

        $argv = $extractor->extract($args);
        $assert->string($argv->at(0))->is('-n');
        $assert->string($argv->at(1))->is('foo');
    }

    <<Test>>
    public function longOption(Assert $assert) : void
    {
        $args = [ '--name=foo' ];
        $options = new OptionSet([
            new OptionValue(
                new StringConsumeHandler('name', [ '-n', '--name' ]),
                'foo',
                ValueType::Optional
            )
        ]);
        $extractor = new ArgumentsExtractor($options);

        $argv = $extractor->extract($args);
        $assert->string($argv->at(0))->is('--name');
        $assert->string($argv->at(1))->is('foo');
    }

    <<Test>>
    public function flagsOption(Assert $assert) : void
    {
        $args = [ '-dV' ];
        $options = new OptionSet([
            new OptionValue(
                new BoolConsumeHandler('debug', [ '-d', '--debug' ]),
                false,
                ValueType::Optional
            ),
            new OptionValue(
                new BoolConsumeHandler('verbose', [ '-V', '--verbose' ]),
                false,
                ValueType::Optional
            )
        ]);
        $extractor = new ArgumentsExtractor($options);

        $argv = $extractor->extract($args);
        $assert->string($argv->at(0))->is('-d');
        $assert->string($argv->at(1))->is('-V');
    }

    <<Test>>
    public function flagLongOption(Assert $assert) : void
    {
        $args = [ '--no-name' ];
        $options = new OptionSet([
            new OptionValue(
                new BoolConsumeHandler('noName', [ '-N', '--no-name' ]),
                false,
                ValueType::Optional
            )
        ]);

        $extractor = new ArgumentsExtractor($options);

        $argv = $extractor->extract($args);
        $assert->string($argv->at(0))->is('--no-name');
    }

    <<Test>>
    public function longWithSepalateOption(Assert $assert) : void
    {
        $args = [ '--long-name', 'foo' ];
        $options = new OptionSet([
            new OptionValue(
                new BoolConsumeHandler('longName', [ '-N', '--long-name' ]),
                false,
                ValueType::Optional
            )
        ]);
        $extractor = new ArgumentsExtractor($options);

        $argv = $extractor->extract($args);
        $assert->string($argv->at(0))->is('--long-name');
        $assert->string($argv->at(1))->is('foo');
    }
}
