<?hh //partial

namespace hhpack\getopt\spec;

use hhpack\getopt\IntOption;
use hhpack\getopt\spec\mock\ArgumentsConsumer;

describe(IntOption::class, function () {
  describe('consume', function () {
    beforeEach(function () {
      $this->option = new IntOption('level', 'l', 'level', 5);
    });
    it('return consumed result', function () {
      $result = $this->option->consume(new ArgumentsConsumer([ '-l', '5' ]));
      list($name, $value) = $result;

      expect($name)->toBe('level');
      expect($value)->toBe(5);
    });
  });
});
