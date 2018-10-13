<?hh //strict

namespace HHPack\Getopt\Test\Spec;

use HHPack\Getopt\Spec\NameMatcher;
use type Facebook\HackTest\HackTest;
use function Facebook\FBExpect\expect;

final class NameMatcherTest extends HackTest {
  public function testMatcher(): void {
    $matcher = new NameMatcher('-f');

    $result = $matcher->matches('-f');
    expect($result)->toBeTrue();

    $result = $matcher->matches('--file');
    expect($result)->toBeFalse();
  }
}
