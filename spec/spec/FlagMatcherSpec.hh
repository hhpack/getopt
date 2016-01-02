<?hh //partial

namespace hhpack\getopt\spec\spec;

use hhpack\getopt\spec\FlagMatcher;

describe(FlagMatcher::class, function () {
  describe('matches', function () {
    beforeEach(function () {
      $this->matcher = new FlagMatcher('-f');
    });
    context('when matches', function () {
      it('return true', function () {
        $result = $this->matcher->matches('-f');
        expect($result)->toBeTrue();
      });
    });
    context('when unmatches', function () {
      it('return false', function () {
        $result = $this->matcher->matches('--file');
        expect($result)->toBeFalse();
      });
    });
  });
});
