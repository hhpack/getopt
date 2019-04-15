namespace HHPack\Getopt\Example;

require_once __DIR__.'/../vendor/hh_autoload.hh';

use HHPack\Getopt as cli;

final class Options {
  public bool $help = false;
  public bool $version = false;
  public string $fileName = 'test';
}

<<__EntryPoint>>
function optparser_main(): noreturn {
  $argv = /* HH_IGNORE_ERROR[2050] */ $GLOBALS['argv'];

  $options = new Options();

  $parser = cli\optparser(
    [
      cli\take_on(
        ['-n', '--name'],
        'NAME',
        'file name',
        ($name) ==> {
          $options->fileName = $name;
        },
      ),
      cli\on(
        ['-h', '--help'],
        'display help message',
        () ==> {
          $options->help = true;
        },
      ),
      cli\on(
        ['-v', '--version'],
        'display version',
        () ==> {
          $options->version = true;
        },
      ),
    ],
  );

  $args = $parser->parse($argv);

  if ($options->help === true) {
    echo 'help on', \PHP_EOL;
  }

  if ($options->version === true) {
    echo 'version on', \PHP_EOL;
  }

  if ($options->fileName !== 'test') {
    echo 'name = ', $options->fileName, \PHP_EOL;
  }

	exit(0);
}
