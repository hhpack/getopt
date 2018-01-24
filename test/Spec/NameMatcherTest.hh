<?hh //strict

namespace HHPack\Getopt\Test\Spec;

use HHPack\Getopt\Spec\NameMatcher;
use HackPack\HackUnit\Contract\Assert;

final class NameMatcherTest {
  <<Test>>
  public function matcher(Assert $assert): void {
    $matcher = new NameMatcher('-f');

    $result = $matcher->matches('-f');
    $assert->bool($result)->is(true);

    $result = $matcher->matches('--file');
    $assert->bool($result)->is(false);
  }
}
