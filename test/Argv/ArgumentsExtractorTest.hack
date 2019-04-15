namespace HHPack\Getopt\Test\Argv;

use HHPack\Getopt\Argv\{ArgumentsExtractor};
use HHPack\Getopt\Spec\{OptionSet, NoArgumentOption, OneArgumentOption};
use HHPack\Getopt\Test\Mock\{OptionContainerMock};
use type Facebook\HackTest\HackTest;
use function Facebook\FBExpect\expect;

final class ArgumentsExtractorTest extends HackTest {
  public function testShortOption(): void {
    $options = new OptionContainerMock([], ['-n', '--name']);

    $extractor = new ArgumentsExtractor($options);
    $argv = $extractor->extract(['-nfoo']);

    expect($argv->at(0))->toBeSame('-n');
    expect($argv->at(1))->toBeSame('foo');
  }

  public function testShortEqOption(): void {
    $options = new OptionContainerMock([], ['-n', '--name']);

    $extractor = new ArgumentsExtractor($options);
    $argv = $extractor->extract(['-n=foo']);

    expect($argv->at(0))->toBeSame('-n');
    expect($argv->at(1))->toBeSame('foo');
  }

  public function testLongOption(): void {
    $options = new OptionContainerMock([], ['-n', '--name']);

    $extractor = new ArgumentsExtractor($options);
    $argv = $extractor->extract(['--name=foo']);

    expect($argv->at(0))->toBeSame('--name');
    expect($argv->at(1))->toBeSame('foo');
  }

  public function testFlagsOption(): void {
    $options =
      new OptionContainerMock(['-d', '--debug', '-V', '--verbose'], []);

    $extractor = new ArgumentsExtractor($options);
    $argv = $extractor->extract(['-dV']);

    expect($argv->at(0))->toBeSame('-d');
    expect($argv->at(1))->toBeSame('-V');
  }

  public function testFlagLongOption(): void {
    $options = new OptionContainerMock(['-N', '--no-name'], []);

    $extractor = new ArgumentsExtractor($options);
    $argv = $extractor->extract(['--no-name']);

    expect($argv->at(0))->toBeSame('--no-name');
  }

  public function testLongWithSepalateOption(): void {
    $options = new OptionContainerMock(['-N', '--long-name'], []);

    $extractor = new ArgumentsExtractor($options);
    $argv = $extractor->extract(['--long-name', 'foo']);

    expect($argv->at(0))->toBeSame('--long-name');
    expect($argv->at(1))->toBeSame('foo');
  }
}
