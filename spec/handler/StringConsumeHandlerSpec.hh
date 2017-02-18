<?hh //partial

namespace HHPack\Getopt\Spec\Handler;

use HHPack\Getopt\Handler\StringConsumeHandler;
use HHPack\Getopt\Spec\NamedMatcher;
use HHPack\Getopt\Spec\Mock\ArgumentsConsumer;

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
