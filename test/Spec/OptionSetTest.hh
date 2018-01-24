<?hh //strict

namespace HHPack\Getopt\Test\Spec;

use HHPack\Getopt\Spec\{OptionSet, NoArgumentOption, OneArgumentOption};
use HackPack\HackUnit\Contract\Assert;

final class OptionSetTest {
  <<Test>>
  public function shortAndLongContains(Assert $assert): void {
    $options = new OptionSet([new NoArgumentOption(['-d', '--debug'])]);

    $result = $options->contains('-d'); // short name
    $assert->bool($result)->is(true);

    $result = $options->contains('--debug'); // long name
    $assert->bool($result)->is(true);
  }

  <<Test>>
  public function lookUpFromContainer(Assert $assert): void {
    $options = new OptionSet([new NoArgumentOption(['-d', '--debug'])]);

    $option = $options->get('-d'); // short name
    $assert->mixed($option)->isTypeOf(NoArgumentOption::class);

    $option = $options->get('--debug'); // long name
    $assert->mixed($option)->isTypeOf(NoArgumentOption::class);
  }

  <<Test>>
  public function noValueContains(Assert $assert): void {
    $options = new OptionSet([new NoArgumentOption(['-d', '--debug'])]);

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
  public function oneValueContains(Assert $assert): void {
    $options = new OptionSet([new OneArgumentOption(['-n', '--name'])]);

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
