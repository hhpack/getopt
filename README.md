# getopt

[![Latest Stable Version](https://poser.pugx.org/hhpack/getopt/v/stable)](https://packagist.org/packages/hhpack/getopt)
[![Build Status](https://travis-ci.org/hhpack/getopt.svg?branch=master)](https://travis-ci.org/hhpack/getopt)
[![Dependency Status](https://www.versioneye.com/user/projects/5684c257eb4f47003000042e/badge.svg?style=flat)](https://www.versioneye.com/user/projects/5684c257eb4f47003000042e)

## Basic usage

It generates the parser as follows, and then parse the option.

```hack
use HHPack\Getopt as cli;

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
```

## Specification of CLI Application

```hack
use HHPack\Getopt as cli;

$spec = cli\app('example', '1.0.0');
$spec->usage("  {app.name} [options]\n\n")
  ->options([
    cli\bool_option('help', '-h|--help', false, 'display help message'),
    cli\bool_option('version', '-v|--version', false, 'display version'),
    cli\string_option('name', '-n|--name=?', 'test', 'file name')
  ]);

$spec->displayVersion(); // display application version
$spec->displayHelp(); // display application help message
```

## Option types

### bool_option

|name|type|description|
|:---|:---|:---|
|name|string|destination name of option|
|spec|string|spec of option|
|defaultValue|bool|default value of option|
|helpHessage|string|help message of option|

### int_option

|name|type|description|
|:---|:---|:---|
|name|string|destination name of option|
|spec|string|spec of option|
|defaultValue|int|default value of option|
|helpHessage|string|help message of option|

### float_option

|name|type|description|
|:---|:---|:---|
|name|string|destination name of option|
|spec|string|spec of option|
|defaultValue|float|default value of option|
|helpHessage|string|help message of option|

### string_option

|name|type|description|
|:---|:---|:---|
|name|string|destination name of option|
|spec|string|spec of option|
|defaultValue|string|default value of option|
|helpHessage|string|help message of option|

## Run the test

	composer install
	composer test
