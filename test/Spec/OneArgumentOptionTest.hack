namespace HHPack\Getopt\Test\Spec;

use HHPack\Getopt\Spec\OneArgumentOption;
use type Facebook\HackTest\HackTest;
use function Facebook\FBExpect\expect;

final class OneArgumentOptionTest extends HackTest {
  public function testHelpLabel(): void {
    $option = new OneArgumentOption(['-n', '--name'], 'NAME', '');
    expect($option->helpLabel())->toBeSame('-n NAME, --name=NAME');
  }
}
