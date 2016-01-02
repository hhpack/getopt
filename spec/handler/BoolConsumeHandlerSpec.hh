<?hh //partial

namespace hhpack\getopt\spec\handler;

use hhpack\getopt\handler\BoolConsumeHandler;
use hhpack\getopt\spec\NamedMatcher;
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
