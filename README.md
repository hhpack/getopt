# getopt

## Basic usage

```hack
use hhpack\getopt\ArgumentParser;
use hhpack\getopt\OptionSet;
use hhpack\getopt\ValueOption;
use hhpack\getopt\FlagOption;

$parser = new ArgumentParser(new OptionSet([
    new FlagOption('help', 'h', 'help'), // dest=help, shortname=h, longname=help
    new FlagOption('version', 'v', 'version'), // dest=version, shortname=v, longname=version
    new ValueOption('name', 'n', 'name', 'test') // dest=name, shortname=n, longname=name
]));

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
```

## Run the test

	composer install
	composer test
