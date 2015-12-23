<?hh //partial

namespace hhpack\getopt\spec;

use hhpack\getopt\OptionSet;
use hhpack\getopt\FlagOption;
use hhpack\getopt\ValueOption;

describe(OptionSet::class, function () {
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
});
