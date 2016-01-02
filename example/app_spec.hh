<?hh //partial

namespace hhpack\getopt\example;

require_once __DIR__ . '/../vendor/autoload.php';

use hhpack\getopt as cli;

$spec = cli\app('example', '1.0.0');
$spec->usage("  {app.name} [options]\n\n")
  ->options([
    cli\bool_option('help', '-h|--help', false, 'display help message'),
    cli\bool_option('version', '-v|--version', false, 'display version'),
    cli\string_option('name', '-n|--name=?', 'test', 'file name')
  ]);

$spec->displayVersion();
$spec->displayHelp();
