<?hh //partial

namespace hhpack\getopt\spec;

use hhpack\getopt\StringConsumeHandler;
use hhpack\getopt\NamedMatcher;
use hhpack\getopt\spec\mock\ArgumentsConsumer;

describe(StringConsumeHandler::class, function () {
  describe('consume', function () {
    beforeEach(function () {
      $this->handler = new StringConsumeHandler('name', [ '-n', '--name' ]);
    });
    it('return consumed result', function () {
      $result = $this->handler->consume(new ArgumentsConsumer([ '-n', 'foo' ]));
      list($name, $value) = $result;

      expect($name)->toBe('name');
      expect($value)->toBe('foo');
    });
  });
});
