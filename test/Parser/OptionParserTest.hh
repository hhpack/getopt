<?hh //strict

namespace HHPack\Getopt\Test\Parser;

use HHPack\Getopt\Parser\OptionParser;
use HHPack\Getopt\Spec\ValueType;
use HHPack\Getopt\Spec\OptionValue;
use HHPack\Getopt\Spec\RequiredException;
use HHPack\Getopt\Handler\StringConsumeHandler;
use HackPack\HackUnit\Contract\Assert;

final class OptionParserTest
{
    <<Test>>
    public function standardOption(Assert $assert) : void
    {
        $args = [ '-nfoo' ];
        $parser = OptionParser::fromOptions([
            new OptionValue(
                new StringConsumeHandler('name', [ '-n', '--name' ]),
                'foo',
                ValueType::Optional
            )
        ]);

        $result = $parser->parse($args);

        $assert->int($result->argumentCount())->eq(0);
        $assert->int($result->optionCount())->eq(1);
        $assert->string((string) $result->getOption('name'))->is('foo');
    }

    <<Test>>
    public function argsSeparator(Assert $assert) : void
    {
        $args = [ '-nfoo', '--', 'value' ];
        $parser = OptionParser::fromOptions([
            new OptionValue(
                new StringConsumeHandler('name', [ '-n', '--name' ]),
                'foo',
                ValueType::Optional
            )
        ]);

        $result = $parser->parse($args);

        $assert->int($result->argumentCount())->eq(1);
        $assert->int($result->optionCount())->eq(1);
        $assert->string((string) $result->getOption('name'))->is('foo');
    }

    <<Test>>
    public function requiredOption(Assert $assert) : void
    {
        $parser = OptionParser::fromOptions([
            new OptionValue(
                new StringConsumeHandler('name', [ '-n', '--name' ]),
                'foo',
                ValueType::Required
            )
        ]);

        $assert->whenCalled(() ==> {
            $parser->parse([ 'foo' ]);
        })->willThrowClass(RequiredException::class);
    }
}
