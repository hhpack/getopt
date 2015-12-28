# getopt

[![Latest Stable Version](https://poser.pugx.org/hhpack/getopt/v/stable)](https://packagist.org/packages/hhpack/getopt)
[![Build Status](https://travis-ci.org/hhpack/getopt.svg?branch=master)](https://travis-ci.org/hhpack/getopt)

## Basic usage

It generates the parser as follows, and then parse the option.

```hack
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
    'required' => ArgumentType::Optional
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
```

### Option types

#### bool_option

|name|type|description|
|:---|:---|:---|
|name|string|destination name of option|
|flags|Traversable<string>|flags of option, example: -d, --debug|
|defaultValue|bool|default value of option|

#### int_option

|name|type|description|
|:---|:---|:---|
|name|string|destination name of option|
|flags|Traversable<string>|flags of option, example: -d, --debug|
|defaultValue|int|default value of option|
|required|ValueType| required or optional option |

#### float_option

|name|type|description|
|:---|:---|:---|
|name|string|destination name of option|
|flags|Traversable<string>|flags of option, example: -d, --debug|
|defaultValue|float|default value of option|
|required|ValueType| required or optional option |

#### string_option

|name|type|description|
|:---|:---|:---|
|name|string|destination name of option|
|flags|Traversable<string>|flags of option, example: -d, --debug|
|defaultValue|string|default value of option|
|required|ValueType| required or optional option |

## Run the test

	composer install
	composer test
