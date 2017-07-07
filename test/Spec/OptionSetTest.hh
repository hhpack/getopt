<?hh //strict

namespace HHPack\Getopt\Test\Spec;

use HHPack\Getopt\Spec\OptionSet;
use HHPack\Getopt\Spec\ValueType;
use HHPack\Getopt\Spec\OptionValue;
use HHPack\Getopt\Handler\StringConsumeHandler;
use HHPack\Getopt\Handler\BoolConsumeHandler;
use HackPack\HackUnit\Contract\Assert;

final class OptionSetTest
{
    <<Test>>
    public function shortAndLongContains(Assert $assert) : void
    {
        $options = new OptionSet([
            new OptionValue(
                new BoolConsumeHandler('debug', [ '-d', '--debug' ]),
                false,
                ValueType::Optional
            )
        ]);

        $result = $options->contains('-d'); // short name
        $assert->bool($result)->is(true);

        $result = $options->contains('--debug'); // long name
        $assert->bool($result)->is(true);
    }

    <<Test>>
    public function lookUpFromContainer(Assert $assert) : void
    {
        $options = new OptionSet([
            new OptionValue(
                new BoolConsumeHandler('debug', [ '-d', '--debug' ]),
                false,
                ValueType::Optional
            )
        ]);

        $option = $options->get('-d'); // short name
        $assert->string($option->name())->is('debug');

        $option = $options->get('--debug'); // long name
        $assert->string($option->name())->is('debug');
    }

    <<Test>>
    public function noValueContains(Assert $assert) : void
    {
        $options = new OptionSet([
            new OptionValue(
                new BoolConsumeHandler('debug', [ '-d', '--debug' ]),
                false,
                ValueType::Optional
            )
        ]);

        $result = $options->hasNoValue('-d'); // short name
        $assert->bool($result)->is(true);

        $result = $options->hasNoValue('--debug'); // long name
        $assert->bool($result)->is(true);

        $result = $options->hasNoValue('-n'); // short name
        $assert->bool($result)->is(false);

        $result = $options->hasNoValue('--name'); // long name
        $assert->bool($result)->is(false);
    }

    <<Test>>
    public function oneValueContains(Assert $assert) : void
    {
        $options = new OptionSet([
            new OptionValue(
                new StringConsumeHandler('name', [ '-n', '--name' ]),
                'bar',
                ValueType::Optional
            )
        ]);

        $result = $options->hasOneValue('-n'); // short name
        $assert->bool($result)->is(true);

        $result = $options->hasOneValue('--name'); // long name
        $assert->bool($result)->is(true);

        $result = $options->hasNoValue('-d'); // short name
        $assert->bool($result)->is(false);

        $result = $options->hasNoValue('--debug'); // long name
        $assert->bool($result)->is(false);
    }
}
