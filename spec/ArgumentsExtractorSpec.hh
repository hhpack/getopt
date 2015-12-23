<?hh //partial

namespace hhpack\getopt\spec;

use hhpack\getopt\ArgumentsExtractor;
use hhpack\getopt\ArgumentOptions;
use hhpack\getopt\FlagOption;
use hhpack\getopt\ValueOption;

describe(ArgumentsExtractor::class, function () {
  describe('items', function () {
    context('when -nfoo', function () {
      beforeEach(function () {
        $this->args = [ '-nfoo' ];
        $this->options = new ArgumentOptions([
          new ValueOption('name', 'n', 'name', 'foo', false)
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
        $this->options = new ArgumentOptions([
          new ValueOption('name', 'n', 'name', 'foo', false)
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
        $this->options = new ArgumentOptions([
          new ValueOption('name', 'n', 'name', 'foo', false)
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
        $this->options = new ArgumentOptions([
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
  });
});
