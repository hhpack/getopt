<?hh //partial

namespace HHPack\Getopt\Example;

require_once __DIR__ . '/../vendor/autoload.php';

use HHPack\Getopt as cli;

function optparser_main(Traversable<string> $argv) : void
{
    $help = false;
    $version = false;
    $fileName = 'test';

    $parser = cli\optparser([
        cli\on([ '-h', '--help' ], 'display help message', () ==> { $help = true; }),
        cli\on([ '-v', '--version' ], 'display version', () ==> { $version = true; }),
        cli\take_on([ '-n', '--name' ], 'file name', ($name) ==> { $fileName = (string) $name; })
    ]);

    $result = $parser->parse($argv);

    if ($help === true) {
        echo 'help on', PHP_EOL;
    }

    if ($version === true) {
        echo 'version on', PHP_EOL;
    }

    if ($fileName !== 'test') {
        echo 'name = ', $fileName, PHP_EOL;
    }
}
optparser_main($argv);
