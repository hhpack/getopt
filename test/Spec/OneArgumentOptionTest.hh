<?hh //strict

namespace HHPack\Getopt\Test\Spec;

use HHPack\Getopt\Spec\OneArgumentOption;
use HackPack\HackUnit\Contract\Assert;

final class OneArgumentOptionTest {
  <<Test>>
  public function helpLabel(Assert $assert): void {
    $option = new OneArgumentOption(['-n', '--name'], 'NAME', '');
    $assert->string($option->helpLabel())->is('-n NAME, --name=NAME');
  }
}
