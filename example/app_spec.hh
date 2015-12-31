<?hh //partial

namespace hhpack\getopt\example;

require_once __DIR__ . '/../vendor/autoload.php';

use hhpack\getopt as cli;
use hhpack\getopt\ValueType;
use hhpack\getopt\ApplicationSpec;

$spec = new ApplicationSpec('example', '1.0.0', [
  cli\bool_option(shape(
    'name' => 'help',
    'flags' => [ '-h', '--help' ],
    'defaultValue' => false,
    'helpMessage' => 'display help message'
  )),
  cli\bool_option(shape(
    'name' => 'version',
    'flags' => [ '-v', '--version' ],
    'defaultValue' => false,
    'helpMessage' => 'display version'
  )),
  cli\string_option(shape(
    'name' => 'name',
    'flags' => [ '-n', '--name' ],
    'defaultValue' => 'test',
    'required' => ValueType::Optional,
    'helpMessage' => 'file name'
  ))
]);

$spec->displayVersion();
$spec->displayHelp();
