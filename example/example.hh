<?hh //partial

namespace hhpack\getopt\example;

require_once __DIR__ . '/../vendor/autoload.php';

use hhpack\getopt as cli;
use hhpack\getopt\OptionParser;
use hhpack\getopt\OptionSet;
use hhpack\getopt\ValueType;

$parser = new OptionParser([
  cli\bool_option(shape(
    'name' => 'help',
    'flags' => [ '-h', '--help' ],
    'defaultValue' => false
  )),
  cli\bool_option(shape(
    'name' => 'version',
    'flags' => [ '-v', '--version' ],
    'defaultValue' => false
  )),
  cli\string_option(shape(
    'name' => 'name',
    'flags' => [ '-n', '--name' ],
    'defaultValue' => 'test',
    'required' => ValueType::Optional
  ))
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
