<?hh //partial

namespace hhpack\getopt\spec;

use hhpack\getopt\FloatOption;
use hhpack\getopt\spec\mock\ArgumentsConsumer;

describe(FloatOption::class, function () {
  describe('consume', function () {
    beforeEach(function () {
      $this->option = new FloatOption('rate', 'r', 'rate', 75.0);
    });
    it('return consumed result', function () {
      $result = $this->option->consume(new ArgumentsConsumer([ '-r', '60.0' ]));
      list($name, $value) = $result;

      expect($name)->toBe('rate');
      expect($value)->toBe(60.0);
    });
  });
});
