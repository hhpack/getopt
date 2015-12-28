<?hh //partial

namespace hhpack\getopt\spec;

use hhpack\getopt\OptionSet;
use hhpack\getopt\ValueType;
use hhpack\getopt\NamedMatcher;
use hhpack\getopt\OptionValue;
use hhpack\getopt\StringConsumeHandler;
use hhpack\getopt\BoolConsumeHandler;

describe(OptionSet::class, function () {
  describe('hasOption', function () {
    context('when have option', function () {
      beforeEach(function () {
        $this->options = new OptionSet([
          new OptionValue(
            new BoolConsumeHandler('debug', [ '-d', '--debug' ]),
            false,
            ValueType::Optional
          )
        ]);
      });
      it('return true', function () {
        $result = $this->options->contains('-d'); // short name
        expect($result)->toBeTrue();

        $result = $this->options->contains('--debug'); // long name
        expect($result)->toBeTrue();
      });
    });
  });
  describe('get', function () {
    context('when have option', function () {
      beforeEach(function () {
        $this->options = new OptionSet([
          new OptionValue(
            new BoolConsumeHandler('debug', [ '-d', '--debug' ]),
            false,
            ValueType::Optional
          )
        ]);
      });
      it('return option', function () {
        $option = $this->options->get('-d'); // short name
        expect($option->name())->toBe('debug');

        $option = $this->options->get('--debug'); // long name
        expect($option->name())->toBe('debug');

        $option = $this->options->get('-d', '--debug'); // short name and short name
        expect($option->name())->toBe('debug');
      });
    });
  });
  describe('hasFlagOption', function () {
    context('when have flag option', function () {
      beforeEach(function () {
        $this->options = new OptionSet([
          new OptionValue(
            new BoolConsumeHandler('debug', [ '-d', '--debug' ]),
            false,
            ValueType::Optional
          )
        ]);
      });
      it('return true', function () {
        $result = $this->options->hasNoValue('-d'); // short name
        expect($result)->toBeTrue();

        $result = $this->options->hasNoValue('--debug'); // long name
        expect($result)->toBeTrue();
      });
    });
    context('when have not flag option', function () {
      beforeEach(function () {
        $this->options = new OptionSet([]);
      });
      it('return false', function () {
        $result = $this->options->hasNoValue('-d'); // short name
        expect($result)->toBeFalse();

        $result = $this->options->hasNoValue('--debug'); // long name
        expect($result)->toBeFalse();
      });
    });
  });
  describe('hasValueOption', function () {
    context('when have value option', function () {
      beforeEach(function () {
        $this->options = new OptionSet([
          new OptionValue(
            new StringConsumeHandler('name', [ '-n', '--name' ]),
            'bar',
            ValueType::Optional
          )
        ]);
      });
      it('return true', function () {
        $result = $this->options->hasOneValue('-n'); // short name
        expect($result)->toBeTrue();

        $result = $this->options->hasOneValue('--name'); // long name
        expect($result)->toBeTrue();
      });
    });
    context('when have not value option', function () {
      beforeEach(function () {
        $this->options = new OptionSet([]);
      });
      it('return false', function () {
        $result = $this->options->hasNoValue('-n'); // short name
        expect($result)->toBeFalse();

        $result = $this->options->hasNoValue('--name'); // long name
        expect($result)->toBeFalse();
      });
    });
  });
});
