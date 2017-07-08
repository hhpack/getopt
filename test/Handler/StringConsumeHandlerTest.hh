<?hh //strict

namespace HHPack\Getopt\Test\Handler;

use HHPack\Getopt\Handler\StringConsumeHandler;
use HHPack\Getopt\Test\Mock\ArgumentsConsumer;
use HackPack\HackUnit\Contract\Assert;

final class StringConsumeHandlerTest
{
    <<Test>>
    public function shortOption(Assert $assert) : void
    {
        $handler = new StringConsumeHandler('name', [ '-n', '--name' ]);
        $result = $handler->consume(new ArgumentsConsumer([ '-n', 'foo' ]));

        list($name, $value) = $result;

        $assert->string($name)->is('name');
        $assert->string($value)->is('foo');
    }
}
