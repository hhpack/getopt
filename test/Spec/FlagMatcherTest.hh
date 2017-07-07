<?hh //strict

namespace HHPack\Getopt\Test\Spec;

use HHPack\Getopt\Spec\FlagMatcher;
use HackPack\HackUnit\Contract\Assert;

final class FlagMatcherTest
{
    <<Test>>
    public function matcher(Assert $assert) : void
    {
        $matcher = new FlagMatcher('-f');

        $result = $matcher->matches('-f');
        $assert->bool($result)->is(true);

        $result = $matcher->matches('--file');
        $assert->bool($result)->is(false);
    }
}
