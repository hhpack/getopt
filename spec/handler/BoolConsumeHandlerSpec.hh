<?hh //partial

namespace HHPack\Getopt\Spec\Handler;

use HHPack\Getopt\Handler\BoolConsumeHandler;
use HHPack\Getopt\Spec\NamedMatcher;
use HHPack\Getopt\Spec\Mock\ArgumentsConsumer;

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
