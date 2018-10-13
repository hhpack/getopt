<?hh //strict

namespace HHPack\Getopt\Test\Parser;

use HHPack\Getopt\Parser\OptionParser;
use HHPack\Getopt\Spec\{OneArgumentOption, NoArgumentOption, OptionSet};
use type Facebook\HackTest\HackTest;
use function Facebook\FBExpect\expect;

final class OptionParserTest extends HackTest {
  private string $name = '';
  private string $type = '';
  private bool $debug = false;

  public function testOneArgumentOption(): void {
    $options = new OptionSet(
      [
        new OneArgumentOption(
          ['-n', '--name'],
          'NAME',
          '',
          ($value) ==> {
            $this->name = (string) $value;
          },
        ),
      ],
    );

    $parser = new OptionParser($options);
    $remainArgs = $parser->parse(['-nfoo']);

    expect(\count($remainArgs))->toBeSame(0);
    expect($this->name)->toBeSame('foo');
  }

  public function testNoArgumentOption(): void {
    $options = new OptionSet(
      [
        new NoArgumentOption(
          ['-d', '--debug'],
          '',
          () ==> {
            $this->debug = true;
          },
        ),
      ],
    );

    $parser = new OptionParser($options);
    $remainArgs = $parser->parse(['-d']);

    expect(\count($remainArgs))->toBeSame(0);
    expect($this->debug)->toBeTrue();
  }

  public function testArgsSeparator(): void {
    $options = new OptionSet(
      [
        new OneArgumentOption(
          ['-n', '--name'],
          'NAME',
          '',
          ($value) ==> {
            $this->name = (string) $value;
          },
        ),
      ],
    );

    $parser = new OptionParser($options);
    $remainArgs = $parser->parse(['-nfoo', '--', 'value']);

    expect(\count($remainArgs))->toBeSame(1);
    expect($this->name)->toBeSame('foo');
  }

  public function testStopNotOption(): void {
    $options = new OptionSet(
      [
        new OneArgumentOption(
          ['-n', '--name'],
          'NAME',
          '',
          ($value) ==> {
            $this->name = (string) $value;
          },
        ),
        new OneArgumentOption(
          ['-t', '--type'],
          'TYPE',
          '',
          ($value) ==> {
            $this->name = (string) $value;
          },
        ),
      ],
    );

    $parser = new OptionParser($options, shape('stopAtNonOption' => true));
    $remainArgs = $parser->parse(['-nfoo', 'value', '-tpartial']);

    expect($this->name)->toBeSame('foo');
    expect(\count($remainArgs))->toBeSame(3);
    expect($remainArgs->at(0))->toBeSame('value');
    expect($remainArgs->at(1))->toBeSame('-t');
    expect($remainArgs->at(2))->toBeSame('partial');
  }

}
