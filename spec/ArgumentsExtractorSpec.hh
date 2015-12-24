<?hh //partial

namespace hhpack\getopt\spec;

use hhpack\getopt\ArgumentsExtractor;
use hhpack\getopt\OptionSet;
use hhpack\getopt\FlagOption;
use hhpack\getopt\StringOption;
use hhpack\getopt\ArgumentType;

describe(ArgumentsExtractor::class, function () {
  describe('at', function () {
    context('when -nfoo', function () {
      beforeEach(function () {
        $this->args = [ '-nfoo' ];
        $this->options = new OptionSet([
          new StringOption('name', 'n', 'name', 'foo', ArgumentType::Optional)
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
          new StringOption('name', 'n', 'name', 'foo', ArgumentType::Optional)
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
          new StringOption('name', 'n', 'name', 'foo', ArgumentType::Optional)
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
          new FlagOption('debug', 'd', 'debug'),
          new FlagOption('verbose', 'V', 'verbose')
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
          new FlagOption('noName', 'N', 'no-name')
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
          new FlagOption('longName', 'N', 'long-name')
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
