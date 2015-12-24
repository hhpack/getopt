<?hh //partial

namespace hhpack\getopt\spec;

use hhpack\getopt\OptionSet;
use hhpack\getopt\FlagOption;
use hhpack\getopt\StringOption;
use hhpack\getopt\ArgumentType;

describe(OptionSet::class, function () {
  describe('hasOption', function () {
    context('when have option', function () {
      beforeEach(function () {
        $this->options = new OptionSet([
          new FlagOption('debug', 'd', 'debug')
        ]);
      });
      it('return true', function () {
        $result = $this->options->hasOption('d'); // short name
        expect($result)->toBeTrue();

        $result = $this->options->hasOption('debug'); // long name
        expect($result)->toBeTrue();

        $result = $this->options->hasOption('d', 'debug'); // short name and short name
        expect($result)->toBeTrue();
      });
    });
  });
  describe('get', function () {
    context('when have option', function () {
      beforeEach(function () {
        $this->options = new OptionSet([
          new FlagOption('debug', 'd', 'debug')
        ]);
      });
      it('return option', function () {
        $option = $this->options->get('d'); // short name
        expect($option->name())->toBe('debug');

        $option = $this->options->get('debug'); // long name
        expect($option->name())->toBe('debug');

        $option = $this->options->get('d', 'debug'); // short name and short name
        expect($option->name())->toBe('debug');
      });
    });
  });
  describe('hasFlagOption', function () {
    context('when have flag option', function () {
      beforeEach(function () {
        $this->options = new OptionSet([
          new FlagOption('debug', 'd', 'debug')
        ]);
      });
      it('return true', function () {
        $result = $this->options->hasFlagOption('d'); // short name
        expect($result)->toBeTrue();

        $result = $this->options->hasFlagOption('debug'); // long name
        expect($result)->toBeTrue();
      });
    });
    context('when have not flag option', function () {
      beforeEach(function () {
        $this->options = new OptionSet([]);
      });
      it('return false', function () {
        $result = $this->options->hasFlagOption('d'); // short name
        expect($result)->toBeFalse();

        $result = $this->options->hasFlagOption('debug'); // long name
        expect($result)->toBeFalse();
      });
    });
  });
  describe('hasValueOption', function () {
    context('when have value option', function () {
      beforeEach(function () {
        $this->options = new OptionSet([
          new StringOption('name', 'n', 'name', 'foo', ArgumentType::Optional)
        ]);
      });
      it('return true', function () {
        $result = $this->options->hasValueOption('n'); // short name
        expect($result)->toBeTrue();

        $result = $this->options->hasValueOption('name'); // long name
        expect($result)->toBeTrue();
      });
    });
    context('when have not value option', function () {
      beforeEach(function () {
        $this->options = new OptionSet([]);
      });
      it('return false', function () {
        $result = $this->options->hasFlagOption('n'); // short name
        expect($result)->toBeFalse();

        $result = $this->options->hasFlagOption('name'); // long name
        expect($result)->toBeFalse();
      });
    });
  });
});
