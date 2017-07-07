<?hh //strict

namespace HHPack\Getopt\Test\Handler;

use HHPack\Getopt\Handler\BoolConsumeHandler;
use HHPack\Getopt\Test\Mock\ArgumentsConsumer;
use HackPack\HackUnit\Contract\Assert;

final class BoolConsumeHandlerTest
{
    <<Test>>
    public function shortOption(Assert $assert) : void
    {
        $handler = new BoolConsumeHandler('debug', [ '-d', '--debug' ]);
        $result = $handler->consume(new ArgumentsConsumer([ '-d' ]));

        list($name, $value) = $result;

        $assert->string($name)->is('debug');
        $assert->bool($value)->is(true);
    }
}
