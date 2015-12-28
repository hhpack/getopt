<?hh //partial

namespace hhpack\getopt\spec;

use hhpack\getopt\ArgumentsExtractor;
use hhpack\getopt\OptionSet;
use hhpack\getopt\OptionValue;
use hhpack\getopt\StringConsumeHandler;
use hhpack\getopt\BoolConsumeHandler;
use hhpack\getopt\ValueType;
use hhpack\getopt\NamedMatcher;

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
        $this->extractor = new ArgumentsExtractor($this->options, $this->args);
      });
      it('return extract arguments', function () {
        expect($this->extractor->at(0))->toBe('-n');
        expect($this->extractor->at(1))->toBe('foo');
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
        $this->extractor = new ArgumentsExtractor($this->options, $this->args);
      });
      it('return extract arguments', function () {
        expect($this->extractor->at(0))->toBe('-n');
        expect($this->extractor->at(1))->toBe('foo');
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
        $this->extractor = new ArgumentsExtractor($this->options, $this->args);
      });
      it('return extract arguments', function () {
        expect($this->extractor->at(0))->toBe('--name');
        expect($this->extractor->at(1))->toBe('foo');
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
        $this->extractor = new ArgumentsExtractor($this->options, $this->args);
      });
      it('return extract arguments', function () {
        expect($this->extractor->at(0))->toBe('-d');
        expect($this->extractor->at(1))->toBe('-V');
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
        $this->extractor = new ArgumentsExtractor($this->options, $this->args);
      });
      it('return extract arguments', function () {
        expect($this->extractor->at(0))->toBe('--no-name');
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
        $this->extractor = new ArgumentsExtractor($this->options, $this->args);
      });
      it('return extract arguments', function () {
        expect($this->extractor->at(0))->toBe('--long-name');
        expect($this->extractor->at(1))->toBe('foo');
      });
    });
  });
});
