<?hh //partial

namespace hhpack\getopt\spec\argv;

use hhpack\getopt\spec\OptionSet;
use hhpack\getopt\spec\OptionValue;
use hhpack\getopt\spec\ValueType;
use hhpack\getopt\spec\NamedMatcher;
use hhpack\getopt\argv\ArgumentsExtractor;
use hhpack\getopt\handler\StringConsumeHandler;
use hhpack\getopt\handler\BoolConsumeHandler;

describe(ArgumentsExtractor::class, function () {
  describe('at', function () {
    context('when -nfoo', function () {
      beforeEach(function () {
        $this->args = [ '-nfoo' ];
        $this->options = new OptionSet([
          new OptionValue(
            new StringConsumeHandler('name', [ '-n', '--name' ]),
            'bar',
            ValueType::Optional
          )
        ]);
        $this->extractor = new ArgumentsExtractor($this->options);
      });
      it('return extract arguments', function () {
        $argv = $this->extractor->extract($this->args);
        expect($argv->at(0))->toBe('-n');
        expect($argv->at(1))->toBe('foo');
      });
    });
    context('when -n=foo', function () {
      beforeEach(function () {
        $this->args = [ '-n=foo' ];
        $this->options = new OptionSet([
          new OptionValue(
            new StringConsumeHandler('name', [ '-n', '--name' ]),
            'foo',
            ValueType::Optional
          )
        ]);
        $this->extractor = new ArgumentsExtractor($this->options);
      });
      it('return extract arguments', function () {
        $argv = $this->extractor->extract($this->args);
        expect($argv->at(0))->toBe('-n');
        expect($argv->at(1))->toBe('foo');
      });
    });
    context('when --name=foo', function () {
      beforeEach(function () {
        $this->args = [ '--name=foo' ];
        $this->options = new OptionSet([
          new OptionValue(
            new StringConsumeHandler('name', [ '-n', '--name' ]),
            'foo',
            ValueType::Optional
          )
        ]);
        $this->extractor = new ArgumentsExtractor($this->options);
      });
      it('return extract arguments', function () {
        $argv = $this->extractor->extract($this->args);
        expect($argv->at(0))->toBe('--name');
        expect($argv->at(1))->toBe('foo');
      });
    });
    context('when -dv', function () {
      beforeEach(function () {
        $this->args = [ '-dV' ];
        $this->options = new OptionSet([
          new OptionValue(
            new BoolConsumeHandler('debug', [ '-d', '--debug' ]),
            false,
            ValueType::Optional
          ),
          new OptionValue(
            new BoolConsumeHandler('verbose', [ '-V', '--verbose' ]),
            false,
            ValueType::Optional
          )
        ]);
        $this->extractor = new ArgumentsExtractor($this->options);
      });
      it('return extract arguments', function () {
        $argv = $this->extractor->extract($this->args);
        expect($argv->at(0))->toBe('-d');
        expect($argv->at(1))->toBe('-V');
      });
    });
    context('when --no-name', function () {
      beforeEach(function () {
        $this->args = [ '--no-name' ];
        $this->options = new OptionSet([
          new OptionValue(
            new BoolConsumeHandler('noName', [ '-N', '--no-name' ]),
            false,
            ValueType::Optional
          )
        ]);
        $this->extractor = new ArgumentsExtractor($this->options);
      });
      it('return extract arguments', function () {
        $argv = $this->extractor->extract($this->args);
        expect($argv->at(0))->toBe('--no-name');
      });
    });
    context('when --long-name foo', function () {
      beforeEach(function () {
        $this->args = [ '--long-name', 'foo' ];
        $this->options = new OptionSet([
          new OptionValue(
            new BoolConsumeHandler('longName', [ '-N', '--long-name' ]),
            false,
            ValueType::Optional
          )
        ]);
        $this->extractor = new ArgumentsExtractor($this->options);
      });
      it('return extract arguments', function () {
        $argv = $this->extractor->extract($this->args);
        expect($argv->at(0))->toBe('--long-name');
        expect($argv->at(1))->toBe('foo');
      });
    });
  });
});
