<?hh //partial

namespace HHPack\Getopt\Example;

require_once __DIR__ . '/../vendor/autoload.php';

use HHPack\Getopt as cli;

function appspec_main() : void
{
    $help = false;
    $version = false;
    $fileName = 'test';

    $spec = cli\app('example', '1.0.0');
    $spec->usage("  {app.name} [options]\n\n")
      ->options([
          cli\on(['-h', '--help'], 'display help message', () ==> { $help = true; }),
          cli\on(['-v', '--version'], 'display version', () ==> { $version = true; }),
          cli\take_on(['-n', '--name'], 'file name', ($name) ==> { $fileName = (string) $name; })
      ]);

    $spec->displayVersion();
    $spec->displayHelp();
}
appspec_main();
