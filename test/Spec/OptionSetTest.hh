<?hh //strict

namespace HHPack\Getopt\Test\Spec;

use HHPack\Getopt\Spec\{OptionSet, NoArgumentOption, OneArgumentOption};
use type Facebook\HackTest\HackTest;
use function Facebook\FBExpect\expect;

final class OptionSetTest extends HackTest {
  public function testShortAndLongContains(): void {
    $options = new OptionSet([new NoArgumentOption(['-d', '--debug'])]);

    $result = $options->contains('-d'); // short name
    expect($result)->toBeTrue();

    $result = $options->contains('--debug'); // long name
    expect($result)->toBeTrue();
  }

  public function testLookUpFromContainer(): void {
    $options = new OptionSet([new NoArgumentOption(['-d', '--debug'])]);

    $option = $options->get('-d'); // short name
    expect($option)->toBeInstanceOf(NoArgumentOption::class);

    $option = $options->get('--debug'); // long name
    expect($option)->toBeInstanceOf(NoArgumentOption::class);
  }

  public function testNoValueContains(): void {
    $options = new OptionSet([new NoArgumentOption(['-d', '--debug'])]);

    $result = $options->hasNoValue('-d'); // short name
    expect($result)->toBeTrue();

    $result = $options->hasNoValue('--debug'); // long name
    expect($result)->toBeTrue();

    $result = $options->hasNoValue('-n'); // short name
    expect($result)->toBeFalse();

    $result = $options->hasNoValue('--name'); // long name
    expect($result)->toBeFalse();
  }

  public function testOneValueContains(): void {
    $options = new OptionSet([new OneArgumentOption(['-n', '--name'])]);

    $result = $options->hasOneValue('-n'); // short name
    expect($result)->toBeTrue();

    $result = $options->hasOneValue('--name'); // long name
    expect($result)->toBeTrue();

    $result = $options->hasNoValue('-d'); // short name
    expect($result)->toBeFalse();

    $result = $options->hasNoValue('--debug'); // long name
    expect($result)->toBeFalse();
  }
}
