namespace HHPack\Getopt\Example;

require_once __DIR__.'/../vendor/hh_autoload.hh';

use HHPack\Getopt as cli;
use HHPack\Getopt\App\{ArgumentParser};

final class CliApplication {

  private bool $help = false;
  private bool $version = false;
  private string $fileName = 'test';
  private ArgumentParser $argParser;

  public function __construct() {
    $this->argParser =
      cli\app('example', '1.0.0')
        ->description("This cli application is example.\n\n")
        ->usage("  {app.name} [OPTIONS]\n\n")
        ->options(
          [
            cli\take_on(
              ['-n', '--name'],
              'NAME',
              'file name',
              ($name) ==> {
                $this->fileName = $name;
              },
            ),
            cli\on(
              ['-h', '--help'],
              'display help message',
              () ==> {
                $this->help = true;
              },
            ),
            cli\on(
              ['-v', '--version'],
              'display version',
              () ==> {
                $this->version = true;
              },
            ),
          ],
        );
  }

  public function run(Traversable<string> $argv): void {
    $this->argParser->parse($argv);

    if ($this->help) {
      $this->argParser->displayHelp();
    } else if ($this->version) {
      $this->argParser->displayVersion();
    } else {
      echo "file name: ", $this->fileName, \PHP_EOL;
    }
  }
}

<<__EntryPoint>>
function main() : noreturn {
	(new CliApplication())->run( /* HH_IGNORE_ERROR[2050] */ $GLOBALS['argv'] );
	exit(0);
}
