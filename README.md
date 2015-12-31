# getopt

[![Latest Stable Version](https://poser.pugx.org/hhpack/getopt/v/stable)](https://packagist.org/packages/hhpack/getopt)
[![Build Status](https://travis-ci.org/hhpack/getopt.svg?branch=master)](https://travis-ci.org/hhpack/getopt)
[![Dependency Status](https://www.versioneye.com/user/projects/5684c257eb4f47003000042e/badge.svg?style=flat)](https://www.versioneye.com/user/projects/5684c257eb4f47003000042e)

## Basic usage

It generates the parser as follows, and then parse the option.

```hack
use hhpack\getopt as cli;
use hhpack\getopt\OptionParser;
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
```

## Specification of CLI Application

```hack
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

$spec->displayVersion(); // display application version
$spec->displayHelp(); // display application help message
```

## Option types

### bool_option

|name|type|description|
|:---|:---|:---|
|name|string|destination name of option|
|flags|Traversable<_string_>|flags of option, example: -d, --debug|
|defaultValue|bool|default value of option|
|helpHessage|string|help message of option|

### int_option

|name|type|description|
|:---|:---|:---|
|name|string|destination name of option|
|flags|Traversable<_string_>|flags of option, example: -d, --debug|
|defaultValue|int|default value of option|
|required|ValueType| required or optional option |
|helpHessage|string|help message of option|

### float_option

|name|type|description|
|:---|:---|:---|
|name|string|destination name of option|
|flags|Traversable<_string_>|flags of option, example: -d, --debug|
|defaultValue|float|default value of option|
|required|ValueType| required or optional option |
|helpHessage|string|help message of option|

### string_option

|name|type|description|
|:---|:---|:---|
|name|string|destination name of option|
|flags|Traversable<_string_>|flags of option, example: -d, --debug|
|defaultValue|string|default value of option|
|required|ValueType| required or optional option |
|helpHessage|string|help message of option|

## Run the test

	composer install
	composer test
