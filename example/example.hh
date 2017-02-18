<?hh //partial

namespace HHPack\Getopt\Example;

require_once __DIR__ . '/../vendor/autoload.php';

use HHPack\Getopt as cli;

function optparser_main(Traversable<string> $argv) : void
{
    $parser = cli\optparser([
        cli\bool_option('help', '-h|--help', false, 'display help message'),
        cli\bool_option('version', '-v|--version', false, 'display version'),
        cli\string_option('name', '-n|--name=?', 'test', 'file name')
    ]);

    $result = $parser->parse($argv);

    if ((bool) $result->getOption('help')) {
        echo 'help on', PHP_EOL;
    }

    if ((bool) $result->getOption('version')) {
        echo 'version on', PHP_EOL;
    }

    if ($result->hasOption('name')) {
        echo 'name = ', $result->getOption('name'), PHP_EOL;
    }
}
optparser_main($argv);
