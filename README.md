# getopt

[![Latest Stable Version](https://poser.pugx.org/hhpack/getopt/v/stable)](https://packagist.org/packages/hhpack/getopt)
[![Build Status](https://travis-ci.org/hhpack/getopt.svg?branch=master)](https://travis-ci.org/hhpack/getopt)
[![Dependency Status](https://www.versioneye.com/user/projects/5684c257eb4f47003000042e/badge.svg?style=flat)](https://www.versioneye.com/user/projects/5684c257eb4f47003000042e)

## Basic usage

The method of parsing command line arguments is as follows.  
Define an option that takes no arguments, use the **on** function.  
Define an option to take one argument, use the **take_on** function.

```hack
use HHPack\Getopt as cli;

$help = false;
$version = false;
$fileName = 'test';

$parser = cli\optparser([
    cli\take_on([ '-n', '--name' ], 'file name', ($name) ==> { $fileName = (string) $name; }),
    cli\on([ '-h', '--help' ], 'display help message', () ==> { $help = true; }),
    cli\on([ '-v', '--version' ], 'display version', () ==> { $version = true; })
]);

$args = $parser->parse($argv);

if ($help === true) {
    echo 'help on', PHP_EOL;
}

if ($version === true) {
    echo 'version on', PHP_EOL;
}

if ($fileName !== 'test') {
    echo 'name = ', $fileName, PHP_EOL;
}
```

## CLI Application

If you want to create cli application, we recommend using **ArgumentParser**.  
ArgumentParser implements an interface to display usage, program version.

```hack
use HHPack\Getopt as cli;
use HHPack\Getopt\App\{ ArgumentParser };

final class CliApplication
{

    private bool $help = false;
    private bool $version = false;
    private string $fileName = 'test';
    private ArgumentParser $argParser;

    public function __construct()
    {
        $this->argParser = cli\app('example', '1.0.0')
            ->description("This cli application is example.\n\n")
            ->usage("  {app.name} [OPTIONS]\n\n")
            ->options([
                cli\on(['-h', '--help'], 'display help message', () ==> {
                    $this->help = true;
                }),
                cli\on(['-v', '--version'], 'display version', () ==> {
                    $this->version = true;
                }),
                cli\take_on(['-n', '--name'], 'file name', ($name) ==> {
                    $this->fileName = $name;
                })
            ]);
    }

    public function run(Traversable<string> $argv): void
    {
        $this->argParser->parse($argv);

        if ($this->help) {
            $this->argParser->displayHelp();
        } else if ($this->version) {
            $this->argParser->displayVersion();
        } else {
            echo "file name: ", $this->fileName, PHP_EOL;
        }
    }
}

(new CliApplication())->run($argv);
```

## Run the test

	composer install
	composer test
