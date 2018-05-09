<?hh //strict

namespace HHPack\Getopt\Test\Parser;

use HHPack\Getopt\Parser\OptionParser;
use HHPack\Getopt\Spec\{OneArgumentOption, NoArgumentOption, OptionSet};
use HackPack\HackUnit\Contract\Assert;

final class OptionParserTest {
  private string $name = '';
  private string $type = '';
  private bool $debug = false;

  <<Test>>
  public function oneArgumentOption(Assert $assert): void {
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

    $assert->int(\count($remainArgs))->eq(0);
    $assert->string($this->name)->is('foo');
  }

  <<Test>>
  public function noArgumentOption(Assert $assert): void {
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

    $assert->int(\count($remainArgs))->eq(0);
    $assert->bool($this->debug)->is(true);
  }

  <<Test>>
  public function argsSeparator(Assert $assert): void {
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

    $assert->int(\count($remainArgs))->eq(1);
    $assert->string($this->name)->is('foo');
  }

  <<Test>>
  public function stopNotOption(Assert $assert): void {
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

    $assert->string($this->name)->is('foo');
    $assert->int(\count($remainArgs))->eq(3);
    $assert->string($remainArgs->at(0))->is('value');
    $assert->string($remainArgs->at(1))->is('-t');
    $assert->string($remainArgs->at(2))->is('partial');
  }

}
