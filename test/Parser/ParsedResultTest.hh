<?hh //strict

namespace HHPack\Getopt\Test\Parser;

use HHPack\Getopt\Parser\ParsedResult;
use HackPack\HackUnit\Contract\Assert;

final class ParsedResultTest
{
    <<Test>>
    public function result(Assert $assert) : void
    {
        $result = new ParsedResult(
            [ 'foo' ],
            [ Pair { 'name', 'string' } ]
        );
        $argCount = $result->map(($result) ==> $result->argumentCount());

        $assert->int($argCount)->eq(1);
    }
}
