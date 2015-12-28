<?hh //partial

namespace hhpack\getopt\spec;

use hhpack\getopt\BoolConsumeHandler;
use hhpack\getopt\NamedMatcher;
use hhpack\getopt\spec\mock\ArgumentsConsumer;

describe(BoolConsumeHandler::class, function () {
  describe('consume', function () {
    beforeEach(function () {
      $this->handler = new BoolConsumeHandler('debug', [ '-d', '--debug' ]);
    });
    it('return consumed result', function () {
      $result = $this->handler->consume(new ArgumentsConsumer([ '-d' ]));
      list($name, $value) = $result;

      expect($name)->toBe('debug');
      expect($value)->toBe(true);
    });
  });
});
